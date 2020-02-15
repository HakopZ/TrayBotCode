#pragma once
#include "main.h"
#include "Setup/PID.hpp"
extern pros::Motor FL;
extern pros::Motor FR;
extern pros::Motor BL;
extern pros::Motor BR;
extern pros::Motor Lift;
extern pros::Motor Tray;
extern pros::Motor LeftIntake;
extern pros::Motor RightIntake;
extern pros::ADIPotentiometer TrayPot;
extern pros::ADIEncoder LeftEnc;
extern pros::ADIEncoder RightEnc;
extern pros::ADIEncoder MiddleEnc;
extern pros::Imu Gyro;
extern pros::ADIDigitalIn ArmButton;
extern PID LeftDrive;
extern PID RightDrive;
extern PID LeftTurn;
extern PID RightTurn;
extern PID TrayPID;
extern PID LiftPID;
extern PID RightSwing;
extern PID LeftSwing;
