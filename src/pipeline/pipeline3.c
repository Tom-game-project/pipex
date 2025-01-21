#include "pipeline.h"
#include "../basic/basic.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	run_pipe(int d, t_input *ti, char *envp[], int input_fd)
{
	if (d == ti->cmdlen - 1)
		return (last_cmd(d, ti, envp, input_fd));
	else
		return (middle_cmd(d, ti, envp, input_fd));
}

int	exec_pipe(t_input *ti, char *envp[])
{
	return (run_pipe(0, ti, envp, -1));
}
