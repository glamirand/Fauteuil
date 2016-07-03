/* A simple server in the internet domain using TCP.
myServer.c
D. Thiebaut
Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
The port number used in 51717.
This code is compiled and run on the Raspberry as follows:

    g++ -o myServer myServer.c
    ./myServer

The server waits for a connection request from a client.
The server assumes the client will send positive integers, which it sends back multiplied by 2.
If the server receives -1 it closes the socket with the client.
If the server receives -2, it exits.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include "steppermotor.h"

using namespace std;

void error( char *msg ) {
  perror(  msg );
  exit(1);
}

int Command[2];

int func( int a ) {
   return 2 * a;
}

void sendData( int sockfd, int x ) {
  int n;

  char buffer[32];
  sprintf( buffer, "%d\n", x );
  if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 )
    error( const_cast<char *>( "ERROR writing to socket") );
  buffer[n] = '\0';
}

string getData( int sockfd ) {
  char buffer[32];
  int n;

  if ( (n = read(sockfd,buffer,31) ) < 0 )
    error( const_cast<char *>( "ERROR reading from socket") );
  buffer[n] = '\0';
  return  string(buffer);
}

int main(int argc, char *argv[]) {
	Command[0] = 0;
	Command[1] = 0;
    cout << "Demarrage de l'application" << endl;
    wiringPiSetup () ;
    StepperMotor sm1(15,16,1);
    sm1.Enable();
    sm1.Start();
	StepperMotor sm2(0, 2, 3);
	sm2.Enable();
	sm2.Start();

     int sockfd, newsockfd, portno = 8000, clilen;
    // char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     //int n;
     int data;

     printf( "using port #%d\n", portno );

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
         error( const_cast<char *>("ERROR opening socket") );
     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons( portno );
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
       error( const_cast<char *>( "ERROR on binding" ) );
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

		string left = "";
		string right = "";
		string s = "";

     //--- infinite wait on a connection ---
     while ( 1 ) {
        printf( "waiting for new client...\n" );
        if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
            error( const_cast<char *>("ERROR on accept") );
        printf( "opened new communication with client\n" );

        while ( 1 ) {
             //---- wait for a number from client ---
             s = getData( newsockfd );
			  if (s.length() >= 8)	
				  {
			 left = s.substr(0, 4);
			 right = s.substr(4, 4);
				 
			Command[0] = stoi(left);
			Command[1] = stoi(right);

             sm1.SetSpeed(Command[0]*120);
printf( "Command[0] : %d\n", Command[0]);
printf( "Command[1] : %d\n", Command[1]);
 }

             //--- send new data back ---
		//	data = 0;
            // printf( "sending back %d\n", data );
           //  sendData( newsockfd, data );

             //if (Command[0] == 0)
             //{
             //    break;
             //}
break;
        }
        close( newsockfd );
     }
     return 0;
}
