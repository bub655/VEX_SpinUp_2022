using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor MotorLF;
extern motor MotorRF;
extern motor MotorLB;
extern motor MotorRB;
extern motor MotorSuction;
extern motor MotorFlick;
extern motor MotorLaunch;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );