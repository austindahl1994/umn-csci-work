#ifndef IMAGE_FACADE_H
#define IMAGE_FACADE_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "drone.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief imageFacade class, would have updated the image seen for simulation facade if found robot
 *
 */
class imageFacade {
public:
    imageFacade();

    void Update(float dt);

    void TakePicture();

    ~imageFacade();

private:
    int id;
};

#endif
