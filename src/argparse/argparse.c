#include <stdlib.h>
#include "src/argparse/private_argparse.h"

int predict_list_length(char *arg_str)
{
    return (0);
}

char **arg_parse(char *arg_str)
{
    char **rlist_str;
    int escape_flag = 0;
    int quotation_flag = 0;
    char *dock;

    rlist_str = malloc(sizeof(char*) * predict_list_length(arg_str));
    dock = arg_str;
    while (*arg_str != '\0')
    {
        if (arg_str == '"')
        {
            if (escape_flag)
                arg_str++;
            else
                quotation_flag = !quotation_flag;
        }
        else if (arg_str == ' '){
            if (quotation_flag)
                arg_str++;
            else{

            }
        }
        else if (arg_str == '\\')
        {
            if (escape_flag){
                escape_flag = 0;
                arg_str++;
            }
            else
                escape_flag = 1;
        }
        else
        {
            if ()
        }
    }
    return (rlist_str);
}