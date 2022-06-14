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
    Vector2 centerLeft, centerRight,centerPedal;
    int x, y, amountRays;
    float ang = 0.0, rayCircle;
    raios *raysLeft = new raios();
    raios *raysRight = new raios();
    Vector2 tranraysleft1[8], tranraysleft2[8];
    float speed = 0.0;
    double scale;
    float vel = 0.01;

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
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2, 4);
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle, 4);
        ///linha cima
        CV::line(centerLeft.x, centerLeft.y, (centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle, 4);
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x, centerLeft.y+rayCircle, centerRight.x-rayCircle+(rayCircle/5), centerRight.y+rayCircle, 4);
        ///guidao
        CV::line(centerRight.x, centerRight.y, centerRight.x-rayCircle/2-rayCircle-(rayCircle/5), centerRight.y+rayCircle*2, 4);
        ///ferro e banco
        CV::line((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2,(centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/7, centerLeft.y+rayCircle+rayCircle/4, 4);
        ///banco
        CV::color(0);
        CV::line((centerRight.x-centerLeft.y)/3 + centerLeft.x-rayCircle/3, centerLeft.y+rayCircle+rayCircle/4, (centerRight.x-centerLeft.y)/3 + centerLeft.x+rayCircle/5, centerLeft.y+rayCircle+rayCircle/4, 4);
        ///pedal
        centerPedal.set((centerRight.x-centerLeft.y)/2 + centerLeft.x, centerLeft.y-rayCircle/2);
        CV::color(0);
        CV::translate(0,0);
        CV::color(0.5,0.5,0.5);
        CV::circleFill(centerPedal,10,10);
        CV::color(0);
        CV::circleFill(centerPedal,4,10);
    }

    ///Cria os raios das rodas
    void CreateRays(){
        float radRot, radPedalLeft, radPedalRight;
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            radPedalLeft = (((PI_2*0.5)/amountRays) * currentRay)+speed;
            radPedalRight = (((PI_2*0)/amountRays) * currentRay)+speed;
            radRot = (((PI_2)/amountRays) * currentRay)+speed;
            this->raysLeft->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            this->raysRight->p2[currentRay].set(cos(radRot) * (rayCircle*scale), sin(radRot)*(rayCircle*scale));
            pedalLeft[1].set(cos(radPedalLeft) * (25*scale), sin(radPedalLeft)*(25*scale));
            pedalRight[1].set(cos(radPedalRight) * (25*scale), sin(radPedalRight)*(25*scale));
        }
        speed -= vel;
    }

    void DrawRays(){
        CV::color(0,0,0);
        CV::translate(centerLeft);
        CV::circle(0,0, rayCircle*scale, 20, 6);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysLeft->p1[currentRay],raysRight->p2[currentRay],2);
        }
        CV::translate(centerRight);
        CV::circle(0,0, rayCircle*scale, 20, 6);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysRight->p1[currentRay],raysRight->p2[currentRay],2);
        }
        CV::translate(centerPedal);
        for(int i = 0; i <2; i++){
            CV::line(pedalLeft[0],pedalLeft[1]);
            CV::line(pedalRight[0],pedalRight[1]);
        }

    }

};

#endif

