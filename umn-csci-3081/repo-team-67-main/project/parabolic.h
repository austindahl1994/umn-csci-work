#ifndef PARABOLIC_H
#define PARABOLIC_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "drone_movement.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief parabolic class
 *
 */
class Parabolic {
public:
 /**
  * @brief Parabolic movement strategy, allows drone to fly in parabolic arc
  *
  *
  */
    Parabolic();

    ~Parabolic();

    void Move (Vector3& position, float dt);

    int T;
    float Y;
 /**
  * @brief Includes variables from optional lab for figuring out parabolic arc
  *
  */
private:
    Vector3 target, V, Vo, Vm, Vt, distance1, distance2, temp, step;
    float j = 265; //height of highest building??
};

#endif