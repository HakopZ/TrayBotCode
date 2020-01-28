 #include "Globals.hpp"

pros::Motor FL(3, true);
pros::Motor FR(2);
pros::Motor BL(8, true);
pros::Motor BR(7);
pros::Motor Lift(17);
pros::Motor Tray(5);
pros::Motor RightIntake(12);
pros::Motor LeftIntake(10,  true);
pros::ADIPotentiometer TrayPot(2);
pros::ADIEncoder LeftEnc(2, 3);
pros::ADIEncoder RightEnc(4, 5);
pros::ADIEncoder MiddleEnc(6, 7);
PID LeftDrive(0.25, 0, 0, 200);
PID RightDrive(0.25, 0, 0, 200);
PID LeftTurn(5, 0, 0, 200);
PID RightTurn(5, 0, 0, 200);

PID LiftPID(2.5, 0, 0, 200);
PID TrayPID(0.3, 0, 0, 200);
