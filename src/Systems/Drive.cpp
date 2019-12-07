#include "Drive.hpp"
PID LeftDrive(0.5, 0, 0, 200);
PID RightDrive(0.5, 0, 0, 200);
PID LeftTurn(0.52, 0, 0, 150);
PID RightTurn(0.52, 0, 0, 150);
void ResetDrive()
{
  FL.set_zero_position(0);
  FR.set_zero_position(0);
}
void SetDrivePower(int left, int right)
{
  BR.move(right);
  FR.move(right);
  FL.move(left);
  BL.move(left);
}
void SetDrive(int Distance, int TimeOut)
{
  Time = 0;
  ResetDrive();
  TurnTask.suspend();
  DriveTask.resume();
  LeftDrive.SetTarget(Distance, TimeOut);
  RightDrive.SetTarget(Distance, TimeOut);
}
void SetTurn(int Value, int TimeOut)
{
  Time = 0;
  ResetDrive();
  DriveTask.suspend();
  TurnTask.resume();
  LeftTurn.SetTarget(Value, TimeOut);
  RightTurn.SetTarget(-Value, TimeOut);
}
void DriveFunc(void *)
{
  while(true)
  {
    SetDrivePower(LeftDrive.Compute(FL.get_position()), RightDrive.Compute(FR.get_position()));
    delay(20);
  }
}
void TurnFunc(void*)
{
  while(true)
  {
    SetDrivePower(LeftTurn.Compute(FL.get_position()), RightTurn.Compute(FR.get_position()));
    delay(20);
  }
}
void Brake()
{
  FL.set_brake_mode(MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void OnlyLimit()
{
  int temp = 0;
  while(temp < 3000 && (LeftLimit.get_value() == 0 || RightLimit.get_value() == 0))
  {
    delay(1);
  }
  DriveTask.suspend();
  Brake();
  SetDrivePower(0,0);

}
pros::Task DriveTask = pros::Task(DriveFunc, nullptr, "Computing Drive PID");
pros::Task TurnTask = pros::Task(TurnFunc, nullptr, "Computing Turn PID");

void PIDWait(pros::Task* Task, PID* Left, PID* Right)
{
  delay(20);
  while(std::abs(Left->Error) > 15 && std::abs(Right->Error) > 15)
  {
    if(Left->Timeout < Time && Right->Timeout < Time)
    {
      Task->suspend();
      Brake();
      SetDrivePower(0, 0);
    }
    Time++;
  }

  for (size_t i = 0; i < 500; i++) {
    delay(1);
  }
  Task->suspend();
  Brake();
  SetDrivePower(0, 0);
}
