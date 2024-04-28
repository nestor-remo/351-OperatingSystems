#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        printf("Child process created with PID: %d\n", getpid());

        grandchild_pid = fork();

        if (grandchild_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (grandchild_pid == 0) {
            printf("Grandchild process created with PID: %d\n", getpid());

            execl("/usr/bin/firefox", "firefox", (char *)NULL);

            perror("execl");
            exit(EXIT_FAILURE);
        } else {
            exit(EXIT_SUCCESS);
        }
    } else {
        wait(NULL);
        printf("Child process %d terminated\n", child_pid);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
