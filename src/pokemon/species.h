#ifndef PKMN_SPECIES_H_
#define PKMN_SPECIES_H_

enum PokemonSpecies {
	SPECIES_NONE = 0,
	SPECIES_HORSEA = 1,
	SPECIES_SEADRA = 2,
	SPECIES_KINGDRA = 3,
	SPECIES_TRAPINCH = 4,
	SPECIES_VIBRAVA = 5,
	SPECIES_FLYGON = 6,
	SPECIES_TOGEPI = 7,
	SPECIES_TOGETIC = 8,
	SPECIES_TOGEKISS = 9,
	SPECIES_YUNGOOS = 10,
	SPECIES_GUMSHOOS = 11,
	SPECIES_BUNNELBY = 12,
	SPECIES_DIGGERSBY = 13,
	SPECIES_BOUNSWEET = 14,
	SPECIES_STEENEE = 15,
	SPECIES_TSAREENA = 16,
	SPECIES_MAREEP = 17,
	SPECIES_FLAAFFY = 18,
	SPECIES_AMPHAROS = 19,
	SPECIES_COMBEE = 20,
	SPECIES_VESPIQUEN = 21,
	SPECIES_SPINARAK = 22,
	SPECIES_ARIADOS = 23,
	SPECIES_JOLTIK = 24,
	SPECIES_GALVANTULA = 25,
	SPECIES_DEWPIDER = 26,
	SPECIES_ARAQUANID = 27,
	SPECIES_ZUBAT = 28,
	SPECIES_GOLBAT = 29,
	SPECIES_CROBAT = 30,
	SPECIES_YANMA = 31,
	SPECIES_YANMEGA = 32,
	SPECIES_MORELULL = 33,
	SPECIES_SHIINOTIC = 34,
	SPECIES_VULPIX = 35,
	SPECIES_NINETALES = 36,
	SPECIES_GROWLITHE = 37,
	SPECIES_ARCANINE = 38,
	SPECIES_PINECO = 39,
	SPECIES_FORRETRESS = 40,
	SPECIES_NINCADA = 41,
	SPECIES_NINJASK = 42,
	SPECIES_SHEDINJA = 43,
	SPECIES_FEEBAS = 44,
	SPECIES_MILOTIC = 45,
	SPECIES_SHELLDER = 46,
	SPECIES_CLOYSTER = 47,
	SPECIES_SLOWPOKE = 48,
	SPECIES_SLOWBRO = 49,
	SPECIES_SLOWKING = 50,
	SPECIES_ABRA = 51,
	SPECIES_KADABRA = 52,
	SPECIES_ALAKAZAM = 53,
	SPECIES_ESPURR = 54,
	SPECIES_MEOWSTIC = 55,
	SPECIES_COTTONEE = 56,
	SPECIES_WHIMSICOTT = 57,
	SPECIES_PETILIL = 58,
	SPECIES_LILLIGANT = 59,
	SPECIES_SHROOMISH = 60,
	SPECIES_BRELOOM = 61,
	SPECIES_SWABLU = 62,
	SPECIES_ALTARIA = 63,
	SPECIES_MURKROW = 64,
	SPECIES_HONCHKROW = 65,
	SPECIES_CLEFFA = 66,
	SPECIES_CLEFAIRY = 67,
	SPECIES_CLEFABLE = 68,
	SPECIES_RIOLU = 69,
	SPECIES_LUCARIO = 70,
	SPECIES_MACHOP = 71,
	SPECIES_MACHOKE = 72,
	SPECIES_MACHAMP = 73,
	SPECIES_SHINX = 74,
	SPECIES_LUXIO = 75,
	SPECIES_LUXRAY = 76,
	SPECIES_LITLEO = 77,
	SPECIES_PYROAR = 78,
	SPECIES_HOUNDOUR = 79,
	SPECIES_HOUNDOOM = 80,
	SPECIES_WINGULL = 81,
	SPECIES_PELIPPER = 82,
	SPECIES_TENTACOOL = 83,
	SPECIES_TENTACRUEL = 84,
	SPECIES_REMORAID = 85,
	SPECIES_OCTILLERY = 86,
	SPECIES_INKAY = 87,
	SPECIES_MALAMAR = 88,
	SPECIES_DWEBBLE = 89,
	SPECIES_CRUSTLE = 90,
	SPECIES_SKRELP = 91,
	SPECIES_DRAGALGE = 92,
	SPECIES_TRUBBISH = 93,
	SPECIES_GARBODOR = 94,
	SPECIES_CROAGUNK = 95,
	SPECIES_TOXICROAK = 96,
	SPECIES_SKORUPI = 97,
	SPECIES_DRAPION = 98,
	SPECIES_CARNIVINE = 99,
	SPECIES_GOOMY = 100,
	SPECIES_SLIGGOO = 101,
	SPECIES_GOODRA = 102,
	SPECIES_MUDBRAY = 103,
	SPECIES_MUDSDALE = 104,
	SPECIES_GASTLY = 105,
	SPECIES_HAUNTER = 106,
	SPECIES_GENGAR = 107,
	SPECIES_DUSKULL = 108,
	SPECIES_DUSCLOPS = 109,
	SPECIES_DUSKNOIR = 110,
	SPECIES_NOIBAT = 111,
	SPECIES_NOIVERN = 112,
	SPECIES_DUNSPARCE = 113,
	SPECIES_MIENFOO = 114,
	SPECIES_MIENSHAO = 115,
	SPECIES_BLITZLE = 116,
	SPECIES_ZEBSTRIKA = 117,
	SPECIES_PONYTA = 118,
	SPECIES_RAPIDASH = 119,
	SPECIES_HERACROSS = 120,
	SPECIES_SCYTHER = 121,
	SPECIES_SCIZOR = 122,
	SPECIES_EEVEE = 123,
	SPECIES_VAPOREON = 124,
	SPECIES_JOLTEON = 125,
	SPECIES_FLAREON = 126,
	SPECIES_ESPEON = 127,
	SPECIES_UMBREON = 128,
	SPECIES_LEAFEON = 129,
	SPECIES_GLACEON = 130,
	SPECIES_SYLVEON = 131,
	SPECIES_ROCKRUFF = 132,
	SPECIES_LYCANROC = 133,
	SPECIES_GEODUDE = 134,
	SPECIES_GRAVELER = 135,
	SPECIES_GOLEM = 136,
	SPECIES_ANORITH = 137,
	SPECIES_ARMALDO = 138,
	SPECIES_LILEEP = 139,
	SPECIES_CRADILY = 140,
	SPECIES_CHINCHOU = 141,
	SPECIES_LANTURN = 142,
	SPECIES_STARYU = 143,
	SPECIES_STARMIE = 144,
	SPECIES_SPHEAL = 145,
	SPECIES_SEALEO = 146,
	SPECIES_WALREIN = 147,
	SPECIES_PAWNIARD = 148,
	SPECIES_BISHARP = 149,
	SPECIES_SCRAGGY = 150,
	SPECIES_SCRAFTY = 151,
	SPECIES_GLIGAR = 152,
	SPECIES_GLISCOR = 153,
	SPECIES_SKIDDO = 154,
	SPECIES_GOGOAT = 155,
	SPECIES_DRAMPA = 156,
	SPECIES_LARVITAR = 157,
	SPECIES_PUPITAR = 158,
	SPECIES_TYRANITAR = 159,
	SPECIES_SALANDIT = 160,
	SPECIES_SALAZZLE = 161,
	SPECIES_SANDILE = 162,
	SPECIES_KROKOROK = 163,
	SPECIES_KROOKODILE = 164,
	SPECIES_SIGILYPH = 165,
	SPECIES_MARACTUS = 166,
	SPECIES_CACNEA = 167,
	SPECIES_CACTURNE = 168,
	SPECIES_SHUCKLE = 169,
	SPECIES_SLUGMA = 170,
	SPECIES_MAGCARGO = 171,
	SPECIES_TORKOAL = 172,
	SPECIES_TURTONATOR = 173,
	SPECIES_LARVESTA = 174,
	SPECIES_VOLCARONA = 175,
	SPECIES_SWIRLIX = 176,
	SPECIES_SLURPUFF = 177,
	SPECIES_SNUBBULL = 178,
	SPECIES_GRANBULL = 179,
	SPECIES_TYNAMO = 180,
	SPECIES_EELEKTRIK = 181,
	SPECIES_EELEKTROSS = 182,
	SPECIES_MAGNEMITE = 183,
	SPECIES_MAGNETON = 184,
	SPECIES_MAGNEZONE = 185,
	SPECIES_TOGEDEMARU = 186,
	SPECIES_ROTOM = 187,
	SPECIES_SANDYGAST = 188,
	SPECIES_PALOSSAND = 189,
	SPECIES_LITWICK = 190,
	SPECIES_LAMPENT = 191,
	SPECIES_CHANDELURE = 192,
	SPECIES_DHELMISE = 193,
	SPECIES_HONEDGE = 194,
	SPECIES_DOUBLADE = 195,
	SPECIES_AEGISLASH = 196,
	SPECIES_SPIRITOMB = 197,
	SPECIES_MAWILE = 198,
	SPECIES_GIRAFARIG = 199,
	SPECIES_MUNCHLAX = 200,
	SPECIES_SNORLAX = 201,
	SPECIES_PANCHAM = 202,
	SPECIES_PANGORO = 203,
	SPECIES_PASSIMIAN = 204,
	SPECIES_STUFFUL = 205,
	SPECIES_BEWEAR = 206,
	SPECIES_BOUFFALANT = 207,
	SPECIES_KANGASKHAN = 208,
	SPECIES_HAWLUCHA = 209,
	SPECIES_TROPIUS = 210,
	SPECIES_LAPRAS = 211,
	SPECIES_SKARMORY = 212,
	SPECIES_SNEASEL = 213,
	SPECIES_WEAVILE = 214,
	SPECIES_SNOVER = 215,
	SPECIES_ABOMASNOW = 216,
	SPECIES_SNORUNT = 217,
	SPECIES_GLALIE = 218,
	SPECIES_FROSLASS = 219,
	SPECIES_BERGMITE = 220,
	SPECIES_AVALUGG = 221,
	SPECIES_CRYOGONAL = 222,
	SPECIES_PORYGON = 223,
	SPECIES_PORYGON2 = 224,
	SPECIES_PORYGONZ = 225,
	SPECIES_DRUDDIGON = 226,
	SPECIES_GOLETT = 227,
	SPECIES_GOLURK = 228,
	SPECIES_DRILBUR = 229,
	SPECIES_EXCADRILL = 230,
	SPECIES_BELDUM = 231,
	SPECIES_METANG = 232,
	SPECIES_METAGROSS = 233,
	SPECIES_GIBLE = 234,
	SPECIES_GABITE = 235,
	SPECIES_GARCHOMP = 236,
	SPECIES_DRATINI = 237,
	SPECIES_DRAGONAIR = 238,
	SPECIES_DRAGONITE = 239,
	SPECIES_LATIAS = 240,
	SPECIES_LATIOS = 241,
	SPECIES_HEATRAN = 242,
	SPECIES_DEOXYS = 243,
	SPECIES_JIRACHI = 244,
	SPECIES_DARKRAI = 245,
	SPECIES_MAX = 246,
};
#endif /*PKMN_SPECIES_H_*/
