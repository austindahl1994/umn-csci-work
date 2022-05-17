/*
 * CSci-4611 Assignment #1 Text Rain
 */
/*Algerian font*/

/* Note: if Processing's video library does not support your particular combination of webcam and
   operating system, then the Sketch may hang in the setup() routine when the list of available
   image capture devices is requestd with "Capture.list()".  If this happens, you can skip all of
   the camera initilization code and just run in movie mode by setting the following global 
   variable to true. 
   
   If you having trouble accessing the cameara on a mac laptop due to a security issue.  Some
   students found this post helpful: 
   https://github.com/processing/processing-video/issues/134#issuecomment-664778394
 */
boolean forceMovieMode = false;

// Global vars used to access video frames from either a live camera or a prerecorded movie file
import processing.video.*;
String[] cameraModes;
Capture cameraDevice;
Movie inputMovie;
boolean initialized = false;


// Both modes of input (live camera and movie) will update this same variable with the lastest
// pixel data each frame.  Use this variable to access the new pixel data each frame!
PImage inputImage;

String str1 = "Hello World";
String word = "test";

float x;
float y;
float speed = 4; 

// Called automatically by Processing, once when the program starts up
void setup() {
  size(1280, 720);  
  PFont font;
  font = loadFont("testFont.vlw");
  textFont(font, random(12, 36));
  inputImage = createImage(width, height, RGB);
  x = random (width);
  if (!forceMovieMode) {
    println("Querying avaialble camera modes.");
    cameraModes = Capture.list();
    println("Found " + cameraModes.length + " camera modes.");
    for (int i=0; i<cameraModes.length; i++) {
      println(" " + i + ". " + cameraModes[i]); 
    }
    // if no cameras were detected, then run in offline mode
    if (cameraModes.length == 0) {
      println("Starting movie mode automatically since no cameras were detected.");
      initializeMovieMode(); 
    }
    else {
      println("Press a number key in the Processing window to select the desired camera mode.");
    }
  }
}

String s = "This is a test string seeing as strings from file would not load without errors";
int i = 0;
// Called automatically by Processing, once per frame
void draw() {
  //String[] s = loadStrings("textData.txt"); wasn't able to get this to work
  // start each frame by clearing the screen
  background(0);
    rect(20,20,55,55);
  if (!initialized) {
    // IF NOT INITIALIZED, DRAW THE INPUT SELECTION MENU
    drawMenuScreen();      
  }
  else {
    // IF WE REACH THIS POINT, WE'RE PAST THE MENU AND THE INPUT MODE HAS BEEN INITIALIZED


    // GET THE NEXT FRAME OF INPUT DATA FROM LIVE CAMERA OR MOVIE  
    if ((cameraDevice != null) && (cameraDevice.available())) {
      // Get image data from cameara and copy it over to the inputImage variable
      cameraDevice.read();
      inputImage.copy(cameraDevice, 0,0,cameraDevice.width,cameraDevice.height, 0,0,inputImage.width,inputImage.height);
    }
    else if ((inputMovie != null) && (inputMovie.available())) {
      // Get image data from the movie file and copy it over to the inputImage variable
      inputMovie.read();
      inputImage.copy(inputMovie, 0,0,inputMovie.width,inputMovie.height, 0,0,inputImage.width,inputImage.height);
    }


    // DRAW THE INPUTIMAGE ACROSS THE ENTIRE SCREEN
    // Note, this is like clearing the screen with an image.  It will cover up anything drawn before this point.
    // So, draw your text rain after this!
    set(0, 0, inputImage);


    // DRAW THE TEXT RAIN, ETC.
    // TODO: Much of your implementation code should go here.  At this point, the latest pixel data from the
    // live camera or movie file will have been copied over to the inputImage variable.  So, if you access
    // the pixel data from the inputImage variable, your code should always work, no matter which mode you run in.

    PFont font;
    font = createFont("Algerian-48.vlw",32); //not working for some reason???
    textFont(font);
    
    y +=speed;
    
    char c = 'A';
    if (s.charAt(i) == ' '){
      i++;
    }else{
      c = s.charAt(i);
    }
    
    text(c, x, y);
    if (i == 0) fill(136,145,120);
    if (y > height ){
    fill(random(255), random(255), random(255));
    x = random (width);
    speed = random(2, 10);
    y = 0;
    i++;
    if (s.length() == i){
      i = 0;
      }
    }
}
}


// Called automatically by Processing once per frame
void keyPressed() {
  if (!initialized) {
    // CHECK FOR A NUMBER KEY PRESS ON THE MENU SCREEN    
    if ((key >= '0') && (key <= '9')) { 
      int input = key - '0';
      if (input == 0) {
        initializeMovieMode();
      }
      else if ((input >= 1) && (input <= 9)) {
        initializeLiveCameraMode(input);
      }
    }
  }
  else {
    // CHECK FOR KEYPRESSES DURING NORMAL OPERATION
    // TODO: Fill in your code to handle keypresses here..
    if (key == CODED) {
      if (keyCode == UP) {
        // up arrow key pressed
      }
      else if (keyCode == DOWN) {
        // down arrow key pressed
      }
    }
    else if (key == ' ') {
      // spacebar pressed
    } 
  }
}



// Loads a movie from a file to simulate camera input.
void initializeMovieMode() {
  String movieFile = "TextRainInput.mov";
  println("Simulating camera input using movie file: " + movieFile);
  inputMovie = new Movie(this, movieFile);
  inputMovie.loop();
  initialized = true;
}


// Starts up a webcam to use for input.
void initializeLiveCameraMode(int cameraMode) {
  println("Activating camera mode #" + cameraMode + ": " + cameraModes[cameraMode-1]);
  cameraDevice = new Capture(this, cameraModes[cameraMode-1]);
  cameraDevice.start();
  initialized = true;
}


// Draws a quick text-based menu to the screen
void drawMenuScreen() {
  int y=10;
  text("Press a number key to select an input mode", 20, y);
  y += 40;
  text("O: Offline mode, test with TextRainInput.mov movie file instead of live camera feed.", 20, y);
  y += 40; 
  for (int i = 0; i < min(9,cameraModes.length); i++) {
    text(i+1 + ": " + cameraModes[i], 20, y);
    y += 40;
  }  
}
