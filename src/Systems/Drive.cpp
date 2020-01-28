#include "Drive.hpp"
#define BaseWidth 10.96875
#define WheelCircumference 3.65 * M_PI
#define Tick_Per_Rev 300 * (7/3)
#define Tick_per_inch (Tick_Per_Rev / (WheelCircumference))
int DriveClampMax = 0;
int DriveClampMin = 0;
int TurnClampMax = 0;
int TurnClampMin = 0;
float StraightScale = 0;
#define inch_per_deg ((BaseWidth * M_PI) / 180)
float TurnTheta = 0;
long Time = 0;
float Heading = 0;
void SetStraight(float Sc)
{
  StraightScale = Sc;
}
void ResetDrive()
{
  BL.set_zero_position(0);
  BR.set_zero_position(0);
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

void SetDrive(float Distance, float Angle, int ClampMax, int ClampMin, float Sc)
{
  StraightScale = Sc;
  DriveClampMax = ClampMax;
  DriveClampMin = ClampMin;
  Time = 0;
  TurnTask.suspend();
  Heading = Angle;
  LeftDrive.SetTarget(BL.get_position() + (Distance*Tick_per_inch));
  RightDrive.SetTarget(BR.get_position() + (Distance * Tick_per_inch));
  DriveTask.resume();
}
void SetTurn(float Value,int ClampMax, int ClampMin)
{
  TurnClampMin = ClampMin;
  TurnClampMax = ClampMax;
  Time = 0;
  DriveTask.suspend();
  Heading = Value;
  LeftTurn.SetTarget(Heading);
  RightTurn.SetTarget(Heading);
  TurnTask.resume();
}
int Clamp(int Given, int Max, int Min)
{
  if(Given > Max)
  {
    return Max;
  }
  return Given < Min ? Min : Given;
}
void DriveFunc(void*)
{
  while(true)
  {

    SetDrivePower(Clamp(LeftDrive.Compute(BL.get_position()), DriveClampMax, DriveClampMin) + ((Heading - TurnTheta) * StraightScale) ,  Clamp(RightDrive.Compute(FR.get_position()), DriveClampMax, DriveClampMin) - ((Heading - TurnTheta) * StraightScale));// + ((Heading - TurnTheta)*10), RightDrive.Compute(FR.get_position())-((Heading - TurnTheta)*10));
  //  pros::lcd::print(5, "LVal: %f", TurnTheta) ;
    delay(20);
  }
}
void Track(void*)
{
  while(true)
  {
    TurnTheta = ((BL.get_position() / Tick_per_inch) - (BR.get_position()/ Tick_per_inch)) / inch_per_deg;
    pros::lcd::print(6, "TurnTheta: %f", TurnTheta);
    delay(20);
  }
}
void TurnFunc(void*)
{
  while(true)
  {
    SetDrivePower(Clamp(LeftTurn.Compute(TurnTheta), TurnClampMax, TurnClampMin), Clamp(-RightTurn.Compute(TurnTheta), TurnClampMax, TurnClampMin));
    delay(20);
  }
}
pros::Task TrackTask = pros::Task(Track, nullptr, "Tracking theta");
void Brake()
{
  FL.set_brake_mode(MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void Coast()
{
  FL.set_brake_mode(MOTOR_BRAKE_COAST);
  FR.set_brake_mode(MOTOR_BRAKE_COAST);
  BL.set_brake_mode(MOTOR_BRAKE_COAST);
  BR.set_brake_mode(MOTOR_BRAKE_COAST);
}
pros::Task DriveTask = pros::Task(DriveFunc, nullptr, "Computing Drive PID");
pros::Task TurnTask = pros::Task(TurnFunc, nullptr, "Computing Turn PID");

void TurnWait(int TimeOut)
{

  while(std::abs(LeftTurn.Error) > 5 && std::abs(RightTurn.Error) > 5)
  {
    if(TimeOut < Time && TimeOut < Time)
    {
      TurnTask.suspend();
      Brake();
      SetDrivePower(0, 0);
      break;
    }
    Time++;
    delay(1);
  }

  for (size_t i = 0; i < 500; i++) {
    delay(1);
  }
  TurnTask.suspend();
  Brake();
  SetDrivePower(0, 0);
}

void DriveWait(int TimeOut)
{

  pros::lcd::print(5, "Entered: %f", LeftDrive.Error);
  while(std::abs(LeftDrive.Error) > 15 && std::abs(RightDrive.Error) > 15)
  {
    pros::lcd::print(6, "Time: &f", TimeOut);
    if(TimeOut < Time && TimeOut < Time)
    {
      DriveTask.suspend();
      Brake();
      SetDrivePower(0, 0);
      break;
    }
    Time++;
    delay(1);
  }
  for (int i = 0; i < 500; i++) {
    delay(1);
  }
  DriveTask.suspend();
  Brake();
  SetDrivePower(0, 0);
}
