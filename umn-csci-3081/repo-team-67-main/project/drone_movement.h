#ifndef Drone_Movement_
#define Drone_Movement_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

using namespace std;

struct Vector3 {
    float x, y, z;
};
//create own Vector3 class eventually with overload??
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief abstract drone movement class
 *
 */
class droneMovement {
public:
 /**
  * @brief uses move class to move drone using position passed by reference, time, and speed
  *
  *
  */
    virtual void Move(Vector3& position, float dt, float speed){};
    ~droneMovement(){};
    Vector3 direction;
    Vector3 target;
 /**
  * @brief time and speed variables
  *
  */
private:
    float dt, speed;
};

#endif