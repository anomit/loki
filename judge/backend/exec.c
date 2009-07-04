#include "exec.h"
#include "common.h"

void exec()
{
    int problemid;
    int userid;
    long int tokenid;
    char execfilename[256];
    memset(execfilename, '\0', sizeof(execfilename));

    MYSQL *conn;
    conn = mysql_init(NULL);
    mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);

    MYSQL_RES * res;
    MYSQL_ROW row;

    char *query = "SELECT problemid, userid, tokenid, file FROM exec_table";
    mysql_query(conn, query);

    res = mysql_store_result(conn);

    if(res)
    {
        printf("Whee!!\n");
        while( ( row = mysql_fetch_row(res) ) )
        {
            problemid = atoi(row[0]);
            userid = atoi(row[1]);
            tokenid = atol(row[2]);
            strcpy(execfilename, row[3]);
            /*again we need to get this from a conf file, for now refer main.c to change execfilepath_prefix*/
            char execfilename_fully_qualified[strlen(execfilepath_prefix)+strlen(execfilename)+1];
            memset(execfilename_fully_qualified, '\0', sizeof(execfilename_fully_qualified));
                
            sprintf(execfilename_fully_qualified, "%s%s", execfilepath_prefix, execfilename);

            int pid;

            struct tms tms_start, tms_end;

            times(&tms_start);
            if ( !(pid = fork()) )
            {
                /*apply restrictions and all*/
                struct rlimit rl;
                getrlimit(RLIMIT_CPU, &rl);
                
                rl.rlim_cur = 3;
                rl.rlim_max = 3;
                
                /*a restriction on just the CPU time, TODO:need to add more like stack size*/
                setrlimit(RLIMIT_CPU, &rl);
                
                //add ptrace here
                execl(execfilename_fully_qualified, execfilename, NULL);
            }

            else if ( pid )
            {
                int status;
                wait(&status);
                times(&tms_end);

                if ( WIFEXITED(status) )
                {
                    if ( WEXITSTATUS(status) == 0 )
                    {
                        /*This uses the clock ticks returned by times() to calculate the "user CPU time"*/
                        clock_t real = tms_end.tms_cutime - tms_start.tms_utime;
                        float running_time = real / (double)sysconf(_SC_CLK_TCK);

                        /*The following uses getrusage() to get the "user CPU time" of the child process.
                         * Uncomment it and comment out the code using times() to see if there is any difference
                         */

                        /*struct rusage ru;
                        getrusage(RUSAGE_CHILDREN, &ru);

                        struct timeval tv = ru.ru_utime;

                        float running_time = (float)tv.tv_sec+(float)(tv.tv_usec/1000000.0);*/
                        
                        /*TODO:Put running time in DB*/
                        printf("Running time for %s:%7.4f\n", execfilename, running_time);
                    }
                }
                /*Delete entry of exec file from DB after it has been processed*/
                char delete_query[256];
                memset(delete_query, '\0', sizeof(delete_query));

                sprintf(delete_query, "DELETE FROM exec_table WHERE userid=%d AND problemid=%d AND tokenid=%ld", userid, problemid, tokenid);

                mysql_query(conn, delete_query);
            }
        }
        mysql_free_result(res);
    }
}
