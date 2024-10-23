#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

char *cmd1[] = {"cat", "test.c", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;

void run_pipes(int d)
{
	pid_t pid;
	int pipe_fd[2];

	if (d == cmd_n - 1)
		 execvp(cmds[0][0], cmds[0]);
	else
	{
		pipe(pipe_fd); // create pipe
		pid = fork();
		if (pid == 0) // if child
		{
			close(pipe_fd[READ]);
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
			close(pipe_fd[WRITE]);
			run_pipes(d + 1);
		}
		else // if parent
		{
			close(pipe_fd[WRITE]);
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
			execvp(cmds[cmd_n-d-1][0], cmds[cmd_n-d-1]);
		}
	}
}


// int main(int argc, char *argv[], char *envp[])
 int main(void)
{
	pid_t pid;

	pid = fork(); // if error pid == -1
	if (pid == 0) // if child
		run_pipes(0);
	else // if parent
		wait(NULL);
	return (0);
}

