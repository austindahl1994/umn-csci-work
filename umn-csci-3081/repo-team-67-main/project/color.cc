#include "color.h"
#include <iostream>
#include <string>


using namespace std;

Color::Color(float r, float g, float b, float a): red(r), green(g), blue(b), alpha(a){

}

Color::Color(){}

int Color::Red(){
  return red;
}

int Color::Green(){
  return green;
}

int Color::Blue(){
  return blue;
}

int Color::Alpha(){
  return alpha;
}

void Color::operator=(const Color& c){
  red = c.red;
  green = c.green;
  blue = c.blue;
  alpha = c.alpha;
}

void Color::operator+(const Color& c){
  red += c.red;
  green += c.green;
  blue += c.blue;
}

void Color::operator*(float x){
  red *= x;
  green *= x;
  blue *= x;
}
