#include "PID.hpp"


PID::PID(float kP, float kI, float kD, float IntegralThreshold)
{
  kP = kP;
  kI = kI;
  kD = kD;
  Timeout = 0;
  IntegralThreshold = IntegralThreshold;
}

PID::~PID()
{}

 int PID::GetOutput()
 {
   return PID::GetOutput();
 }

void PID::SetScalors(float kP, float kI, float kD)
{
  kP = kP;
  kI = kI;
  kD = kD;
}

void PID::SetTarget(int Target, int Timeout)
{
  PID::Target = Target;
  PID::Timeout = Timeout;
  PrevError = 0;
}

int PID::Compute(int SensorVal)
{
    Error = Target - SensorVal;
    Integral += Error;
    if(Error > IntegralThreshold)
    {
      Integral = 0;
    }
    Derivative = PrevError - Error;

    Output = Error * kP + Integral * kI + Derivative * kD;
    PrevError = Error;
    return Output;
}
