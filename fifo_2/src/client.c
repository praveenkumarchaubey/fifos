#include "header.h"


int main()
{
        int fd1, fd2, len=0;
        char buffer[MAX];
	memset(buffer,'\0',MAX);
	strcpy(buffer, "./../bin/txt");
	len = strlen(buffer);

        fd1 = open("fifo1",O_RDONLY);
        fd2 = open("fifo2",O_WRONLY);


        read(fd1, buffer, MAX);
        if(strncmp(buffer,"connect", 7) == 0)
        {
		write(fd2,"connection established",22);
		sleep(1);
        }
        else
        {
                printf("Connection not established\n");
                exit(1);
        }

	write(fd2, buffer, len);
        printf("file requested by the client\n");
        sleep(1);
         while(1)
         {      
                 len = read(fd1, buffer, MAX);
                 if(strncmp(buffer,"terminate",len)==0)
                 {
		        printf("exiting from client\n");
                        exit(0);
                 }
                 else
		{
                         printf("Read from fifo1---->\t%s\n",buffer);
		}
         }//end of while
         exit(0);
}

