#ifndef GreyScaleFilter_H
#define GreyScaleFilter_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "filter.h"
#include "image.h"
#include <vector>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Slightly modified greyscale filter using CCIR 601
 *
 */
class GreyScaleFilter: public Filter{
public:
 /**
  * @brief creation of modified greyscalefilter and use with inheritance of Apply from filter
  */
  GreyScaleFilter();

  ~GreyScaleFilter(){};
  
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif // GreyScaleFilter_H