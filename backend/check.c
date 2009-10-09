#include "check.h"

void check()
{
    
    int problemid;
    int userid;
    char source[256];
    char tokenid[32];
    memset(source, '\0', sizeof(source));
    memset(tokenid, '\0', sizeof(tokenid));

    int pid;

    MYSQL * conn;
    conn = mysql_init(NULL);
    mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);

    MYSQL_RES * res;
    MYSQL_ROW row;

    char *query = "SELECT problemid, userid, source, tokenid FROM compile_table WHERE checked=0";
    mysql_query(conn, query);

    /* get all the rows at once so that the connection is freed up for later queries */
    res = mysql_store_result(conn);

   
    if(res)
    {
        while( ( row = mysql_fetch_row ( res ) ) )
        {
            problemid = atoi(row[0]);
            userid = atoi(row[1]);
            strcpy(source, row[2]);
            strcpy(tokenid, row[3]);

            /*TODO: put paths in a conf file*/
            char fullpath[strlen(source_file_path)+strlen(source)+1];
            memset(fullpath, '\0', sizeof(fullpath));
            GEN_FULL_SOURCEPATH(fullpath, source_file_path, source);

            char execfile[strlen(execfilepath_prefix)+strlen("exec")+strlen(tokenid)+1];
            memset(execfile, '\0', sizeof(execfile));
            GEN_FULL_EXECPATH(execfile, execfilepath_prefix, tokenid);

            if( !( pid = fork() ) )
            {
                struct rlimit rl;
                getrlimit(RLIMIT_CPU, &rl);

                rl.rlim_cur = 5;
                rl.rlim_max = 5;
                
                setrlimit(RLIMIT_CPU, &rl);
                chroot(chroot_jail_path);
                chdir("/");

                if(mkdir(execfilepath_prefix, 0755) == EEXIST)
                    printf("Directory exec already exists\n");

                execl("/usr/bin/gcc", "gcc", "-Wall", "-std=c99", fullpath, "-o",execfile, "-lm", NULL);
           }

            else if (pid)
            {
                int rv;
                wait(&rv);

                if ( WIFEXITED ( rv ) )
                {
                    if ( WEXITSTATUS ( rv ) == 0 )
                    {
                        /* 
                         * Compilation was successful, zero exit code on return. Awesome!
                         * update compile_table to let it know code has been compiled successfully
                         */
                        char update[256];
                        memset(update, '\0', sizeof(update));
                        sprintf(update, "UPDATE compile_table SET checked=1 WHERE userid=%d AND problemid=%d AND tokenid=%s", userid, problemid, tokenid);
                      
                        mysql_query(conn, update);

                        /*put the location of the file to be executed in exec_table*/
                        char insert[256];
                        memset(insert, '\0', sizeof(insert));
                       
                        sprintf(insert, "INSERT INTO exec_table VALUES (%d, %d, %s, 'exec%s')",problemid, userid, tokenid, tokenid);

                        if(mysql_query(conn, insert))
                           printf("Error inserting into exec_table\n%s",mysql_error(conn));;
                    }
                           
                    else
                    {
                        /*TODO:Delete the row corresponding to the wrong source code*/
                        char delete_query[256];
                        memset(delete_query, '\0', sizeof(delete_query));

                        sprintf(delete_query, "DELETE FROM compile_table WHERE problemid=%d AND userid=%d AND tokenid=%s", problemid, userid, tokenid);

                        //unlink(fullpath);
                    }
                }
            }
        }
        mysql_free_result(res);
    }
}

