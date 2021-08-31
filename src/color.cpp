#include "color.h"

Color::Color(float r,float g,float b):Vector3(r,g,b){

}
  
float Color::red() const{return x;}
float Color::green() const{return y;}
float Color::blue() const{return z;}

