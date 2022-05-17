
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include "image.h"
#include "filter.h"
#include "canny_edge_filter.h"
#include "color.h"
#include "non-max_suppression.h"
#include "gaussian-blur_filter.h"
#include "modified_grayscale_filter.h"
#include "color.h"
#include "sobel_filter.h"
#include "blob_detection.h"

CannyEdgeFilter::CannyEdgeFilter() {};

void CannyEdgeFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

  unique_ptr<Filter> f = unique_ptr<Filter>(new GreyScaleFilter());
  unique_ptr<Filter> f2 = unique_ptr<Filter>(new GaussianBlurFilter());
  unique_ptr<Filter> f3 = unique_ptr<Filter>(new SobelFilter());
  unique_ptr<Filter> f4 = unique_ptr<Filter>(new NonMaxSuppressionFilter());
  //Create input and output vectors
  Image output;
  Image output2;
  Image output3;
  Image output32;
  Image output4;
  Image output5;
  std::vector<Image*> inputs;
  std::vector<Image*> outputs;
  inputs.push_back(original[0]);
  outputs.push_back(&output);

  // Apply filter based on filter type
  f->Apply(inputs, outputs);

  std::vector<Image*> inputs2;
  std::vector<Image*> outputs2;
  inputs2.push_back(&output);
  outputs2.push_back(&output2);

  f2->Apply(inputs2, outputs2);

  // Save output image


  std::vector<Image*> inputs3;
  std::vector<Image*> outputs3;
  inputs3.push_back(&output2);
  outputs3.push_back(&output3);
  outputs3.push_back(&output32);

  f3->Apply(inputs3, outputs3);

  // Save output image

  std::vector<Image*> inputs4;
  std::vector<Image*> outputs4;
  inputs4.push_back(&output3);
  inputs4.push_back(&output32);
  outputs4.push_back(filtered[0]);

  f4->Apply(inputs4, outputs4);

}
