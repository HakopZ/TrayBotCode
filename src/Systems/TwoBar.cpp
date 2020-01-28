#include "TwoBar.hpp"
long LTime = 0;
void SetLift(int Power)
{
  Lift.move(Power);
}
void SetHeight(int Value)
{
  LTime = 0;
  LiftPID.SetTarget(Value);
  LiftTask.resume();
}
void SlowLift(int Value, int Power)
{
  LiftTask.suspend();
  while(Lift.get_position() < Value)
  {
    SetLift(Power);
  }
  SetLift(0);
}
void LiftCompute(void*)
{
  while(true)
  {
    SetLift(LiftPID.Compute(Lift.get_position()));
    delay(20);
  }
}
void LiftBrake()
{
  Lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void LiftWait(int TimeOut)
{
  while(std::abs(LiftPID.Error) > 15)
  {
    if(TimeOut < LTime)
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
