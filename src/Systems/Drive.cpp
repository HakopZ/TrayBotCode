#include "Drive.hpp"
#define BaseWidth 11.265
#define WheelCircumference 3.75 * M_PI
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
void SetLeft(int P)
{
  FL.move(P);
  BL.move(P);
}
void SetRight(int P)
{
  BR.move(P);
  FR.move(P);

}
void SetDrivePower(int left, int right)
{
  SetLeft(left);
  SetRight(right);
}

void SetDrive(float Distance, int ClampMax, int ClampMin, float Sc, float Angle)
{

  StraightScale = Sc;
  DriveClampMax = ClampMax;
  DriveClampMin = ClampMin;
  Time = 0;
  TurnTask.suspend();
  if(Angle != -1)
    Heading = Angle;

  LeftDrive.SetTarget(BL.get_position() + (Distance*Tick_per_inch));
  RightDrive.SetTarget(BR.get_position() + (Distance * Tick_per_inch));
  DriveTask.resume();
}
bool SP = true;
int FirstTheta = 0;
void SetTurn(float Value,int ClampMax, int ClampMin, bool GetSPath)
{
  FirstTheta = TurnTheta;
  TurnClampMin = ClampMin;
  TurnClampMax = ClampMax;
  Time = 0;
  DriveTask.suspend();
  Heading = Value;
  SP = GetSPath;
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
    if(pros::millis() < 750)
    {
      SetDrivePower(0, 0);
    }
    else
    {
      if(Heading == 0)
      {
        SetDrivePower(Clamp(LeftDrive.Compute(BL.get_position()), DriveClampMax, DriveClampMin) + ((TurnTheta > 180 ? 360 : 0 - TurnTheta) * StraightScale) ,  Clamp(RightDrive.Compute(FR.get_position()), DriveClampMax, DriveClampMin) - ((TurnTheta > 180 ? 360 : 0 - TurnTheta) * StraightScale));// + ((Heading - TurnTheta)*10), RightDrive.Compute(FR.get_position())-((Heading - TurnTheta)*10
      }
      else
      {
        SetDrivePower(Clamp(LeftDrive.Compute(BL.get_position()), DriveClampMax, DriveClampMin) + ((Heading - TurnTheta) * StraightScale) ,  Clamp(RightDrive.Compute(FR.get_position()), DriveClampMax, DriveClampMin) - ((Heading - TurnTheta) * StraightScale));// + ((Heading - TurnTheta)*10), RightDrive.Compute(FR.get_position())-((Heading - TurnTheta)*10));
      }
    }
  //  pros::lcd::print(5, "LVal: %f", TurnTheta) ;
    delay(20);
  }
}
void Track(void*)
{
  while(true)
  {
    TurnTheta =  ((BL.get_position() / Tick_per_inch) - (BR.get_position()/ Tick_per_inch)) / inch_per_deg;//Gyro.get_heading();
    pros::lcd::print(6, "TurnTheta: %f", TurnTheta);
    delay(20);
  }
}
int GetShortestPath()
{
  int LeftAbs = 0;
  int RightAbs = 0;

  if(Heading < TurnTheta)
  {
    LeftAbs = TurnTheta - (Heading + 360);
  }
  else
  {
   LeftAbs = Heading - TurnTheta;
   RightAbs = (TurnTheta + 360) - Heading;
  }

   pros::lcd::print(4, "RightAbs: %i", RightAbs);
  return std::abs(LeftAbs) < std::abs(RightAbs) ? TurnTheta : (RightAbs);
}
bool SLeft;
void SDriveWait(float TimeOut)
{
  delay(20);
  float t = -1;
  while(std::abs(LeftDrive.Error) > 15 && std::abs(RightDrive.Error) > 15)
  {
    if(TimeOut < t && TimeOut < t)
    {
      DriveTask.suspend();
      return;
    }
    t++;
    delay(1);
  }
  DriveTask.suspend();
}
void SwingWait(float Timeout)
{
  delay(20);
  float t = -1;
  if(SLeft)
  {
  while(std::abs(LeftSwing.Error) > 2)
  {
    if(Timeout < t && Timeout < t)
    {
      SwingTask.suspend();
      return;
    }
    t++;
    delay(1);
  }
}
else
{
  while(std::abs(RightSwing.Error) > 2)
  {
    if(Timeout < t && Timeout < t)
    {
      SwingTask.suspend();
      return;
    }
    t++;
    delay(1);
  }
}
  SwingTask.suspend();
}

void SetSwing(int Angle, int SecondAngle, int T, bool Left, int Power, float MidDis, float MidT, float Max)
{
  int CurrAngle = TurnTheta;
  SLeft = Left;
  Heading = Angle;
if(Left)
{
  SwingTask.resume();
  LeftSwing.SetTarget(Angle);
  SetRight(Power);
  //delay(5000);
  SwingWait(T);
  SetDrive(MidDis, Max, -Max, 0, 0);
  SDriveWait(MidT);
  SLeft = !Left;
  SwingTask.resume();
  RightSwing.SetTarget(SecondAngle);
  SetLeft(Power);
  SwingWait(T);
  delay(20);
  SetDrivePower(0, 0);

}
else
{
  SwingTask.resume();
  RightSwing.SetTarget(Angle);
  SetLeft(Power);
  SwingWait(T);
  SetDrive(MidDis, Max, -Max, 0, 0);
  SDriveWait(MidT);
  SLeft = !Left;
  SwingTask.resume();
  LeftSwing.SetTarget(SecondAngle);
  SetRight(Power);
  SwingWait(T);
  delay(300);
  SetDrivePower(0, 0);

}

}
void SwingFunc(void*)
{
  while(true)
  {
    if(pros::millis() < 750)
    {
      SetDrivePower(0, 0);
    }
    else
    {
      if(SLeft)
      {
        SetLeft(LeftSwing.Compute(TurnTheta));
      }
      else
      {
        SetRight(-RightSwing.Compute(TurnTheta));
      }
    }
      delay(20);
    }
}
pros::Task SwingTask(SwingFunc, nullptr,"Swing T");
void TurnFunc(void*)
{
  while(true)
  {
    if(pros::millis() < 750)
    {
      SetDrivePower(0, 0);
    }
    else
    {

    SetDrivePower(Clamp(LeftTurn.Compute(/*SP ? GetShortestPath() :*/ TurnTheta), TurnClampMax, TurnClampMin), Clamp(-RightTurn.Compute(/*SP ? GetShortestPath() : */TurnTheta), TurnClampMax, TurnClampMin));
    }
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
      return;
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
  delay(20);
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
  for (int i = 0; i < 300; i++) {
    delay(1);
  }
  DriveTask.suspend();
  Brake();
  SetDrivePower(0, 0);
}
