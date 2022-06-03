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
//  Instru��es:
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
#define M_PI           3.14159265358979323846  /* pi */


int screenWidth = 1176, screenHeight = 600; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
bool click = false;
int aresta = 60, raio = 3.5, centrocirc = 250, dist_aresta = 30;
int iniciox = 100, inicioy = 100;


Rect *rect;
Bicicleta *bike;

void render()
{
//    rect->Transf();
//    rect->render();

    bike->draw_wheel();

}

void keyboard(int key)
{
   if( key == 95 )
   {
      click == true;
   }
}

void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
printf("mx: %d, my: %d\n", x,y);
   mouseX = x;
   mouseY = y;

   if( state == 0 )
   {
       click = true;
   }

}

int main(void)
{
    rect = new Rect(100,100,50,50);

    CV::init(&screenWidth, &screenHeight, "testes");
    CV::run();
    return 0;
}