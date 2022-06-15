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
// *********************************************************************/
///Implementações:
///-Desenho da bicicleta e personagem;
///-Animação de pedalar com posicionamento correto das pernas e pedais, e correta rotação das rodas;
///-Controle de FPS;
///-Curva de Bezier;
///-Ligação matematicamente correta entre o pedal e a perna.


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "geotrans.h"
#include "scene.h"
#include "Frames.h"

int screenWidth = 800, screenHeight = 588;//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int keyPress; //variaveis globais do mouse para poder exibir dentro da render().
bool click = false;
Vector2 cL, cR;
int amountRays = 8;
float fps;

GeoTrans *geotrans;
Scene *scene;
Frames *frames;

void render()
{
    geotrans->render();
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
        geotrans->vel += 0.01;
        scene->vel = true;
        break;
    case 200:
        geotrans->vel -= 0.01;
        scene->vel = false;
        break;
    case 43:
        geotrans->amountRays +=4;
        break;
    case 45:
        if(amountRays != 4){
            geotrans->amountRays -=4;
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
    geotrans = new GeoTrans(amountRays, cL, cR, 50, 1);
    scene = new Scene();
    frames = new Frames();
    CV::init(&screenWidth, &screenHeight, "T3");
    CV::run();
    return 0;
}
