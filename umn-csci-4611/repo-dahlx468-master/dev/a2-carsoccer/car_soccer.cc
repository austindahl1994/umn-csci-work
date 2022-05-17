/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"


// Remember in C++, the .h file list all the functions and member variables that are part of the class!
// Look there first to understand what is part of the CarSoccer class, then look below to see how each
// function is implemented.


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // If you are having trouble driving the car with the keybaord, you can set this to true to use
    // the mouse instead.  The mouse controls are based on the postion of the mouse cursor on the window.
    // There is a "dead zone" in the middle of the window, and if you move the mouse up/down or left/right
    // outside of that zone, it is like pushing the up/down and/or left/right keys on the keyboard
    use_mouse_ = false;
        
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


void CarSoccer::OnMouseMove(const Point2& pos, const Vector2& delta)
{
    mouse_pos_ = PixelsToNormalizedDeviceCoords(pos);
}

void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        float x = rand() % 50;
        float y = rand() % 50;
        float z = rand() % 50;
        Vector3 test = Vector3(x, y, z);
        ball_.Reset(test);
    }
}

/// This is a little utility function that is helpful.  It treats the arrow keys like a joystick or D-pad on a game controller
/// and returns the direction you are pressing as a 2D vector, taking into account the fact that you might be holding
/// down more than one key at a time.
Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;

    if (use_mouse_) {
        // threshold defines the size of the "dead zone" in the middle of the screen
        // if the mouse's x,y position falls outside of this, then it is like pushing
        // the corresponding key on the keyboard
        const float threshold = 0.2f;
        dir[0] = 0;
        if (mouse_pos_[0] < -threshold) {
            dir[0] = -1;
        }
        else if (mouse_pos_[0] > threshold) {
            dir[0] = 1;
        }
        dir[1] = 0;
        if (mouse_pos_[1] < -threshold) {
            dir[1] = -1;
        }
        else if (mouse_pos_[1] > threshold) {
            dir[1] = 1;
        }
    }
    else {
        // the default user interface is to use the arrow keys on the keyboard.
        // like a D-pad on a game controller, you can hold more than one key down at a time if you want.
        if (IsKeyDown(GLFW_KEY_LEFT))
            dir[0]--;
        if (IsKeyDown(GLFW_KEY_RIGHT))
            dir[0]++;
        if (IsKeyDown(GLFW_KEY_UP))
            dir[1]++;
        if (IsKeyDown(GLFW_KEY_DOWN))
            dir[1]--;
    }

    return dir;
}

// dt is for "Delta Time", the elapsed time in seconds since the last frame
void CarSoccer::UpdateSimulation(double dt) {
    Vector2 dpad_dir = joystick_direction();
    std::cout << "D-Pad Direction: " << dpad_dir << std::endl;

    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball based on the elapsed time and checking for collisions.  Filling
    // in this routine is the main part of the assignment.

    // Example: This is not the "correct way" to drive the car, but this code
    // will at least move the car around for testing
    float metersPerSec = 10.0f;
    car_.set_position(car_.position() + metersPerSec * Vector3(dpad_dir[0], 0, -dpad_dir[1]) * dt);
    
}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    modelMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));
 
    // Set a background color for the screen (don't worry if you get a depricated warning on this line in OSX)
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    
    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {

    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);

    // Draw the car and the ball
    car_.Draw(quickShapes_, modelMatrix_, viewMatrix_, projMatrix_);
    ball_.Draw(quickShapes_, modelMatrix_, viewMatrix_, projMatrix_);
    
    // Draw the field with the field texture on it.
    Color col(16.0f/255.0f, 46.0f/255.0f, 9.0f/255.0f);
    Matrix4 M = Matrix4::Translation(Vector3(0.0f, -0.201f, 0.0f)) * Matrix4::Scale(Vector3(50.0f, 1.0f, 60.0f));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0.0f, -0.2f, 0.0f)) * Matrix4::Scale(Vector3(40.0f, 1.0f, 50.0f));
    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()
    int width, height;
    for (width = -10; width < 10; width++) {
        for (height = 0; height < 10; height++) {
            goal_Post.push_back(Point3(width, height, 0));
        }
        if (width != 9) { 
            goal_Post.push_back(Point3(width + 1, height - 1, 0)); 
        }
    }
    goal_Post.push_back(Point3(9, 0, 0));
    goal_Post.push_back(Point3(-10, 0, 0));

    Color goal_Top(0, 0, 1);
    Matrix4 goals1 = Matrix4::Translation(Vector3(0, 0, 50));
    quickShapes_.DrawLines(modelMatrix_ * goals1, viewMatrix_, projMatrix_, goal_Top, goal_Post, QuickShapes::LinesType::LINE_STRIP, 0.1);

    Color goal_Bot(1, 0, 0);
    Matrix4 goals2 = Matrix4::Translation(Vector3(0, 0, -50));
    quickShapes_.DrawLines(modelMatrix_ * goals2, viewMatrix_, projMatrix_, goal_Bot, goal_Post, QuickShapes::LinesType::LINE_STRIP, 0.1);

    short_Lines.push_back(Point3(-40, 0, 0));
    short_Lines.push_back(Point3(-40, 35, 0));
    short_Lines.push_back(Point3(40, 35, 0));
    short_Lines.push_back(Point3(40, 0, 0));
    short_Lines.push_back(Point3(-40, 0, 0));

    long_Lines.push_back(Point3(0, 0, 50));
    long_Lines.push_back(Point3(0, 35, 50));
    long_Lines.push_back(Point3(0, 35, -50));
    long_Lines.push_back(Point3(0, 0, -50));
    long_Lines.push_back(Point3(0, 0, 50));

    Matrix4 line1 = Matrix4::Translation(Vector3(0, 0, 50));
    Matrix4 line2 = Matrix4::Translation(Vector3(0, 0, -50));
    Matrix4 line3 = Matrix4::Translation(Vector3(-40, 0, 0));
    Matrix4 line4 = Matrix4::Translation(Vector3(40, 0, 0));

    quickShapes_.DrawLines(modelMatrix_ * line1, viewMatrix_, projMatrix_, Color(1, 1, 1), short_Lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_ * line2, viewMatrix_, projMatrix_, Color(1, 1, 1), short_Lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_ * line3, viewMatrix_, projMatrix_, Color(1, 1, 1), long_Lines, QuickShapes::LinesType::LINE_LOOP, 0.1);
    quickShapes_.DrawLines(modelMatrix_ * line4, viewMatrix_, projMatrix_, Color(1, 1, 1), long_Lines, QuickShapes::LinesType::LINE_LOOP, 0.1);


}
