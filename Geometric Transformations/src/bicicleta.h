#ifndef ___BICICLETA__H___
#define ___BICICLETA__H___

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "bezier.h"


class raios {
public:
    Vector2 p1[32];
    Vector2 p2[32];
};

class Bicicleta
{
public:
    Vector2 aros[8], arosTrans[8], pedalLeft[2], pedalRight[2];
    std::vector<Vector2*> v;
    Vector2 centerLeft, centerRight;
    int x, y, amountRays;
    float ang = 0.0, rayCircle;
    raios *raysLeft = new raios();
    raios *raysRight = new raios();
    Vector2 tranraysleft1[8], tranraysleft2[8];
    float speed = 0.0;
    double scale;

    Bicicleta(){
    }

    Bicicleta(int _amountRays, Vector2 _centerLeft, Vector2 _centerRight, float _rayCircle, double _scale){
        this->amountRays = _amountRays;
        this->centerLeft.set(_centerLeft.x, _centerLeft.y);
        this->centerRight.set(_centerRight.x, _centerRight.y);
        this->rayCircle = _rayCircle;
        this->scale = _scale;
    }

    void render(){
        CreateRays();
        DrawRays();
        DrawBike();
    }

    void DrawBike(){
        ///Quadro
        CV::color(1,0,0);
        CV::translate(0,0);
        ///linha baixo
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2);
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle);
        ///linha cima
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle);
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle);
        ///guidao
        CV::line(centerRight.x, centerRight.y, centerRight.x-rayCircle/2-rayCircle-(rayCircle/5), centerRight.y+rayCircle*2);
        ///ferro e banco
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2,(centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/7, centerLeft.y+rayCircle+rayCircle/4);
        ///banco
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/3, centerLeft.y+rayCircle+rayCircle/4, (centerRight.x-centerLeft.y)/3 + centerLeft.x+rayCircle/5, centerLeft.y+rayCircle+rayCircle/4);
        ///pedal
        pedalLeft[1].set((centerRight.x-centerLeft.y)/2 + centerLeft.x -rayCircle/2, centerLeft.y-rayCircle/2);
        pedalLeft[0].set((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2);
        pedalRight[0].set((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2);
        pedalRight[1].set((centerRight.x-centerLeft.y)/2 + centerLeft.x +rayCircle/2, centerLeft.y-rayCircle/2);
        CV::color(0);
        //CV::line(pedalRight[0],pedalRight[1]);
        CV::color(0.5,0.5,0.5);
        CV::circleFill((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2,10,10);
        CV::color(0);
        CV::circleFill((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2,4,10);
        //CV::line(pedalLeft[0],pedalLeft[1]);

        v.push_back(new Vector2(this->centerRight.x, this->centerRight.y));
        v.push_back(new Vector2(this->centerRight.x + 100,this->centerLeft.y + 300));
        v.push_back(new Vector2(this->centerLeft.x, this->centerLeft.y));
        BE::CurvaSimples(v);
    }

    ///Cria os raios das rodas
    void CreateRays(){
        float radRot;
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            radRot = (((PI_2)/amountRays) * currentRay)+speed;
            this->raysLeft->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            this->raysRight->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            pedalLeft[1].set(cos(radRot) * (pedalLeft[1].x*scale), sin(radRot)*(pedalLeft[1].x*scale));
        }
        speed += 0.01;
    }

    void DrawRays(){
        CV::color(0,0,0);
        CV::translate(centerLeft);
        CV::circle(0,0, rayCircle*scale, 20);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysLeft->p1[currentRay],raysRight->p2[currentRay]);
            CV::line(pedalLeft[0],pedalLeft[1]);
        }
        CV::translate(centerRight);
        CV::circle(0,0, rayCircle*scale, 20);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysRight->p1[currentRay],raysRight->p2[currentRay]);
            //CV::line(pedalRight[0],pedalRight[1]);
        }

    }

};

#endif

