#ifndef __SCENE__H___
#define __SCENE__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "bezier.h"

class Scene
{
public:
    std::vector<Vector2*> montain;
    bool pass = true;

    void render(){
        if(pass == true){
            createMontain();
        }
        viewMontain();
    }

    void createMontain(){
        int tempyhigh,tempylow, tempx, xant= 0;
        for(int i= 0;i < 36; i+=3){
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
        BE::CurvaGrande(montain);
    }
};


#endif // __SCENE__H___
