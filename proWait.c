#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>  // This is necessary for wait macros

void proWait(void);
void wait_handler(int signum, siginfo_t *info, void* context);

int main() {
    pid_t pid;
    int child_count = 10; // Number of child processes to fork

    for (int i = 0; i < child_count; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            // Child Process: Sleep for 2 seconds and then exit with a status
            sleep(4);
            return 42 + i; // Exit with a custom status (e.g., 42, 43, 44)
        }
    }

    // Parent Process: Set up signal handling
    proWait();

    // Simulate parent doing other work while children exit
    int remaining_children = child_count;
    while (remaining_children > 0) {
        // Parent can do other tasks or wait for signal interrupts
        sleep(1);
        remaining_children--;
    }

    return 0;
}


void proWait(void) {
    struct sigaction sa;
    sigset_t set;

    sigemptyset(&set);  // Initialize the signal set to empty
    sa.sa_flags = SA_SIGINFO; // Commented out SA_NOCLDWAIT to avoid automatically discarding the child
    sa.sa_mask = set; // Set the signal mask to avoid blocking

    sa.sa_sigaction = wait_handler; // Define the signal handler for SIGCHLD

    // Set the handler for SIGCHLD
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
    }
}

void wait_handler(int signum, siginfo_t *info, void* context) {
    pid_t child_pid = info->si_pid;
    int status;

    // Manually call waitpid to prevent zombie processes
    if (waitpid(child_pid, &status, WNOHANG) > 0) {
        // Child process has terminated, now check its status
        if (WIFEXITED(status)) {
            printf("Child with PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child with PID %d killed by signal %d\n", child_pid, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Child with PID %d stopped by signal %d\n", child_pid, WSTOPSIG(status));
        }
    }
}

