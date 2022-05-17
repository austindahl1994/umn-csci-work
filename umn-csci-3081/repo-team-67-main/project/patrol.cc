#include "patrol.h"
//#include<cstime>
#include<cstdlib>
#include <cmath>


void Patrol::Move(Vector3& position, float dt, float speed) {

    srand((unsigned int)time(NULL));
    float a = 10;
    for(int i = 0; i < 5;i++){
        target.x = (float(rand())/float((RAND_MAX)) * a);
        target.y = (float(rand())/float((RAND_MAX)) * a);
        target.z = (float(rand())/float((RAND_MAX)) * a);

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
        
        position.x = position.x + step.x;
        position.y = position.y + step.y;
        position.z = position.z + step.z;
    }
}