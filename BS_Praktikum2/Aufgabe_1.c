

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFSIZE 512

int childPid = 0;

int p[2];
int pipe();
char buf[BUFSIZE];
int n;
int status;
char readbuffer[80];

main() {

    while(1){
    if ((childPid = fork()) == -1) {
        fprintf(stderr, "can't fork\n");
        exit(1);
    } else if (childPid == 0) {

        int n = read(p[0], buf, sizeof (buf));
        if (n < 0) {
            perror("read error");

        } else {

            // Child process closes up input side of pipe 
            close(p[1]);

            // Send "string" through the output side of pipe 
            fprintf(stderr, "Prozessmanager: ");
            //fgets(n, 80, stdin);
            write(1, buf, sizeof (buf));
            if (strchr(buf, 'q') != NULL) {
                fprintf(stderr, "SUCCESS!!");
                exit(0);
            } else {
                fprintf(stderr, "ERROR!!");
                exit(1);
            }
        }
    } else {

        // Parent process closes up output side of pipe 
        
        close(p[0]);
        fprintf(stderr, "Kommandant: ");
        write(p[1], buf, (strlen(buf) + 1));
        wait(&status);
        exit(0);

    }



    }

}
