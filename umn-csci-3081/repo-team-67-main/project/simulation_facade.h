#ifndef SIMULATION_H
#define SIMULATION_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "drone.h"
#include "image_facade.h"
#include "simulation_facade.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief simulation facade would have moved the drone based on movement strategy, work with image facade
 *
 */
//web app::update and drone::update eventually
class Simulation {
public:
    void Update(double dt);

    void setMovement(double x, double y, double z);

    //std::vector<findRobot*> cameras;
    float oldTime = 0.0;
    float time = 0.0;

private:

};

#endif
