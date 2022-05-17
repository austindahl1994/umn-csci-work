#ifndef PATROL_H_
#define PATROL_H_
#include "drone_movement.h"


class Patrol : public droneMovement {

public:

    void Move(Vector3& position, float dt, float speed);

    Vector3 velocity;
    Vector3 step;
    Vector3 temp;
    float magnitude;
    Vector3 target;
    Vector3 direction;

// private:
//     Vector3 target;
        

};


#endif