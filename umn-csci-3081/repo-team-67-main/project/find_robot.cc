#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include "image.h"
#include "filter.h"
#include "blob_detection.h"
#include "find_robot.h"

using namespace std;

Find::Find(int position[3]){
  camera_position[0] = position[0];
  camera_position[1] = position[1];
  camera_position[2] = position[2];
}

float * Find::Find_1(std::vector<Image*> original){

  unique_ptr<Filter> f = unique_ptr<Filter>(new Blob_Detection(255, 161, 29));

  Image output;
  Image output1;
  std::vector<Image*> inputs;
  std::vector<Image*> outputs;
  inputs.push_back(original[0]); //original[0] - original image
  outputs.push_back(&output);
  outputs.push_back(&output1);
  f->Apply(inputs, outputs); //applying blob filter on original image

  float pos[3] = {-1, -1, -1};
  int w = original[0]->GetWidth();
  int h = original[0]->GetHeight();

  //finding strong pixels (robot pixels)
  for (int w1=0; w1<w; w1++){
    for (int h1=0; h1<h; h1++){
      Color pixel = output.GetPixel(w1,h1);
      if (pixel.Red()==255){
        pos[0] = w1;
        pos[1] = h1;
      }
    }
  }

  //return if filtered image does not have strong pixels
  if(pos[0]==-1){
    return pos;
  }

  Color pixel2 = original[1]->GetPixel(pos[0],pos[1]); //original[1] - depth image

  //Directional vector
  float r = (float(pixel2.Red())/255.0 - 0.5)*2;
  float g = (float(pixel2.Green())/255.0 - 0.5)*2;
  float b = (float(pixel2.Blue())/255.0 - 0.5)*2;

  float mdirvec = sqrt(r*r+g*g+b*b);

  //Distance
  float distance = (1.0 - mdirvec)*50;

  //Direction
  float drd = distance*r/mdirvec;
  float dgd = distance*g/mdirvec;
  float dbd = distance*b/mdirvec;

  //Pixel location
  pos[0] =  float(camera_position[0]) + drd;
  pos[1] =  float(camera_position[1]) + dgd;
  pos[2] =  float(camera_position[2]) + dbd;

  return pos;

}
