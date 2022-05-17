#ifndef CannyEdgeFilter_H
#define CannyEdgeFilter_H

#include <iostream>
#include "filter.h"
#include "image.h"
#include <vector>

class CannyEdgeFilter: public Filter{
public:
  CannyEdgeFilter();
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

};
#endif // CannyEdgeFilter_H
