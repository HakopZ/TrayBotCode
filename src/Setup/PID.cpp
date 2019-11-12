#include "PID.hpp"


template<typename T>
PID<T>::PID(float kP, float kI, float kD, int Timeout, T Sensor, float IntegralThreshold)
{
  PID::kP = kP;
  PID::kI = kI;
  PID::kD = kD;
  PID::Timeout = Timeout;
  PID::Sensor = Sensor;
  IntegralThreshold = IntegralThreshold;
}

template<typename T>
PID<T>::~PID<T>()
{}

 template<typename T>
 int PID<T>::GetOutput()
 {
   return PID::GetOutput();
 }
 template<typename T>
void PID<T>::SetScalors(float kP, float kI, float kD)
{
  PID::kP = kP;
  PID::kI = kI;
  PID::kD = kD;
}

template<typename T>
void PID<T>::SetTarget(int Target, int Timeout)
{
  PID::Target = Target;
  PID::Timeout = Timeout;
}
template<typename T>
void PID<T>::Compute(void *)
{
  PrevError = 0;

  while(true)
  {
    Error = Target - Sensor.get_value();
    Integral += Error;
    if(Error > IntegralThreshold)
    {
      Integral = 0;
    }
    Derivative = PrevError - Error;

    Output = Error * kP + Integral * kI + Derivative * kD;
    PrevError = Error;
    pros::delay(20);
  }
}
