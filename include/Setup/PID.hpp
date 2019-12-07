#pragma once
#include "main.h"
class PID
{
public:
  PID(float kP, float kI, float kD, float IntegralThreshold);
  ~PID();
  void SetScalors(float, float, float);
  void SetTarget(int, int);
   int GetOutput();
  float Error;
  float Derivative;
  float Integral;
  float Target;
  float Output;
  int Timeout;
  int Compute(int);
private:
  float IntegralThreshold;
  float kP;
  float kI;
  float kD;
  float PrevError;


};
