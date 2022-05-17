#include "sobel_filter.h"
#include "color.h"
#include <cmath>

SobelFilter::SobelFilter() {};

void SobelFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  int kx[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
  int ky[3][3] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};

  int w1 = original[0]->GetWidth();
  int h1 = original[0]->GetHeight();
  *filtered[0] = *original[0];
  *filtered[1] = *original[0];

  int pixr[h1][w1];
  int pixg[h1][w1];
  int pixb[h1][w1];

  int maxr=0;
  int maxg=0;
  int maxb=0;

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixels = original[0]->GetPixel(w,h);
      Color ix(0,0,0,0);
      Color iy(0,0,0,0);
      for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
          if (w+i-1 >= 0 && h+j-1 >= 0 && w+i-1<w1 && h+j-1<h1){

            Color p = original[0]->GetPixel(w+i-1,h+j-1);

            Color px = p;
            Color py = p;

            px*kx[j][i];
            py*ky[j][i];

            ix + px;
            iy + py;
          }
        }
      }

      int rx=ix.Red()*ix.Red();
      int ry=iy.Red()*iy.Red();
      int r = sqrt(rx+ry);

      int gx=ix.Green()*ix.Green();
      int gy=iy.Green()*iy.Green();
      int g = sqrt(gx+gy);

      int bx=ix.Blue()*ix.Blue();
      int by=iy.Blue()*iy.Blue();
      int b = sqrt(bx+by);


      pixr[h][w] = r;
      pixg[h][w] = g;
      pixb[h][w] = b;

      if(r>maxr){
        maxr = r;
      }
      if(g>maxg){
        maxg = g;
      }
      if(b>maxb){
        maxb = b;
      }

      int ar =atan2(iy.Red(), ix.Red());
      int ag =atan2(iy.Green(), ix.Green());
      int ab =atan2(iy.Blue(), ix.Blue());
      Color pix(ar, ag, ab, pixels.Alpha());
      filtered[1]->SetPixel(w, h, pix);
    }

  }

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixels = original[0]->GetPixel(w,h);
      int r = (pixr[h][w]*255)/maxr;
      int g = (pixg[h][w]*255)/maxg;
      int b = (pixb[h][w]*255)/maxb;
      int a = pixels.Alpha();

      Color pixel1(r,g,b,a);
      filtered[0]->SetPixel(w,h, pixel1);
    }
  }


}
