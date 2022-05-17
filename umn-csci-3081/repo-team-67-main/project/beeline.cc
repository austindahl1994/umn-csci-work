#include <iostream>
#include "beeline.h"
#include "drone_movement.h"
#include <cmath>
using namespace std;

Beeline::Beeline(){
    
};

void Beeline::Move(Vector3& position, float dt, float speed){
    // calculate direction d = A - D, how to get point A? Point A is Target from movement.h
    //normalize the direction
    //~~~~~~~~~~ all between is to normalize
    //all x, y, z squared, then add together, take square root, add to vector3 getmagnitude
    //divide x, y, z direction vector each by magnitude, now normalized
    //5 4 3, 25 16 9, 50, magn = ~7
    //~~~~~~~~~~

    //calculate the velocity of drone, v = normalized_direction*speed
    //Calculate the distance traveled over time step, step = v*dt
    //Move drone using eularian integration, position = position + step
    //position = position + (velocity * dt) or step

    //CREATE VECTOR3 CLASS WITH OVERLOAD OPERATORS

    //calculating normalized vector
    direction.x = target.x - position.x;
    direction.y = target.y - position.y;
    direction.z = target.z - position.z;

    temp.x = direction.x * direction.x;
    temp.y = direction.y * direction.y;
    temp.z = direction.z * direction.z;

    magnitude = temp.x + temp.y + temp.z;
    magnitude = sqrt(magnitude);

    direction.x = direction.x / magnitude;
    direction.y = direction.y / magnitude;
    direction.z = direction.z / magnitude;

    //calculate velocity
    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
    velocity.z = direction.z * speed;

    //calculate distance traveled over time step
    step.x = velocity.x * dt;
    step.y = velocity.y * dt;
    step.z = velocity.z * dt;

    /*Vector3 operator+(Vector3 vec) {
        return Vector3(x + vec.x, y + vec.y, z + vec.z);
    }*/
    
    position.x = position.x + step.x;
    position.y = position.y + step.y;
    position.z = position.z + step.z;
    
};

// for patrol to find instead target, target.x = position.x + 4; target.z = position.z + 4