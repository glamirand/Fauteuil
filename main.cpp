#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include "steppermotor.h"

using namespace std;

int main ()
{
    cout << "Demarrage de l'application" << endl;
    wiringPiSetup () ;
    StepperMotor sm1(0);
    sm1.Enable();
    sm1.Start();
    for (int sp=10;sp<12000;sp+=200)
    {
        sm1.SetSpeed(sp);
        cout << "Vitesse : " << sp << endl;
        delay(100);
    }
    delay(3000);
    for (int sp=12000;sp>0;sp-=200)
    {
        sm1.SetSpeed(sp);
        cout << "Vitesse : " << sp << endl;
        delay(100);
    }

  return 0 ;
}
