#ifndef SobelFilter_H
#define SobelFilter_H

#include <iostream>
#include "filter.h"
#include "image.h"
#include <vector>
#include <cmath>

class SobelFilter: public Filter{
public:
  SobelFilter();
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif // SobelFilter_H
