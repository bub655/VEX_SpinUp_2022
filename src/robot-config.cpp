#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor motor_lf = motor(PORT4, ratio18_1, false);
motor motor_lm = motor(PORT5, ratio18_1, false);
motor motor_lb = motor(PORT6, ratio18_1, false);
motor motor_rf = motor(PORT7, ratio18_1, false);
motor motor_rm = motor(PORT8, ratio18_1, false);
motor motor_rb = motor(PORT9, ratio18_1, false);
motor motor_suc = motor(PORT11, ratio18_1, false);
motor motor_lau = motor(PORT13, ratio6_1, false);
controller Controller1 = controller(primary);
digital_out indexer = digital_out(Brain.ThreeWirePort.A);
digital_out expansion = digital_out(Brain.ThreeWirePort.B);
inertial iner = inertial(PORT15);

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
