#ifndef ___BEZIER__H___
#define ___BEZIER__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"

int xx = 0;
class BE
{
 public:


    static void CurvaSimples(std::vector<Vector2*> v){
        Vector2 p;
        CV::color(1);
        CV::translate(0,0);
            for(float t = 0; t < 1; t+=0.001){
                p = *v[0] * (1-t) * (1-t) +
                    *v[1] * 2 * t * (1-t) +
                    *v[2] * (t * t);
                CV::point(p.x,p.y);
            }
    }

    static void CurvaGrande(std::vector<Vector2*> v, bool vel) {
       Vector2 p;
       int size_v;
       size_v = v.size();
       CV::color(0);

       if(vel){
            xx ++;
       } else {
           xx --;
       }

       for(int i = 0; i < size_v; i+=3){
           for (float t = 0; t < 1; t += 0.0001) {
                p = *v[i] * (1-t)*(1-t) +
                    *v[i+1] * 2 * t * (1 - t) +
                    *v[i+2] * (t * t);
                    CV::point(p.x-xx,p.y);
           }
       }
    }

};

#endif

