#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_actions/actions.h"
#include "../battle_events/battle_events.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../battle_text/stat_window.h"
#include "../../pokemon/pokemon.h"
#include "../../global.h"

extern const u8 AnimSummaryLoad;
extern const u8 AnimLearnMove;
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);
extern u32 PokemonExpNeededToLevel(u8 slot);
extern void VblankMergeStatsBox(void);
extern u8 PokemonLearnsMoveLevel(u16 species, u8 level, u16* moveBuffer);

u32 calc_exp(u8 fainted, u8 reciever, u8 defeaterLevel)
{
    // check if reciever participated in battle
    u32 recieverId = pokemon_getattr(&party_player[reciever], REQUEST_PID, NULL);
    bool participated = false;
    for (u8 i = 0; i < 6; i++) {
        if (gBattleMaster->participatingIDs[i] == recieverId) {
            participated = true;
            dprintf("slot %d participated in battle\n", i);
            break;
        }
    }

    // trainer gives 50% move exp
    u8 trainer_mon = (battle_type_flag != BATTLE_MODE_WILD) ? 150 : 100; // a

    // traded pokemon give 50% more exp
    u32 traded = pokemon_getattr(&party_player[reciever], REQUEST_TID, NULL) & 0xFFFF;
    u32 temp = gSaveBlock2Ptr->playerTrainerId[1] << 8 | gSaveBlock2Ptr->playerTrainerId[0];
    //dprintf("reciever traded ids were %x and %x\n", traded, temp);
    traded = (traded == temp) ? 100 : 150; // t
    //dprintf("result: %d\n", traded);
    // species base exp yield
    u16 species = pokemon_getattr(gPkmnBank[fainted]->this_pkmn, REQUEST_SPECIES, NULL);
    u16 base_yield =  gBaseStats[species].expYield; // b
    // E = 50% more exp if the winning Pokémon is holding a lucky egg -- omitted

    u8 fainted_lvl = gPkmnBank[fainted]->battleData.level; // L

    u32 exp_part1 = fainted_lvl * base_yield;
    exp_part1 = PERCENT(exp_part1, trainer_mon);
    if (participated)
        exp_part1 = exp_part1 / 5;
    else
        exp_part1 = MAX((exp_part1 / 50), 1);

    u32 exp_part2 = ((2 *fainted_lvl) + 10);
    exp_part2 *= (exp_part2 * PERCENT(exp_part2, 50));
    u32 exp_part3 = (fainted_lvl + defeaterLevel + 10);
    exp_part3 *= (exp_part3 * PERCENT(exp_part3, 50));
    exp_part2 /= exp_part3;
    exp_part2 = MAX(exp_part2, 1);
    exp_part1 = (exp_part1 * exp_part2) + 1;
    return PERCENT(exp_part1, traded);
}


void give_exp(u8 fainted, u8 defeater)
{
    u32 experience;
    u8 pkmnLevel = pokemon_getattr(gPkmnBank[defeater]->this_pkmn, REQUEST_LEVEL, NULL); // Lp
    for (u8 i = 0; i < 6; i++) {
        u16 species = pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL);
        bool is_egg = pokemon_getattr(&party_player[i], REQUEST_IS_EGG, NULL);
        u16 currentHP = pokemon_getattr(&party_player[i], REQUEST_CURRENT_HP, NULL);
        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!is_egg) && (currentHP > 0)) {
             // calc exp to grant for level
            experience = calc_exp(fainted, i, pkmnLevel);
            QueueMessage(i, defeater, STRING_EXP_GAIN, experience);
            u32 currentExp = pokemon_getattr(&party_player[i], REQUEST_EXP_POINTS, NULL);
            u8 levelOld = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);
            u8 newLevel = levelOld;

            // while the exp needed for slot to level < exp, grant exp needed to level
            u32 neededExp = PokemonExpNeededToLevel(i);
            while (neededExp < experience) {
                // log old stats
                struct StatWindow* stats = (struct StatWindow*)malloc_and_clear(sizeof(struct StatWindow));
                stats->slot = i;
                stats->level = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);
                stats->totalHP = pokemon_getattr(&party_player[i], REQUEST_TOTAL_HP, NULL);
                stats->attack = pokemon_getattr(&party_player[i], REQUEST_ATK, NULL);
                stats->defense = pokemon_getattr(&party_player[i], REQUEST_DEF, NULL);
                stats->speed = pokemon_getattr(&party_player[i], REQUEST_SPD, NULL);
                stats->spattack = pokemon_getattr(&party_player[i], REQUEST_SPATK, NULL);
                stats->spdefense = pokemon_getattr(&party_player[i], REQUEST_SPDEF, NULL);
                // grant needed exp and recalc stats
                experience -=neededExp;
                neededExp += currentExp;
                pokemon_setattr(&party_player[i], REQUEST_EXP_POINTS, &neededExp);
                recalculate_stats(&party_player[i]);
                currentExp = pokemon_getattr(&party_player[i], REQUEST_EXP_POINTS, NULL);
                newLevel += 1;
                stats->levelNew = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);
                stats->totalHPNew = pokemon_getattr(&party_player[i], REQUEST_TOTAL_HP, NULL);
                stats->attackNew = pokemon_getattr(&party_player[i], REQUEST_ATK, NULL);
                stats->defenseNew = pokemon_getattr(&party_player[i], REQUEST_DEF, NULL);
                stats->speedNew = pokemon_getattr(&party_player[i], REQUEST_SPD, NULL);
                stats->spattackNew = pokemon_getattr(&party_player[i], REQUEST_SPATK, NULL);
                stats->spdefenseNew = pokemon_getattr(&party_player[i], REQUEST_SPDEF, NULL);
                QueueMessage(i, defeater, STRING_LEVEL_UP, newLevel);
                // show updated stats
                struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
                a->action_bank = defeater;
                a->script = (u32)&AnimSummaryLoad;
                a->priv32 = (u32)stats;
                dprintf("storage was at %x\n", a->priv32);

                // check if pokemon learns a move at this level
                u16 moveBuffer[4] = {0, 0, 0, 0};
                u8 learnableMoves = PokemonLearnsMoveLevel(species, newLevel, &moveBuffer[0]);
                u8 buffIndex = 0;
                while (learnableMoves > buffIndex) {
                    u8 moveCount = PokemonCountUsableMoves(&party_player[i]);
                    if ((moveCount < 4) && (learnableMoves > 0)) {
                        // teach move to pokemon in an open slot
                        pokemon_setattr(&party_player[i], REQUEST_MOVE1 + moveCount, &moveBuffer[buffIndex]);
                        u8 pp = gBattleMoves[moveBuffer[buffIndex]].pp;
                        pokemon_setattr(&party_player[i], REQUEST_PP1 + moveCount, &pp);
                        QueueMessage(i, defeater, STRING_LEARN_MOVE, moveBuffer[buffIndex]);
                    }
                    // TODO needs to forget a move
                    // // action to learn move
                    // a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
                    // a->action_bank = defeater;
                    // a->script = (u32)&TaskLearnMove;
                    // a->priv[0] = moveBuffer[buffIndex];
                     buffIndex++;
                }
                // TODO check if pokemon evolves
                neededExp = PokemonExpNeededToLevel(i);
            }
            // grant remaining exp
            experience += currentExp;
            pokemon_setattr(&party_player[i], REQUEST_EXP_POINTS, &experience);
            recalculate_stats(&party_player[i]);

        }
    }
    return;
}

#define state CURRENT_ACTION->priv[0]
#define TEXTBOX_COUNT 1
#include "../battle_text/battle_textbox_gfx.h"
extern void ShowStatBoostText(struct StatWindow* stats);
extern void ShowStatBoostTextComplete(struct StatWindow* stats);
extern void VblankMergeStatTextBox(void);
extern void VblankMergeTextBox(void);

void TaskStatScreen(u8 taskId)
{
    struct StatWindow* stats = (struct StatWindow*)CURRENT_ACTION->priv32;
    switch(state) {
        case 0:
            {
            // copy textbox image
            void* char_base = (void *)0x600C000;
            void* map_base = (void *)0x600F800;
            lz77UnCompVram((void *)bboxTiles, char_base);
            CpuFastSet((void*)battle_textbox_statMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
            u8 **bg0_map = (u8**)0x030008EC;
            u8 *dst = (u8 *)(*bg0_map);
            CpuFastSet((void*)battle_textbox_statMap, (void*)dst, CPUModeFS(0x800, CPUFSCPY));
            // write palettes
            SetVBlankCallback(VblankMergeStatTextBox);
            state++;
            break;
            }
        case 1:
            ShowStatBoostText(stats);
            state++;
            break;
        case 2:
            if (gMain.newKeys & (KEY_A | KEY_B)) {
                PlaySE(SOUND_GENERIC_CLINK);
                ShowStatBoostTextComplete(stats);
                state++;
            }
            break;
        case 3:
            if (gMain.newKeys & (KEY_A | KEY_B)) {
                PlaySE(SOUND_GENERIC_CLINK);
                // get rid of the status bar
                void* char_base = (void *)0x600C000;
                void* map_base = (void *)0x600F800;
                lz77UnCompVram((void *)bboxTiles, char_base);
                CpuFastSet((void*)battle_textboxMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
                u8 **bg0_map = (u8**)0x030008EC;
                u8 *dst = (u8 *)(*bg0_map);
                CpuFastSet((void*)battle_textboxMap, (void*)dst, CPUModeFS(0x800, CPUFSCPY));
                SetVBlankCallback(VblankMergeTextBox);
                obj_free(&gSprites[stats->iconId]);
                free(stats);
                DestroyTask(taskId);
                state++;
            }
            break;
        case 4:
            break;
    };
}
#undef state

void TaskLearnMove(u8 taskId)
{
    // TODO
    DestroyTask(taskId);
}
