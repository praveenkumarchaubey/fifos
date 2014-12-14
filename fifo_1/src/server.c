#include "header.h"

int main()
{
        int ret, fd1, fd2, fd, len=0;
        char buffer[MAX];
	memset(buffer,'\0', MAX);

        ret = mkfifo("fifo1",S_IRWXU);
        if(ret == -1)
	{
        	printf("Unable to create fifo1");
		perror("FIFO Error");

		if(EEXIST == errno)
		{
			printf("FIFO1 already exists\n");
		}
		else
			exit(-1);
	}

        ret=mkfifo("fifo2",S_IRWXU);
        if(ret == -1)
	{
        	printf("Unable to create fifo2");
		perror("FIFO Error");

		if(EEXIST == errno)
		{
			printf("FIFO2 already exists\n");
		}
		else
			exit(-1);
	}


        fd1 = open("fifo1",O_WRONLY);
        fd2 = open("fifo2",O_RDONLY);


        write(fd1,"connect",7);
        sleep(1);
        read(fd2, buffer, MAX);
        if(strncmp(buffer,"connection established",22) == 0)
        {
               printf("Connection Established\n");
        }
        else
        {
                printf("Connection not established\n");
                exit(1);
        }

        fd = open("../bin/abc.txt", O_RDONLY);

         while(1)
         {
                 len = read(fd, buffer, MAX);
                 if(len == 0)
                 {
			write(fd1,"terminate",9);
                        printf("terminate by server\n");
                        sleep(5);
                        break;
                 }
                 else
                 {
                 	write(fd1, buffer, len);
                 	sleep(1);
                 }

                 len = read(fd2, buffer, MAX);
                 if(strncmp(buffer,"terminate",len)==0)
                 {
		       write(fd1,"ack",3);
                       printf("ack written by server\n");
                       sleep(1);
                       break;
                 }
                 else if(strncmp(buffer,"ack",3)==0)
                 {
		       printf("exiting from server\n");
                       exit(0);
                 }
                 else
                         printf("Read from fifo2---->\t%s\n",buffer);
         }
	unlink("./fifo1");
	unlink("./fifo2");
         exit(0);
}


