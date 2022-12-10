#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include "display.cpp"
#include "network.cpp"

int main()
{
    printf("hello from %s!\n", "CyberToothTigerVistionSystem");

    std::ifstream confFile; confFile.open("VisionSystem.conf");
    std::string confline;
    std::map<std::string, int> configParmsMap;

    configParmsMap["Network-IP"] = 1;
    string NetworkIPValue = "127.0.0.1";
    configParmsMap["Network-Port"] = 2;
    int NetworkPort = 9090;
    configParmsMap["Camera-LeftDevice"] = 3;
    int CameraLeftDevice = 1;
    configParmsMap["Camera-RightDevice"] = 4;
    int CameraRightDevice = 3;
    configParmsMap["Camera-Width"] = 5;
    int CameraWidth = 1280;
    configParmsMap["Camera-Hight"] = 6;
    int CameraHight = 720;

    if (confFile.is_open()) {
        while (confFile) {
            std::getline(confFile, confline);
            std::cout << confline << ": " << confFile.tellg() << '\n';

            //confline now contains the peramitor name and value
            int seperatorpos;
            if (confline.find_first_of(':', seperatorpos) != std::string::npos) {
                printf("invalid line in config file");
                printf(confline.c_str());
            }

            //split into permaiter and value
            string peramitor = confline.substr(0, seperatorpos);
            string value = confline.substr(seperatorpos, confline.size());
            //turn input into hashed int
            int configParmSwitch = configParmsMap.find(peramitor)->second;
            //switch on the peramiter
            switch (configParmSwitch) {
            case 1: // Network-IP
                NetworkIPValue = value;
                break; 
            case 2: // Network-Port
                NetworkPort = atoi(value.c_str());
                break;
            case 3: // Camera-LeftDevice
                CameraLeftDevice = atoi(value.c_str());
                break;
            case 4: // Camera-RightDevice
                CameraRightDevice = atoi(value.c_str());
                break;
            case 5: // Camera-Width
                CameraWidth = atoi(value.c_str());
                break;
            case 6: // Camera-Hight
                CameraHight = atoi(value.c_str());
                break;
            }
        }
    }

    vision();
    return 0;
}
