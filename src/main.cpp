/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Anav Bordia                                               */
/*    Created:      Monday September 10th 2022                                */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// motor_lf             motor         4               
// motor_lm             motor         5               
// motor_lb             motor         6               
// motor_rf             motor         7               
// motor_rm             motor         8               
// motor_rb             motor         9               
// motor_suc            motor         11              
// motor_lau            motor         13              
// Controller1          controller                    
// indexer              digital_out   A               
// expansion            digital_out   B               
// iner                 inertial      15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global i[nstances of motors and other devices here
/*
vex::motor motor_lf(PORT6,vex::gearSetting::ratio18_1);
vex::motor motor_rf(PORT7,vex::gearSetting::ratio18_1);
vex::motor motor_lb(PORT5,vex::gearSetting::ratio18_1);
vex::motor motor_rb(PORT4,vex::gearSetting::ratio18_1);
vex::motor motor_suc(PORT10,vex::gearSetting::ratio18_1);
vex::motor motor_fli(PORT11,vex::gearSetting::ratio18_1);
vex::motor motor_lau1(PORT13,vex::gearSetting::ratio6_1);
vex::motor motor_lau2(PORT14, vex::gearSetting::ratio6_1, false);
vex::motor_group motor_lau(motor_lau1, motor_lau2);
vex::motor motor_exp(PORT9,vex::gearSetting::ratio18_1);
vex::controller Controller1;
*/

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//VARIABLE DECLARATIONS
timer startTimer;
bool launcherCall = false;
bool launcherPressed = false;
bool launcherSpeed =  100;
bool launcherSpeedPressed = false;

char suctionCall = 'n';
bool suctionPressed1 = false;
bool suctionPressed2 = false;

bool driveLaunch = true;
bool drivePressed = false;

void pre_auton(void) {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
//MOVEMENT
//move forwards or backwards with a given distance (in degrees) and a given speed (in rpm)
void side(double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  motor_lf.startRotateTo(-num,deg,speed,rpm);
  motor_rf.startRotateTo(-num,deg,speed,rpm);
  motor_lb.startRotateTo(num,deg,speed,rpm);
  motor_rb.spinFor(num,deg,speed,rpm);
}
//move sideways with a given distance (in degrees) and a given speed (in rpm)
void ahead(double num,double speed){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  motor_lm.resetPosition();
  motor_rm.resetPosition();
  motor_lf.startRotateTo(-num,deg,speed,rpm);
  motor_rf.startRotateTo(num,deg,speed,rpm);
  motor_lm.startRotateTo(-num,deg,speed,rpm);
  motor_rm.startRotateTo(num,deg,speed,rpm);
  motor_lb.startRotateTo(-num,deg,speed,rpm);
  motor_rb.spinFor(num,deg,speed,rpm);
}

//move sideways with a given distance (in degrees) and a given speed (in rpm)
void ahead2(double time){
  motor_lf.resetPosition();
  motor_rf.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  motor_lf.rotateFor(forward, time, sec);
  motor_rf.rotateFor(forward, time, sec);
  motor_lb.rotateFor(forward, time, sec);
  motor_rb.spinFor(forward, time, sec);
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
  motor_lm.resetPosition();
  motor_rm.resetPosition();
  motor_lb.resetPosition();
  motor_rb.resetPosition();
  if(dir==right){
    num = -num;
  }
  motor_lf.startRotateTo(num, deg,speed,rpm);
  motor_lb.startRotateTo(num,deg,speed,rpm);
  motor_lm.startRotateTo(num,deg,speed,rpm);
  motor_lm.startRotateTo(num,deg,speed,rpm);
  motor_rf.startRotateTo(num,deg,speed,rpm);
  motor_rb.spinFor(num,deg,speed,rpm);
}

// void flick() {
//   indexer.set(true);
  
//   motor_fli.setVelocity(100, percent);
//   motor_fli.rotateTo(110,deg,true);
//   motor_fli.rotateTo(0,deg,true);
// }

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//ANAV AUTONS BELOW
//shoot2ez
// void autonomous(void) {
//   ahead(-120, 50);
//   wait(1, sec);
//   motor_suc.spin(reverse, 50, percent);
//   wait(0.3, sec);
//   motor_suc.stop();
//   ahead(100, 100);
//   turn(left, 25, 25);
//   motor_rf.stop(hold);
//   motor_lf.stop(hold);
//   motor_rb.stop(hold);
//   motor_lb.stop(hold);
//   motor_lau.spin(vex::forward, 65, vex::percent);
//   wait(3.7, sec);
//   flick();
//   wait(0.9, sec);
//   flick();
//   motor_lau.stop(coast);
//   turn(right, 360, 25);
// }

//shoot5ez
// void autonomous(void) {
//   ahead(-50, 50);
//   wait(1, sec);
//   motor_suc.spin(reverse, 50, percent);
//   wait(0.3, sec);
//   motor_suc.stop();
//   ahead(100, 100);
//   turn(left, 20, 25);
//   motor_rf.stop(hold);
//   motor_lf.stop(hold);
//   motor_rb.stop(hold);
//   motor_lb.stop(hold);
//   motor_lau.spin(vex::forward, 11, voltageUnits::volt);
//   wait(3.3, sec);
//   flick(); 
//   wait(0.9, sec);
//   flick();
//   motor_lau.stop(coast);            
//   turn(left, 540, 50);
//   ahead(-500, 150);
//   motor_suc.setVelocity(100, percent);
//   motor_suc.spin(forward);
//   ahead(-550, 80);
//   turn(right, 400, 75);
//   motor_lau.spin(vex::forward, 10, voltageUnits::volt);
//   wait(2.5, sec);
//   flick();
//   motor_lau.spin(vex::forward, 11, voltageUnits::volt);
//   wait(0.3, sec);
//   flick();
//   motor_lau.stop(coast);
// }

//shoot2long
// void autonomous(void) {
//   side(560, 100);
//   ahead(-160, 50);
//   wait(1, sec);
//   motor_suc.spin(reverse, 50, percent);
//   wait(0.3, sec);
//   motor_suc.stop();
//   ahead(100, 100);
//   turn(right, 90, 25);
//   motor_rf.stop(hold);
//   motor_lf.stop(hold);
//   motor_rb.stop(hold);
//   motor_lb.stop(hold);
//   motor_lau.spin(vex::forward, 11, volt);
//   wait(3.7, sec);
//   flick();
//   wait(0.9, sec);
//   flick();
//   motor_lau.stop(coast);
// }

//shoot5long
// void autonomous(void) {
//   side(750, 200);
//   ahead(-120, 50);
//   wait(1, sec);
//   motor_suc.spin(reverse, 50, percent);
//   wait(0.3, sec);
//   motor_suc.stop();
//   ahead(100, 100);
//   turn(right, 25, 25);
//   motor_rf.stop(hold);
//   motor_lf.stop(hold);
//   motor_rb.stop(hold);
//   motor_lb.stop(hold);
//   motor_lau.spin(vex::forward, 65, vex::percent);
//   wait(3.7, sec);
//   flick();
//   wait(0.9, sec);
//   flick();
//   motor_lau.stop(coast);
//   turn(right, 100, 25);

// void autonomous(void) {
//   ahead(-100, 50);
//   turn(left, 360, 100);
//   motor_suc.spin(vex::fwd, 100, percent);
//   ahead(-50, 50);
//   motor_suc.stop(coast);
//   ahead(75, 50);
//   motor_lau.spin(vex::fwd, 100, percent);
//   turn(left, 720, 100);
//   motor_suc.spin(vex::fwd, 1000, percent);
//   indexer.set(true);
//   wait(65, msec);
//   indexer.set(false);
//   wait(300, msec);
//   indexer.set(true);
//   wait(65, msec);
//   indexer.set(false);
//   wait(300, msec);


//   // motor_suc.stop();
//   // turn(right, 180, 100);
//   // motor_lau.spin(vex::fwd, 100, percent);

// }

void autonomous(void) {
  motor_suc.spin(vex::forward, 25, percent);
  ahead(-100, 100);
  
  ahead(100, 50);
  motor_suc.stop();
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
  motor_lb.setVelocity(100, percent);
  motor_lf.setVelocity(100, percent);
  motor_rb.setVelocity(100, percent);
  motor_rf.setVelocity(100, percent);
  Controller1.Screen.clearScreen();
  Controller1.Screen.clearLine();
  Controller1.Screen.print("suction");

  while (1) {
  //DRIVE CODE
    

    //Set drive motor values
    if(Controller1.ButtonX.pressing()) {
      if(!drivePressed) {
        driveLaunch = !driveLaunch;
        drivePressed = true;
        Controller1.Screen.clearScreen();
        Controller1.Screen.clearLine();
        if(driveLaunch) {
          Controller1.Screen.print("suction");
        } else {
          Controller1.Screen.print("launcher");
        }
      }
    } else {
      drivePressed = false;
    }

    int forward = Controller1.Axis3.position(vex::percent);
    int turn = Controller1.Axis1.position(vex::percent);
    int sideways = Controller1.Axis4.position(vex::percent);

    if(driveLaunch) {
      forward = -forward;
      sideways = -sideways;
    }

    //Send final drive values
    motor_lf.spin( vex::forward, -forward + sideways + turn, percent);
    motor_lm.spin(vex::fwd, -forward + turn, percent);
    motor_lb.spin( vex::forward, -forward - sideways + turn, percent);
    motor_rf.spin( vex::forward, forward + sideways + turn, percent);
    motor_rm.spin(vex::fwd, forward + turn, percent);
    motor_rb.spin( vex::forward, forward - sideways + turn, percent);
    // motor_lf.spin( vex::forward, 0.75*(-forward + turn), percent);
    // motor_lm.spin(vex::fwd, 0.75*(-forward + turn), percent);
    // motor_lb.spin( vex::forward, 0.75*(-forward + turn), percent);
    // motor_rf.spin( vex::forward, 0.75*(forward + turn), percent);
    // motor_rm.spin(vex::fwd, 0.75*(forward + turn), percent);
    // motor_rb.spin( vex::forward, 0.75*(forward + turn), percent);

    if(forward == 0 && turn == 0) {
      motor_lb.stop(hold);
      motor_lf.stop(hold);
      motor_rb.stop(hold);
      motor_rf.stop(hold);
      motor_lm.stop(hold);
      motor_rm.stop(hold);
    } if(sideways != 0) {
      motor_lm.stop(coast);
      motor_rm.stop(coast);
    }
    //ACCESSORY
    //spins sucrtion forward, backward, and stops
    if(Controller1.ButtonL1.pressing()) {
      if(!suctionPressed1) {
        if(suctionCall == 'n') {
          suctionCall = 'f';
        } else {
          suctionCall = 'n';
        }
        suctionPressed1 = !suctionPressed1;
      }
    } else if(Controller1.ButtonL2.pressing()) {
      if(!suctionPressed1) {
        if(suctionCall == 'n') {
          suctionCall = 'b';
        } else {
          suctionCall = 'n';
        }
        suctionPressed1 = !suctionPressed1;
      }
    } else {
      suctionPressed1 = false;
      suctionPressed2 = false;
    }

    if(suctionCall == 'f') {
      motor_suc.spin(vex::forward, 100, percent);
    } else if (suctionCall == 'b') {
      motor_suc.spin(vex::reverse, 100, percent);
    } else {
      motor_suc.stop();
    }

    //starts the spinning motor to launch
    if(Controller1.ButtonR1.pressing()) {
      if(!launcherPressed) {
        // change the toggle state
        launcherCall = !launcherCall;
        // Note the button is pressed
        launcherPressed = true;
      }
    } else {
      // the button is not pressed
      launcherPressed = false;
    }

    if(launcherCall) {
      motor_lau.setVelocity(100, percent);
      motor_lau.spin(vex::reverse);
    } else {
      motor_lau.stop(coast);
    }
    if(Controller1.ButtonR2.pressing())  {
      indexer.set(true);
      wait(65, msec);
      indexer.set(false);
      wait(100, msec);
      // indexer.set(false);lll
      // wait(20, mse ..gy67c);
    }
    //flicks the disks so that it can launch
    // if(Controller1.ButtonR2.pressing()){
    //   flick();
    // }
    if(Controller1.ButtonRight.pressing()) {
      expansion.set(true);
    }
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
