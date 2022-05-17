#ifndef Find_H
#define Find_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include "color.h"
#include "image.h"
#include "filter.h"

using namespace std;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Find class finds object on the image based on RGB
 */
class Find{
public:
 /**
  * @brief Constructor. Initializes the coordinates of camera_position.
  */
  Find(int position[3]);

  ~Find() {};
  /**
   * @brief finds an object on the image based on camera_position, image, and depth image
   *
   * @param original - original[0] (original image), original[1] (depth Image)
   * @return position of an object
   */
  float * Find_1(std::vector<Image*> original);

  /**
   * @brief camera position variable
   *
   */
private:
  float camera_position[3]={0,0,0};

};
#endif // Find_H
