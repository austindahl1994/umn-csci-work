#include <iostream>
#include "parabolic.h"
#include <cmath>

Parabolic::~Parabolic(){};

void Parabolic::Move(Vector3& position, float dt){
    Vo = position;
    V = target;

//    Vm.x = (Vo.x - target.x) / 2;
    Vm.y = (Vo.y - target.y) / 2;
//    Vm.z = (Vo.z - target.z) / 2;

    T = dt;
    if ( T % 2 != 0){
        T++;
    }
    //type casting does same thing?

//    Vt.x = (Vo.x - V.x) / T;
    Vt.y = (Vo.y - V.y) / T;
//    Vt.z = (Vo.z - V.z) / T;

//    V.x = Vo.x + Vt.x * T;
    V.y = Vo.y + Vt.y * T;
//    V.z = Vo.z + Vt.z * T;

//    distance1.x = V.x - Vm.x;
    distance1.y = V.y - Vm.y;
    // distance1.z = V.z - Vm.z;
    // distance1.x = distance1.x * distance1.x;
    distance1.y = distance1.y * distance1.y;
    // distance1.z = distance1.z * distance1.z;

    // distance2.x = V.x - Vo.x;
    distance2.y = V.y - Vo.y;
    // distance2.z = V.z - Vo.z;
    // distance2.x = distance2.x * distance2.x;
    distance2.y = distance2.y * distance2.y;
    // distance2.z = distance2.z * distance2.z;

    // temp.x = 1 - (distance1.x / distance2.x) * j;
    temp.y = 1 - (distance1.y / distance2.y) * j;
    // temp.z = 1 - (distance1.z / distance2.z) * j;

    Y = temp.y;

    position.y = position.y + Y;
    //only need the y values?
};

// y = (1 - distance(V, Vm)2 / distance(Vo, Vm)2) * j (2)
//Vo is our source point - position
//V is the point we are moving to - target
// Vm is our midpoint equal to difference(source, destination) / 2
// T is the number of steps we are estimating = dt
// Vt is our step interval equal to difference(source, destination) / T

//alternatively can set height of y equal to 265m,
//5 meters higher than highest building on campus?

//j is peak height
//battery class, add to drone subtract time from battery
//if drone is dying too quickly, set it higher, give it infinite battery power!
