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
#include "bicicleta.h"
#include "scene.h"
#include "Frames.h"

int screenWidth = 800, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int keyPress; //variaveis globais do mouse para poder exibir dentro da render().
bool click = false;
Vector2 cL, cR;
int amountRays = 8;
float fps;

Bicicleta *bike;
Scene *scene;
Frames *frames;

void render()
{
    bike->render();
    scene->render();
    fps = frames->getFrames();
    scene->viewFrames(fps, screenWidth, screenHeight);
    scene->viewInstructions(screenWidth, screenHeight);
}

void keyboard(int key)
{
    ///Controla a velocidade da bicicleta e quantitade de raios
    switch(key){
    case 202:
        bike->vel += 0.01;
        scene->vel += 0.01;
        break;
    case 200:
        bike->vel -= 0.01;
        scene->vel -= 0.01;
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
}

int main(void)
{
    cL.set(200,200);
    cR.set(400,200);
    bike = new Bicicleta(amountRays, cL, cR, 50, 1);
    scene = new Scene();
    frames = new Frames();
    CV::init(&screenWidth, &screenHeight, "T3");
    CV::run();
    return 0;
}
