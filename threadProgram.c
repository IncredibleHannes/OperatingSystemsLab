#define _POSIX_C_SOURCE 200112L
//Johannes Hartmann, Jonas Einig
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* perform_work( void* argument )
{
  printf("new thread running\n");
  return NULL;
}

int main( int argc, char** argv )
{
  pthread_t threads[ 1 ];
  pthread_create( &threads[1], NULL, perform_work, NULL );

  // wait for thread to complete
  // block until thread 'index' completes
  pthread_join( threads[ 1 ], NULL );

   printf( "In main: All threads completed successfully\n" );
   exit( EXIT_SUCCESS );
}

// Quelle: inspiriert von Wikipedia: https://en.wikipedia.org/wiki/POSIX_Threads
