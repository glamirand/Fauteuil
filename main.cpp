#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>

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

void boucle2()
{
   pinMode (1, OUTPUT) ;
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
    cout << "Demarrage de l'application" << endl;

   cout << "Demarrage du thread" << endl;
   std::thread th1 (boucle1);
   std::thread th2 (boucle2);
   cout << "Thread demarre" << endl;
  th1.join();
  th2.join();
  cout << "Thread 1 termine" << endl;

  return 0 ;
}
