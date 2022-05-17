#ifndef DRONE_H
#define DRONE_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "drone_movement.h"
#include "image.h" //need new class from groupmate, findrobot??
#include "image_facade.h"
#include "simulation_facade.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief drone class
 *
 */
//web app::update and drone::update eventually
class Drone {

public:
 /**
  * @brief updates for movement and power used in watts
  *
  *
  */
    Drone(droneMovement* s);

    virtual ~Drone();

    virtual void Update(float dt, float watts, float totalWeight);

    float watts = 1000000000;
    float droneWeight = 20; //kilograms
    float batteryWeight = 0;//kilograms
    float totalWeight = droneWeight + batteryWeight;
    int numBatteries = 0;
 /**
  * @brief uses position, speed, time, and a movement strategy
  *
  */
private:
    Vector3 position {};
    float speed, time;
    droneMovement* strategy = nullptr;
};

#endif
