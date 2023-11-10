#include <include all this stuff.h>

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

// Get Alvin's dad.
void getAlvinsDad() {
    return;
}

// Call initialize() at the beginning of your program.
// If nothing must be done before running the robot, leave this function body blank.
void initialize() {
    setLeftDtVel(0);
    setRightDtVel(0);
    setDtDirection(true);

    buttonYWasPressed = false;
}

int main() {
    initialize();
    DriverControl driverControl = DriverControl{};

    while (true) {
        driverControl.updateRobot();
        sleep();
    }
}