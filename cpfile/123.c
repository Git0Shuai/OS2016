#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int copyfile(char *filefrom, char *fileto);
int main(int argc, char *argv[]){
    int err;
    if(argc == 3){
        err = copyfile(argv[1], argv[2]);
        switch(err){
            case -1:
                printf("open %s FAILED!", argv[1]);
                break;
            case -2:
                printf("open %s FAILED!", argv[2]);
                break;
            case -3:
                printf("malloc buffer FAILED!");
                break;
            case -4:
                printf("read file FAILED!");
                break;
            case -5:
                printf("write fle FAILED!");
                break;
            case 0:
                printf("succeed!");
                break;
            default:
                printf("unkowned!");
        }
    }
    else
        printf("too few arguments!");
    return 1;
}

int copyfile(char *filefrom, char *fileto)
{
    int fd_filefrom = open(filefrom, O_RDONLY);
    if(fd_filefrom < 0)
        return -1;
    int fd_fileto = open(fileto, O_WRONLY|O_CREAT);
    if(fd_fileto < 0)
        return -2;
    void *buf;
    buf = malloc(sizeof(char)*1024);
    if(!buf)
        return -3;
    int len;
    do{
        len = read(fd_filefrom, buf, sizeof(char)*1024);
        if(len < 0)
            return -4;
        if(write(fd_fileto, buf, len) < 0)
            return -5;
    }while(len > 0);
    close(fd_filefrom);
    close(fd_fileto);
    return 0; 
}
