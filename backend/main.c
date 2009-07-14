#include "common.h"
#include "exec.h"
#include "check.h"

char *server = "localhost";
char *user = "root";
char *password = "mysql";
char *database = "judge";

/*Obviously, path to the chroot jail*/
char *chroot_jail_path = "/var/chroot/";

/*path relative to the chroot jail where the submitted files are stored
 * The field 'source' in compile_table has entries of the format 'files/filename.c'
 */
char *source_file_path = "home/judge/";

/*path relative to the chroot jail where the executables are stored*/
char *execfilepath_prefix = "home/judge/exec/";

/*path relative to the chroot jail where the input files are stored*/
char *inputfilepath_prefix = "home/judge/input/";

/*path relative to the chroot jail where the output files are stored*/
char *outputfilepath_prefix = "home/judge/output/";


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
