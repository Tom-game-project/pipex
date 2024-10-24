#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

char *cmd1[] = {"cat", "test.c", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;

int child_proc(int d, int pipe_fd[2]);
int parent_proc(int d, int pipe_fd[2]);

void run_pipes(int d)
{
	pid_t pid;
	int pipe_fd[2];

	if (d == 0)
		 execvp(cmds[d][0], cmds[d]);
	else
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			child_proc(d, pipe_fd);
		else 
			parent_proc(d, pipe_fd);
	}
}

int child_proc(int d, int pipe_fd[2])
{
	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	run_pipes(d - 1);
	return (0);
}

int parent_proc(int d, int pipe_fd[2])
{
	// env d
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
	execvp(cmds[d][0], cmds[d]);
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
 int main(void)
{
	pid_t pid;

	pid = fork(); // if error pid == -1
	if (pid == 0) // if child
		run_pipes(cmd_n - 1);
	else // if parent
		wait(NULL);
	return (0);
}

