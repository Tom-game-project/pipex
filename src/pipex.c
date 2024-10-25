#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>
#include "./basic/basic.h"
#include "./argparse/private_argparse.h"

#define READ 0
#define WRITE 1

char *cmd1[] = {"cat", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;

int child_proc(int d, int pipe_fd[2]);
int parent_proc(int d, int pipe_fd[2]);
int origin_proc(int d,  char *filename);

void run_pipes(int d)
{
	pid_t pid;
	int pipe_fd[2];

	pipe(pipe_fd);
	if (d == 0)
		origin_proc(d, "./test.c\0");
	else
	{
		pid = fork();
		if (pid == 0)
			child_proc(d, pipe_fd);
		else 
			parent_proc(d, pipe_fd);
	}
}

int origin_proc(int d, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp(cmds[d][0], cmds[d]);
	return (0);
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

int main(int argc, char *argv[], char *envp[])
{
	char ***cmds;
	pid_t pid;

	cmds = get_cmds(argc, argv);
	pid = fork(); // if error pid == -1
	if (pid == 0) // if child
		run_pipes(cmd_n - 1);
	else if (pid == -1)
	{
		// pass;
	}
	else // if parent
		wait(NULL);
	clear_cmds(argc, cmds);
	return (0);
}

/*
/// argparse test
///
int main2(int argc, char *argv[])
{
	char ***cmds;
	int i;
	int j;

	cmds = get_cmds(argc, argv);
	i = 0;
	while (i + 1 < argc)
	{
		j = 0;
		printf("number %d\n", i);
		while (cmds[i][j] != NULL)
		{
			printf("%s\n", cmds[i][j]);
			j++;
		}
		i++;
	}
	clear_cmds(argc, cmds);
	return (0);
}

*/
