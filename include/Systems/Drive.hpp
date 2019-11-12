#include "Setup/PID.hpp"
#include "Globals.hpp"
#define DRIVE_HPP
#ifndef DRIVE_HPP
void SetDrivePower(int left, int right);
void SetDrive(int Distance, int TimeOut);
void SetTurn(int Value, int TimeOut);
extern PID<pros::ADIEncoder> LeftDrive;
extern PID<pros::ADIEncoder> RightDrive;

#endif
