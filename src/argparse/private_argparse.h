#ifndef PRIVATE_ARGPARSE_H
#define PRIVATE_ARGPARSE_H

int ft_strlen(char *str);
char *copy_string(char *start,char *end);
int count_cmd_args(char *str);
char **get_cmd(char *str);
char ***get_cmds(int argc, char *argv[]);
void clear_cmds(int argc, char ***cmds);
char *copy_string(char *start, char *end);

#endif
