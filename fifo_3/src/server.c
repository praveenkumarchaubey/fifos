#include "header.h"

int main()
{
        int ret, fd1, fd2;
        char buffer[MAX];
	memset(buffer,'\0', MAX);

	//sleep(1);
        fd1 = open("fifo1",O_WRONLY);
	write(fd1,"connect, fifo2 created",22);

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
	        
        fd2 = open("fifo2",O_RDONLY);
	sleep(1);
      
        read(fd2, buffer, MAX);
        if(strncmp(buffer,"connection established",22) == 0)
        {
                printf("Connection Established\n");
		write(fd1,"terminate",9);
                printf("terminate by server\n");
                sleep(5);
		unlink("./fifo1");
		unlink("./fifo2");
		exit(0);
        }
        else
        {
                printf("Connection not established\n");
                exit(1);
        }

	
         exit(0);
}

