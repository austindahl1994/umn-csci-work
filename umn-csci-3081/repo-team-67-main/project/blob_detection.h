#ifndef BLOBDETECTION_H
#define BLOBDETECTION_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "filter.h"
#include "image.h"
#include <vector>
/*Declare functions/attributes*/
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Blob detection is used for detecting if there is an object with approximate RGB on image. Blob detection filter is used in Find.
 *
 */
class Blob_Detection: public Filter{
public:
  /**
   * @brief Blob_Detection constructor. Initializes RGB of an object.
   *
   */
  Blob_Detection(int r, int g, int b);
  /**
   * @brief Detects whether or not there is an object with RGB (+/-10%) is on the image.
   * Converts an original image to an image with strong and weak pixels based on RGB.
   * Uses Canny Edge filter to determine whether strong pixels are object pixels or not.
   *
   * @param original - original[0] (original image)
   * @param filtered - filtered[0] (stores filtered image after blob filter), filtered[1] (stores filtered image after canny edge filter)
   */
  virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);
private:
  /**
   * @brief RGB of an object, use 255, 161, 29 as test for orange color
   *
   */
  float red, green, blue;
};
#endif // BLOBDETECTION_H
