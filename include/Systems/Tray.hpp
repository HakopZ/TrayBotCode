#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetTray(int Power);
void SetPosition(int Value);
void TraySlow(int Value, int Power, int TimeOut);
void TrayWait(int);
extern PID TrayPID;
extern pros::Task TrayTask;
extern long Ttime;
