CFLAGS = -g -Wall -c
MYSQLCFLAGS = -I/usr/include/mysql  -DBIG_JOINS=1 -fPIC
MYSQLLFLAGS = -Wl,-Bsymbolic-functions -rdynamic -L/usr/lib/mysql -lmysqlclient
OBJS = check.o main.o exec.o
CC = gcc

judge : $(OBJS)
	$(CC) -g $(OBJS) $(MYSQLLFLAGS) -o judge

check.o : check.c check.h common.h
	$(CC) $(CFLAGS) $(MYSQLCFLAGS) check.c

exec.o : exec.c exec.h common.h
	$(CC) $(CFLAGS) $(MYSQLCFLAGS) exec.c

main.o : main.c check.h
	$(CC) $(CFLAGS) main.c

clean : 
	rm -f *.o judge
