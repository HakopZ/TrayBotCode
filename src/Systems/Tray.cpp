#include "Tray.hpp"
PID TrayPID(0.6, 0, 0, 200);
void SetTray(int Power)
{
  Tray.move(Power);
}
void SetPosition(int Value, int Timeout)
{
  Ttime = 0;
  TrayPID.SetTarget(Value, Timeout);
  TrayTask.resume();
}
void SlowTray(int Value, int Power)
{
  TrayTask.suspend();
  while(TrayPot.get_value() < Value)
  {
    SetTray(Power);
  }
  SetTray(0);
}
void TrayCompute(void*)
{
  while(true)
  {
    SetTray(TrayPID.Compute(TrayPID.get_value()));
    delay(20);
  }
}
void TrayBrake()
{
  Tray.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void TrayWait()
{
  while(std::abs(Tray.Error) > 15)
  {
    if(Tray.Timeout < LTime)
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
