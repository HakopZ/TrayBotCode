#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetDrivePower(int left, int right);
void SetDrive(int Distance, int TimeOut);
void ResetDrive();
void SetTurn(int Value, int TimeOut);
void DriveFunc(void*);
void OnlyLimit();
extern PID LeftDrive;
extern PID RightDrive;
extern PID LeftTurn;
extern PID RightTurn;
extern long Time;
extern pros::Task DriveTask;
extern pros::Task TurnTask;
void PIDWait(pros::Task*,  PID*, PID*);
