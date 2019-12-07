#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetLift(int Power);
void SetHeight(int Value, int Timeout);
void SlowLift(int Value, int Power);
void LiftWait();
extern PID Lift;
extern pros::Task LiftTask;
extern long LTime;
