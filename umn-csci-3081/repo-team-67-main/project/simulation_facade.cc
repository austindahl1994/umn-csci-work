#include <iostream>
#include "simulation_facade.h"

// void Simulation::Update(float dt){
//     int id; double pos[3]; double dir[3]; double speed;
//     for (int i = 0; i < 3; i++) {
//            pos[i] += speed*dir[i]*dt;
//        }

//        // Take a picture every 5 seconds with front camera
//        time += dt;
//        if (time - oldTime > 5.0) {
//            cameras[0]->TakePicture();
//            oldTime = time;
//        }
// }

// void setMovement(float x, float y, float z){
//     dir[0] = x; dir[1] = y; dir[2] = z;
// }

// Simulation::~Simulation(){

// }
//to show actual movement
// void WebApp::FinishUpdate(picojson::object& returnValue) {
//     // Called after all updating is done.

//     // Below is an example of how to send the position and direction to the UI.
//     // In general you will want to loop through entities that have changed to update
//     // their position and direction:
//     picojson::object entity;
//     entity["entityId"] = picojson::value((double)0);

//     // Save the position as an array
//     picojson::array pos;
//     pos.push_back(picojson::value(deleteThisDrone.pos[0]));
//     pos.push_back(picojson::value(deleteThisDrone.pos[1]));
//     pos.push_back(picojson::value(deleteThisDrone.pos[2]));
//     entity["pos"] = picojson::value(pos);

//     // Save the direction as an array
//     picojson::array dir;
//     dir.push_back(picojson::value(deleteThisDrone.dir[0]));
//     dir.push_back(picojson::value(deleteThisDrone.dir[1]));
//     dir.push_back(picojson::value(deleteThisDrone.dir[2]));
//     entity["dir"] = picojson::value(dir);

//     // Send the compile picojson data to the UI in the returnValue variable
//     returnValue["entity"+std::to_string(deleteThisDrone.id)] = picojson::value(entity);
// }
