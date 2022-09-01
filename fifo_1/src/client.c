#include "header.h"

int main()
{
    int fd1, fd2, fd, len=0;
    char buffer[MAX];
    memset(buffer,'\0',32);

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

    fd = open("../bin/xyz.txt",O_RDONLY);

    while(1)
    {
        len = read(fd, buffer, MAX);
        sleep(1);
        if(len == 0)
        {       
            write(fd2, "terminate", 9);
            printf("terminate by client\n");
            sleep(1);
            break;
        }
        else
        {
            write(fd2,buffer,len);
            sleep(1);
        }

        len=read(fd1,buffer,MAX);
        if(strncmp(buffer,"terminate",len)==0)
        {
            write(fd2,"ack",3);
            printf("ack written by client\n");
            sleep(1);
            break;
        }
        else if(strncmp(buffer,"ack",3)==0)
        {
            printf("exiting from client\n");
            exit(0);
        }
        else
            printf("Read from fifo1---->\t%s\n",buffer);
    }//end of while
    exit(0);
}

