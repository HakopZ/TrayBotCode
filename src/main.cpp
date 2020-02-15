#include "main.h"
#include "Globals.hpp"
#include "Systems/Drive.hpp"
#include "Systems/TwoBar.hpp"
#include "Systems/Tray.hpp"

Controller x(E_CONTROLLER_MASTER);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

 #define LiftPos 50
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

  enum ArmStates
  {
    Down,
    Low,
    LowD,
    Mid,
    MidD,
    Reset
  };
  void IntakeCoast() {
    LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
    RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  }
  ArmStates StateCheck(ArmStates temp )
  {
    if(x.get_digital(DIGITAL_B))
    {
      return (x.get_digital(DIGITAL_L1) ? LowD : Low);
    }
    else if(x.get_digital(DIGITAL_DOWN))
    {
      return (x.get_digital(DIGITAL_L1) ? MidD : Mid);
    }
    else if(x.get_digital(DIGITAL_Y))
    {
      return (x.get_digital(DIGITAL_L1) ? Reset : Down);
    }
    else
    {
      return temp;
    }
  }
  ArmStates current = Down;
  void ArmPreset(void*)
  {
    current = Down;
    while(true)
    {
      switch(current){
      case Down:
      /*  LiftTask.suspend();
        if(ArmButton.get_value() == 0)
        {
          SetLift(-100);
        }
        else if(ArmButton.get_value() == 1)
        {
          Lift.set_zero_position(0);
        SetLift(-10);
      }*/
      SetHeight(0);
       current = StateCheck(current);
        break;
      case Reset:
       Lift.set_zero_position(0);
       current = StateCheck(current);
       break;
      case Low:
        SetHeight(675);
        current = StateCheck(current);
        break;
      case LowD:
        SetHeight(620);
        current = StateCheck(current);
        break;
      case Mid:
        SetHeight(925);
        current = StateCheck(current);
        break;
      case MidD:
        SetHeight(925);
        current = StateCheck(current);
        break;
    }
    delay(20);
  }
}

void initialize(){
  delay(500);
  TrayTask.suspend();

  DriveTask.suspend();
  TurnTask.suspend();
  LiftTask.suspend();

  BL.set_encoder_units(MOTOR_ENCODER_COUNTS);
  BR.set_encoder_units(MOTOR_ENCODER_COUNTS);
  Coast();
  Lift.set_encoder_units(MOTOR_ENCODER_DEGREES);
  ResetDrive();
  Lift.set_zero_position(0);
  SwingTask.suspend();
 	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
  delay(200);
}

void ArmPreset(ArmStates x) {
  switch(x){
    case Down:
      LiftTask.suspend();
      if(ArmButton.get_value() == 0)
      {
        SetLift(-100);
      }
      else if(ArmButton.get_value() == 1)
      {
        Lift.set_zero_position(0);
      SetLift(-10);
    }

    break;
  case Reset:
   Lift.set_zero_position(0);
   break;
  case Low:
    SetHeight(438);
    break;
  case LowD:
    SetHeight(400);
    break;
  case Mid:
    SetHeight(540);
    break;
  case MidD:
    SetHeight(540);
    break;
}
}
void disabled() {}

void competition_initialize() {}

void SetIntake(int power)
{
  LeftIntake.move(power);
  RightIntake.move(power);
}
void Skills()
{

  SetIntake(80);
  SetDrivePower(-50, -50);
  delay(50);
  ArmPreset(Mid);
  delay(350);
  ArmPreset(Down);
  delay(200);
  SetIntake(-140);
  delay(1);
  SetDrivePower(0, 0);
  delay(200);
  ResetDrive();
  SetIntake(-140);
  SetDrive(115, 40, -40, 0, 0);
  DriveWait(11000);
  SetTurn(45, 70, -70);
  TurnWait(800);
  SetIntake(65);
  delay(250);
  SetIntake(0);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(1800);
  SetDrive(18, 50, -50, 0);

  DriveWait(900);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(2250, 90, 1000);
  delay(150);
  SetDrive(-25, 50, -50, 0, 0);
  SetPosition(1450);
  DriveWait(1500);
  SetTurn(200, 70, -70);
  TurnWait(2500);
  SetIntake(-140);
  SetDrive(25, 70, -70, 0, 0);
  DriveWait(1000);
  SetDrive(-5, 90, -90, 0, 0);
  DriveWait(600);
  SetIntake(65);
  delay(250);
  SetIntake(0);
  ArmPreset(Low);
  delay(1000);
  SetIntake(80);

}
void RedEight()
{
  SetIntake(80);
  SetDrivePower(-50, -50);
  delay(50);
  ArmPreset(Mid);
  delay(350);
  ArmPreset(Down);
  delay(200);
  SetIntake(-140);
  delay(1);
  SetDrivePower(0, 0);
  delay(200);
  ResetDrive();
  SetIntake(-140);
  SetDrive(35, 55, -55, 10, 0);
  DriveWait(2200);
  SetSwing(-80, -10, 1000, true, -13, 0, 0, 60);
  SetDrivePower(-60, -60);
  delay(500);
  SetDrivePower(0, 0);
  delay(100);
  ResetDrive();
  delay(1);
  SetDrive(40, 40, -40, 0, 0);
  DriveWait(2900);
  SetDrive(-20, 100, -100, 0);
  delay(20);
  DriveWait(1400);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(135, 80, -80);
  delay(20);
  TurnWait(1000);

  SetIntake(65);
  delay(250);
  SetIntake(0);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(1800);
  SetDrive(18, 50, -50, 0);
  delay(20);
  DriveWait(900);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(2250, 80, 1000);
  delay(300);
  SetDrivePower(-40, -40);
  delay(250);
   SetTray(-70);

}

void SevenPointRed()
{

//  SetIntake(-80)
}
void SixBlueBack()
{
  SetTray(10);
  ArmPreset(Low);
  delay(700);
  DriveTask.suspend();
  //ArmPreset(Intake);
  delay(1000);
  SetDrivePower(-80, -80);
  delay(350);
  SetDrivePower(0, 0);
  ResetDrive();
  SetIntake(-127);
  SetDrive(46, 0, 50, -50, 12);
  SetIntake(-127);
  delay(20);
  DriveWait(3500);
  SetTurn(30, 60, -60);
  delay(20);
  TurnWait(1000);
  SetDrive(15, 30, 100, -100, 12);
  delay(20);
  DriveWait(1000);
  SetDrive(-15, 30, 100, -100, 12);
  delay(20);
  DriveWait(1000);
  SetTurn(0, 60, -60);
  delay(20);
  TurnWait(1000);
  SetDrive(-22, 0, 127, -127, 12);
  delay(20);
  DriveWait(2000);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(-120, 60, -60);
  delay(20);
  TurnWait(1200);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(950);
  SetDrive(15, -120, 70, -70, 10);
  delay(20);
  DriveWait(650);
  SetIntake(50);
  delay(150);
  SetIntake(0);
  delay(100);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(1576, 90, 2000);
  delay(500);
  SetDrivePower(-40, -40);

}
void SixRedBack()
{
  SetTray(-15);
  SetIntake(-127);
  delay(1000);
  SetDrivePower(-80, -80);
  delay(400);
  SetDrivePower(0, 0);
  ResetDrive();
  SetDrive(45, 0, 45, -45, 12);
  delay(20);
  DriveWait(3500);
  SetTurn(-25, 70, -70);
  delay(20);
  TurnWait(1000);
  SetDrive(15, -25, 127, -127, 12);
  delay(20);
  DriveWait(1500);
  SetDrive(-15, -25, 127, -127, 12);
  delay(20);
  DriveWait(1000);
  SetTurn(0, 70, -70);
  delay(20);
  TurnWait(1000);
  SetDrive(-15, 0, 127, -127, 12);
  delay(20);
  DriveWait(1000);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(155, 60, -60);
  delay(20);
  TurnWait(1200);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(950);
  SetDrive(15, 135, 70, -70, 10);
  delay(20);
  DriveWait(650);
  SetIntake(50);
  delay(150);
  SetIntake(0);
  delay(100);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(1576, 110, 1700);
  delay(500);
  SetDrivePower(-40, -40);

}
void SixPointBlue()
{
  SetIntake(80);
   SetDrive(10, 70, -70, 0, 0);
   delay(500);
   SetDrive(-10, 70, -70, 0, 0);
   ArmPreset(Low);
   delay(800);
   ArmPreset(Down);
   delay(650);
   SetIntake(-127);
   delay(1);
   SetDrivePower(0, 0);
   delay(300);
   ResetDrive();
   SetDrive(40, 47, -47, 0, 0);
   delay(20);
   DriveWait(3000);
   SetTurn(30, 100, -100);
   delay(20);
   TurnWait(400);
   SetDrive(11, 100, -100, 12);
   delay(20);
   DriveWait(600);
   SetDrive(-10, 100, -100, 12);
   delay(20);
   DriveWait(400);
   SetTurn(0, 70, -70);
   delay(20);
   TurnWait(400);
  SetDrive(-20, 127, -127, 0);
   delay(20);
   DriveWait(1400);
   SetIntake(0);
   LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
   RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
   SetTurn(-140, 60, -60);
   delay(20);
   TurnWait(1250);
   SetIntake(60);
   delay(250);
   SetIntake(0);
   delay(20);
   Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
   SetPosition(1800);
   SetDrive(18, 50, -50, 0);
   delay(20);
   DriveWait(900);
   LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   TraySlow(2250, 127, 1000);
   delay(100);
   SetDrivePower(-40, -40);
  delay(250);
    SetTray(-70);
}
void FivePointBlue()
{

     SetIntake(80);
     SetDrive(10, 70, -70, 0, 0);
     delay(1000);
     SetDrive(-10, 70, -70, 0, 0);
     delay(500);
     ArmPreset(Low);
     delay(600);
     ArmPreset(Down);
     delay(800);
     SetIntake(-140);
     delay(1);
     SetDrivePower(0, 0);
     delay(300);
     ResetDrive();
     SetDrive(45, 40, -40, 0, 0);
     delay(20);
     DriveWait(3850);
     SetDrive(-25, 127, -127, 0);
     delay(20);
     DriveWait(1750);
     SetIntake(0);
     LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
     RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
     SetTurn(-140, 80, -80);
     delay(20);
     TurnWait(1200);
     SetIntake(60);
     delay(250);
     SetIntake(0);
     delay(20);
     Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
     SetPosition(1800);
     SetDrive(21, 55, -55, 0);
     delay(20);
     DriveWait(1000);
     LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
     RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
     TraySlow(2250, 127, 1000);
     delay(100);
     SetDrivePower(-40, -40);
    delay(250);
      SetTray(-70);

}
void FivePointBRed()
{
  SetIntake(80);
  delay(400);
  ArmPreset(Low);
  delay(600);
  ArmPreset(Down);
  delay(1000);
  SetIntake(-140);
  delay(1);
  SetDrivePower(0, 0);
  delay(300);
  ResetDrive();
  SetDrive(40, 40, -40, 0, 0);
  delay(20);
  DriveWait(3500);
  SetDrive(-20, 127, -127, 0);
  delay(20);
  DriveWait(1400);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(150, 80, -80);
  delay(20);
  TurnWait(1200);
  SetIntake(60);
  delay(250);
  SetIntake(0);
  delay(20);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(1800);
  SetDrive(18, 50, -50, 0);
  delay(20);
  DriveWait(900);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(2250, 127, 1000);
  delay(100);
  SetDrivePower(-40, -40);
 delay(250);
   SetTray(-70);

}

void SixPointRed()
{

   SetIntake(80);
   SetDrivePower(-50, -50);
   delay(50);
   ArmPreset(Mid);
   delay(600);
   ArmPreset(Down);
   delay(200);
   SetIntake(-140);
   delay(1);
   SetDrivePower(0, 0);
   delay(200);
   ResetDrive();
   SetDrive(40, 42, -42, 0, 0);
   delay(20);
   DriveWait(3500);
   SetTurn(-30, 70, -70);
   delay(20);
   TurnWait(2000);
   x.print(1, 2, "30 : %f", TurnTheta);

   SetDrive(10, 50, -50, 0, 0);
   delay(20);
   DriveWait(700);
   SetDrive(-10, 70, -70, 0, 0);
   delay(20);
   DriveWait(700);
   SetTurn(0, 50, -50);
   delay(20);
   TurnWait(2000);

   x.print(2, 2, "0 : %f", TurnTheta);
   SetDrive(-20, 100, -100, 0);
   delay(20);
   DriveWait(1400);
   SetIntake(0);
   LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
   RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
   SetTurn(140, 80, -80);
   delay(20);
   TurnWait(1000);
   SetIntake(65);
   delay(250);
   SetIntake(0);
   delay(20);
   Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
   SetPosition(1800);
   SetDrive(18, 50, -50, 0);
   delay(20);
   DriveWait(900);
   LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   TraySlow(2250, 127, 1000);
   delay(100);
   SetDrivePower(-40, -40);
  delay(250);
    SetTray(-70);

}
void SixPointR()
{
  ArmPreset(Low);
  delay(500);
  DriveTask.suspend();
  SetDrivePower(-60, -60);
  ArmPreset(Down);
  delay(1000);
  SetDrive(57, 0, 50, -50, 10);
  SetIntake(-127);
  delay(20);
  DriveWait(5000);
  SetDrive(-30, 0, 65, -65, 10);
  delay(20);
  DriveWait(3000);
  SetIntake(0);
  SetTurn(140, 50, -50);
  delay(20);
  TurnWait(1000);
  SetDrive(18, 140, 70, -70, 10);
  delay(20);
  DriveWait(1500);
  SetIntake(50);
  delay(100);
  SetIntake(0);

  SetPosition(1735);
  delay(2250);
  SetDrivePower(-40, -40);
}
void SixPointB()
{
  SetIntake(-127);
  SetDrive(50, 0, 45, -45, 10);
  delay(20);
  DriveWait(4500);
  SetDrive(-30, 0, 45, -45, 10);
  delay(20);
  DriveWait(4000);
  SetIntake(0);
  SetTurn(-120, 50, -50);
  delay(20);
  TurnWait(1000);
  SetDrive(20, -120, 70, -70, 10);
  delay(20);
  DriveWait(2500);
  SetIntake(50);
  delay(400);
  SetIntake(0);

  SetPosition(1735);
  delay(2250);
  SetDrivePower(-40, -40);

}
void RedAutonomous()
{
  SetIntake(-127);
  delay(1600);
  SetDrive(45, 0, 50, -50, 10);
  delay(20);
  DriveWait(3000);
  SetTurn(30, 70, -70);
  delay(20);
  TurnWait(600);
  SetDrive(-39, 38, 127, -127, 10);
  delay(20);
  DriveWait(1500);
  SetTurn(0, 50, -50);
  delay(20);
  TurnWait(750);
  SetDrive(32, 0, 60, -60, 10);
  delay(20);
  DriveWait(1350);
  SetIntake(0);
  SetTurn(145, 65, -65);
  delay(20);
  TurnWait(1300);
  SetDrive(50, 145, 90, -90, 10);
  delay(1200);
  SetIntake(85);
  delay(450);
  SetIntake(0);
  delay(500);
  SetPosition(1735);
  DriveWait(500);
  delay(1100);
  SetDrivePower(-40, -40);

}
void RedFlip()
{

  SetDrive(45, 0, 55, -55, 10);
  delay(100);
  SetIntake(-127);
  DriveWait(3000);
  SetTurn(-40, 70, -70);
  delay(20);
  TurnWait(1000);
  SetDrive(-37, -40, 120, -120, 10);
  delay(20);
  DriveWait(1600);
  SetTurn(1, 55, -55);
  delay(20);
  TurnWait(1000);
  SetDrive(35, 0, 50, -50, 10);
  delay(20);
  DriveWait(2000);
  SetIntake(0);
  SetTurn(160, 65, -65);
  delay(20);
  TurnWait(1300);
  SetPosition(1100);
  delay(750);
  TrayTask.suspend();
  SetTray(0);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetDrive(36, 160, 110, -110, 10);
  delay(20);
  DriveWait(1700);
  SetPosition(1735);
  delay(2000);
  SetDrivePower(-40, -40);

}
void BlueAutonomous()
{
  SetIntake(-127);
  SetDrive(50, 0, 45, -45, 10);
  delay(20);
  DriveWait(4500);
  SetDrive(-10, 0 , 50, -50, 10);
  delay(20);
  DriveWait(1000);
  SetTurn(-25, 50, -50);
  delay(20);
  TurnWait(1000);
  SetDrive(-30, -25, 85, -85, 10);
  delay(20);
  DriveWait(2000);
  SetTurn(0, 50, -50);
  delay(20);
  TurnWait(1000);
  SetDrive(30, 0, 35, -35, 10);
  delay(20);
  DriveWait(2500);
  SetTurn(-15, 50, -50);
  delay(20);
  TurnWait(1000);
  SetDrive(20, -15, 50, -50, 10);
  delay(20);
  DriveWait(1500);
  SetTurn(-75, 50, -50);
  delay(20);
  TurnWait(1200);
  SetDrive(75, -75, 80, -80, 10);
  delay(20);
  DriveWait(2750);

  DriveTask.suspend();
  TurnTask.suspend();
  delay(1);
  SetDrivePower(0, 0);
  SetIntake(85);
  delay(500);
  SetIntake(0);
  SetPosition(1735);
  delay(2500);
  SetDrivePower(-40, -40);
}
void FiveCubeFront()
{
  SetDrive(15, 0, 60, -60, 10);
  delay(800);
  SetIntake(-80);
  DriveWait(900);
  SetIntake(80);
  delay(450);
  SetIntake(0);
  SetDrive(40, 0, 75, -75, 10);
  delay(20);
  delay(500);
  SetIntake(-127);
  DriveWait(700);

  delay(100);
  SetDrive(-37, 0, 60, -60, 10);
  delay(20);
  DriveWait(2500);
  SetTurn(-90, 55, -55);
  delay(20);
  TurnWait(1250);
  SetDrive(20, -90, 60, -60, 10);
  delay(20);
  DriveWait(1500);
}
void OneP()
{
  ArmPreset(Low);
  delay(750);
//  ArmPreset(Intake);
  delay(500);
  SetIntake(-127);
  delay(50);
  SetDrivePower(-80, -80);
  delay(500);
  SetDrivePower(0, 0);
  ResetDrive();
  delay(400);

}
void RedF()
{
  SetIntake(80);
  SetDrive(10, 70, -70, 0, 0);
  delay(1000);
  SetDrive(-10, 70, -70, 0, 0);
  delay(500);
  ArmPreset(Low);
  delay(600);
  ArmPreset(Down);
  delay(500);
  SetIntake(-140);
  delay(1);
  SetDrivePower(0, 0);
  delay(300);
  ResetDrive();
  SetDrive(20, 40, -40, 0, 0);
  delay(20);
  DriveWait(3500);
  SetTurn(90, 80, -80);
  delay(20);
  TurnWait(1200);
  SetDrive(30, 50, -50, 0, 0);
  delay(20);
  DriveWait(2000);
  SetTurn(130, 70, -70);
  delay(20);
  TurnWait(700);
  SetIntake(60);
  delay(250);
  SetIntake(0);
  delay(20);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(1800);
  SetDrive(18, 50, -50, 0);
  delay(20);
  DriveWait(900);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(2250, 127, 1000);
  delay(100);
  SetDrivePower(-40, -40);
 delay(250);
   SetTray(-70);

}
void autonomous() {
  LiftTask.suspend();
  DriveTask.suspend();
  TrayTask.suspend();
  TurnTask.suspend();
  delay(20);
 ResetDrive();
 Lift.set_zero_position(0);
 Lift.set_brake_mode(MOTOR_BRAKE_HOLD);


  ArmPreset(Down);
  RedEight();

  //SetDrive(40, 0, 60, -60, 1);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void opcontrol() {
   LiftTask.suspend();
   DriveTask.suspend();
   TrayTask.suspend();
   TurnTask.suspend();
   delay(300);


   Lift.set_zero_position(0);
   Lift.set_brake_mode(MOTOR_BRAKE_HOLD);

   LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   ResetDrive();
   pros::Task Armtask = pros::Task(ArmPreset, nullptr, "Arm Drive Task");
	while (true) {
    SetDrivePower(x.get_analog(ANALOG_LEFT_Y), x.get_analog(ANALOG_RIGHT_Y));
    if(x.get_digital(DIGITAL_L2) && !x.get_digital(DIGITAL_L1))
    {
      if(TrayPot.get_value() < 1670)
      {
        SetTray(127);
      }
      else if(TrayPot.get_value() >= 1670 && TrayPot.get_value() < 1950)
      {
        SetTray(80);
      }
      else if(TrayPot.get_value() >= 1950 && TrayPot.get_value() < 2300)
      {
        SetTray(55);
      }
      else
      {
        SetTray(0);
      }
    }
    else if(x.get_digital(DIGITAL_L2) && x.get_digital(DIGITAL_L1))
    {
      SetTray(-127);
    }
    else
    {
      SetTray(0);
    }
    if(x.get_digital(DIGITAL_R2))
    {
      LeftIntake.move(x.get_digital(DIGITAL_L1) ? 80 : 127);
      RightIntake.move(x.get_digital(DIGITAL_L1) ? 80 : 127);
    }
    else if(x.get_digital(DIGITAL_R1))
    {
      LeftIntake.move(x.get_digital(DIGITAL_L1) ? -80: -127);
      RightIntake.move(x.get_digital(DIGITAL_L1) ? -80: -127);
    }
    else
    {
      if(TrayPot.get_value() < 1600 && current == Down)
      {
      LeftIntake.move(-7);
      RightIntake.move(-7);
     }
     else
     {
       LeftIntake.move(0);
       RightIntake.move(0);
     }

    }
		pros::delay(20);
	}
}
