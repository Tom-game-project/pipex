#include "src/argparse/private_argparse.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    char *a = "{hello} world";
    char *open_position;
    char *close_position;
    char *copied_tmp;

    open_position = NULL;
    close_position = open_position;
    while (*a != '\0'){
        if (*a == '{')
            open_position = a;
        else if (open_position != NULL && *a == '}'){
            close_position = a;
        }
        a++;
    }
    if (open_position != NULL && close_position != NULL){
        copied_tmp = copy_string(open_position,close_position);
        printf("%s\n",copied_tmp);
        free(copied_tmp);
    }
    else {
        printf("something wrong with input value\n");
    }
    return (0);
}