#include <iostream>
#include "drone.h"
#include "battery.h"
Drone::Drone(droneMovement* s){
    strategy = s;
}

Drone::~Drone(){
    delete strategy;
}

 void Drone::Update(float dt, float watts, float totalWeight){
     strategy->Move(position, dt, speed);
//     Battery(watts, totalWeight);
}
//battery in as well, facade looks at drone position vector, change position vector
//in drone it will move in simulation
//-------------------------------------------------------------------------------
// void WebApp::Update(double dt) {
//     // Updates the simulation.  This may be called multiple times per frame.

//     // Below is an example of how to use keyboard commands:
//     deleteThisDrone.SetJoystick(
//         IsKeyDown("ArrowRight") ? 1 : (IsKeyDown("ArrowLeft") ? -1 : 0),
//         IsKeyDown("w") ? 1 : (IsKeyDown("s") ? -1 : 0),
//         IsKeyDown("ArrowUp") ? -1 : (IsKeyDown("ArrowDown") ? 1 : 0),
//         IsKeyDown("a") ? 1 : (IsKeyDown("d") ? -1 : 0)
//     );

//     // Below is an example of how to update an entity.
//     // This code should be in the simulation facade, not here!
//     deleteThisDrone.Update(dt);
// }
