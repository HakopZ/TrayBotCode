#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetDrivePower(int left, int right);
void SetDrive(float Distance, float Angle, int ClampMax, int ClampMin, float Sc);
void ResetDrive();
void Coast();
void SetStraight(float Sc);
void SetTurn(float Value, int ClampMax, int ClampMin);
extern long Time;
extern float TurnTheta;
extern pros::Task DriveTask;
extern int DriveClampMax;
extern int DriveClampMin;
extern int TurnClampMax;
extern int TurnClampMin;
extern pros::Task TurnTask;
void DriveWait(int);
void TurnWait(int);
