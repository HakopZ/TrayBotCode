#include "main.h"
#include "Globals.hpp"
#include "Systems/Drive.hpp"
#include "Systems/TwoBar.hpp"
#include "Systems/Tray.hpp"

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
    Intake,
    AutoIntake,
  };
  void IntakeCoast() {
    LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
    RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  }
  void ArmPreset(ArmStates x)
  {
   switch(x)
   {
     case Down:

       SetHeight(-5);
       break;

     case Intake:
       SetHeight(LiftPos + 35);
       break;
     case AutoIntake:
      SetHeight(LiftPos);
      break;
     case Low:
       SetHeight(875);
       break;
     case LowD:
       SetHeight(785);
       break;
     case Mid:
       SetHeight(1125);
       break;
     case MidD:
       SetHeight(1050);
       break;

   }
  }

void initialize() {
 TrayTask.suspend();

 DriveTask.suspend();
 TurnTask.suspend();
 LiftTask.suspend();

 BL.set_encoder_units(MOTOR_ENCODER_COUNTS);
 BR.set_encoder_units(MOTOR_ENCODER_COUNTS);
 Coast();
 Lift.set_encoder_units(MOTOR_ENCODER_DEGREES);


 	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
 delay(500);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void SetIntake(int power)
{
  LeftIntake.move(power);
  RightIntake.move(power);
}
void Skills()
{
  SetTray(10);
  ArmPreset(Low);
  delay(700);
  DriveTask.suspend();
  ArmPreset(Intake);
  delay(1100);
  SetDrivePower(-80, -80);
  delay(350);
  SetDrivePower(0, 0);
  ResetDrive();
  SetIntake(-127);
  SetDrive(115, 0, 40, -40, 12);
  delay(20);
  DriveWait(8500);
  SetTurn(40, 50, -50);
  delay(20);
  TurnWait(600);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(950);
  SetDrive(15, 40, 60, -60, 12);
  delay(20);
  DriveWait(800);
  SetIntake(50);
  delay(150);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  delay(400);
  TraySlow(1570, 90, 2000);
  delay(750);
  SetDrive(-17, 40, 60, -60, 0);
  delay(750);
  SetStraight(12);
  SetPosition(500);
  delay(20);
  DriveWait(1250);
  TrayTask.suspend();
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  SetTurn(100, 50, -50);
  delay(20);
  TurnWait(1500);
  SetDrive(-17, 100, 127, -127, 12);
  delay(20);
  DriveWait(1000);
  SetTurn(190, 60, -60);
  delay(20);
  TurnWait(1000);
  SetDrivePower(-100, -100);
  delay(1500);
  SetDrivePower(0, 0);
  delay(10);
  ResetDrive();
  delay(10);
  SetDrive(15, 0, 100, -100, 12);
  delay(20);
  DriveWait(1200);

  SetTurn(90, 60, -60);
  delay(20);
  TurnWait(1000);
  SetIntake(-127);
  SetDrive(14, 90, 90, -90, 12);
  delay(20);
  DriveWait(1000);
  SetDrive(-7, 90, 100, -100, 12);
  delay(20);
  DriveWait(700);
  SetIntake(80);
  delay(400);
  SetIntake(0);
  ArmPreset(Mid);
  delay(750);
  SetDrive(10, 90, 100, -100, 12);
  delay(750);
  SetIntake(127);
  delay(500);
  SetDrive(-22, 90, 127, -127, 12);
  delay(20);
  ArmPreset(AutoIntake);
  DriveWait(1000);
  /*

  DriveWait(1250);
  SetDrive(-11, 200, 60, -60, 12);
  SetIntake(70);
  delay(400);
  SetIntake(0);
  ArmPreset(Low);
  delay(1000);
  SetDrive(7, 200, 70, -70, 12);
  delay(500);
  SetIntake(100);
  delay(350);
  ArmPreset(AutoIntake);
  SetTurn(145, 60, -60);
  delay(20);
  TurnWait(1500);
  SetDrive(28, 145, 100, -100, 12);
  SetIntake(-127);
  delay(20);
  DriveWait(1500);
  SetDrive(-30, 145, 127, -127, 12);
  delay(20);
  DriveWait(1500);
  SetTurn(130, 60, -60);
  delay(20);
  TurnWait(1000);
  SetIntake(80);
  delay(400);
  SetIntake(0);
  ArmPreset(Low);
  SetDrive(17, 130, 75, -75, 12);
  delay(1500);
  SetIntake(80);
  SetDrive(-10, 100, 75, -75, 12);
  /*SetIntake(70);
  delay(350);
  SetIntake(0);
  ArmPreset(Mid);
  delay(900);
  SetDrive(7, -90, 80, -80, 10);
  delay(20);
  DriveWait(500);
  SetIntake(127);
  delay(700);
  SetIntake(-127);
  SetTurn(-140, 60, -60);
  delay(20);
  TurnWait(1000);
  SetDrive(-25, -140, 80, -80, 12);
  delay(20);
  DriveWait(1750);
  ArmPreset(Down);
  delay(20);
  SetTurn(-190, 50, -50);
  delay(20);
  TurnWait(1750);
  DriveTask.suspend();
  SetDrivePower(-70, -70);
  delay(750);
  SetDrive(115, -210, 45, -45, 11);
  delay(20);
  DriveWait(7000);
  SetTurn(150, 60, -60);
  delay(20);
  TurnWait(1000);
*/}
void SevenPointRed()
{
  ArmPreset(Low);
  delay(500);
  DriveTask.suspend();
  SetDrivePower(-60, -60);
  ArmPreset(AutoIntake);
  delay(1000);
  SetDrive(47, 0, 40, -40, 10);
  SetIntake(-127);
  delay(20);
  DriveWait(5000);
  SetDrive(10, -35, 60, -60, 10);
  delay(1500);
  SetDrive(-35, 0, 127, -127, 10);
  delay(20);
  DriveWait(1500);
  SetIntake(0);
  SetTurn(130, 65, -65);
  delay(20);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  TurnWait(1300);
  SetDrive(15, 130, 70, -70, 10);
  delay(20);
  DriveWait(800);
  SetIntake(0);

  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  SetPosition(1735);
  delay(2250);
  SetDrivePower(-40, -40);

}
void SixBlueBack()
{
  SetTray(10);
  ArmPreset(Low);
  delay(700);
  DriveTask.suspend();
  ArmPreset(Intake);
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
  DriveWait(1250);
  SetDrive(-15, -25, 127, -127, 12);
  delay(20);
  DriveWait(1000);
  SetTurn(0, 70, -70);
  delay(20);
  TurnWait(1000);
  SetDrive(-18, 0, 127, -127, 12);
  delay(20);
  DriveWait(1000);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(135, 60, -60);
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
void FivePointBlue()
{
  ArmPreset(Low);
  delay(750);
  ArmPreset(Intake);
  delay(500);
  SetIntake(-127);
  delay(50);
  SetDrivePower(-80, -80);
  delay(500);
  SetDrivePower(0, 0);
  ResetDrive();
  delay(400);
  SetDrive(49, 0, 43, -43, 12);
  delay(20);
  DriveWait(3500);
  SetDrive(-22, 0, 90, -90, 12);
  delay(20);
  DriveWait(1500);
  SetIntake(0);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetTurn(-150, 60, -60);
  delay(20);
  TurnWait(1500);
  Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  SetPosition(950);
  SetDrive(18, -150, 50, -50, 10);
  delay(20);
  DriveWait(900);
  SetIntake(50);
  delay(150);
  SetIntake(0);
  delay(100);
  LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
  TraySlow(1576, 127, 1700);
  delay(500);
  SetDrivePower(-40, -40);

}
void FivePointRed()
{
 ArmPreset(Low);
 delay(650);
 ArmPreset(Intake);
 delay(650);
 SetIntake(-127);
 delay(1);
 SetDrivePower(-80, -80);
 delay(500);
 SetDrivePower(0, 0);
 delay(500);
 ResetDrive();
 SetDrive(49, 0, 43, -43, 12);
 delay(20);
 DriveWait(3500);
 SetDrive(-22, 0, 127, -127, 12);
 delay(20);
 DriveWait(1000);
 SetIntake(0);
 LeftIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
 RightIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
 SetTurn(140, 60, -60);
 delay(20);
 TurnWait(1200);
 Tray.set_brake_mode(MOTOR_BRAKE_HOLD);
 SetPosition(950);
 SetDrive(18, 140, 50, -50, 12);
 delay(20);
 DriveWait(900);
 SetIntake(50);
 delay(150);
 SetIntake(0);
 delay(250);
 LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
 RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
 TraySlow(1576, 99, 1700);
 delay(500);
 SetDrivePower(-40, -40);

}
void SixPointRed()
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
void SixPointBlue()
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

  //SetDrive(17, -85,  60, -60, 10);
  //delay(20);
  //DriveWait(800);
}
void OneP()
{
  ArmPreset(Low);
  delay(750);
  ArmPreset(Intake);
  delay(500);
  SetIntake(-127);
  delay(50);
  SetDrivePower(-80, -80);
  delay(500);
  SetDrivePower(0, 0);
  ResetDrive();
  delay(400);

}
void autonomous() {
  LiftTask.suspend();
  DriveTask.suspend();
  TrayTask.suspend();
  TurnTask.suspend();
  delay(500);
 ResetDrive();
 Lift.set_zero_position(0);
 Lift.set_brake_mode(MOTOR_BRAKE_HOLD);


  ArmPreset(Down);
  FivePointBlue();
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
 Controller x(E_CONTROLLER_MASTER);
 void opcontrol() {
   LiftTask.suspend();
   DriveTask.suspend();
   TrayTask.suspend();
   TurnTask.suspend();
   delay(300);
   ArmPreset(Intake);


   LeftIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   RightIntake.set_brake_mode(MOTOR_BRAKE_COAST);
   ResetDrive();

	while (true) {
    SetDrivePower(x.get_analog(ANALOG_LEFT_Y), x.get_analog(ANALOG_RIGHT_Y));
    if(x.get_digital(DIGITAL_B))
    {
      ArmPreset(x.get_digital(DIGITAL_L1) ? LowD : Low);
    }
    else if(x.get_digital(DIGITAL_DOWN))
    {
      ArmPreset(x.get_digital(DIGITAL_L1) ? MidD : Mid);
    }
    else if(x.get_digital(DIGITAL_Y))
    {
      ArmPreset(x.get_digital(DIGITAL_L1) ? Down : Intake);
    }
    if(x.get_digital(DIGITAL_L2) && !x.get_digital(DIGITAL_L1))
    {
      if(TrayPot.get_value() < 1100)
      {
        SetTray(127);
      }
      else if(TrayPot.get_value() >= 1100 && TrayPot.get_value() < 1765)
      {
        SetTray(80);
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
      if(TrayPot.get_value() < 1130 && Lift.get_position() < 75)
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
