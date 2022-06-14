#ifndef ___BEZIER__H___
#define ___BEZIER__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "gl_canvas2d.h"

#include "Vector2.h"

class BE
{
 public:
    //static std::vector<Vector2*> v;

    #if 0
    BE(std::vector<Vector2*> _v){
        this->v = _v;
    }
    #endif

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

    static void CurvaGrande(std::vector<Vector2*> v) {
       int lastP = 0;
       for (float t = 0; t < 1; t += 0.0001) {
          Vector2 p = *v[0]*((1-t)*(1-t)) + *v[1]*((2*t*(1-t))) + *v[2]*(t*t);

          if ((int) p.x != lastP)
             CV::line(p, Vector2(p.x,0));

          lastP = p.x;
       }
    }

};

#endif

