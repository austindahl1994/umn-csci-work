#ifndef double_threshold_H
#define double_threshold_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "filter.h"
#include "image.h"
#include "color.h"
using namespace std;
/*Declare functions/attributes*/
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief double threshold filter
 *
 */
class DoubleThresholdFilter: public Filter {
public:
 /**
  * @brief Use of double threshold filter, input 2 thresholds, 2 color values
  *
  *
  */
    DoubleThresholdFilter(float highThreshold, float weakThreshold, Color strongPixel, Color weakPixel);

    ~DoubleThresholdFilter(){};

    void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

private:
 /**
  * @brief two ratios, use 0.1 and 0.2 as tests, two colors for the strong and weak tests
  *
  */
    float highThresholdRatio;
    float lowThresholdRatio;
    Color strong;
    Color weak;
};


#endif
