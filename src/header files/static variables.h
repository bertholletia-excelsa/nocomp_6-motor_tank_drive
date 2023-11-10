#include <vex.h>
#include <dependent constants.h>

// An array of all motors that are connected the left drivetrain wheels.
// <static variables.h>
motor leftDtMotors[MOTORS_PER_DT_SIDE] = {LeftDtMotor1, LeftDtMotor2, LeftDtMotor3};

// An array of all motors that are connected to the right drivetrain wheels.
// <static variables.h>
motor rightDtMotors[MOTORS_PER_DT_SIDE] = {RightDtMotor1, RightDtMotor2, RightDtMotor3};

// true if the robot's forward direction is toward its pushing side,
// false otherwise.
// <static variables.h>
bool facingPusher;

// true if the y button on the controller was depressed last call of DriverControl::updateRobot(),
// false otherwise.
// Its value is updated in DriverControl::updateButtonPresses().
// <static variables.h>
bool buttonYWasPressed;