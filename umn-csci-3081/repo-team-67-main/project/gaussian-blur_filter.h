#ifndef GaussianBlurFilter_H
#define GaussianBlurFilter_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "filter.h"
#include "image.h"
#include <vector>
#include <cmath>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Gaussian-blur filter
 *
 */
class GaussianBlurFilter: public Filter{
public:
 /**
  * @brief Uses inheritance from filter for Apply for gaussian-blur filter
  *
  */
  GaussianBlurFilter();
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif // GaussianBlurFilter_H
