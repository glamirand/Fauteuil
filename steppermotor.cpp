#include "steppermotor.h"
#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

StepperMotor::StepperMotor()
{

}
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

    cout << "StepperMotor creation ended" << endl;
}

void StepperMotor::Lancer(){
    std::thread th3 (StepperMotor::Boucle);
    th3.join();
    th3.detach();
}

void StepperMotor::Boucle()
 {
    // pinMode (0, OUTPUT) ;
    for (;;)
    {
      digitalWrite (0, HIGH) ;
      //delay (0.01) ;
      usleep(80);
      digitalWrite (0,  LOW) ;
      usleep(80);
      //delay (0.01) ;
  }
}
