#pragma once
#include "main.h"
class PID
{
public:
  PID(float kP, float kI, float kD, float IntegralThreshold);
  ~PID();
  void SetScalors(float, float, float);
  void SetTarget(float);
   int GetOutput();
  float Error;
  float Derivative;
  float Integral;
  float Target;
  float Output;
  float kP;
  float kI;
  float kD;

  int Compute(int);
private:
  float IntegralThreshold;
  long dT;
  float last_time;
  float PrevError;


};
