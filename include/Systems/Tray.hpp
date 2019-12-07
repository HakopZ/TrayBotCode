#pragma once
#include "Setup/PID.hpp"
#include "Globals.hpp"
void SetTray(int Power);
void SetPosition(int Value, int Timeout);
void TraySlow(int Value, int Power);
void TrayWait();
extern PID TrayPID;
extern pros::Task TrayTask;
extern long Ttime;
