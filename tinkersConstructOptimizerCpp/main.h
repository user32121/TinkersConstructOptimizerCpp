#include <map>

using namespace std;

//enums
enum class TOOL {
    PICKAXE,
    SHOVEL,
    HATCHET,
    MATTOCK,
    KAMA,
    SCYTHE,
    HAMMER,
    EXCAVATOR,
    LUMBERAXE,
    BROADSWORD,
    LONGSWORD,
    RAPIER,
    BATTLESIGN,
    FRYPAN,
    CLEAVER,
    ARROW,
    SHORTBOW,
    LONGBOW,
    BOLT,
    CROSSBOW,
    SHURIKEN,
};
enum class TOOLPART {
    HEAD,
    HANDLE,
    EXTRA,
    BOW,
    BOWSTRING,
    SHAFT,
    FLETCHLING,
};
struct namedToolPart {
    string name;
    vector<TOOLPART> parts;
};
enum class MATERIAL {
    NAGASCALE,
    STEELEAF,
    FIERYINGOT,
    KNIGHTMETAL,
    WOOD,
    STONE,
    FLINT,
    CACTUS,
    BONE,
    OBSIDIAN,
    PRISMARINE,
    ENDSTONE,
    PAPER,
    SPONGE,
    FIREWOOD,
    IRON,
    PIGIRON,
    KNIGHTSLIME,
    SLIME,
    BLUESLIME,
    MAGMASLIME,
    NETHERRACK,
    COBALT,
    ARDITE,
    MANYULLYN,
    MAGICALWOOD,
    EVILINFUSEDIRON,
    ENCHANTEDMETAL,
    DEMONICMETAL,
    STRING,
    SLIMEVINE,
    VINES,
    BLAZEROD,
    REEDS,
    ICE,
    ENDROD,
    RAVENFEATHER,
    FEATHER,
    SLIMELEAF,
    LEAF,
};
enum class TRAIT {
    ALIEN,
    AQUADYNAMIC,
    ARIDICULOUS,
    AUTOSMELT,
    BACONLICIOUS,
    BEHEADING,
    BREAKABLE,
    CHEAP,
    CHEAPSKATE,
    COLDBLOODED,
    CRUDE,
    CRUDEII,
    CRUMBLING,
    DURITAE,
    ECOLOGICAL,
    ENDERFERENCE,
    ENDSPEED,
    EVILAURA,
    EXPERIENCEBOOST,
    FLAMMABLE,
    FRACTURED,
    FREEZING,
    HELLISH,
    HOVERING,
    INSATIABLE,
    JAGGED,
    LIGHTWEIGHT,
    MAGNETIC,
    MAGNETICII,
    MAGICALLYBRITTLE,
    MAGICALLYMODIFIABLE,
    MOMENTUM,
    PETRAMOR,
    PRECIPITATE,
    PRICKLY,
    SHARP,
    SLIMEY,
    SPIKY,
    SPLINTERING,
    SPLITTING,
    SQUEAKY,
    STALWART,
    STONEBOUND,
    SUPERHEAT,
    SYNERGY,
    TASTY,
    TWILIT,
    UNNATURAL,
    WHISPERING,
    WRITABLE,
    WRITABLEII,
    VEILED,
};
enum class OPTIMIZATIONTARGET {
    DURABILITY,
    MININGSPEED,
    ATTACKSPEED,
    ATTACKDAMAGE,
    DPS,
};
enum class ADVANCED {
    EMBOSSMENT,
    HANDMINEABLE,
    TWILIGHTFOREST,
    TARGETHEALTH,
    TARGETIMMUNETOFIRE,
    TARGETONFIRE,
    TEMPERATURE,
    RAINFALL,
    HEALTH,
    BLOCKLEVEL,
};
enum class TOOLPROPERTIES {
    DURABILITY,
    ATTACKDAMAGE,
    ATTACKSPEED,
    MININGSPEED,
    MININGLEVEL,
    DRAWTIME,
    PROJECTILEDAMAGE,
    PROJECTILESPEED,
    BONUSDAMAGE,
    ACCURACY,
    DRAWSPEED,
    RANGEMULTIPLIER,
    DURABILITYMODIFIER,
    BONUSAMMO,
};

const vector<MATERIAL> allMaterials = {
    MATERIAL::NAGASCALE,
    MATERIAL::STEELEAF,
    MATERIAL::FIERYINGOT,
    MATERIAL::KNIGHTMETAL,
    MATERIAL::WOOD,
    MATERIAL::STONE,
    MATERIAL::FLINT,
    MATERIAL::CACTUS,
    MATERIAL::BONE,
    MATERIAL::OBSIDIAN,
    MATERIAL::PRISMARINE,
    MATERIAL::ENDSTONE,
    MATERIAL::PAPER,
    MATERIAL::SPONGE,
    MATERIAL::FIREWOOD,
    MATERIAL::IRON,
    MATERIAL::PIGIRON,
    MATERIAL::KNIGHTSLIME,
    MATERIAL::SLIME,
    MATERIAL::BLUESLIME,
    MATERIAL::MAGMASLIME,
    MATERIAL::NETHERRACK,
    MATERIAL::COBALT,
    MATERIAL::ARDITE,
    MATERIAL::MANYULLYN,
    MATERIAL::MAGICALWOOD,
    MATERIAL::EVILINFUSEDIRON,
    MATERIAL::ENCHANTEDMETAL,
    MATERIAL::DEMONICMETAL,
    MATERIAL::STRING,
    MATERIAL::SLIMEVINE,
    MATERIAL::VINES,
    MATERIAL::BLAZEROD,
    MATERIAL::REEDS,
    MATERIAL::ICE,
    MATERIAL::ENDROD,
    MATERIAL::RAVENFEATHER,
    MATERIAL::FEATHER,
    MATERIAL::SLIMELEAF,
    MATERIAL::LEAF,
};
struct toolEmbossment {
    namedToolPart part;
    MATERIAL material;
};
struct toolResult {
    vector<MATERIAL> materials;
    toolEmbossment embossment;
};

//parsing enums
const map<string, TOOL> stringToTool = {
    { "pickaxe",TOOL::PICKAXE},
    { "shovel",TOOL::SHOVEL },
    { "hatchet",TOOL::HATCHET },
    { "mattock",TOOL::MATTOCK },
    { "kama",TOOL::KAMA },
    { "scythe",TOOL::SCYTHE },
    { "hammer",TOOL::HAMMER },
    { "excavator",TOOL::EXCAVATOR },
    { "lumberaxe",TOOL::LUMBERAXE },
    { "broadsword",TOOL::BROADSWORD },
    { "longsword",TOOL::LONGSWORD },
    { "rapier",TOOL::RAPIER },
    { "battlesign",TOOL::BATTLESIGN },
    { "frypan",TOOL::FRYPAN },
    { "cleaver",TOOL::CLEAVER },
    { "arrow",TOOL::ARROW },
    { "shortbow",TOOL::SHORTBOW },
    { "longbow",TOOL::LONGBOW },
    { "bolt",TOOL::BOLT },
    { "crossbow",TOOL::CROSSBOW },
    { "shuriken",TOOL::SHURIKEN },
};
map<TOOL, string> toolToString;

const map<string, TOOLPART> stringToToolPart = {
    {"head",TOOLPART::HEAD},
    {"handle",TOOLPART::HANDLE,},
    {"extra",TOOLPART::EXTRA},
    {"bow",TOOLPART::BOW},
    {"bowstring",TOOLPART::BOWSTRING},
    {"shaft",TOOLPART::SHAFT},
    {"fletchling",TOOLPART::FLETCHLING},
};
map<TOOLPART, string> toolPartToString;

const map<string, MATERIAL> stringToMaterial = {
    {"nagascale",MATERIAL::NAGASCALE},
    {"steeleaf",MATERIAL::STEELEAF},
    {"fieryingot",MATERIAL::FIERYINGOT},
    {"knightmetal",MATERIAL::KNIGHTMETAL},
    {"wood",MATERIAL::WOOD},
    {"stone",MATERIAL::STONE},
    {"flint",MATERIAL::FLINT},
    {"cactus",MATERIAL::CACTUS},
    {"bone",MATERIAL::BONE},
    {"obsidian",MATERIAL::OBSIDIAN},
    {"prismarine",MATERIAL::PRISMARINE},
    {"endstone",MATERIAL::ENDSTONE},
    {"paper",MATERIAL::PAPER},
    {"sponge",MATERIAL::SPONGE},
    {"firewood",MATERIAL::FIREWOOD},
    {"iron",MATERIAL::IRON},
    {"pigiron",MATERIAL::PIGIRON},
    {"knightslime",MATERIAL::KNIGHTSLIME},
    {"slime",MATERIAL::SLIME},
    {"blueslime",MATERIAL::BLUESLIME},
    {"magmaslime",MATERIAL::MAGMASLIME},
    {"netherrack",MATERIAL::NETHERRACK},
    {"cobalt",MATERIAL::COBALT},
    {"ardite",MATERIAL::ARDITE},
    {"manyuallyn",MATERIAL::MANYULLYN},
    {"magicalwood",MATERIAL::MAGICALWOOD},
    {"evilinfusediron",MATERIAL::EVILINFUSEDIRON},
    {"enchantedmetal",MATERIAL::ENCHANTEDMETAL},
    {"demonicmetal",MATERIAL::DEMONICMETAL},
    {"string",MATERIAL::STRING},
    {"slimevine",MATERIAL::SLIMEVINE},
    {"vines",MATERIAL::VINES},
    {"blazerod",MATERIAL::BLAZEROD},
    {"reeds",MATERIAL::REEDS},
    {"ice",MATERIAL::ICE},
    {"endrod",MATERIAL::ENDROD},
    {"ravenfeather",MATERIAL::RAVENFEATHER},
    {"feather",MATERIAL::FEATHER},
    {"slimeleaf",MATERIAL::SLIMELEAF},
    {"leaf",MATERIAL::LEAF},
};
map<MATERIAL, string> materialToString;

const map<string, OPTIMIZATIONTARGET> stringToOptimTarget = {
    {"durability",OPTIMIZATIONTARGET::DURABILITY},
    {"miningspeed",OPTIMIZATIONTARGET::MININGSPEED},
    {"attackspeed",OPTIMIZATIONTARGET::ATTACKSPEED},
    {"attackdamage",OPTIMIZATIONTARGET::ATTACKDAMAGE},
    {"dps",OPTIMIZATIONTARGET::DPS},
};
map<OPTIMIZATIONTARGET, string> optimTargetToString;

map<string, TRAIT> stringToTrait = {
    {"alien",TRAIT::ALIEN},
    {"aquadynamic",TRAIT::AQUADYNAMIC},
    {"aridiculous",TRAIT::ARIDICULOUS},
    {"autosmelt",TRAIT::AUTOSMELT},
    {"baconlicious",TRAIT::BACONLICIOUS},
    {"beheading",TRAIT::BEHEADING},
    {"breakable",TRAIT::BREAKABLE},
    {"cheap",TRAIT::CHEAP},
    {"cheapskate",TRAIT::CHEAPSKATE},
    {"coldblooded",TRAIT::COLDBLOODED},
    {"crude",TRAIT::CRUDE},
    {"crudeii",TRAIT::CRUDEII},
    {"crumbling",TRAIT::CRUMBLING},
    {"duritae",TRAIT::DURITAE},
    {"ecological",TRAIT::ECOLOGICAL},
    {"enderference",TRAIT::ENDERFERENCE},
    {"endspeed",TRAIT::ENDSPEED},
    {"evilaura",TRAIT::EVILAURA},
    {"experienceboost",TRAIT::EXPERIENCEBOOST},
    {"flammable",TRAIT::FLAMMABLE},
    {"fractured",TRAIT::FRACTURED},
    {"freezing",TRAIT::FREEZING},
    {"hellish",TRAIT::HELLISH},
    {"hovering",TRAIT::HOVERING},
    {"insatiable",TRAIT::INSATIABLE},
    {"jagged",TRAIT::JAGGED},
    {"lightweight",TRAIT::LIGHTWEIGHT},
    {"magnetic",TRAIT::MAGNETIC},
    {"magneticii",TRAIT::MAGNETICII},
    {"magicallybrittle",TRAIT::MAGICALLYBRITTLE},
    {"magicallymodifiable",TRAIT::MAGICALLYMODIFIABLE},
    {"momentum",TRAIT::MOMENTUM},
    {"petramor",TRAIT::PETRAMOR},
    {"precipitate",TRAIT::PRECIPITATE},
    {"prickly",TRAIT::PRICKLY},
    {"sharp",TRAIT::SHARP},
    {"slimey",TRAIT::SLIMEY},
    {"spiky",TRAIT::SPIKY},
    {"splintering",TRAIT::SPLINTERING},
    {"splitting",TRAIT::SPLITTING},
    {"squeaky",TRAIT::SQUEAKY},
    {"stalwart",TRAIT::STALWART},
    {"stonebound",TRAIT::STONEBOUND},
    {"superheat",TRAIT::SUPERHEAT},
    {"synergy",TRAIT::SYNERGY},
    {"tasty",TRAIT::TASTY},
    {"twilit",TRAIT::TWILIT},
    {"unnatural",TRAIT::UNNATURAL},
    {"whispering",TRAIT::WHISPERING},
    {"writable",TRAIT::WRITABLE},
    {"writableii",TRAIT::WRITABLEII},
    {"veiled",TRAIT::VEILED},
};
map<TRAIT, string> traitToString;

map<string, int> stringToBlockLevel = {
    {"Stone",1},
    {"Iron",2},
    {"Diamond",3},
    {"Obsidian",4},
    {"Cobalt",5},
};

//tool properties
map<TOOL, vector<namedToolPart*>*> toolToToolparts = {
    { TOOL::PICKAXE, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Pickaxe Head", {TOOLPART::HEAD}},
        new namedToolPart {"Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::SHOVEL, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Shovel Head", {TOOLPART::HEAD}},
        new namedToolPart {"Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::HATCHET, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Axe Head", {TOOLPART::HEAD}},
        new namedToolPart {"Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::MATTOCK, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Axe Head", {TOOLPART::HEAD}},
        new namedToolPart {"Shovel Head", {TOOLPART::HEAD}},
    }},
    { TOOL::KAMA, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Kama Head", {TOOLPART::HEAD}},
        new namedToolPart {"Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::SCYTHE, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Scythe Head", {TOOLPART::HEAD}},
        new namedToolPart {"Tough Binding", {TOOLPART::EXTRA}},
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
    }},
    { TOOL::HAMMER, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Hammer Head", {TOOLPART::HEAD,TOOLPART::HEAD}},
        new namedToolPart {"Large Plate", {TOOLPART::HEAD}},
        new namedToolPart {"Large Plate", {TOOLPART::HEAD}},
    }},
    { TOOL::EXCAVATOR, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Excavator Head", {TOOLPART::HEAD}},
        new namedToolPart {"Large Plate", {TOOLPART::HEAD}},
        new namedToolPart {"Tough Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::LUMBERAXE, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Broad Axe Head", {TOOLPART::HEAD}},
        new namedToolPart {"Large Plate", {TOOLPART::HEAD}},
        new namedToolPart {"Tough Binding", {TOOLPART::EXTRA}},
    }},
    { TOOL::BROADSWORD, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Sword Blade", {TOOLPART::HEAD}},
        new namedToolPart {"Wide Guard", {TOOLPART::EXTRA}},
    }},
    { TOOL::LONGSWORD, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Sword Blade", {TOOLPART::HEAD}},
        new namedToolPart {"Hand Guard", {TOOLPART::EXTRA}},
    }},
    { TOOL::RAPIER, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Sword Blade", {TOOLPART::HEAD}},
        new namedToolPart {"Cross Guard", {TOOLPART::EXTRA}},
    }},
    { TOOL::BATTLESIGN, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Sign Plate", {TOOLPART::HEAD}},
    }},
    { TOOL::FRYPAN, new vector<namedToolPart*> {
        new namedToolPart {"Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Pan", {TOOLPART::HEAD}},
    }},
    { TOOL::CLEAVER, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE}},
        new namedToolPart {"Large Sword Blade", {TOOLPART::HEAD}},
        new namedToolPart {"Large Plate", {TOOLPART::HEAD}},
        new namedToolPart {"Tough Tool Rod", {TOOLPART::EXTRA}},
    }},
    { TOOL::ARROW, new vector<namedToolPart*> {
        new namedToolPart {"Arrow Shaft", {TOOLPART::SHAFT}},
        new namedToolPart {"Arrow Head", {TOOLPART::HEAD}},
        new namedToolPart {"Fletchling", {TOOLPART::FLETCHLING}},
    }},
    { TOOL::SHORTBOW, new vector<namedToolPart*> {
        new namedToolPart {"Bowlimb", {TOOLPART::HEAD,TOOLPART::BOW}},
        new namedToolPart {"Bowlimb", {TOOLPART::HEAD,TOOLPART::BOW}},
        new namedToolPart {"Bowstring", {TOOLPART::BOWSTRING}},
    }},
    { TOOL::LONGBOW, new vector<namedToolPart*> {
        new namedToolPart {"Bowlimb", {TOOLPART::HEAD,TOOLPART::BOW}},
        new namedToolPart {"Bowlimb", {TOOLPART::HEAD,TOOLPART::BOW}},
        new namedToolPart {"Large Plate", {TOOLPART::EXTRA}},
        new namedToolPart {"Bowstring", {TOOLPART::BOWSTRING}},
    }},
    { TOOL::BOLT, new vector<namedToolPart*> {
        new namedToolPart {"Bolt Core (Shaft)", {TOOLPART::SHAFT}},
        new namedToolPart {"Bolt Core (Head)", {TOOLPART::HEAD}},
        new namedToolPart {"Fletchling", {TOOLPART::FLETCHLING}},
    }},
    { TOOL::CROSSBOW, new vector<namedToolPart*> {
        new namedToolPart {"Tough Tool Rod", {TOOLPART::HANDLE,TOOLPART::EXTRA}},
        new namedToolPart {"Bowlimb", {TOOLPART::HEAD,TOOLPART::BOW}},
        new namedToolPart {"Tough Binding", {TOOLPART::EXTRA}},
        new namedToolPart {"Bowstring", {TOOLPART::BOWSTRING}},
    }},
    { TOOL::SHURIKEN, new vector<namedToolPart*> {
        new namedToolPart {"Knife Blade", {TOOLPART::HEAD,TOOLPART::EXTRA}},
        new namedToolPart {"Knife Blade", {TOOLPART::HEAD,TOOLPART::EXTRA}},
        new namedToolPart {"Knife Blade", {TOOLPART::HEAD,TOOLPART::EXTRA}},
        new namedToolPart {"Knife Blade", {TOOLPART::HEAD,TOOLPART::EXTRA}},
    }},
};
map<MATERIAL, map<TOOLPART, pair<map<TOOLPROPERTIES, double>, vector<TRAIT>>>> materialToolParts = {
    { MATERIAL::NAGASCALE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 460},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 8.9},
                {TOOLPROPERTIES::ATTACKDAMAGE, 4.3},
            },
            {TRAIT::TWILIT, TRAIT::PRECIPITATE}
        }},
        { TOOLPART::BOW, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.67},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 2},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::TWILIT, TRAIT::PRECIPITATE}
        }},
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.4},
                {TOOLPROPERTIES::BONUSAMMO, 20},
            },
            {TRAIT::TWILIT, TRAIT::PRECIPITATE}
        }},
    }},
    { MATERIAL::STEELEAF, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 180},
                {TOOLPROPERTIES::MININGLEVEL, 3},
                {TOOLPROPERTIES::MININGSPEED, 7},
                {TOOLPROPERTIES::ATTACKDAMAGE, 6},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 100},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.8},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 90},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.83},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.5},
                {TOOLPROPERTIES::BONUSDAMAGE, 2},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.6},
                {TOOLPROPERTIES::BONUSAMMO, 10},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
        { TOOLPART::FLETCHLING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.8},
                {TOOLPROPERTIES::ACCURACY, 1},
            },
            {TRAIT::TWILIT, TRAIT::SYNERGY}
        }},
    }},
    { MATERIAL::FIERYINGOT, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 720},
                {TOOLPROPERTIES::MININGLEVEL, 4},
                {TOOLPROPERTIES::MININGSPEED, 7.2},
                {TOOLPROPERTIES::ATTACKDAMAGE, 6.6},
            },
            {TRAIT::TWILIT, TRAIT::AUTOSMELT, TRAIT::SUPERHEAT, TRAIT::FLAMMABLE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 400},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.7},
            },
            {TRAIT::TWILIT, TRAIT::FLAMMABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 200},
            },
            {TRAIT::TWILIT, TRAIT::FLAMMABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.9},
                {TOOLPROPERTIES::BONUSDAMAGE, 4},
            },
            {TRAIT::TWILIT, TRAIT::FLAMMABLE}
        }},
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.8},
                {TOOLPROPERTIES::BONUSAMMO, 0},
            },
            {TRAIT::TWILIT, TRAIT::FLAMMABLE}
        }},
    }},
    { MATERIAL::KNIGHTMETAL, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 900},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 7},
                {TOOLPROPERTIES::ATTACKDAMAGE, 6},
            },
            {TRAIT::TWILIT, TRAIT::STALWART}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 100},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.25},
            },
            {TRAIT::TWILIT, TRAIT::STALWART}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 400},
            },
            {TRAIT::TWILIT, TRAIT::STALWART}
        }},
    }},
    { MATERIAL::WOOD, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 35},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 2},
                {TOOLPROPERTIES::ATTACKDAMAGE, 2},
            },
            {TRAIT::ECOLOGICAL}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 25},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {TRAIT::ECOLOGICAL}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 15},
            },
            {TRAIT::ECOLOGICAL}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::ECOLOGICAL}
        }},
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
                {TOOLPROPERTIES::BONUSAMMO, 0},
            },
            {TRAIT::ECOLOGICAL}
        }},
    }},
    { MATERIAL::STONE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 120},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 4},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3},
            },
            {TRAIT::CHEAPSKATE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -50},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.5},
            },
            {TRAIT::CHEAP}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 20},
            },
            {TRAIT::CHEAP}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::CHEAP}
        }},
    }},
    { MATERIAL::FLINT, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 150},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 5},
                {TOOLPROPERTIES::ATTACKDAMAGE, 2.9},
            },
            {TRAIT::CRUDEII}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -60},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.6},
            },
            {TRAIT::CRUDE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 40},
            },
            {TRAIT::CRUDE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::CRUDE, TRAIT::CRUDEII}
        }},
    }},
    { MATERIAL::CACTUS, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 210},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 4},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3.4},
            },
            {TRAIT::PRICKLY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 20},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.85},
            },
            {TRAIT::SPIKY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 50},
            },
            {TRAIT::SPIKY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.95},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.9},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::SPIKY}
        }},
    }},
    { MATERIAL::BONE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 200},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 5.09},
                {TOOLPROPERTIES::ATTACKDAMAGE, 2.5},
            },
            {TRAIT::SPLINTERING}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 50},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.1},
            },
            {TRAIT::FRACTURED}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 65},
            },
            {TRAIT::FRACTURED}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.05},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.15},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::FRACTURED}
        }},
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.9},
                {TOOLPROPERTIES::BONUSAMMO, 5},
            },
            {TRAIT::SPLITTING}
        }},
    }},
    { MATERIAL::OBSIDIAN, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 139},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 7.07},
                {TOOLPROPERTIES::ATTACKDAMAGE, 4.2},
            },
            {TRAIT::DURITAE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -100},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.9},
            },
            {TRAIT::DURITAE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 90},
            },
            {TRAIT::DURITAE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::DURITAE}
        }},
    }},
    { MATERIAL::PRISMARINE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 430},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 5.5},
                {TOOLPROPERTIES::ATTACKDAMAGE, 6.2},
            },
            {TRAIT::JAGGED, TRAIT::AQUADYNAMIC}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -150},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.6},
            },
            {TRAIT::AQUADYNAMIC}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 100},
            },
            {TRAIT::AQUADYNAMIC}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::AQUADYNAMIC}
        }},
    }},
    { MATERIAL::ENDSTONE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 420},
                {TOOLPROPERTIES::MININGLEVEL, 4},
                {TOOLPROPERTIES::MININGSPEED, 3.23},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3.23},
            },
            {TRAIT::ALIEN}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 0},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.85},
            },
            {TRAIT::ENDERFERENCE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 42},
            },
            {TRAIT::ENDERFERENCE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::ENDERFERENCE}
        }},
    }},
    { MATERIAL::PAPER, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 12},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 0.51},
                {TOOLPROPERTIES::ATTACKDAMAGE, 0.05},
            },
            {TRAIT::WRITABLE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 5},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.1},
            },
            {TRAIT::WRITABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 15},
            },
            {TRAIT::WRITABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.67},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -2},
            },
            {TRAIT::WRITABLEII}
        }},
    }},
    { MATERIAL::SPONGE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 1050},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 3.02},
                {TOOLPROPERTIES::ATTACKDAMAGE, 0},
            },
            {TRAIT::SQUEAKY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 250},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.2},
            },
            {TRAIT::SQUEAKY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 250},
            },
            {TRAIT::SQUEAKY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.87},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.75},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::SQUEAKY}
        }},
    }},
    { MATERIAL::FIREWOOD, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 550},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 6},
                {TOOLPROPERTIES::ATTACKDAMAGE, 5.5},
            },
            {TRAIT::AUTOSMELT}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -200},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {TRAIT::AUTOSMELT}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 150},
            },
            {TRAIT::AUTOSMELT}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::AUTOSMELT}
        }},
    }},
    { MATERIAL::IRON, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 204},
                {TOOLPROPERTIES::MININGLEVEL, 3},
                {TOOLPROPERTIES::MININGSPEED, 6},
                {TOOLPROPERTIES::ATTACKDAMAGE, 4},
            },
            {TRAIT::MAGNETICII}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 60},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.85},
            },
            {TRAIT::MAGNETIC}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 50},
            },
            {TRAIT::MAGNETIC}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 2},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.5},
                {TOOLPROPERTIES::BONUSDAMAGE, 7},
            },
            {TRAIT::MAGNETIC, TRAIT::MAGNETICII}
        }},
    }},
    { MATERIAL::PIGIRON, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 380},
                {TOOLPROPERTIES::MININGLEVEL, 3},
                {TOOLPROPERTIES::MININGSPEED, 6.2},
                {TOOLPROPERTIES::ATTACKDAMAGE, 4.5},
            },
            {TRAIT::BACONLICIOUS, TRAIT::TASTY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 0},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.2},
            },
            {TRAIT::TASTY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 170},
            },
            {TRAIT::TASTY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.67},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.4},
                {TOOLPROPERTIES::BONUSDAMAGE, 7},
            },
            {TRAIT::TASTY}
        }},
    }},
    { MATERIAL::KNIGHTSLIME, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 850},
                {TOOLPROPERTIES::MININGLEVEL, 4},
                {TOOLPROPERTIES::MININGSPEED, 5.8},
                {TOOLPROPERTIES::ATTACKDAMAGE, 5.1},
            },
            {TRAIT::CRUMBLING}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 500},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.5},
            },
            {TRAIT::UNNATURAL}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 125},
            },
            {TRAIT::UNNATURAL}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 2.5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 2},
                {TOOLPROPERTIES::BONUSDAMAGE, 2},
            },
            {TRAIT::UNNATURAL}
        }},
    }},
    { MATERIAL::SLIME, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 1000},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 4.24},
                {TOOLPROPERTIES::ATTACKDAMAGE, 1.8},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 0},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.7},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 350},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.18},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.3},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::SLIMEY}
        }},
    }},
    { MATERIAL::BLUESLIME, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 780},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 4.03},
                {TOOLPROPERTIES::ATTACKDAMAGE, 1.8},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -50},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.3},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 200},
            },
            {TRAIT::SLIMEY}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.95},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::SLIMEY}
        }},
    }},
    { MATERIAL::MAGMASLIME, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 600},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 2.1},
                {TOOLPROPERTIES::ATTACKDAMAGE, 7},
            },
            {TRAIT::SUPERHEAT}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -200},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.85},
            },
            {TRAIT::FLAMMABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 150},
            },
            {TRAIT::FLAMMABLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 0.91},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.05},
                {TOOLPROPERTIES::BONUSDAMAGE, 1},
            },
            {TRAIT::FLAMMABLE}
        }},
    }},
    { MATERIAL::NETHERRACK, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 270},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 4.5},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3},
            },
            {TRAIT::ARIDICULOUS, TRAIT::HELLISH}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -150},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.85},
            },
            {TRAIT::HELLISH}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 75},
            },
            {TRAIT::HELLISH}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 5},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.4},
                {TOOLPROPERTIES::BONUSDAMAGE, -1},
            },
            {TRAIT::HELLISH}
        }},
    }},
    { MATERIAL::COBALT, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 780},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 12},
                {TOOLPROPERTIES::ATTACKDAMAGE, 4.1},
            },
            {TRAIT::MOMENTUM}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 100},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.9},
            },
            {TRAIT::LIGHTWEIGHT}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 300},
            },
            {TRAIT::LIGHTWEIGHT}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.33},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.3},
                {TOOLPROPERTIES::BONUSDAMAGE, 3},
            },
            {TRAIT::LIGHTWEIGHT}
        }},
    }},
    { MATERIAL::ARDITE, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 990},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 3.5},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3.6},
            },
            {TRAIT::STONEBOUND}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, -200},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.4},
            },
            {TRAIT::PETRAMOR}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 450},
            },
            {TRAIT::PETRAMOR}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 2.22},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 0.8},
                {TOOLPROPERTIES::BONUSDAMAGE, 1},
            },
            {TRAIT::PETRAMOR}
        }},
    }},
    { MATERIAL::MANYULLYN, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 820},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 7.02},
                {TOOLPROPERTIES::ATTACKDAMAGE, 8.72},
            },
            {TRAIT::INSATIABLE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 250},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.5},
            },
            {TRAIT::COLDBLOODED}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 50},
            },
            {TRAIT::COLDBLOODED}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.54},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.2},
                {TOOLPROPERTIES::BONUSDAMAGE, 4},
            },
            {TRAIT::COLDBLOODED}
        }},
    }},
    { MATERIAL::MAGICALWOOD, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 35},
                {TOOLPROPERTIES::MININGLEVEL, 1},
                {TOOLPROPERTIES::MININGSPEED, 2},
                {TOOLPROPERTIES::ATTACKDAMAGE, 2},
            },
            {TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGICALLYBRITTLE}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 25},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGICALLYBRITTLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 15},
            },
            {TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGICALLYBRITTLE}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1},
                {TOOLPROPERTIES::BONUSDAMAGE, 0},
            },
            {TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGICALLYBRITTLE}
        }},
    }},
    { MATERIAL::EVILINFUSEDIRON, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 666},
                {TOOLPROPERTIES::MININGLEVEL, 5},
                {TOOLPROPERTIES::MININGSPEED, 13},
                {TOOLPROPERTIES::ATTACKDAMAGE, 13},
            },
            {TRAIT::EVILAURA}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 0},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 66},
            },
            {}
        }},
    }},
    { MATERIAL::ENCHANTEDMETAL, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 350},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 7},
                {TOOLPROPERTIES::ATTACKDAMAGE, 3.5},
            },
            {TRAIT::EXPERIENCEBOOST}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 20},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.1},
            },
            {TRAIT::EXPERIENCEBOOST}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 80},
            },
            {TRAIT::EXPERIENCEBOOST}
        }},
    }},
    { MATERIAL::DEMONICMETAL, {
        { TOOLPART::HEAD, {
            {
                {TOOLPROPERTIES::DURABILITY, 80},
                {TOOLPROPERTIES::MININGLEVEL, 2},
                {TOOLPROPERTIES::MININGSPEED, 0.5},
                {TOOLPROPERTIES::ATTACKDAMAGE, 11.1},
            },
            {TRAIT::WHISPERING}
        }},
        { TOOLPART::HANDLE, {
            {
                {TOOLPROPERTIES::DURABILITY, 100},
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.25},
            },
            {}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DURABILITY, 20},
            },
            {}
        }},
        { TOOLPART::EXTRA, {
            {
                {TOOLPROPERTIES::DRAWSPEED, 1.43},
                {TOOLPROPERTIES::RANGEMULTIPLIER, 1.1},
                {TOOLPROPERTIES::BONUSDAMAGE, 4},
            },
            {}
        }},
    }},
    { MATERIAL::STRING, {
        { TOOLPART::BOWSTRING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {}
        }},
    }},
    { MATERIAL::SLIMEVINE, {
        { TOOLPART::BOWSTRING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {}
        }},
    }},
    { MATERIAL::VINES, {
        { TOOLPART::BOWSTRING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
            },
            {}
        }},
    }},
    { MATERIAL::BLAZEROD, {
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.8},
                {TOOLPROPERTIES::BONUSAMMO, 3},
            },
            {TRAIT::HOVERING}
        }},
    }},
    { MATERIAL::REEDS, {
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.5},
                {TOOLPROPERTIES::BONUSAMMO, 20},
            },
            {TRAIT::BREAKABLE}
        }},
    }},
    { MATERIAL::ICE, {
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.95},
                {TOOLPROPERTIES::BONUSAMMO, 0},
            },
            {TRAIT::FREEZING}
        }},
    }},
    { MATERIAL::ENDROD, {
        { TOOLPART::SHAFT, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 0.7},
                {TOOLPROPERTIES::BONUSAMMO, 1},
            },
            {TRAIT::ENDSPEED}
        }},
    }},
    { MATERIAL::RAVENFEATHER, {
        { TOOLPART::FLETCHLING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.15},
                {TOOLPROPERTIES::ACCURACY, 0.95},
            },
            {TRAIT::TWILIT, TRAIT::VEILED}
        }},
    }},
    { MATERIAL::FEATHER, {
        { TOOLPART::FLETCHLING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1},
                {TOOLPROPERTIES::ACCURACY, 1},
            },
            {}
        }},
    }},
    { MATERIAL::SLIMELEAF, {
        { TOOLPART::FLETCHLING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.25},
                {TOOLPROPERTIES::ACCURACY, 0.8},
            },
            {}
        }},
    }},
    { MATERIAL::LEAF, {
        { TOOLPART::FLETCHLING, {
            {
                {TOOLPROPERTIES::DURABILITYMODIFIER, 1.5},
                {TOOLPROPERTIES::ACCURACY, 0.5},
            },
            {}
        }},
    }},
};
map<TOOL, map<TOOLPROPERTIES, vector<pair<char, double>>>> toolToToolModifiers = {
    { TOOL::PICKAXE, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.2}} },
    }},
    { TOOL::SHOVEL, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.9}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1}} },
    }},
    { TOOL::HATCHET, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 0.5},{'*', 1.1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.1}} },
    }},
    { TOOL::MATTOCK, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 1},{'*', 0.9}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.9}} },
        { TOOLPROPERTIES::MININGSPEED, {{'*', 0.95}} },
    }},
    { TOOL::KAMA, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.3}} },
    }},
    { TOOL::SCYTHE, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 2.2}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.75}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.9}} },
    }},
    { TOOL::HAMMER, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 2.5}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1.2}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.8}} },
        { TOOLPROPERTIES::MININGSPEED, {{'*', 0.4}} },
        { TOOLPROPERTIES::MININGLEVEL, {{'=', 1}} },  //mining level takes trait from hammer head (use index)
    }},
    { TOOL::EXCAVATOR, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 1.75}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1.25}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.7}} },
        { TOOLPROPERTIES::MININGSPEED, {{'*', 0.28}} },
    }},
    { TOOL::LUMBERAXE, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 2}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 2},{'*', 1.2}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.8}} },
        { TOOLPROPERTIES::MININGSPEED, {{'*', 0.35}} },
    }},
    { TOOL::BROADSWORD, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 1.1}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 1},{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.6}} },
    }},
    { TOOL::LONGSWORD, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 1.05}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 0.5},{'*', 1.1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.4}} },
    }},
    { TOOL::RAPIER, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 0.8}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.55}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 3}} },
    }},
    { TOOL::BATTLESIGN, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.86}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.2}} },
    }},
    { TOOL::FRYPAN, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.4}} },
    }},
    { TOOL::CLEAVER, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 2}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1.3},{'+', 3},{'*', 1.2}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 0.7}} },
    }},
    { TOOL::ARROW, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 2},{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1}} },
    }},
    { TOOL::SHORTBOW, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.7}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.5}} },
        { TOOLPROPERTIES::DRAWTIME, {{'=', 12}} },
        { TOOLPROPERTIES::PROJECTILEDAMAGE, {{'=', 0},{'*', 0.8}} },
        { TOOLPROPERTIES::PROJECTILESPEED, {{'=', 3}} },
    }},
    { TOOL::LONGBOW, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 1.4}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1.3}} },
        { TOOLPROPERTIES::DRAWTIME, {{'=', 30}} },
        { TOOLPROPERTIES::PROJECTILEDAMAGE, {{'=', 2.5},{'*', 1.25}} },
        { TOOLPROPERTIES::PROJECTILESPEED, {{'=', 5.5}} },
    }},
    { TOOL::BOLT, {
        { TOOLPROPERTIES::DURABILITY, {{'*', 0.8}} },
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 1}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 1}} },
    }},
    { TOOL::CROSSBOW, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'*', 0.8}} },
        { TOOLPROPERTIES::BONUSDAMAGE, {{'*', 1.5}} },
        { TOOLPROPERTIES::ATTACKSPEED, {{'*', 2}} },
        { TOOLPROPERTIES::DRAWTIME, {{'=', 45}} },
        { TOOLPROPERTIES::PROJECTILEDAMAGE, {{'=', 3},{'*', 1.3}} },
        { TOOLPROPERTIES::PROJECTILESPEED, {{'=', 7}} },
    }},
    { TOOL::SHURIKEN, {
        { TOOLPROPERTIES::ATTACKDAMAGE, {{'+', 1},{'*', 0.7}} },
        { TOOLPROPERTIES::ACCURACY, {{'=', 1}} },
    }},
};

//function to construct inverse maps
void initializeInverseMaps()
{
    for(auto keyValue : stringToTool)
        toolToString[keyValue.second] = keyValue.first;
    for(auto keyValue : stringToToolPart)
        toolPartToString[keyValue.second] = keyValue.first;
    for(auto keyValue : stringToMaterial)
    {
        string s = keyValue.first;
        s[0] = toupper(s[0]);
        materialToString[keyValue.second] = s;
    }
    materialToString[MATERIAL::LEAF] = "LeaF";
    for(auto keyValue : stringToOptimTarget)
        optimTargetToString[keyValue.second] = keyValue.first;
    for(auto keyValue : stringToTrait)
        traitToString[keyValue.second] = keyValue.first;
}
