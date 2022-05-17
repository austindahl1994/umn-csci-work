#ifndef Image_H
#define Image_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include "color.h"

using namespace std;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Image class is used for loading and saving images, changing pixels in images.
  *
  */
class Image{
public:
 /**
  * @brief Image Constructor. Creates an image with width=256, height=256
  *
  */
  Image();

  /**
   * @brief Image constructor. Loads file to image and sets width, height, and components
   *
   * @param myString - name of the file
   */
  Image(const std::string& myString);

  ~Image() {};

  /**
   * @brief Copies image, width, heaight, component from parameter
   *
   */
  void operator=(const Image& o);

  /**
   * @brief Saves image to filename file
   *
   */
  void SaveAs(const std::string& filename);

  /**
   *
   * @return height of an image
   */
  int GetHeight();

  /**
   *
   * @return width of an image
   */
  int GetWidth();

  /**
   *
   * @return number of components of an image
   */
  int GetComponentNum();

  /**
  * @brief Gets a pixel based on width and height
  *
  * @param x - position of a pixel in the width of an image
  * @param y - position of a pixel in the height of an image
  *
  * @return pixel
  */
  Color GetPixel(int x, int y);


  /**
  * @brief Sets a new pixel to the indicated width and height
  *
  * @param x - position of a pixel in the width of an image
  * @param y - position of a pixel in the height of an image
  * @param c - new pixel
  */
  void SetPixel(int a, int b, Color c);

private:
 /**
  * @brief int values for width, height, components, and unsigned char* image
  *
  */
  int width, height, components=4;
  unsigned char* image;

};
#endif // Image_H
