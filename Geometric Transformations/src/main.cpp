/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "rect.h"
#include "bicicleta.h"
#include "Bmp.h"
#include "Draw.h"
#include "scene.h"

#define M_PI           3.14159265358979323846  /* pi */

int screenWidth = 1176, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY, keyPress; //variaveis globais do mouse para poder exibir dentro da render().
bool click = false;
Vector2 cL, cR;
int amountRays = 8;

Rect *rect;
Bicicleta *bike;
Bmp *bmp;
Img *img;
Scene *scene;

void render()
{
    bike->render();
    scene->render();
}

void keyboard(int key)
{
    ///Controla a velocidade da bicicleta
    switch(key){
    case 202:
        bike->vel += 0.01;
        break;
    case 200:
        bike->vel -= 0.01;
        break;
    case 43:
        bike->amountRays +=4;
        break;
    case 45:
        if(amountRays != 4){
            bike->amountRays -=4;
        }
        break;
    }
}

void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   //printf("mx: %d, my: %d, key: $d\n", x,y,keyPress);
   mouseX = x;
   mouseY = y;

   if( state == 0 )
   {
       click = true;
   }
//
}

int main(void)
{

    unsigned char *data;
    bmp = new Bmp("..\Geometric Transformations\resources\scene.bmp");
    bmp->convertBGRtoRGB();
    data = bmp->getImage();
//    img = Img(bmp->getHeight(), bmp->getWidth(), 0,0,data);

    cL.set(200,200);
    cR.set(400,200);
    rect = new Rect(100,100,50,50);
    bike = new Bicicleta(amountRays, cL, cR, 50, 1);
    scene = new Scene();
    CV::init(&screenWidth, &screenHeight, "testes");
    CV::run();
    return 0;

}
