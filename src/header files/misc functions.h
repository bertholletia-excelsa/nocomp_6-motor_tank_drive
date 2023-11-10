#include <vex.h>
#include <mutable constants.h>
#include <immutable constants.h>
#include <static variables.h>

// Returns a modification of num squared:
// If num is negative, then the return value will be negative.
// <misc functions.h>
double signedSquare(double num) {
    double square = num * num;

    return num < 0 ? -square : square;
}

// Returns a modification of the square root of num:
// If num is negative, then it will return -sqrt(-num).
// <misc functions.h>
double signedSqrt(double num) {
    return num < 0 ? -sqrt(-num) : sqrt(num);
}

// Put sleep() inside potentially infinite loops to prevent overheating.
// <misc functions.h>
void sleep() {
    this_thread::sleep_for(WAIT_TIME_MSEC);
}

// Set the velocity of the motors connected to the left drivetrain wheels.
// <misc functions.h>
void setLeftDtVel(double newVelocity) {
    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        leftDtMotors[i].setVelocity(newVelocity, percent);
    }
}

// Set the velocity of the motors connected to the right drivetrain wheels.
// <misc functions.h>
void setRightDtVel(double newVelocity) {
    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        rightDtMotors[i].setVelocity(newVelocity, percent);
    }
}

// Sets the direction that the robot will travel if the drivetrain has positive velocity:
// In the direction of the pusher if willFacePusher is true,
// In the opposite direction otherwise.
// <misc functions.h>
void setDtDirection(bool willFacePusher) {
    directionType dir = willFacePusher ? directionType::fwd : directionType::rev;

    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        leftDtMotors[i].spin(dir);
        rightDtMotors[i].spin(dir);
    }

    facingPusher = willFacePusher;
}

// Reverses the direction of the drivetrain.
// <misc functions.h>
void reverseDtDirection() {
    setDtDirection(!facingPusher);
}