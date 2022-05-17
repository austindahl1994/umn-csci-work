#include "image.h"
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;

Image::Image(){
  width = 256;
  height = 256;
  image = new unsigned char[width*height*4];
}

Image::Image(const std::string& myString_1){
  char* myString = const_cast<char*>(myString_1.c_str());
	unsigned char *loadedImage = stbi_load(myString, &width, &height, &components, 0);
  image = new unsigned char[width*height*components];
	std::copy(loadedImage, loadedImage + width*height*components, image); // copy allows us to copy one byte array to another
  stbi_image_free(loadedImage);
}

void Image::operator=(const Image& o){
  width = o.width;
  height = o.height;
  components = o.components;
  image = new unsigned char[width*height*4];
  std::copy(o.image, o.image + o.width*o.height*o.components, image);
}

void Image::SaveAs(const std::string& f){
  char* fl = const_cast<char*>(f.c_str());
  stbi_write_png(fl, width, height, components, image, width*components);
}

int Image::GetHeight(){
  return height;
}

int Image::GetWidth(){
  return width;
}

int Image::GetComponentNum(){
  return components;
}

Color Image::GetPixel(int x, int y){
  unsigned char* pixel = &image[(y*width+x)*components];
  return Color((int) pixel[0], (int) pixel[1], (int) pixel[2], (int) pixel[3]);
}

void Image::SetPixel(int x, int y, Color pixel){

  unsigned char* pixels = &image[(y*width+x)*components];
  pixels[0] = pixel.Red();
  pixels[1] = pixel.Green();
  pixels[2] = pixel.Blue();
  pixels[3] = 255;
}
