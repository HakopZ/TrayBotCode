#include "Tray.hpp"
long Ttime = 0;
void SetTray(int Power)
{
  Tray.move(Power);
}
void SetPosition(int Value)
{
  Ttime = 0;
  TrayPID.SetTarget(Value);
  TrayTask.resume();
}
void TraySlow(int Value, int Power, int TimeOut)
{
  TrayTask.suspend();
  int time = TimeOut;
  long Current = pros::millis();
  while(TrayPot.get_value() < Value)
  {
    if(time < pros::millis() - Current)
    {
      break;
    }
    SetTray(Power);
  }
  SetTray(0);
}
void TrayCompute(void*)
{
  while(true)
  {
    SetTray(TrayPID.Compute(TrayPot.get_value()));
    delay(20);
  }
}
void TrayBrake()
{
  Tray.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void TrayWait(int TimeOut)
{
  while(std::abs(TrayPID.Error) > 15)
  {
    if(TimeOut < Ttime)
    {
      TrayTask.suspend();
      TrayBrake();
      SetTray(0);
    }
    Ttime++;
  }

  for (size_t i = 0; i < 500; i++) {
    delay(1);
  }
  TrayTask.suspend();
  TrayBrake();
  SetTray(0);
}
pros::Task TrayTask(TrayCompute, nullptr, "Tray Computation");
