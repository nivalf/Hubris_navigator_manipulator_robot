#include "Constants.h"

const short int SPEED = 100;
const short int REDUCED_SPEED = 30;
const short int TURN_SPEED = 50;
// the percentage difference between the speed of the left and right motors when turning (LINE FOLLOWER)
const float STEERING_FACTOR = 0.2;
// the time in milliseconds that the robot will wait after turning before moving forward again
const short int STEERING_COOL_OFF_TIME = 30;

// CORRECTION_FACTOR is used to correct the speed of the left wheel (right moves faster than left)
const float CORRECTION_FACTOR = 1.09;
const float TURN_CORRECTION_FACTOR = 1.12;

// rotation of the wheel to move quarter of the circle circumference (while rotating on its axis)
const float ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE = 0.705;
// encoder difference for 90 degree turn
// one wheel will be +x and the other will be -x. Thus the * 2
const short int ENCODER_DIFF_FOR_90_DEGREE_ORIENTATION = 683 * 2;
const short int ORIENTATION_TURN_SPEED = 20;