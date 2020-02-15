#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetDrivePower(int left, int right);
void SetDrive(float Distance, int ClampMax, int ClampMin, float Sc, float Angle = -1);
void ResetDrive();

void SetSwing(int Angle, int SecondAngle, int T, bool Left, int Power, float MidDis, float MidT, float Max);
void Coast();
void SetStraight(float Sc);
void SetTurn(float Value, int ClampMax, int ClampMin, bool GetSPath = true);
void SwingWait(float Timeout);
extern long Time;
extern float TurnTheta;
extern pros::Task DriveTask;
extern pros::Task SwingTask;
extern int DriveClampMax;
extern int DriveClampMin;
extern int TurnClampMax;
extern int TurnClampMin;
extern pros::Task TurnTask;

void DriveWait(int);
void TurnWait(int);
