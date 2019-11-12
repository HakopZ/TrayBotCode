#define PID_HPP
#ifndef PID_HPP
#include "main.h"
template<typename T>
class PID
{
public:
  PID(float kP, float kI, float kD, int Timeout, T Sensor, float IntegralThreshold);
  ~PID();
  void SetScalors(float, float, float);
  void SetTarget(int, int);
   int GetOutput();
  float Error;
  float Derivative;
  float Integral;
  float Target;
  float Output;
  T Sensor;
private:
  int Timeout;
  float IntegralThreshold;
  const float kP;
  const float kI;
  const float kD;
  float PrevError;

  void Compute(void*);

};
#endif
