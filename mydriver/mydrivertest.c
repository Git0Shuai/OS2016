#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int my_dev;
    char *buffer = malloc(sizeof(char)*1);
    if(argc == 1)
        printf("too few arguments!\n");
    else if((strlen(argv[1]) == 1)&&(*argv[1] == 'r')){     //when the second is 'r'
        /*
         *open dev and read
         */
        if((my_dev = open("/dev/mydriver", O_RDONLY)) < 0){
            printf("open /dev/mydriver failed!\n");
            return -1;
        }
	printf("open /dev/mydriver succeed!\n");
        read(my_dev, buffer, 1);
        printf("read succeed: %c\n", *buffer);
        close(my_dev);    
    }
    else if((argc == 3)                                 //when there are three arguments
            &&(strlen(argv[1]) == 1)&&(*argv[1] == 'w')){   //and the second is 'w'
        /*
         *open dev and write
         */
        if((my_dev = open("/dev/mydriver", O_WRONLY)) < 0){
            printf("open /dev/mydriver failed!\n");
            return -1;
        }
	*buffer = *argv[2];
	printf("open /dev/mydriver succeed!\n");
        write(my_dev, buffer, 1);
        printf("write succeed: %c\n ", *buffer);
        close(my_dev);
    }
    else{
        printf("Unknown Options!\n");
        printf("    r:  read from dev.\n");
        printf("    w:  write to dev.\n");
        return -1;
    }

}
