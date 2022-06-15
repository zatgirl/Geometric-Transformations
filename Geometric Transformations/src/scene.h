#ifndef __SCENE__H___
#define __SCENE__H___

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include "bezier.h"

class Scene
{
public:
    std::vector<Vector2*> montain;
    bool pass = true;
    float vel;

    void render(){
        if(pass == true){
            createMontain();
        }
        viewMontain();
    }

    void createMontain(){
        int tempyhigh,tempylow, tempx, xant= 0;
        for(int i= 0;i < 64; i+=3){
            tempyhigh = 0+rand()%350;
            montain.push_back(new Vector2(xant,350));
            tempx = 0+rand()%100;
            xant = xant+tempx;
            montain.push_back(new Vector2(xant,tempyhigh+350));
            tempx = 0+rand()%100;
            xant = xant+tempx;
            montain.push_back(new Vector2(xant,350));
        }
       pass = false;
    }
    void viewMontain(){
        BE::CurvaGrande(montain, vel);
    }

    void viewFrames(float fps, int screenWidth, int screenHeight){
        char* tempFtoChar = (char*)malloc(5);
        CV::color(1,1,0);
        CV::rectFill(0,screenHeight-22, 50, screenHeight);
        std::sprintf(tempFtoChar, "%.2f", fps);
        CV::color(0,0,0);
        CV::text(0,screenHeight-20, tempFtoChar);
    }

    void viewInstructions(int screenWidth, int screenHeight){
        CV::text(0, screenHeight-40, "[+] Adiciona raios na bicicleta");
        CV::text(0, screenHeight-60, "[-] Remove raios na bicicleta");
        CV::text(0, screenHeight-80, "[>] Aumenta velocidade");
        CV::text(0, screenHeight-100, "[<] Diminui velocidade");
    }
};


#endif // __SCENE__H___
