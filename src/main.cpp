#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDtMotor1         motor         1               
// LeftDtMotor2         motor         2               
// LeftDtMotor3         motor         3               
// RightDtMotor1        motor         4               
// RightDtMotor2        motor         5               
// RightDtMotor3        motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

/*
* <INDEPENDENT CODE>
*/

/*
* <Independent constants>
*/

// The number of milliseconds waited when sleep() is called.
const int WAIT_TIME_MSEC = 22;

// The angle (clockwise) in degrees that the left joystick must be held at to drive the robot straight.
// 0 degrees means straight up (y=100).
const double STICK_OFFSET_DEG = 10;

/*
* </Independent constants>
*/

// The angle (clockwise) in radians that the left joystick must be held at to drive the robot straight.
// Radians are used because cos(double) and sin(double) take radians instead of degrees.
const double STICK_OFFSET_RAD = M_PI * STICK_OFFSET_DEG / 180;

// The cosine of the left joystick's offset angle.
// It is used to calculate the inverse transformation of the offset.
const double COS_STICK_OFFSET = cos(STICK_OFFSET_RAD);

// The sine of the left joystick's offset angle.
// It is used to calculate the inverse transformation of the offset.
const double SIN_STICK_OFFSET = sin(STICK_OFFSET_RAD);

// The number of motors per side of the drivetrain.
// e.g. 6-motor drive: 3 motors per side.
// Change this value in the advent of a robot redesign that alters the number of drivetrain motors.
const int MOTORS_PER_DT_SIDE = 3;

// An array of all motors that are connected the left drivetrain wheels.
motor leftDtMotors[MOTORS_PER_DT_SIDE] = {LeftDtMotor1, LeftDtMotor2, LeftDtMotor3};

// An array of all motors that are connected to the right drivetrain wheels.
motor rightDtMotors[MOTORS_PER_DT_SIDE] = {RightDtMotor1, RightDtMotor2, RightDtMotor3};

// true if the robot's forward direction is toward its pushing side,
// false otherwise.
bool facingPusher;

// true if the y button on the controller was depressed last call of DriverControl::updateRobot(),
// false otherwise.
// Its value is updated in DriverControl::updateButtonPresses.
bool buttonYWasPressed;

/*
* <Misc self-contained helper functions>
*/

// Returns a modification of num squared:
// If num is negative, then the return value will be negative.
double signedSquare(double num) {
    double square = num * num;

    return num < 0 ? -square : square;
}

// Returns a modification of the square root of num:
// If num is negative, then it will return -sqrt(-num).
double signedSqrt(double num) {
    return num < 0 ? -sqrt(-num) : sqrt(num);
}

/*
* </Misc self-contained helper functions>
*/

// Put sleep() inside potentially infinite loops to prevent overheating.
void sleep() {
    this_thread::sleep_for(WAIT_TIME_MSEC);
}

// Set the velocity of the motors connected to the left drivetrain wheels.
void setLeftDtVel(double newVelocity) {
    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        leftDtMotors[i].setVelocity(newVelocity, percent);
    }
}

// Set the velocity of the motors connected to the right drivetrain wheels.
void setRightDtVel(double newVelocity) {
    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        rightDtMotors[i].setVelocity(newVelocity, percent);
    }
}

// Sets the direction that the robot will travel if the drivetrain has positive velocity:
// In the direction of the pusher if willFacePusher is true,
// In the opposite direction otherwise.
void setDtDirection(bool willFacePusher) {
    directionType dir = willFacePusher ? directionType::fwd : directionType::rev;

    for (int i = 0; i < MOTORS_PER_DT_SIDE; i++) {
        leftDtMotors[i].spin(dir);
        rightDtMotors[i].spin(dir);
    }

    facingPusher = willFacePusher;
}

// Reverses the direction of the drivetrain.
void reverseDtDirection() {
    setDtDirection(!facingPusher);
}

// Call initialize() at the beginning of your program.
// If nothing must be done before running the robot, leave function body blank.
void initialize() {
    setLeftDtVel(0);
    setRightDtVel(0);
    setDtDirection(true);

    buttonYWasPressed = false;
}

/*
* <Driver control>
*/

// This struct contains every function that is necessarily driver-control specific.
// It does not need to exist, but I have it for organization.
struct DriverControl {

    // Returns a modified x-position of the left joystick:
    // Rotates the joystick position STICK_OFFSET_DEG degrees counter-clockwise.
    double getTransformedLeftStickXPos(double rawXPos, double rawYPos) {
        double a = rawXPos * COS_STICK_OFFSET;
        double b = rawYPos * SIN_STICK_OFFSET;

        return a - b;
    }

    // Returns a modified y-position of the left joystick:
    // Rotates the joystick position STICK_OFFSET_DEG degrees counter-clockwise.
    double getTransformedLeftStickYPos(double rawXPos, double rawYPos) {
        double a = rawXPos * SIN_STICK_OFFSET;
        double b = rawYPos * COS_STICK_OFFSET;

        return a + b;
    }

    // Updates the velocity of each drivetrain motor once.
    void updateDrivetrain() {
        double rawX = Controller.Axis4.position();
        double rawY = Controller.Axis3.position();

        double transformedX = getTransformedLeftStickXPos(rawX, rawY);
        double transformedY = getTransformedLeftStickYPos(rawX, rawY);

        double xSignedSquare = signedSquare(transformedX);
        double ySignedSquare = signedSquare(transformedY);

        double leftDtVel = signedSqrt(xSignedSquare + ySignedSquare);
        double rightDtVel = signedSqrt(xSignedSquare - ySignedSquare);

        setLeftDtVel(leftDtVel);
        setRightDtVel(rightDtVel);
    }

    // Calls specific functions if certain buttons were just pressed:
    // Y button on the controller: reverseDtDirection()
    void updateButtonPresses() {
        bool buttonYIsPressed = Controller.ButtonY.pressing();

        if (buttonYIsPressed && !buttonYWasPressed) {
            reverseDtDirection();
        }

        buttonYWasPressed = buttonYIsPressed;
    }
    
    // Updates all subsystems once.
    void updateRobot() {
        updateDrivetrain();
        updateButtonPresses();
    }
};

/*
* </Driver control>
*/

/*
* </INDEPENDENT CODE>
*/

int main() {
    initialize();
    DriverControl driverControl = DriverControl{};

    while (true) {
        driverControl.updateRobot();
        sleep();
    }
}