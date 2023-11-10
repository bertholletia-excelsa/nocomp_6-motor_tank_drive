#include <vex.h>
#include <dependent constants.h>
#include <helper functions.h>

// This struct contains every function that is necessarily driver-control specific.
// It does not need to exist, but I have it for organization.
// <drive control.h>
struct DriverControl {

    // Returns a modified x-position of the left joystick:
    // Rotates the joystick position STICK_OFFSET_DEG degrees counter-clockwise.
    // <driver control.h>
    double getTransformedLeftStickXPos(double rawXPos, double rawYPos) {
        double a = rawXPos * COS_STICK_OFFSET;
        double b = rawYPos * SIN_STICK_OFFSET;

        return a - b;
    }

    // Returns a modified y-position of the left joystick:
    // Rotates the joystick position STICK_OFFSET_DEG degrees counter-clockwise.
    // <drive control.h>
    double getTransformedLeftStickYPos(double rawXPos, double rawYPos) {
        double a = rawXPos * SIN_STICK_OFFSET;
        double b = rawYPos * COS_STICK_OFFSET;

        return a + b;
    }

    // Updates the velocity of each drivetrain motor once.
    // <driver control.h>
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
    // <driver control.h>
    void updateButtonPresses() {
        bool buttonYIsPressed = Controller.ButtonY.pressing();

        if (buttonYIsPressed && !buttonYWasPressed) {
            reverseDtDirection();
        }

        buttonYWasPressed = buttonYIsPressed;
    }
    
    // Updates all subsystems once.
    // <driver control.h>
    void updateRobot() {
        updateDrivetrain();
        updateButtonPresses();
    }
};