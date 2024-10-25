#ifndef PIPELINE_H
#define PIPELINE_H

typedef struct s_input
{
	char *infile;
	char ***cmds;
	char *outfile;
}	 t_input;

int parent_proc(int d, int pipe_fd[2], t_input *ti);
void run_pipes(int d, t_input *ti);


#endif

