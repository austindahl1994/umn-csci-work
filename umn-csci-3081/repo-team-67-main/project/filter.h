#ifndef FILTER_H
#define FILTER_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "image.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The filter header file
 */

class Filter{
public:
 /**
  * @brief allow use of Apply for those that inherit from filter
  *
  */
  virtual ~Filter() {};
  virtual void Apply(std::vector<Image*> input, std::vector<Image*> output){
  };
};
#endif // Filter_H
