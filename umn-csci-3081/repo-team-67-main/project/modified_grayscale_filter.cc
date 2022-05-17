#include "modified_grayscale_filter.h"
#include "color.h"

/*Talked with Dan, he said it was fine to change values and use as one 
of CP4 filters */

GreyScaleFilter::GreyScaleFilter() {};

void GreyScaleFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  int w1 = original[0]->GetWidth();
  int h1 = original[0]->GetHeight();

  *filtered[0] = *original[0];

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixels2 = filtered[0]->GetPixel(w,h);
      int L = 0.299*pixels2.Red() + 0.587*pixels2.Green() + 0.144*pixels2.Blue();
      Color pixels3(L, L, L, 255);
      filtered[0]->SetPixel(w,h, pixels3);
    }
  }
}