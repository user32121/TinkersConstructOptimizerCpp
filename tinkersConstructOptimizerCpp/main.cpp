#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

#include "main.h"

using namespace std;

//main parameters
TOOL tool;
vector<namedToolPart*>* toolParts;
OPTIMIZATIONTARGET target;
vector<MATERIAL> materials;

//results
toolResult curTool, bestTool;
pair<double,double> bestStat = {-1,-1};  //(base, bonus)

//options
bool useEmbossment = false;
bool verbose = false;
//environment
double temperature = 0.8;       //--temperature
double rainfall = 0;            //--rainfall
bool handBreakable = false;     //--hand-breakable
double playerHealth = 1;        //--player-health
int blockLevel = -1;            //--block-level
bool inTwilight = false;        //--twilight
bool targetFullHealth = false;   //--target-full-health
bool targetfireimmune = false;  //--target-fire-immune
bool targetOnFire = false;       //--target-on-fire

double getDurability()
{
    double headSum = 0, headCount = 0;  //head durability
    double extraSum = 0, extraCount = 0;  //extra durability
    double handleSum = 0, handleCount = 0;  //handle durability
    double modifierSum = 0, modifierCount = 0;  //handle multiplier
    double fletchlingSum = 0, fletchlingCount = 0;  //fletchling multiplier
    double shaftSum = 0, shaftCount = 0;  //shaft multiplier
    double shaftBonusSum = 0, shaftBonusCount = 0;  //shaft bonus
    double bowstringSum = 0, bowstringCount = 0;  //bowstring multiplier
    
    auto temp = (*toolParts)[0]->parts;
    
    for(int i = 0; i < toolParts->size(); i++)
        for(TOOLPART part : (*toolParts)[i]->parts)
            if(part == TOOLPART::HEAD)
            {
                headSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITY];
                headCount++;
            }
            else if(part == TOOLPART::EXTRA)
            {
                extraSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITY];
                extraCount++;
            }
            else if(part == TOOLPART::HANDLE)
            {
                handleSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITY];
                handleCount++;
                modifierSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITYMODIFIER];
                modifierCount++;
            }
            else if(part == TOOLPART::FLETCHLING)
            {
                fletchlingSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITYMODIFIER];
                fletchlingCount++;
            }
            else if(part == TOOLPART::SHAFT)
            {
                shaftSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITYMODIFIER];
                shaftCount++;
                shaftBonusSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::BONUSAMMO];
                shaftBonusCount++;
            }
            else if(part == TOOLPART::BOW)
            {}  //no durability stat
            else if(part == TOOLPART::BOWSTRING)
            {
                bowstringSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DURABILITYMODIFIER];
                bowstringCount++;
            }
            else
                throw "Not Implemented Exception (part "+toolPartToString[part]+")";
    
    double headAvg = headCount ? (headSum/headCount) : 0;
    double extraAvg = extraCount ? (extraSum/extraCount) : 0;
    double handleAvg = handleCount ? (handleSum/handleCount) : 0;
    double modifierAvg = modifierCount ? (modifierSum/modifierCount) : 1;
    double fletchlingAvg = fletchlingCount ? (fletchlingSum/fletchlingCount) : 1;
    double shaftAvg = shaftCount ? (shaftSum/shaftCount) : 1;
    double shaftBonusAvg = shaftBonusCount ? (shaftBonusSum/shaftBonusCount) : 0;
    double bowstringAvg = bowstringCount ? (bowstringSum/bowstringCount) : 1;
    
    double durability = ((headAvg + extraAvg) * modifierAvg * fletchlingAvg * shaftAvg + handleAvg + shaftBonusAvg) * bowstringAvg;
    
    //tool modifiers
    auto it = toolToToolModifiers[tool].find(TOOLPROPERTIES::DURABILITY);
    if(it != toolToToolModifiers[tool].end())
        for(pair<char,double> modifier : it->second)
        {
            if(modifier.first == '=')
                durability = modifier.second;
            else if(modifier.first == '+')
                durability += modifier.second;
            else if(modifier.first == '*')
                durability *= modifier.second;
            else
                throw string("Not Implemented Exception (")+modifier.first+")";
        }
    
    return durability;
}

const set<TRAIT> miningSpeedIgnoredTraits = { TRAIT::AUTOSMELT, TRAIT::BACONLICIOUS, TRAIT::BEHEADING, TRAIT::BREAKABLE, TRAIT::CHEAP, TRAIT::CHEAPSKATE, TRAIT::COLDBLOODED, TRAIT::CRUDE, TRAIT::CRUDEII, TRAIT::DURITAE, TRAIT::ECOLOGICAL, TRAIT::ENDERFERENCE, TRAIT::ENDSPEED, TRAIT::EVILAURA, TRAIT::EXPERIENCEBOOST, TRAIT::FLAMMABLE, TRAIT::FRACTURED, TRAIT::FREEZING, TRAIT::HELLISH, TRAIT::HOVERING, TRAIT::INSATIABLE, TRAIT::JAGGED, TRAIT::MAGICALLYBRITTLE, TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGNETIC, TRAIT::MAGNETICII, TRAIT::PETRAMOR, TRAIT::PRICKLY, TRAIT::SHARP, TRAIT::SLIMEY, TRAIT::SPIKY, TRAIT::SPLINTERING, TRAIT::SPLITTING, TRAIT::SQUEAKY, TRAIT::STALWART, TRAIT::SUPERHEAT, TRAIT::SYNERGY, TRAIT::TASTY, TRAIT::WHISPERING, TRAIT::WRITABLE, TRAIT::WRITABLEII, TRAIT::VEILED,
};
pair<double,double> getMiningSpeed()
{
    double miningSpeedSum = 0, miningSpeedCount = 0;
    int miningLevelMax = 0;
    vector<int> miningLevels;
    set<TRAIT> traits;
    
    //base mining speed
    for(int i = 0; i < toolParts->size(); i++)
        for(TOOLPART part : (*toolParts)[i]->parts)
        {
            if(part == TOOLPART::HEAD)
            {
                miningSpeedSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::MININGSPEED];
                miningSpeedCount++;
                int t = materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::MININGLEVEL];
                miningLevels.push_back(t);
                miningLevelMax = max(miningLevelMax, t);
            }
            else if(part==TOOLPART::EXTRA || part==TOOLPART::HANDLE || part==TOOLPART::SHAFT || part==TOOLPART::FLETCHLING || part==TOOLPART::BOW || part==TOOLPART::BOWSTRING)
            {}
            else
                throw "Not Implemented Exception (part "+toolPartToString[part]+")";
            
            //traits
            for(TRAIT trait : materialToolParts[curTool.materials[i]][part].second)
                traits.insert(trait);
        }
    
    double miningSpeedAvg = miningSpeedSum / miningSpeedCount;
    
    double toolSpeed = miningSpeedAvg;
    
    //tool modifiers
    auto it = toolToToolModifiers[tool].find(TOOLPROPERTIES::MININGSPEED);
    if(it != toolToToolModifiers[tool].end())
        for(pair<char,double> modifier : it->second)
        {
            if(modifier.first == '+')
                toolSpeed += modifier.second;
            else if(modifier.first == '*')
                toolSpeed *= modifier.second;
            else
                throw string("Not Implemented Exception (")+modifier.first+")";
        }
    
    it = toolToToolModifiers[tool].find(TOOLPROPERTIES::MININGLEVEL);
    if(it != toolToToolModifiers[tool].end())
        for(pair<char,double> modifier : it->second)
        {
            if(modifier.first == '=')
                miningLevelMax = materialToolParts[curTool.materials[modifier.second]][TOOLPART::HEAD].first[TOOLPROPERTIES::MININGLEVEL];
            else
                throw string("Not Implemented Exception (")+modifier.first+")";
        }

    double finalSpeed = toolSpeed;
    
    //traits
    if(useEmbossment)
        for(TOOLPART partTypes : curTool.embossment.part.parts)
            for(TRAIT trait : materialToolParts[curTool.embossment.material][partTypes].second)
                traits.insert(trait);
    for(TRAIT trait : traits)
    {
        if(trait == TRAIT::ALIEN)
        {
            finalSpeed += 1.862;
        }
        else if(trait == TRAIT::ARIDICULOUS)
        {
            finalSpeed += toolSpeed * ((pow(1.25, 3 * (0.5 + temperature - rainfall)) - 1.25) - rainfall/2) / 10;
        }
        else if(trait == TRAIT::AQUADYNAMIC)
        {
            finalSpeed += toolSpeed * rainfall/1.6;
        }
        else if(trait == TRAIT::CRUMBLING)
        {
            if(handBreakable)
                finalSpeed *= toolSpeed * 0.5;
        }
        else if(trait == TRAIT::LIGHTWEIGHT)
        {
            finalSpeed *= 1.1;
        }
        else if(trait == TRAIT::MOMENTUM)
        {
            finalSpeed += toolSpeed * 0.4;
        }
        else if(trait == TRAIT::PRECIPITATE)
        {
            finalSpeed += toolSpeed * (1-playerHealth);
        }
        else if(trait == TRAIT::STONEBOUND)
        {
            finalSpeed += log((getDurability()-1) / 72 + 1) * 2;
        }
        else if(trait == TRAIT::TWILIT)
        {
            if(inTwilight)
                finalSpeed += 2;
        }
        else if(trait == TRAIT::UNNATURAL)
        {
            if(blockLevel != -1 && miningLevelMax > blockLevel)
                finalSpeed += miningLevelMax - blockLevel;
        }
        else if(miningSpeedIgnoredTraits.count(trait))
        { }  //trait has no effect on mining speed
        else
            throw "Not Implemented Exception (trait "+traitToString[trait]+")";
    }
        
    return { toolSpeed, finalSpeed-toolSpeed };
}

const set<TRAIT> attackSpeedIgnoredTraits = { TRAIT::AQUADYNAMIC, TRAIT::AUTOSMELT, TRAIT::BACONLICIOUS, TRAIT::BEHEADING, TRAIT::BREAKABLE, TRAIT::CHEAP, TRAIT::CHEAPSKATE, TRAIT::COLDBLOODED, TRAIT::CRUDE, TRAIT::CRUDEII, TRAIT::DURITAE, TRAIT::ECOLOGICAL, TRAIT::ENDERFERENCE, TRAIT::ENDSPEED, TRAIT::EVILAURA, TRAIT::EXPERIENCEBOOST, TRAIT::FLAMMABLE, TRAIT::FRACTURED, TRAIT::FREEZING, TRAIT::HELLISH, TRAIT::HOVERING, TRAIT::INSATIABLE, TRAIT::JAGGED, TRAIT::MAGICALLYBRITTLE, TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGNETIC, TRAIT::MAGNETICII, TRAIT::PETRAMOR, TRAIT::PRICKLY, TRAIT::SHARP, TRAIT::SLIMEY, TRAIT::SPIKY, TRAIT::SPLINTERING, TRAIT::SPLITTING, TRAIT::SQUEAKY, TRAIT::STALWART, TRAIT::SUPERHEAT, TRAIT::SYNERGY, TRAIT::TASTY, TRAIT::WHISPERING, TRAIT::WRITABLE, TRAIT::WRITABLEII, TRAIT::VEILED, TRAIT::TWILIT, TRAIT::ALIEN, TRAIT::ARIDICULOUS, TRAIT::CRUMBLING, TRAIT::MOMENTUM, TRAIT::PRECIPITATE, TRAIT::STONEBOUND, TRAIT::UNNATURAL,
};
pair<double,double> getAttackSpeed()
{
    double attackSpeed = 1;
    double drawSpeedSum = 0, drawSpeedCount = 0;
    set<TRAIT> traits;
    
    //get traits
    for(int i = 0; i < toolParts->size(); i++)
        for(TOOLPART part : (*toolParts)[i]->parts)
        {
            if(part == TOOLPART::BOW)
            {
                drawSpeedSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::DRAWSPEED];
                drawSpeedCount++;
            }
            for(TRAIT trait : materialToolParts[curTool.materials[i]][part].second)
                traits.insert(trait);
        }
    
    double drawSpeedAvg = drawSpeedCount ? (1/(drawSpeedSum/drawSpeedCount)) : 1;
    double toolSpeed = attackSpeed * drawSpeedAvg;
    
    //tool modifiers
    auto it = toolToToolModifiers[tool].find(TOOLPROPERTIES::ATTACKSPEED);
    if(it != toolToToolModifiers[tool].end())
        for(pair<char,double> modifier : it->second)
        {
            if(modifier.first == '+')
                toolSpeed += modifier.second;
            else if(modifier.first == '*')
                toolSpeed *= modifier.second;
            else
                throw string("Not Implemented Exception (")+modifier.first+")";
        }
    
    double finalSpeed = toolSpeed;
    
    //traits
    if(useEmbossment)
        for(TOOLPART partTypes : curTool.embossment.part.parts)
            for(TRAIT trait : materialToolParts[curTool.embossment.material][partTypes].second)
                traits.insert(trait);
    for(TRAIT trait : traits)
    {
        if(trait == TRAIT::LIGHTWEIGHT)
        {
            finalSpeed *= 1.1;
        }
        else if(attackSpeedIgnoredTraits.count(trait))
        {}  //trait has no effect on attack speed
        else
            throw "Not Implemented Exception (trait "+traitToString[trait]+")";
    }
    
    return { toolSpeed, finalSpeed-toolSpeed };
}

const set<TRAIT> attackDamageIgnoredTraits = { TRAIT::AQUADYNAMIC, TRAIT::AUTOSMELT, TRAIT::BACONLICIOUS, TRAIT::BEHEADING, TRAIT::BREAKABLE, TRAIT::CHEAP, TRAIT::CHEAPSKATE, TRAIT::CRUMBLING, TRAIT::DURITAE, TRAIT::ECOLOGICAL, TRAIT::ENDERFERENCE, TRAIT::ENDSPEED, TRAIT::EVILAURA, TRAIT::EXPERIENCEBOOST, TRAIT::FLAMMABLE, TRAIT::FREEZING, TRAIT::HOVERING, TRAIT::LIGHTWEIGHT, TRAIT::MAGICALLYBRITTLE, TRAIT::MAGICALLYMODIFIABLE, TRAIT::MAGNETIC, TRAIT::MAGNETICII, TRAIT::MOMENTUM, TRAIT::PETRAMOR, TRAIT::PRECIPITATE, TRAIT::SHARP, TRAIT::SLIMEY, TRAIT::SPIKY, TRAIT::SPLITTING, TRAIT::STALWART, TRAIT::STONEBOUND, TRAIT::SYNERGY, TRAIT::TASTY, TRAIT::UNNATURAL, TRAIT::WHISPERING, TRAIT::WRITABLE, TRAIT::WRITABLEII, TRAIT::VEILED,
};
pair<double,double> getAttackDamage()
{
    double attackDamageSum = 0, attackDamageCount = 0;
    double bonusDamageSum = 0, bonusDamageCount = 0;
    set<TRAIT> traits;
    
    //base attack damage
    for(int i = 0; i < toolParts->size(); i++)
        for(TOOLPART part : (*toolParts)[i]->parts)
        {
            if(part == TOOLPART::HEAD)
            {
                attackDamageSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::ATTACKDAMAGE];
                attackDamageCount++;
            }
            else if(part == TOOLPART::BOW)
            {
                bonusDamageSum += materialToolParts[curTool.materials[i]][part].first[TOOLPROPERTIES::BONUSDAMAGE];
                bonusDamageCount++;
            }
            else if(part==TOOLPART::EXTRA || part==TOOLPART::HANDLE || part==TOOLPART::SHAFT || part==TOOLPART::FLETCHLING || part==TOOLPART::BOWSTRING)
            { }
            else
                throw "Not Implemented Exception (part "+toolPartToString[part]+")";
            
            //traits
            for(TRAIT trait : materialToolParts[curTool.materials[i]][part].second)
                traits.insert(trait);
        }
    
    double attackDamageAvg = attackDamageSum/attackDamageCount;
    double bonusDamageAvg = bonusDamageCount ? bonusDamageSum/bonusDamageCount : 0;
    double toolDamage = attackDamageAvg;
    
    //tool modifiers
    auto it = toolToToolModifiers[tool].find(TOOLPROPERTIES::ATTACKSPEED);
    if(it != toolToToolModifiers[tool].end())
        for(pair<char,double> modifier : it->second)
        {
            if(modifier.first == '+')
                toolDamage += modifier.second;
            else if(modifier.first == '*')
                toolDamage *= modifier.second;
            else
                throw string("Not Implemented Exception (")+modifier.first+")";
        }

    double finalDamage = toolDamage + bonusDamageAvg;
    
    //traits
    if(useEmbossment)
        for(TOOLPART partTypes : curTool.embossment.part.parts)
            for(TRAIT trait : materialToolParts[curTool.embossment.material][partTypes].second)
                traits.insert(trait);
    for(TRAIT trait : traits)
    {
        if(trait == TRAIT::ALIEN)
        {
            finalDamage += 1.33;
        }
        else if(trait == TRAIT::ARIDICULOUS)
        {
            finalDamage += ((pow(1.25, 3 * (0.5 + temperature - rainfall)) - 1.25) - rainfall/2) * 2;
        }
        else if(trait == TRAIT::COLDBLOODED)
        {
            if(targetFullHealth)
                finalDamage += toolDamage/2;
        }
        else if(trait == TRAIT::CRUDE)
        {
            finalDamage += toolDamage*0.05;
        }
        else if(trait == TRAIT::CRUDEII)
        {
            finalDamage += toolDamage*0.1;
        }
        else if(trait == TRAIT::FRACTURED)
        {
            finalDamage += 1.5;
        }
        else if(trait == TRAIT::HELLISH)
        {
            if(!targetfireimmune)
                finalDamage += 4;
        }
        else if(trait == TRAIT::INSATIABLE)
        {
            finalDamage += 10/3;
        }
        else if(trait == TRAIT::JAGGED)
        {
            finalDamage += log((getDurability()-1) / 72 + 1) * 2;
        }
        else if(trait == TRAIT::PRICKLY)
        {
            finalDamage += 1;
        }
        else if(trait == TRAIT::SPLINTERING)
        {
            finalDamage += 0.3 * (5+1);
        }
        else if(trait == TRAIT::SQUEAKY)
        {
            finalDamage = 0;
            toolDamage = 0;
        }
        else if(trait == TRAIT::SUPERHEAT)
        {
            if(targetOnFire)
                finalDamage += toolDamage * 0.35;
        }
        else if(trait == TRAIT::TWILIT)
        {
            if(!inTwilight)
                finalDamage += 2;
        }
        else if(attackDamageIgnoredTraits.count(trait))
        {}  //trait has no effect on mining speed
        else
            throw "Not Implemented Exception (trait "+traitToString[trait]+")";
    }
    
    return { toolDamage, finalDamage-toolDamage };
}

void selectToolPart(int index)
{
    if(index == toolParts->size() + (useEmbossment?1:0))
    {
        //evaluate tool
        if(target == OPTIMIZATIONTARGET::DURABILITY)
        {
            double curStat = getDurability();
            if(curStat > bestStat.first+bestStat.second)
            {
                bestStat.first = curStat;
                bestTool = curTool;
            }
        }
        else if(target == OPTIMIZATIONTARGET::MININGSPEED)
        {
            pair<double,double> curStat = getMiningSpeed();
            if(curStat.first+curStat.second > bestStat.first+bestStat.second)
            {
                bestStat = curStat;
                bestTool = curTool;
            }
        }
        else if(target == OPTIMIZATIONTARGET::ATTACKSPEED)
        {
            pair<double,double> curStat = getAttackSpeed();
            if(curStat.first+curStat.second > bestStat.first+bestStat.second)
            {
                bestStat = curStat;
                bestTool = curTool;
            }
        }
        else if(target == OPTIMIZATIONTARGET::ATTACKDAMAGE)
        {
            pair<double,double> curStat = getAttackDamage();
            if(curStat.first+curStat.second > bestStat.first+bestStat.second)
            {
                bestStat = curStat;
                bestTool = curTool;
            }
        }
        else if(target == OPTIMIZATIONTARGET::DPS)
        {
            pair<double, double> dmg = getAttackDamage();
            pair<double, double> spd = getAttackSpeed();
            double curStat = (dmg.first+dmg.second)*(spd.first+spd.second);
            if(curStat > bestStat.first)
            {
                bestStat.first = curStat;
                bestTool = curTool;
            }
        }
                
        return;
    }
    else if(index == toolParts->size() && useEmbossment)
    {
        //select embossment
        for(MATERIAL material : materials)
            for(namedToolPart* part : *toolParts)
            {
                bool valid = true;
                for(TOOLPART partType : part->parts)
                {
                    auto it = materialToolParts[material].find(partType);
                    if(it == materialToolParts[material].end())
                        valid = false;
                }
                if(valid)
                {
                    curTool.embossment = { *part, material };
                    selectToolPart(index + 1);
                }
            }
        return;
    }
    //select material
    int i = 0;
    for(MATERIAL material : materials)
    {
        if(verbose && index == 0)
            printf("%i/%lu\n", i++, materials.size());
        
        bool valid = true;
        for(TOOLPART partType : (*toolParts)[index]->parts)
        {
            auto it = materialToolParts[material].find(partType);
            if(it == materialToolParts[material].end())
                valid = false;
        }
        if(valid)
        {
            curTool.materials[index] = material;
            selectToolPart(index + 1);
        }
    }
    return;
}

void optimize()
{
    if(materials.size() == 0)
    {
        cout << "no materials selected" << endl;
        cout << "did you mean to use \"-m all\" ?" << endl;
        return;
    }
    
    toolParts = toolToToolparts.find(tool)->second;
    curTool.materials.resize(toolParts->size());
    
    if(verbose)
    {
        //tool
        cout << toolToString[tool] << endl;
        //toolparts
        
        for(auto toolpart : (*toolParts))
            cout << toolpart->name << ", ";
        cout << endl;
        //optimization target
        cout << optimTargetToString[target] << endl;
        //materials
        for(auto material : materials)
            cout << materialToString[material] << ", ";
        cout << endl;
        //embossment
        if(useEmbossment)
            cout << "embossment" << endl;
        cout << endl;
    }
    
    selectToolPart(0);
    
    //display results
    for(int i = 0; i < bestTool.materials.size(); i++)
                printf("%s %s\n", materialToString[bestTool.materials[i]].c_str(), (*toolParts)[i]->name.c_str());
            if(useEmbossment)
            {
                printf("%s %s Embossment\n", materialToString[bestTool.embossment.material].c_str(), bestTool.embossment.part.name.c_str());
            }
            if(bestStat.second == -1)
                printf("%f\n", bestStat.first);
            else
                printf("%f + %f\n", bestStat.first, bestStat.second);
}

void showHelp()
{
    cout << "usage: optimize [options] <tool> <optimization>" << endl;
    cout << endl;
    cout << "options:" << endl;
    printf("%-30s%s\n", "-e, --embossment", "Enables embossment");
    printf("%-30s%s\n", "-h, --help", "Shows this help");
    printf("%-30s%s\n", "-m, --material <material>", "Add a material to the material list");
    printf("%-30s%s\n", "-n <material>", "Remove a material to the material list");
    printf("%-30s%s\n", "-v, --verbose", "Additional program output");
    cout << "advanced options:" << endl;
    printf("%-30s%s\n", "--temperature <#>", "Biome temperature; range [-1,2]");
    printf("%-30s%s\n", "--rainfall <#>", "The amount of rain; range [0,2]");
    printf("%-30s%s\n", "--hand-breakable", "The target block can be broken by hand");
    printf("%-30s%s\n", "--player-health <#>", "The player's current health; range [0,1]");
    printf("%-30s%s\n", "--block-level <level>", "The mining level of the target block; level [stone|iron|diamond|obsidian|cobalt]");
    printf("%-30s%s\n", "--twilight", "The player is in the Twilight Forest");
    printf("%-30s%s\n", "--target-full-health", "The target is at full health");
    printf("%-30s%s\n", "--target-fire-immune", "The target is immune to fire");
    printf("%-30s%s\n", "--target-on-fire", "The target is on fire");
    
}

int main(int argc, char *argv[])
{
    //initialize
    initializeInverseMaps();
    vector<string> args(argc);
    for (size_t i = 0; i < argc; i++)
        args[i] = argv[i];
    
    //process input
    int reqParamIdx = 0;
    if(argc == 1)
    {
        showHelp();
        return 0;
    }
    for (size_t i = 1; i < argc; i++)
    {
        if(args[i] == "help")
        {
            showHelp();
            return 0;
        }
        else if(args[i].rfind("-", 0) == 0)  //starts with "-"
        {
            if(args[i] == "-h" || args[i] == "--help")
            {
                showHelp();
                return 0;
            }
            else if(args[i] == "-m" || args[i] == "--material")
            {
                //-m MATERIAL
                //-m all
                i++;
                if(i >= argc)
                {
                    cout << "missing parameter after -m" << endl;
                    return 1;
                }
                else if(args[i] == "all")
                    materials = allMaterials;
                else
                {
                    auto it = stringToMaterial.find(args[i]);
                    if(it != stringToMaterial.end())
                        materials.push_back(it->second);
                    else
                        printf("unrecognized tool \"%s\"\n", args[i].c_str());
                }
            }
            else if(args[i] == "-n")
            {
                //-n MATERIAL
                //-n all
                i++;
                if(i >= argc)
                {
                    cout << "missing parameter after -n" << endl;
                    return 1;
                }
                else if(args[i] == "all")
                    materials.clear();
                else
                {
                    auto it = stringToMaterial.find(args[i]);
                    if(it != stringToMaterial.end())
                        materials.erase(find(materials.begin(), materials.end(), it->second));
                    else
                        printf("unrecognized tool \"%s\"\n", args[i].c_str());
                }
            }
            else if(args[i] == "-e" || args[i] == "--embossment")
                useEmbossment = true;
            else if(args[i] == "-v" || args[i] == "--verbose")
                verbose = true;
            else if(args[i] == "--temperature")
                try {
                    i++;
                    if(i >= argc)
                    {
                        printf("not enought parameters\n");
                        return 0;
                    }
                    temperature = stod(args[i]);
                } catch (invalid_argument e) {
                    printf("\"%s\" not a valid temperature\n", args[i].c_str());
                    return 0;
                } catch (out_of_range e) {
                    printf("\"%s\" not a valid temperature\n", args[i].c_str());
                    return 0;
                }
            else if(args[i] == "--rainfall")
                try {
                    i++;
                    if(i >= argc)
                    {
                        printf("not enought parameters\n");
                        return 0;
                    }
                    rainfall = stod(args[i]);
                } catch (invalid_argument e) {
                    printf("\"%s\" not a valid rainfall\n", args[i].c_str());
                    return 0;
                } catch (out_of_range e) {
                    printf("\"%s\" not a valid rainfall\n", args[i].c_str());
                    return 0;
                }
            else if(args[i] == "--hand-breakable")
                handBreakable = true;
            else if(args[i] == "--player-health")
                try {
                    i++;
                    if(i >= argc)
                    {
                        printf("not enought parameters\n");
                        return 0;
                    }
                    playerHealth = stod(args[i]);
                } catch (invalid_argument e) {
                    printf("\"%s\" not a valid health\n", args[i].c_str());
                    return 0;
                } catch (out_of_range e) {
                    printf("\"%s\" not a valid health\n", args[i].c_str());
                    return 0;
                }
            else if(args[i] == "--block-level")
            {
                i++;
                if(i >= argc)
                {
                    printf("not enought parameters\n");
                    return 0;
                }
                auto it = stringToBlockLevel.find(args[i]);
                if(it == stringToBlockLevel.end())
                    printf("\"%s\" not a valid block level\n", args[i].c_str());
                blockLevel = it->second;
            }
            else if(args[i] == "--twilight")
                inTwilight = true;
            else if(args[i] == "--target-full-health")
                targetFullHealth = true;
            else if(args[i] == "--target-fire-immune")
                handBreakable = true;
            else if(args[i] == "--target-on-fire")
                handBreakable = true;
            else
                printf("unrecognized option \"%s\"\n", args[i].c_str());
        }
        else
        {
            if(reqParamIdx == 0)
            {
                //tool
                auto it = stringToTool.find(args[i]);
                if(it != stringToTool.end())
                    tool = it->second;
                else
                    printf("unrecognized tool \"%s\"\n", args[i].c_str());
                reqParamIdx++;
            }
            else if(reqParamIdx == 1)
            {
                //optimization
                auto it = stringToOptimTarget.find(args[i]);
                if(it != stringToOptimTarget.end())
                    target = it->second;
                else
                    printf("unrecognized optimization \"%s\"\n", args[i].c_str());
                reqParamIdx++;
            }
            else
                printf("extra argument \"%s\"\n", args[i].c_str());
        }
    }
    
    //calculate
    optimize();
    
    return 0;
}
