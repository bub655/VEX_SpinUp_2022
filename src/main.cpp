/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nikola Mazzola                                            */
/*    Created:      Monday September 10th 2022                                */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MotorLF              motor         11              
// MotorRF              motor         16              
// MotorLB              motor         13              
// MotorRB              motor         14              
// MotorSuction         motor         20              
// MotorFlick           motor         6               
// MotorLaunch          motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
vex::motor motor_lf(PORT11,vex::gearSetting::ratio18_1);
vex::motor motor_rf(PORT16,vex::gearSetting::ratio18_1);
vex::motor motor_lb(PORT13,vex::gearSetting::ratio18_1);
vex::motor motor_rb(PORT14,vex::gearSetting::ratio18_1);
vex::motor motor_suc(PORT20,vex::gearSetting::ratio18_1);
vex::motor motor_fli(PORT1,vex::gearSetting::ratio18_1);
vex::motor motor_lau(PORT15,vex::gearSetting::ratio18_1);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
//MOVEMENT
//move forwards or backwards with a given distance (in degrees) and a given speed (in rpm)
void ahead(double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  motor_lf.startRotateTo(num,deg,speed,rpm);
  motor_rf.startRotateTo(num,deg,speed,rpm);
  motor_lb.startRotateTo(num,deg,speed,rpm);
  motor_rb.startRotateTo(num,deg,speed,rpm);
  wait(10,msec);
}
//move sideways with a given distance (in degrees) and a given speed (in rpm)
void side(double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  motor_lf.startRotateTo(num,deg,speed,rpm);
  motor_rf.startRotateTo(-num,deg,speed,rpm);
  motor_lb.startRotateTo(-num,deg,speed,rpm);
  motor_rb.startRotateTo(num,deg,speed,rpm);
}
//move diagonally with a given direction (left/right), distance (in degrees), and a given speed (in rpm)
void diagonal(turnType dir,double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  if(dir==right){
    motor_lf.startRotateTo(num,deg,speed,rpm);
    motor_rb.startRotateTo(num,deg,speed,rpm);
  }
  if(dir==right){
    motor_rf.startRotateTo(num,deg,speed,rpm);
    motor_lb.startRotateTo(num,deg,speed,rpm);
  }
}
//turn about the center with a given direction (left/right), distance (in degrees), and a given speed (in rpm)
void turn(turnType dir,double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  if(dir==right){
    motor_lf.startRotateTo(num,deg,speed,rpm);
    motor_lb.startRotateTo(num,deg,speed,rpm);
    motor_rf.startRotateTo(-num,deg,speed,rpm);
    motor_rb.startRotateTo(-num,deg,speed,rpm);
  }
  if(dir==right){
    motor_lf.startRotateTo(-num,deg,speed,rpm);
    motor_lb.startRotateTo(-num,deg,speed,rpm);
    motor_rf.startRotateTo(num,deg,speed,rpm);
    motor_rb.startRotateTo(num,deg,speed,rpm);
  }
}
//ACCESSORY
//Activates the suction for a given time and speed
double rolltime = 1; //time to flip the roller
//creates a struct
struct suckargstype{
  double time;
  double speed;
};
//Main suction code
int suck(double time, double speed){
  motor_suc.rotateFor(time,sec,speed,rpm);
  return 0;
}
//Redirects the Suction task to the Main Suction code to be able to use parameters
int suck(void*args){
  suckargstype* suckargs = (suckargstype*)args;
  return suck(suckargs->time,suckargs->speed);
}

//Launches a number of discs
void launch(int num){
  motor_lau.startRotateFor(20,rev,600,rpm);
  for(int i=1;i<=num;i++){
    motor_fli.rotateTo(80,deg,true);
    wait(100,msec);
    motor_fli.rotateTo(0,deg,true);
    wait(100,msec);
  }
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  suck(1,200); //Depending on preload, transfers it to the holding bay
  wait(500,msec);
  launch(2); //Launches two discs to begin auton winpoint
  wait(500,msec);
  turn(right,90,100); //Turns towards roller
  suck(rolltime,50); //Turns the suction to be able to turn the rollers
  turn(left,135,100); //Turns back towards 4 discs parallel to main diagonal
  //creates a struct to allow the task to work while driving
  suckargstype suckargs;
  suckargs.time=10;
  suckargs.speed=200; 
  task Suction(suck, (void*)&suckargs); //enables the suction while driving
  ahead(1000,200); //drives along the diagonal to pick up 3 discs
  turn(right,45,100); //aims at the goal
  launch(3); //shoots three discs at the goal to allow for autonomous bonus
  //add more discs if time allows
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  
  // User control code here, inside the loop
    while (1) {
    //DRIVE CODE
    //get the controler inputs
    int ctrl_right = Controller1.Axis3.position(vex::percent);
    int ctrl_turn = Controller1.Axis4.position(vex::percent);
    int ctrl_fwd = Controller1.Axis1.position(vex::percent);

    //clip values close to 0
    const int deadband = 15;
    if(abs(ctrl_fwd)<deadband) ctrl_fwd=0;
    if(abs(ctrl_turn)<deadband) ctrl_turn=0;
    if(abs(ctrl_right)<deadband) ctrl_right=0;

    //Set drive motor values
    int drive_l_front = ctrl_fwd + ctrl_turn + ctrl_right;
    int drive_l_back  = ctrl_fwd - ctrl_turn - ctrl_right;
 
    int drive_r_front = ctrl_fwd + ctrl_turn - ctrl_right;
    int drive_r_back  = ctrl_fwd - ctrl_turn + ctrl_right;

    //Send final drive values
    motor_lf.spin( vex::forward, drive_l_front, vex::rpm );
    motor_lb.spin( vex::forward, drive_l_back , vex::rpm );
    motor_rf.spin( vex::forward, drive_r_front, vex::rpm );
    motor_rb.spin( vex::forward, drive_r_back , vex::rpm );

    Brain.Screen.clearScreen();
    Brain.Screen.print(Controller1.Axis3.position());
    Brain.Screen.print(Controller1.Axis1.position());

    //ACCESSORY
    //Spins the conveyor belt: L1 forward, L2 backward
    if(Controller1.ButtonL1.pressing()) motor_suc.spin(vex::forward,100,vex::percent);
    if(!Controller1.ButtonL1.pressing()&&!Controller1.ButtonL2.pressing()) motor_suc.stop(brake);
    if(Controller1.ButtonL2.pressing()) motor_suc.spin(vex::forward,-100,vex::pct);

    if(Controller1.ButtonR1.pressing()) launch(1);

    //Launches discs
    
    

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
