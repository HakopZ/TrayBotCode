#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetLift(int Power);
void SetHeight(int Value);
void SlowLift(int Value, int Power);
void LiftWait(int);
extern PID LiftPID;
extern pros::Task LiftTask;
extern long LTime;
