#ifndef PRIVATE_ARGPARSE_H
#define PRIVATE_ARGPARSE_H

// int count_cmd_args(char *str);
// char **get_cmd(char *str);
char ***get_cmds(int argc, char *argv[]);
void clear_cmds(int argc, char ***cmds);

#endif
