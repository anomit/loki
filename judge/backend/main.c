#include "common.h"
#include "exec.h"
#include "check.h"

char *server = "localhost";
char *user = "root";
char *password = "mysql";
char *database = "judge";
char *execfilepath_prefix = "/home/anomit/code/php/judge/backend";


int main()
{
    /*TODO: Daemonize the process after checking the effective uid*/
    if(geteuid())
    {
        printf("You need to be uid 0\n");
        exit(1);
    }

    //while(1)
    //{
        check();
        exec();
    //}
    /*This is really redundant right now*/
    return 0;
}
