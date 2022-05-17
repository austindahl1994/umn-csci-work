/**
 * @file non-max_suppression.cc
 *
 */


 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include "non-max_suppression.h"
#include "color.h"
#include <math.h>


NonMaxSuppressionFilter::NonMaxSuppressionFilter() {};

void NonMaxSuppressionFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  int w = original[0]->GetWidth();
  int h = original[0]->GetHeight();
  *filtered[0] = *original[1];
  std::cout << h << '\n';

  for(int h1=0; h1<h; h1++){
    for(int w1=0; w1<w; w1++){
      int q = 255;
      int r = 266;
      Color k = original[0]->GetPixel(w1, h1);
      //std::cout << k.Red()<<" "<<k.Green()<<" "<<k.Blue() << '\n';
      float angle = float(original[1]->GetPixel(w1, h1).Red()) * 180.0/M_PI;

      if (angle<0){
        angle += 180;
      }

      if ((0 <= angle < 22.5) || (157.5 <= angle && angle<= 180) && h1-1 >= 0  && h1+1<h1){
        q = original[0]->GetPixel(w1, h1+1).Red();
        r = original[0]->GetPixel(w1, h1-1).Red();
      }

      else if ((22.5 <= angle < 67.5) && w1-1 >= 0 && h1-1 >= 0 && w1+1<w && h1+1<h1){
        q = original[0]->GetPixel(w1+1, h1-1).Red();
        r = original[0]->GetPixel(w1-1, h1+1).Red();
      }

      else if ((67.5 <= angle < 112.5) && w1-1 >= 0 &&  w1+1<=w){
        q = original[0]->GetPixel(w1+1, h1).Red();
        r = original[0]->GetPixel(w1-1, h1).Red();
      }

      else if ((112.5 <= angle < 157.5) && w1-1 >= 0 && h1-1 >= 0 && w1+1<w && h1+1<h1){
        q = original[0]->GetPixel(w1-1, h1-1).Red();
        r = original[0]->GetPixel(w1+1, h1+1).Red();
      }

      if ((original[0]->GetPixel(w1, h1).Red() >= q) && (original[0]->GetPixel(w1, h1).Red() >= r)){
        Color pixels2 = original[0]->GetPixel(w1,h1);
        filtered[0]->SetPixel(w1,h1, pixels2);
      }
      else{
        Color pixel2(0,0,0,0);
        filtered[0]->SetPixel(w1,h1, pixel2);
      }
      std::cout << h1 << '\n';
    }


  }
};
