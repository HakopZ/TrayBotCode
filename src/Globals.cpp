 #include "Globals.hpp"

pros::Motor FL(18, true);
pros::Motor FR(19);
pros::Motor BL(17, true);
pros::Motor BR(20);
pros::Motor Lift(4);
pros::Motor Tray(11);
pros::Motor RightIntake(2);
pros::Motor LeftIntake(1,  true);
pros::ADIPotentiometer TrayPot(1);
pros::ADIDigitalIn ArmButton(5);
pros::ADIEncoder LeftEnc(2, 3);
pros::ADIEncoder RightEnc(7, 8);
pros::Imu Gyro(16);
PID LeftDrive(0.25, 0, 0, 200);
PID RightDrive(0.25, 0, 0, 200);
PID LeftTurn(2.3, 0, 250, 200);
PID RightTurn(2.3, 0, 250, 200);
PID RightSwing(4, 0 , 0, 200);
PID LeftSwing(4, 0, 0, 200);
PID LiftPID(3, 0, 0, 200);  //3
PID TrayPID(0.3, 0, 0, 200);
