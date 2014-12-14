#include "header.h"


int main()
{
        int fd1, fd2, ret, len=0;
        char buffer[MAX];
	memset(buffer,'\0',MAX);

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

        fd1 = open("fifo1",O_RDONLY);
	sleep(1);

        read(fd1, buffer, MAX);
        if(strncmp(buffer,"connect", 7) == 0)
        {
		fd2 = open("fifo2",O_WRONLY);
		write(fd2,"connection established",22);
		sleep(1);
        }
        else
        {
                printf("Connection not established\n");
                exit(1);
        }

        len = read(fd1,buffer,MAX);
        if(strncmp(buffer,"terminate",len)==0)
        {
		write(fd2,"ack",3);
                printf("ack written by client\n");
                exit(0);
	}
	else
	{
		printf("connection not terminated by server\n");
		exit(1);
	}
	exit(0);
}

