#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include "steppermotor.h"

using namespace std;

void boucle1()
{
   pinMode (0, OUTPUT) ;
  //unsigned int tempo(0) ;

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

int main ()
{
    wiringPiSetup () ;
    StepperMotor sm1(0);
    cout << "Demarrage de l'application" << endl;

   cout << "Demarrage du thread" << endl;
  sm1.Lancer();
  // std::thread th1 (boucle1);
      cout << "Thread 1 demarre" << endl;
  //th1.join();
  return 0 ;
}
