#include "TwoBar.hpp"
PID Lift(0.6, 0, 0, 200);
void SetLift(int Power)
{
  Lift.move(Power);
}
void SetHeight(int Value, int Timeout)
{
  LTime = 0;
  Lift.SetTarget(Value, Timeout);
  LiftTask.resume();
}
void SlowLift(int Value, int Power)
{
  LiftTask.suspend();
  while(LiftPot.get_value() < Value)
  {
    SetLift(Power);
  }
  SetLift(0);
}
void LiftCompute(void*)
{
  while(true)
  {
    SetLift(Lift.Compute(LiftPot.get_value()));
    delay(20);
  }
}
void LiftBrake()
{
  LeftLift.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RightLift.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void LiftWait()
{
  while(std::abs(Lift.Error) > 15)
  {
    if(Lift.Timeout < LTime)
    {
      LiftTask.suspend();
      LiftBrake();
      SetLift(0);
    }
    LTime++;
  }

  for (size_t i = 0; i < 500; i++) {
    delay(1);
  }
  LiftTask.suspend();
  LiftBrake();
  SetLift(0);
}
pros::Task LiftTask(LiftCompute, nullptr, "Lift Computation");
