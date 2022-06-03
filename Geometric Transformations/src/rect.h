#ifndef ___RECT__H___
#define ___RECT__H___

#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Vector2.h"

class Rect
{
public:
   Vector2 vertices[8], verticesTrans[8];
   int x, y, largura, altura, newx = 200, newy = 200;
   float ang = 0.0;

    Rect(int _x, int _y, int _largura, int _altura){
        x = _x;     largura = _largura;
        y = _y;     altura = _altura;

        vertices[0].set(x          , y);            vertices[4].set(x + largura/2          , y + altura/2);
        vertices[1].set(x + largura, y);            vertices[5].set(x + largura + largura/2, y + altura/2);
        vertices[2].set(x + largura, y + altura);   vertices[6].set(x + largura + largura/2, y + altura + altura/2);
        vertices[3].set(x          , y + altura);   vertices[7].set(x + largura/2          , y + altura + altura/2);

        verticesTrans[0] = vertices[0];             verticesTrans[4] = vertices[4];
        verticesTrans[1] = vertices[1];             verticesTrans[5] = vertices[5];
        verticesTrans[2] = vertices[2];             verticesTrans[6] = vertices[6];
        verticesTrans[3] = vertices[3];             verticesTrans[7] = vertices[7];
    }

    void render(){
        CV::color(1);
        CV::line(vertices[0], vertices[1]);
        CV::line(vertices[1], vertices[2]);
        CV::line(vertices[2], vertices[3]);
        CV::line(vertices[3], vertices[0]);
        CV::line(vertices[4], vertices[5]);
        CV::line(vertices[5], vertices[6]);
        CV::line(vertices[6], vertices[7]);
        CV::line(vertices[7], vertices[4]);
        CV::line(vertices[0], vertices[4]);
        CV::line(vertices[1], vertices[5]);
        CV::line(vertices[2], vertices[6]);
        CV::line(vertices[3], vertices[7]);

        CV::color(3);
        CV::line(verticesTrans[0], verticesTrans[1]);
        CV::line(verticesTrans[1], verticesTrans[2]);
        CV::line(verticesTrans[2], verticesTrans[3]);
        CV::line(verticesTrans[3], verticesTrans[0]);
        CV::line(verticesTrans[4], verticesTrans[5]);
        CV::line(verticesTrans[5], verticesTrans[6]);
        CV::line(verticesTrans[6], verticesTrans[7]);
        CV::line(verticesTrans[7], verticesTrans[4]);
        CV::line(verticesTrans[0], verticesTrans[4]);
        CV::line(verticesTrans[1], verticesTrans[5]);
        CV::line(verticesTrans[2], verticesTrans[6]);
        CV::line(verticesTrans[3], verticesTrans[7]);

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
            verticeTemp = vertices[i];
            ///-x e -y para retornar a origem
            verticeTemp = translate(verticeTemp, -this->x-largura, -this->y);
            verticeTemp = Rot(verticeTemp);
            verticeTemp = translate(verticeTemp, this->x+largura, this->y);
            verticesTrans[i] = verticeTemp;
        }
    }


};

#endif
