#ifndef bee_line_
#define bee_line_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "drone_movement.h"
using namespace std;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief beeline class
 *
 */
class Beeline : public droneMovement {
public:
    Beeline();

    ~Beeline();

    void Move (Vector3& position, float dt, float speed);

    Vector3 temp;
    float magnitude;
    Vector3 velocity;
    Vector3 step;
    Vector3 direction;
/**
 * @brief contains Vector3 target which is the found robot
 *
 */
private:
    Vector3 target;
};

#endif