#ifndef ___BICICLETA__H___
#define ___BICICLETA__H___

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gl_canvas2d.h"
#include "Vector2.h"

//raios *raiosDef;

class raios {
public:
    Vector2 p1[32];
    Vector2 p2[32];
};
//extern raios *raiosDef;

class Bicicleta
{
public:
    Vector2 aros[8], arosTrans[8];
    Vector2 centerLeft, centerRight;
    int x, y, amountRays;
    float ang = 0.0, rayCircle;
    raios *raysLeft = new raios();
    raios *raysRight = new raios();
    Vector2 tranraysleft1[8], tranraysleft2[8];
    float speed = 0.0;

    Bicicleta(){
    }

    Bicicleta(int _amountRays, Vector2 _centerLeft, Vector2 _centerRight, float _rayCircle){
        this->amountRays = _amountRays;
        this->centerLeft.set(_centerLeft.x, _centerLeft.y);
        this->centerRight.set(_centerRight.x, _centerRight.y);
        this->rayCircle = _rayCircle;
        printf("CenterLeft: %. 2f | %.2f\n", centerLeft.x, centerLeft.y);
    }

    void render(){
        CreateRays();
        DrawRays();
    }

    void DrawBike(){

    }

    ///Cria os raios das rodas
    void CreateRays(){
        float radRot;
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            radRot = (((PI_2)/amountRays) * currentRay)+speed;
            this->raysLeft->p2[currentRay].set(cos(radRot) * rayCircle, sin(radRot)*rayCircle);
            this->raysRight->p2[currentRay].set(cos(radRot) * rayCircle, sin(radRot)*rayCircle);
        }
        speed += 0.01;
    }

    void DrawRays(){
        CV::color(0,0,0);
        CV::translate(centerLeft);
        CV::circle(0,0, rayCircle, 20);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysLeft->p1[currentRay],raysRight->p2[currentRay]);
        }
        CV::translate(centerRight);
        CV::circle(0,0, rayCircle, 20);
        for (int currentRay = 0;currentRay < amountRays ;currentRay ++){
            CV::line(raysRight->p1[currentRay],raysRight->p2[currentRay]);
        }

    }

};

#endif

