#include "blob_detection.h"
#include "canny_edge_filter.h"
#include "color.h"
#include<memory>
Blob_Detection::Blob_Detection(int r, int g, int b) {
  red = float(r);
  green = float(g);
  blue = float(b);
};

void Blob_Detection::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  int r9 = red*0.9;
  int r11 = red*1.1;

  int g9 = green*0.9;
  int g11 = green*1.1;

  int b9 = blue*0.9;
  int b11 = blue*1.1;

  int w1 = original[0]->GetWidth();
  int h1 = original[0]->GetHeight();

  *filtered[0] = *original[0];

  int blob_pixels = 0;

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixel = filtered[0]->GetPixel(w,h);
      if ((r9<=pixel.Red() && pixel.Red()<=r11) && (g9<=pixel.Green() && pixel.Green()<=g11) && (b9<=pixel.Blue() && pixel.Blue()<=b11)){
        Color pixel2(255,255,255,255);
        filtered[0]->SetPixel(w,h, pixel2);
        blob_pixels += 1;
      }
      else{
        Color pixel2(0,0,0,255);
        filtered[0]->SetPixel(w,h, pixel2);
      }
    }
  }
  unique_ptr<Filter> f = unique_ptr<Filter>(new CannyEdgeFilter());
  std::vector<Image*> inputs;
  std::vector<Image*> outputs;
  inputs.push_back(filtered[0]);
  outputs.push_back(filtered[1]);
  f->Apply(inputs, outputs);

  int edge_pixels = 0;

  for (int w=0; w<w1; w++){
    for (int h=0; h<h1; h++){
      Color pixel3 = filtered[1]->GetPixel(w,h);
      if (pixel3.Red()==255){
        edge_pixels += 1;
      }
    }
  }

  float ratio = float(blob_pixels)/float(edge_pixels);
  if(ratio<10){
    for (int w=0; w<w1; w++){
      for (int h=0; h<h1; h++){
        Color pixel2(0,0,0,255);
        filtered[0]->SetPixel(w,h, pixel2);
      }
    }
  }
}
