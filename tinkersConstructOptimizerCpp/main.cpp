#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "main.h"

using namespace std;

//main parameters
TOOL tool;
vector<namedToolPart> toolParts;
OPTIMIZATIONTARGET target;
set<MATERIAL> materials;

//results
toolResult curTool, bestTool;

//options
bool useEmbossment = false;
bool verbose = false;

void selectToolPart(int index)
{
    if(index == toolParts.size() + (useEmbossment?1:0))
    {
        //evaluate tool
        cout << materialToString[curTool.materials.front()] << endl;
        return;
    }
    else if(index == toolParts.size() && useEmbossment)
    {
        //select embossment
        for(MATERIAL material : materials)
            for(namedToolPart part : toolParts)
            {
                bool valid = true;
                for(TOOLPART partType : part.parts)
                {
                    auto it = materialToolParts[material].find(partType);
                    if(it == materialToolParts[material].end())
                        valid = false;
                }
                if(valid)
                {
                    curTool.embossment = { part, material };
                    selectToolPart(index + 1);
                }
            }
        return;
    }
    //select material
    for(MATERIAL material : materials)
    {
        bool valid = true;
        for(TOOLPART partType : toolParts[index].parts)
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
    toolParts = toolToToolparts.find(tool)->second;
    curTool.materials.resize(toolParts.size());
    
    if(verbose)
    {
        //tool
        cout << toolToString[tool] << endl;
        //toolparts
        
        for(auto toolpart : toolParts)
            cout << toolpart.name << ", ";
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
    }
    
    selectToolPart(0);
}

void showHelp()
{
    cout << "usage: optimize [options] <tool> <optimization>" << endl;
    cout << endl;
    cout << "options:" << endl;
    printf("%-20s%s\n", "-e", "Enables embossment");
    printf("%-20s%s\n", "-m <material>", "Add a material to the material list");
    printf("%-20s%s\n", "-n <material>", "Remove a material to the material list");
    printf("%-20s%s\n", "-v, --verbose", "Additional program output");
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
            if(args[i].rfind("-m", 0) == 0)
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
                    materials.insert(allMaterials.begin(), allMaterials.end());
                else
                {
                    auto it = stringToMaterial.find(args[i]);
                    if(it != stringToMaterial.end())
                        materials.insert(it->second);
                    else
                        printf("unrecognized tool \"%s\"\n", args[i].c_str());
                }
            }
            else if(args[i].rfind("-n", 0) == 0)
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
                        materials.erase(it->second);
                    else
                        printf("unrecognized tool \"%s\"\n", args[i].c_str());
                }
            }
            else if(args[i].rfind("-e", 0) == 0)
            {
                //embossment
                useEmbossment = true;
            }
            else if(args[i].rfind("-v", 0) == 0 || args[i].rfind("--verbose", 0) == 0)
            {
                //embossment
                verbose = true;
            }
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
