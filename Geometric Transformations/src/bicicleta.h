#ifndef ___BICICLETA__H___
#define ___BICICLETA__H___

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gl_canvas2d.h"
#include "Vector2.h"


class raios {
public:
    Vector2 left;
    Vector2 right;
};
extern raios *raiosDef;

class Bicicleta
{
public:
   Vector2 aros[8], arosTrans[8];
   int x, y, amountRays;
   float ang = 0.0;


    Bicicleta(){
    }

    Bicicleta(int _amountRays){
        this->amountRays = _amountRays;
        raiosDef[32] = new raios;
        raios *raiosDef[32];
    }

    void render(){

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
        Vector2 verticeTemp;
        ///Pega os pontos, leva a origem, e translada de volta após a rotação
        for (int i = 0; i < 8; i++){
//            verticeTemp = vertices[i];
            ///-x e -y para retornar a origem
 //           verticeTemp = translate(verticeTemp, -this->x-largura, -this->y);
 //           verticeTemp = Rot(verticeTemp);
 //           verticeTemp = translate(verticeTemp, this->x+largura, this->y);
 //           verticesTrans[i] = verticeTemp;
        }
    }

    Vector2 RotateRays(float _rad, Vector2& _ray){
        Vector2 rayTemp;
        float _x = (_ray.x - _ray.x) * cos(_rad) - (_ray.y - _ray.y) * sin(_rad) + _ray.x;
        float _y = (_ray.x - _ray.x) * sin(_rad) + (_ray.y - _ray.y) * cos(_rad) + _ray.y;
        rayTemp.x = _x;
        rayTemp.y = _y;
        return rayTemp;
    }

    ///Cria os raios da bicicleta
    void CreateRays(Vector2 centro, float rayCircle){
        float radRot;
        ///Raio base cruzando diâmetro da roda
        arosDef[0]->left = (centro.x - rayCircle, centro.y);
        arosDef[0]->right = (centro.x + rayCircle, centro.y);
        ///Cria outros raios rotacionando o raio base por ?graus
        for (int currentRay = 1;currentRay < amountRays ;currentRay ++){
            radRot = ((PI/2)/amountRays) * currentRay;
            arosDef[currentRay].left  = (RotateRays(radRot, arosDef[0].left), RotateRays(radRot, arosDef[0].left));
            arosDef[currentRay].right = (RotateRays(radRot, arosDef[0].right), RotateRays(radRot, arosDef[0].right));
        }
    }

    void DrawRays(){
    }

};

#endif

