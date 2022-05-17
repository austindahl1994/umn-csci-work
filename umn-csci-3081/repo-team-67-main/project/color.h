#ifndef COLOR_H
#define COLOR_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>

using namespace std;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Color class is used to store and make modification on pixels.
 *
 */
class Color{
public:
  /**
   * @brief Color constructor. Initializes RGBA of a pixel.
   *
   */
  Color(float red, float green, float blue, float alpha);


  Color();

  /**
   *
   * @return Red value of the pixel
   */
  int Red();

  /**
   *
   * @return Green value of a pixel
   */
  int Green();

  /**
   *
   * @return Blue value of the pixel
   */
  int Blue();

  /**
   *
   * @return Aplha value of the pixel
   */
  int Alpha();

  /**
   * @brief Copies RGBA from parameter
   *
   */
  void operator=(const Color& color);

  /**
   * @brief adds each term of RGBA by parameter
   *
   */
  void operator+(const Color& color);

  /**
   * @brief multiplies each term of RGBA by parameter
   *
   */
  void operator*(float x);

private:
  /**
   * @brief int values (0-255) of pixel in RGBA format
   *
   */
  int red=0;
  int green=0;
  int blue=0;
  int alpha=0;

};
#endif // Color_H
