using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor motor_lf;
extern motor motor_lm;
extern motor motor_lb;
extern motor motor_rf;
extern motor motor_rm;
extern motor motor_rb;
extern motor motor_suc;
extern motor motor_lau;
extern controller Controller1;
extern digital_out indexer;
extern digital_out expansion;
extern inertial iner;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
