#include "gaussian-blur_filter.h"
#include "color.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter() {};

void GaussianBlurFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  int size =5;
  float sigma = 2.0;
  int x[2*size][2*size];
  int y[2*size][2*size];
  float g[2*size][2*size];
  float normal = 1.0 / (2.0 * M_PI * sigma*sigma);
  int i1 = 0;
  int j1 = 0;
  float ker = 0;
  for(int i= -1*size/2; i<size/2+1; i++){
    for(int j= -1*size/2; j<size/2+1; j++){
      x[i][j] = i;
      y[i][j] = j;
      float c = i*i + j*j;
      float k = exp(-(c / (2.0*sigma*sigma)));
      g[i1][j1] = normal*k;
      ker += g[i1][j1];
      j1++;
    }
    i1++;
    j1=0;
    std::cout << ker << '\n';
  }
  std::cout << ker << '\n';

  int w1 = original[0]->GetWidth();
  int h1 = original[0]->GetHeight();
  std::cout << w1 << '\n';
  std::cout << h1 << '\n';
  *filtered[0] = *original[0];

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixels = original[0]->GetPixel(w,h);
      pixels * ker;
      filtered[0]->SetPixel(w,h, pixels);
    }
  }


}
