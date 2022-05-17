#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "image.h"
#include "filter.h"
#include "canny_edge_filter.h"
#include "color.h"

using namespace std;

int main(int argc, const char* argv[]) {
    // Get input file, filter type, and output file from command line
    // argc = # of arguments
    // argv = an array of arguments
    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    unique_ptr<Filter> f = unique_ptr<Filter>(new CannyEdgeFilter());
    // Create input and output vectors
    Image input(inputFile);
    Image output;
    std::vector<Image*> inputs;
    std::vector<Image*> outputs;

    // Apply filter based on filter type
    f->Apply(inputs, outputs);

    // Save output image
    output.SaveAs(outputFile);
}
