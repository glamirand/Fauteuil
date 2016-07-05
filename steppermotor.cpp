#include "steppermotor.h"
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

StepperMotor::StepperMotor(int TriggerPinNumber)
{
    StepperMotor::StepperMotorConstructor(TriggerPinNumber,-1,-1);
}

StepperMotor::StepperMotor(int TriggerPinNumber, int DirectionPinNumber)
{
    StepperMotor::StepperMotorConstructor(TriggerPinNumber,DirectionPinNumber,-1);
}

StepperMotor::StepperMotor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber)
{
    StepperMotor::StepperMotorConstructor(TriggerPinNumber,DirectionPinNumber,EnablePinNumber);
}

void StepperMotor::StepperMotorConstructor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber)
{
    cout << "Starting StepperMotor creation" << endl;
   //TriggerPin
    StepperMotor::m_TriggerPinNumber = TriggerPinNumber;
    if (StepperMotor::m_TriggerPinNumber>=0)
    {
         pinMode (StepperMotor::m_TriggerPinNumber, OUTPUT) ;
    }
    cout << "StepperMotor Trigger Pin Number : " << StepperMotor::m_TriggerPinNumber << endl;

    //DirectionPin
    StepperMotor::m_DirectionPinNumber = DirectionPinNumber;
     if (StepperMotor::m_DirectionPinNumber>=0)
     {
          pinMode (StepperMotor::m_DirectionPinNumber, OUTPUT) ;
     }
     cout << "StepperMotor Direction Pin Number : " << StepperMotor::m_DirectionPinNumber << endl;

     //EnablePin
     StepperMotor::m_EnablePinNumber = EnablePinNumber;
      if (StepperMotor::m_EnablePinNumber>=0)
      {
           pinMode (StepperMotor::m_EnablePinNumber, OUTPUT) ;
      }
      cout << "StepperMotor Enable Pin Number : " << StepperMotor::m_EnablePinNumber << endl;

      //Min Trigger Time
      StepperMotor::m_MinTriggerTime = 80;

      //Reverse
      StepperMotor::m_Reverse = false;

      //Enabled
      StepperMotor::m_Enabled = false;

      //Run
      StepperMotor::m_Run = false;

      //Target Speed
      StepperMotor::m_TargetSpeed = 0;

      //Current Speed
      StepperMotor::m_CurrentSpeed = 0;

    cout << "StepperMotor creation ended" << endl;
}

void StepperMotor::Start(){
    StepperMotor::m_Run = true;
    std::thread mainThread (&StepperMotor::Main,this);
    mainThread.detach();
  //  mainThread.join();
}

void StepperMotor::SetSpeed(int Speed)
{
    if (Speed == 0)
    {
        StepperMotor::Stop();
    }
    else if (StepperMotor::m_Enabled == true)
    {
       StepperMotor::m_Run = true;
    }
    StepperMotor::m_TargetSpeed = Speed;
}

void StepperMotor::Stop()
{
    StepperMotor::m_Run = false;
}

void StepperMotor::Enable()
{
if (StepperMotor::m_Enabled == false)
{
    if (StepperMotor::m_EnablePinNumber >=0)
{
    digitalWrite (StepperMotor::m_EnablePinNumber, LOW) ;
}
    StepperMotor::m_Enabled = true;
}
}

void StepperMotor::Dislable()
{
    if (StepperMotor::m_Enabled == true)
    {
        if (StepperMotor::m_EnablePinNumber >=0)
    {
        digitalWrite (StepperMotor::m_EnablePinNumber, LOW) ;
    }
        StepperMotor::m_Enabled = false;
    }
}

unsigned int StepperMotor::ComputeTime(int Speed)
{
    return (unsigned int)(1000000 / abs(Speed));
}

void StepperMotor::SetReverse()
{
    if (StepperMotor::m_DirectionPinNumber>=0)
    {
        if ((StepperMotor::m_Reverse == true && StepperMotor::m_CurrentSpeed>=0) || (StepperMotor::m_Reverse == false && StepperMotor::m_CurrentSpeed<0))
        {
           digitalWrite (StepperMotor::m_DirectionPinNumber, HIGH) ;
        }
        else
        {
            digitalWrite (StepperMotor::m_DirectionPinNumber, FALSE) ;
        }
    }
}

void StepperMotor::Main()
 {
    while (1)
    {
        if (StepperMotor::m_Run == true && StepperMotor::m_TargetSpeed !=0 )
        {
            StepperMotor::m_CurrentSpeed = StepperMotor::m_TargetSpeed;
            StepperMotor::SetReverse();
            digitalWrite (StepperMotor::m_TriggerPinNumber, HIGH) ;
            usleep(StepperMotor::m_MinTriggerTime);
            digitalWrite (StepperMotor::m_TriggerPinNumber,  LOW) ;
            usleep(StepperMotor::ComputeTime(StepperMotor::m_CurrentSpeed)-StepperMotor::m_MinTriggerTime);
        }

  }
}
