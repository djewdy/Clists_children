
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    // Define the environment variable name we are looking for.
    const char* env_var_name = "MY_ENV_VAR";
    char* env_value;
    
    // Retrieve the environment variable.
    env_value = getenv(env_var_name);
    if (env_value == NULL) {
        fprintf(stderr, "Error: Environment variable %s not set.\n", env_var_name);
        return EXIT_FAILURE;
    }
    
    // Create a pipe for IPC.
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    
    // Fork the current process.
    pid_t pid = fork();
    if (pid == -1) {
        // Error handling.
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Child process.
        close(fd[0]); // Close unused read end.
        // Write the value of the environment variable to the pipe.
        write(fd[1], env_value, strlen(env_value) + 1);
        close(fd[1]); // Close the write end of the pipe.
        exit(EXIT_SUCCESS);
    } else {
        // Parent process.
        char buffer[128];
        close(fd[1]); // Close unused write end.
        // Read the value from the pipe.
        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]); // Close the read end of the pipe.
        // Wait for child process to finish.
        wait(NULL);
        printf("Parent process received value: %s\n", buffer);
    }
    
    return EXIT_SUCCESS;
}


