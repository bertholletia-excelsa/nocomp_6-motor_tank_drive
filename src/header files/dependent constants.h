#include <independent constants.h>
#include <math.h>

// The angle (clockwise) in radians that the left joystick must be held at to drive the robot straight.
// Radians are used because cos(double) and sin(double) take radians instead of degrees.
// <dependent constants.h>
const double STICK_OFFSET_RAD = M_PI * STICK_OFFSET_DEG / 180;

// The cosine of the left joystick's offset angle.
// It is used to calculate the inverse transformation of the offset.
// <dependent constants.h>
const double COS_STICK_OFFSET = cos(STICK_OFFSET_RAD);

// The sine of the left joystick's offset angle.
// It is used to calculate the inverse transformation of the offset.
// <dependent constants.h>
const double SIN_STICK_OFFSET = sin(STICK_OFFSET_RAD);

// The number of motors per side of the drivetrain.
// e.g. 6-motor drive: 3 motors per side.
// Change this value in the advent of a robot redesign that alters the number of drivetrain motors.
// <dependent constants.h>
const int MOTORS_PER_DT_SIDE = 3;