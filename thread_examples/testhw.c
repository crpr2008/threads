#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 1

//struct to be used as a linked list to hold the name letters as they appear.  not optimal implmentation
//but then again this file pedagogical :-)
typedef struct Letter {
	char cLetter;
	struct Letter *next;
} Letter_t;

//create threads to open 3 files, find a pattern, and use pps object to pass messages between this and another program
// that a pattern has been found

void showEyeC(int i);
void *functionA();
void *functionB();
void *functionC();

int main (int argc, char * argv[])
{
    if (argc< 4)
    {
       printf("l2w - usage : infilenameA infilenameB infilenameC\n");
       return FALSE;
    }

// spawn thread for files
	printf("Creating thread for file A.\n");
	pthread_create(NULL, NULL, &functionA ,argv[1]);
	printf("Creating another thread.\n");
	pthread_create(NULL,NULL, &functionB ,argv[2]);
	printf("Creating yet another thread.\n");
	pthread_create(NULL,NULL, &functionC ,argv[3]);

	/* Hitting Ctrl+C sends a SIGTERM signal to the process. If the
	 * process receives this signal, it is killed along with all of
	 * its threads. We now use the pause() function to wait for
	 * the signal.
	 */
	 pause();

	/* Hitting Ctrl+C will end the whole program, thus any lines
	 * after the pause() and the } will not be executed.
	 * If you want the main thread exit after the others threads
	 * finished, use pthread_join() as shown above.
	 * Have fun while exploring!
	 */
	 return EXIT_SUCCESS;
}

void showEyeC(int i)
{
        if (i%2)
        {
            printf("%d/ ",i);
        }
        else
        {
            printf("\\%d",i);
        }
        fflush(stdout);    //needed in ubuntu, otherwise stdout is not updated on the printf
//        sleep(1);
        printf("\r      \r"); //clear the line
}

void *functionA(char *argv)
{
    FILE *fp=0;
    char myChar='\0';
    int patternCount=0;
    int letterCount=0;

	printf("functionA active\n");
    printf("opening file %s\n", argv);
    fp = fopen(argv,"r");
    if (fp)
    {
       printf("success opening file %s\n", argv);
       do
       {
          myChar = fgetc(fp);
          if (myChar=='c' ||
        	  myChar=='a' ||
      		  myChar=='r' ||
      		  myChar=='l' ||
      		  myChar=='o' ||
      		  myChar=='s' )
      		{
      			if ( (++letterCount)==sizeof("carlos") )
      			{
//      				send the sync pps or pulse
        		       printf("pattern found in file %s, %d times\n", argv, ++patternCount);
          		       letterCount=0;
          		       //add letter to the letter linked list in the order that they appear
          		       //send sync signal pulse or whatever to the other processes listening
      			}
      		}
       } while (myChar!=EOF);
       fclose(fp);
    }
    else if ( !fp )
    {
       printf("failed to open file %s\n", argv);
    }
	printf ("functionA is finished.\n");
	return (NULL);
}

void *functionB(char *argv)
{
    FILE *fp=0;
    char myChar='\0';
    int patternCount=0;
    int letterCount=0;

	printf("functionB active\n");
    printf("opening file %s\n", argv);
    fp = fopen(argv,"r");
    if (fp)
    {
       printf("success opening file %s\n", argv);
       do
       {
          myChar = fgetc(fp);
          if (myChar=='r' ||
        	  myChar=='i' ||
      		  myChar=='v' ||
      		  myChar=='e' ||
      		  myChar=='r' ||
      		  myChar=='a' )
      		{
      			if ( (++letterCount)==sizeof("rivera") )
      			{
//      				send the sync pps or pulse
       		       printf("pattern found in file %s, %d times\n", argv, ++patternCount);
      		       letterCount=0;
      			}
      		}
       } while (myChar!=EOF);
       fclose(fp);
    }
    else if ( !fp )
    {
       printf("failed to open file %s\n", argv);
    }
	printf ("functionB is finished.\n");
	return (NULL);
}

void *functionC(char *argv)
{
    FILE *fp=0;
    char myChar='\0';
    int patternCount=0;
    int letterCount=0;

	printf("functionC active\n");
    printf("opening file %s\n", argv);
    fp = fopen(argv,"r");
    if (fp)
    {
       printf("success opening file %s\n", argv);
       do
       {
          myChar = fgetc(fp);
          if (myChar=='c' ||
        	  myChar=='i' ||
      		  myChar=='n' ||
      		  myChar=='t' ||
      		  myChar=='r' ||
      		  myChar=='o' ||
      		  myChar=='n' )
      		{
      			if ( (++letterCount)==sizeof("cintron") )
      			{
//      				send the sync pps or pulse
      		       printf("pattern found in file %s, %d times\n", argv, ++patternCount);
      		       letterCount=0;
      			}
      		}
       } while (myChar!=EOF);
       fclose(fp);
    }
    else if ( !fp )
    {
       printf("failed to open file %s\n", argv);
    }
	printf ("functionC is finished.\n");
	return (NULL);
}
