#include <pokeagb/pokeagb.h>
#include "HUD/dexnav_hud.h"
#include "../../pokemon/pokemon.h"
#include "../../battle/moves/moves.h"


u8 get_encounter_level(u16 species, u8 environment) {
    u8 index = get_wild_data_index_for_map();
    u8 min = 100;
    u8 max = 0;
    switch (environment) {
        // grass
        case 0:
        {
            u8 i;
            for (i = 0; i < 12; i++) {
                struct wild_pokemon w_pkmn = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[i];
                if (w_pkmn.species == species) {
                    min = (min < w_pkmn.min_level) ? min : w_pkmn.min_level;
                    max = (max > w_pkmn.max_level) ? max : w_pkmn.max_level;

                }
            }
            break;
        }
        // surf
        case 1:
        {
            u8 i;
            for (i = 0; i < 5; i++) {
                struct wild_pokemon w_pkmn = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[i];
                if (w_pkmn.species == species) {
                    min = (min < w_pkmn.min_level) ? min : w_pkmn.min_level;
                    max = (max > w_pkmn.max_level) ? max : w_pkmn.max_level;
                }
            }
            break;
        }
        default:
        {
            return 22; // Hidden pokemon should only appear on walkable tiles or surf tiles
            break;
        }
    };
    if (max == 0) {
        // free dexnav display message
        return 0xFF;
    }

    // mod div by 0 edge case.
    if (min == max) {
        return min;
    }
    return (min + (rand() % (max - min)));
}

void dexnav_generate_move(u16 species, u8 search_level, u8 encounter_level, u16* move_loc) {
    bool gen_move = false;
    u16 rand_val = rand() % 100;

    // evaluate if Pokemon should get a custom first move
    if (search_level < 5) {
        if (rand_val <= SEARCHLEVEL0_MOVECHANCE) {
                gen_move = true;
        }
    } else if (search_level < 10) {
        if (rand_val <= SEARCHLEVEL5_MOVECHANCE) {
                gen_move = true;
        }
    } else if (search_level < 25) {
        if (rand_val <= SEARCHLEVEL10_MOVECHANCE) {
                gen_move = true;
        }
    } else if (search_level < 50) {
        if (rand_val <= SEARCHLEVEL25_MOVECHANCE) {
                gen_move = true;
        }
    } else if (search_level < 100) {
        if (rand_val <= SEARCHLEVEL50_MOVECHANCE) {
                gen_move = true;
        }
    } else {
        if (rand_val <= SEARCHLEVEL100_MOVECHANCE) {
                gen_move = true;
        }
    }
    // gen_move = true;
    // get the species's egg move, if one exists
    enum Move move[4] = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE};
    if (gen_move) {
        u8 moveCount = CountEggMoves(species);
        u16* eggMoves = GetEggMoves(species);
        move[0] =  eggMoves[rand_range(0, moveCount)];
    } else {
        // case the species has no egg generatedMoves
        gen_move = false;
    }

    // calculate the normal generatedMoves
    enum Move this_move = MOVE_NONE;

    u8 i = 0;
    u8 c_move_index = gen_move;
    while (this_move < MOVE_MAX) {
       struct LearnMove learnableMove = (struct LearnMove)gLevelUpLearnsets[species][i];
       this_move = learnableMove.move;

       // learnset is level ordered, so exit early
       if (learnableMove.level > encounter_level) {
            break;
       } else {
            // if an eggmove is in the first slot, skip it and move to the next slot
            if ((gen_move) && (!(i % 4))) {
                move[1] = this_move;
            } else {
                move[c_move_index] = this_move;
            }
       }
       i += 1;
       c_move_index += 1;

    }

    // assign generatedMoves to array
    for (i = 0; i < 4; i++) {
        move_loc[i] = move[i];
    }
    return;
}

enum PokemonAbility dexnav_generate_hiddenability(u16 species, u8 search_level) {
    bool gen_ability = false;
    u16 rand_val = rand() % 100;
    if (search_level < 5) {
        if (rand_val <= SEARCHLEVEL0_ABILITYCHANCE) {
                gen_ability = true;
        }
    } else if (search_level < 10) {
        if (rand_val <= SEARCHLEVEL5_ABILITYCHANCE) {
                gen_ability = true;
        }
    } else if (search_level < 25) {
        if (rand_val <= SEARCHLEVEL10_ABILITYCHANCE) {
                gen_ability = true;
        }
    } else if (search_level < 50) {
        if (rand_val <= SEARCHLEVEL25_ABILITYCHANCE) {
                gen_ability = true;
        }
    } else if (search_level < 100) {
        if (rand_val <= SEARCHLEVEL50_ABILITYCHANCE) {
                gen_ability = true;
        }
    } else {
        if (rand_val <= SEARCHLEVEL100_ABILITYCHANCE) {
                gen_ability = true;
        }
    }

    if ((gen_ability) && (gBaseStats[species].hidden_ability != ABILITY_NONE)) {
        return gBaseStats[species].hidden_ability; // should be ability when reworked
    } else {
        // pick a normal ability of that Pokemon
        if (gBaseStats[species].ability2) {
            return rand_val % 2 ? gBaseStats[species].ability1 : gBaseStats[species].ability2;
        } else {
            return gBaseStats[species].ability1;
        }
    }
}

u8 dexnav_generate_potential(u8 search_level) {
    u8 gen_chance = 0;
    u16 rand_val = rand() % 100;
    if (search_level < 5) {
        gen_chance = SEARCHLEVEL0_ONESTAR + SEARCHLEVEL0_TWOSTAR + SEARCHLEVEL0_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL0_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL0_ONESTAR + SEARCHLEVEL0_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    } else if (search_level < 10) {
        gen_chance = SEARCHLEVEL5_ONESTAR + SEARCHLEVEL5_TWOSTAR + SEARCHLEVEL5_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL5_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL5_ONESTAR + SEARCHLEVEL5_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    } else if (search_level < 25) {
        gen_chance = SEARCHLEVEL10_ONESTAR + SEARCHLEVEL10_TWOSTAR + SEARCHLEVEL10_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL10_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL10_ONESTAR + SEARCHLEVEL10_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    } else if (search_level < 50) {
        gen_chance = SEARCHLEVEL25_ONESTAR + SEARCHLEVEL25_TWOSTAR + SEARCHLEVEL25_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL25_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL25_ONESTAR + SEARCHLEVEL25_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    } else if (search_level < 100) {
        gen_chance = SEARCHLEVEL50_ONESTAR + SEARCHLEVEL50_TWOSTAR + SEARCHLEVEL50_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL50_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL50_ONESTAR + SEARCHLEVEL50_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    } else {
        gen_chance = SEARCHLEVEL100_ONESTAR + SEARCHLEVEL100_TWOSTAR + SEARCHLEVEL100_THREESTAR;
        if (rand_val <= gen_chance) {
            // figure out which star it is
            if (rand_val <= SEARCHLEVEL100_ONESTAR) {
                return 1;
            } else if (rand_val <= (SEARCHLEVEL100_ONESTAR + SEARCHLEVEL100_TWOSTAR)) {
                return 2;
            } else {
                return 3;
            }
        }
    }
    // No potential
    return 0;
}

enum Item dexnav_generate_helditem(u16 species, u8 search_level) {
    u16 rand_val = rand() % 100;
    u8 search_level_influence = search_level >> 1;
    enum Item item1 = gBaseStats[species].item1;
    enum Item item2 = gBaseStats[species].item2;

    // if both are the same, 100% to hold
    if (item1 == item2) {
        return item1;
    }

    // if no items can be held, then yeah..no items
    if ((item2 == ITEM_NONE) && (item1 == ITEM_NONE)) {
        return ITEM_NONE;
    }

    // if only one entry, 50% chance
    if ((item2 == ITEM_NONE) && (item1 != ITEM_NONE)) {
        return (rand_val <= 50) ? item1 : ITEM_NONE;
    }

    // if both are distinct item1 = 50% + srclvl/2; item2 = 5% + srchlvl/2
    if (rand_val < ((50 + search_level_influence) + (5 + search_level))) {
        return (rand_val > (5 + search_level_influence)) ? item1 : item2;
    } else {
        return ITEM_NONE;
    }
    return ITEM_NONE;
}

u8 dexnav_generate_pokemonlvl(u16 species, u8 search_level, u8 environment) {
    u8 level_base = get_encounter_level(species, environment);
    if (level_base > 100) {
        return (0);
    }
    u8 search_level_bonus = 0;
    if ((search_level >> 2) > 20) {
        search_level_bonus = 20;
    } else {
        search_level_bonus = (search_level >> 2);
    }
    if ((search_level_bonus + level_base) > 100) {
        return 100;
    } else {
        return ((search_level >> 2) + (level_base));
    }
}


void dexnav_gen_pkmnn(u16 species, u8 potential, u8 level, u8 ability, u16* generatedMoves) {
    struct Pokemon* pkmn = party_opponent;
    // clear canvas
    memset((void*)pkmn, 0, 100);
    u32 trainerId = (u32)gSaveBlock2Ptr->playerTrainerId;
    pokemon_make(&pkmn->box, species, level, 0x0, 0, 0, 0, trainerId);


    // set IVs randomly
    u8 i;
    u8 current_iv = REQUEST_HP_IV;
    for (i = 0; i < 6; i++) {
        u8 iv_value = (rand() & 0x1F);
        set_pokemon_data_2(pkmn, current_iv, (void*) &iv_value);
        current_iv++;
    }

    // pick potential ivs to set to 31
    while (1) {
        u8 iv[3];
        iv[0] = rand() % 6;
        iv[1] = rand() % 6;
        iv[2] = rand() % 6;
        if ((iv[0] != iv[1]) && (iv[0] != iv[2]) && (iv[1] != iv[2])) {
            u8 perfect_iv = 0x1F;
            if (potential > 2) {
                set_pokemon_data_2(pkmn, REQUEST_HP_IV + iv[2], (void*) &perfect_iv);
            }
            if (potential > 1) {
                set_pokemon_data_2(pkmn, REQUEST_HP_IV + iv[1], (void*) &perfect_iv);
            }
            if (potential) {
                set_pokemon_data_2(pkmn, REQUEST_HP_IV + iv[0], (void*) &perfect_iv);
            }
        }
        break;
    }

    // set ability
    if (gBaseStats[species].ability1 == ability){
        pkmn->box.unused = 0;
    } else if (gBaseStats[species].ability2 == ability) {
        pkmn->box.unused = 1;
    } else {
        pkmn->box.unused = 2;
    }

    // set generated moves
    set_pokemon_data_2(pkmn, REQUEST_MOVE1, (void*) (generatedMoves));
    set_pokemon_data_2(pkmn, REQUEST_MOVE2, (void*) (generatedMoves + 1));
    set_pokemon_data_2(pkmn, REQUEST_MOVE3, (void*) (generatedMoves + 2));
    set_pokemon_data_2(pkmn, REQUEST_MOVE4, (void*) (generatedMoves + 3));

    // set PP of generated moves
    set_pokemon_data_2(pkmn, REQUEST_PP1, (void *) &gBattleMoves[generatedMoves[0]].pp);
    set_pokemon_data_2(pkmn, REQUEST_PP2, (void *) &gBattleMoves[generatedMoves[1]].pp);
    set_pokemon_data_2(pkmn, REQUEST_PP3, (void *) &gBattleMoves[generatedMoves[2]].pp);
    set_pokemon_data_2(pkmn, REQUEST_PP4, (void *) &gBattleMoves[generatedMoves[3]].pp);

    // pokerus
    i = 0xFF;
    set_pokemon_data_2(pkmn, REQUEST_POKERUS_REMAINING, &i);
    recalculate_stats(pkmn);


}
