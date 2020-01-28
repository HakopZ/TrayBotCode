#include "PID.hpp"


PID::PID(float kP, float kI, float kD, float IntegralThreshold)
{
  PID::kP = kP;
  PID::kI = kI;
  PID::kD = kD;
  PID::IntegralThreshold = IntegralThreshold;
}

PID::~PID()
{}

 int PID::GetOutput()
 {
   return PID::Output;
 }

void PID::SetScalors(float kP, float kI, float kD)
{
  PID::kP = kP;
  PID::kI = kI;
  PID::kD = kD;
}

void PID::SetTarget(float Target)
{
  PID::Target = Target;
  PID::PrevError = 0;
  PID::last_time = 0;
}

int PID::Compute(int SensorVal)
{
    PID::dT = millis() - PID::last_time;
    PID::Error = PID::Target - SensorVal;
    PID::Integral += PID::Error;
    if(PID::Error > PID::IntegralThreshold)
    {
      PID::Integral = 0;
    }
    PID::Derivative = dT == 0 ? 0 : (Error - PrevError)/dT;

    Output = Error * kP + Integral * kI + Derivative * kD;
    PrevError = Error;
    last_time = millis();
    return Output;
}
