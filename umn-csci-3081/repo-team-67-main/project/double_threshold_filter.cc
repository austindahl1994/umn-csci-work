#include <iostream>
#include "double_threshold_filter.h"
#include "color.h"

using namespace std;
/*Implement code*/

DoubleThresholdFilter::DoubleThresholdFilter(float high, float low, Color strongPixel, Color weakPixel){
    highThresholdRatio = high;
    lowThresholdRatio = low;
    strong = strongPixel;
    weak = weakPixel;
};

void DoubleThresholdFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){
    int w1 = original[0]->GetWidth();
    int h1 = original[0]->GetHeight();

    float maxPixel = 0;
    for (int w=0; w<w1; w++){
        for (int h=0; h<h1; h++){
            Color pixel = original[0]->GetPixel(w,h);
            if (pixel.Red() > maxPixel)
                maxPixel = pixel.Red();
        }
    }

    float highThreshold = maxPixel * highThresholdRatio;
    float lowThreshold = highThreshold * lowThresholdRatio;

    *filtered[0] = *original[0];
    Color zero (0, 0, 0, 255);
    for (int w=0; w<w1; w++){
        for (int h=0; h<h1; h++){
            Color pixel = original[0]->GetPixel(w,h);
            if (pixel.Red() >= highThreshold){
                filtered[0]->SetPixel(w, h, strong);
            }
            if (pixel.Red() < lowThreshold){
                filtered[0]->SetPixel(w, h, zero);
            }
            if (pixel.Red() <= highThreshold && pixel.Red() >= lowThreshold){
                filtered[0]->SetPixel(w, h, weak);
            }
        }
    }
}
