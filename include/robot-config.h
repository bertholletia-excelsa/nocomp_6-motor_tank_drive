using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller;
extern motor LeftDtMotor1;
extern motor LeftDtMotor2;
extern motor RightDtMotor1;
extern motor RightDtMotor2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );