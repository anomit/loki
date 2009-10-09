#ifndef COMMON_H
#define COMMON_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/* 
 * Macro for generating the source file name from problemid and tokenid 
 * looks better than an ugly sprintf hack
 */
#define GEN_SOURCEFILE(char_array, pid, tid) sprintf(char_array, "source%d%ld", pid, tid)

/*
 * Generate the full source path from a given path prefix and file name
 */
#define GEN_FULL_SOURCEPATH(char_array, source_prefix, source_file) \
    sprintf(fullpath,"%s%s", source_file_path, source)

/*
 * Generate the full path for the executable from the path prefix and tokenid
 */
#define GEN_FULL_EXECPATH(char_array, execpath_prefix, tid) \
    sprintf(char_array,"%sexec%s",execpath_prefix, tid)

extern char *server;
extern char *user;
extern char *password;
extern char *database;

extern char *chroot_jail_path;
extern char *source_file_path;
extern char *execfilepath_prefix;
extern char *inputfilepath_prefix;
extern char *outputfilepath_prefix;
#endif
