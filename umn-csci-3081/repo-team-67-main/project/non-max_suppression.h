#ifndef NONMAXSIPPRESSIONFILER_H
#define NONMAXSIPPRESSIONFILER_H
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
 * @brief non-max_supression filter
 *
 */
class NonMaxSuppressionFilter: public Filter{
public:
/**
  * @brief creation of non-max_supression filter
  */
  NonMaxSuppressionFilter();
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif // NonMaxSuppressionFilter_H
