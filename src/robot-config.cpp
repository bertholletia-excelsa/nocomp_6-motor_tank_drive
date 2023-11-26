#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller = controller(primary);
motor LeftDtMotor1 = motor(PORT1, ratio6_1, false);
motor LeftDtMotor2 = motor(PORT2, ratio6_1, false);
motor RightDtMotor1 = motor(PORT4, ratio6_1, true);
motor RightDtMotor2 = motor(PORT5, ratio6_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}