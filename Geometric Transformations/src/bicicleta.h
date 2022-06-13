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

    Vector2 Rot(Vector2 ponto){
        Vector2 pontoLine;
        ang += 0.01;
        pontoLine.x = ponto.x * cos (ang) - ponto.y * sin(ang);
        pontoLine.y = ponto.x * sin (ang) + ponto.y * cos(ang);
        return pontoLine;
    }

    Vector2 translate (Vector2 ponto, int x, int y){
        Vector2 verticep;

        verticep.x = ponto.x+x;
        verticep.y = ponto.y+y;
        return verticep;
    }

    void Transf(){
        Vector2 verticeTemp1, verticeTemp2;
        ///Pega os pontos, leva a origem, e translada de volta após a rotação
        for (int i = 0; i < 8; i++){
            verticeTemp1 = raysLeft->p1[i];
            ///-x e -y para retornar a origem
            verticeTemp1 = translate(verticeTemp1, -this->raysLeft->p1[i].x, -this->raysLeft->p1[i].y);
            verticeTemp1 = Rot(verticeTemp1);
            verticeTemp1 = translate(verticeTemp1, this->raysLeft->p1[i].x, this->raysLeft->p1[i].y);
            tranraysleft1[i] = verticeTemp1;
        }
        for (int i = 0; i < 8; i++){
            verticeTemp2 = raysLeft->p2[i];
            ///-x e -y para retornar a origem
            verticeTemp2 = translate(verticeTemp2, -this->raysLeft->p2[i].x, -this->raysLeft->p2[i].y);
            verticeTemp2 = Rot(verticeTemp2);
            verticeTemp2 = translate(verticeTemp2, this->raysLeft->p2[i].x, this->raysLeft->p2[i].y);
            tranraysleft2[i] = verticeTemp2;
        }
    }

    Vector2 RotateRays(float _rad, Vector2& _rayP1, Vector2& _rayP2){
        printf("ent\n");
        Vector2 rayTemp;
        float _x = (_rayP2.x - _rayP1.x) * cos(_rad) - (_rayP2.y - _rayP1.y) * sin(_rad) + _rayP1.x;
        float _y = (_rayP2.x - _rayP1.x) * sin(_rad) + (_rayP2.y - _rayP1.y) * cos(_rad) + _rayP1.y;
        rayTemp.x = _x;
        rayTemp.y = _y;
        printf("rayTemp: %. 2f | %.2f\n", rayTemp.x, rayTemp.y);
        return rayTemp;
    }

    ///Cria os raios das rodas
    void CreateRays(){
        float radRot;
        Vector2 tempLeftP1,tempLeftP2, tempRightP1, tempRightP2;
        ///Raio base cruzando diâmetro da roda
        this->raysLeft->p1[0].set(centerLeft.x - rayCircle, centerLeft.y);
        this->raysLeft->p2[0].set(centerLeft.x + rayCircle, centerLeft.y);
        this->raysRight->p1[0].set(centerRight.x - rayCircle, centerRight.y);
        this->raysRight->p2[0].set(centerRight.x + rayCircle, centerRight.y);
        printf("Left p1: %.2f . %.2f, Left p2: %.2f . %.2f \n", raysLeft->p1[0].x, raysLeft->p1[0].y, raysLeft->p2[0].x, raysLeft->p2[0].y);

        ///Cria outros raios rotacionando o raio base por ?graus
        for (int currentRay = 1;currentRay < amountRays ;currentRay ++){
            radRot = ((PI_2)/amountRays) * currentRay;
            //t1 = translate(raysLeft->p1[0], -this->rayCircle, -this->centerLeft.y);
            //t2 = translate(raysLeft->p2[0], -this->rayCircle, -this->centerLeft.y);
            //tempLeftP1 = translate(raysLeft->p1[0], -this->x, -this->y);
            tempLeftP1 = RotateRays(radRot, raysLeft->p1[0], raysLeft->p2[0]);
            tempRightP1 = RotateRays(radRot, raysRight->p1[0], raysRight->p2[0]);
            this->raysLeft->p1[currentRay].set(tempLeftP1.x, tempLeftP1.y);
            this->raysLeft->p2[currentRay].set(tempLeftP2.x, tempLeftP2.y);
            this->raysRight->p1[currentRay].set(tempRightP1.x, tempRightP1.y);
            this->raysRight->p2[currentRay].set(tempRightP2.x, tempRightP2.y);
            printf("Left p1: %.2f . %.2f, Left p2: %.2f . %.2f \n", raysLeft->p1[currentRay].x, raysLeft->p1[currentRay].y, raysLeft->p2[currentRay].x, raysLeft->p2[currentRay].y);

        }
        Transf();
    }

    void DrawRays(){
        CV::color(0,0,0);
        CV::translate(200,200);
        CV::circle(0,0, rayCircle, 20);
        CV::line(tranraysleft1[0],tranraysleft2[0]);
        CV::color(1);
        CV::line(tranraysleft1[1],tranraysleft2[1]);
        CV::color(2);
        CV::line(tranraysleft1[2],tranraysleft2[2]);
        CV::color(3);
        CV::line(tranraysleft1[3],tranraysleft2[3]);
        CV::color(4);
    /*    CV::line(tranraysleft1[4],tranraysleft2[4]);
        CV::color(5);
        CV::line(tranraysleft1[5],tranraysleft2[5]);
        CV::color(6);
        CV::line(tranraysleft1[6],tranraysleft2[6]);
        CV::color(7);
        CV::line(tranraysleft1[7],tranraysleft2[7]);
        CV::color(8);

        CV::line(raysLeft->p1[0],raysLeft->p2[0]);
        CV::color(1);
        CV::line(raysLeft->p1[1],raysLeft->p2[1]);
        CV::color(2);
        CV::line(raysLeft->p1[2],raysLeft->p2[2]);
        CV::color(3);
        CV::line(raysLeft->p1[3],raysLeft->p2[3]);
        CV::color(4);
        CV::line(raysLeft->p1[4],raysLeft->p2[4]);
        CV::color(5);
        CV::line(raysLeft->p1[5],raysLeft->p2[5]);
        CV::color(6);
        CV::line(raysLeft->p1[6],raysLeft->p2[6]);
        CV::color(7);
        CV::line(raysLeft->p1[7],raysLeft->p2[7]);
        CV::color(8);

        for (int currentRay = -1;currentRay < amountRays ;currentRay ++){
            CV::line(raysLeft->p1[currentRay],raysLeft->p2[currentRay]);
            CV::line(raysRight->p1[currentRay],raysRight->p2[currentRay]);
        }
*/
    }

};

#endif

