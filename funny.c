/* Copyright (c) 1979 Regents of the University of California */


/* funny -
 * funny accepts a line from the user and prints it out in
 * a mildly amusing manner.
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define WORDLEN 200
char nl[] = { 015, 0};

char	is3a;

int rnd(int);
void rubout(int);

int
main(int ct, char **av)
{
	time_t cvec;
	int size,i;
	char order[WORDLEN];
	void pick(int, char *);
	void prch(int, char *, char *);
	char *word,current[WORDLEN],myline[WORDLEN],*src;

	if (ct > 1 && av[1][0] == '-') {
		is3a++;
		ct--;
		av++;
	}
	time(&cvec);
	srand(cvec);
	if (ct<2)
	{
		printf("Input a line - ");
		fflush(stdout);
		size=read(0,myline,WORDLEN)-1;
		myline[size]=0;
		src=myline;
	}
	else src=av[1];
	signal(2,rubout);
	word=src;
	size=0;
	while (*word++) size++;
	if (size>=WORDLEN)
	{
		printf("%s\nLINE TOO LONG.\n",src);
		exit(9);
	}
	word=src;
	for (;;)
	{
		for (i=0;i<size;++i) current[i]=040;
		pick(size,order);
		for (i=0;i<size;++i) prch(order[i],word,current);
		printf("\n");
	}
}

void
pick(int s, char *a)
{
	int i,j,r;
	char this[WORDLEN];
	for (i=0;i<s;++i) this[i]=i;
	for (i=s-1;i>=0;--i)
	{
		r=rnd(i+1);
		a[i]=this[r];
		this[r]=this[i];
	}
}

int
rnd(int i)
{
	int r;
	r=rand();
	if (r<0) r= -r;
	return(r % i);
}

/* nanosleep has an api that needs an api around it */
void
nsleep(long slp)
{
	struct timespec req;

	req.tv_sec = 0;
	req.tv_nsec = slp;
	(void)nanosleep(&req, NULL);
}

void
prch(int who, char *from, char *to)
{
	int i;
	to[who]=from[who];
	long slp = 100000L * (WORDLEN - strlen(from) * 2);
	
	if (is3a) {
		printf("\033=%c%c%c", ' '+23, ' '+who, to[who]);
		return;
	}
	for (i=0;i<=who;++i) {
		write(1,to+i,1);
		nsleep(slp);
	}
/*
	for (i=0;i<=who;++i) write(1,"\b",1);
*/
	write(1,nl,1);
}

void
rubout(int z)
{
	char *cp,resp[100];
	signal(2,SIG_DFL);
	printf("\nHad enough?");
	fflush(stdout);
	read(0,resp,100);
	cp=resp;
	while (*cp != 012 && *cp != 'y' && *cp !='n') ++cp;
	if (*cp == 'n')
	{
		signal(2,rubout);
		return;
	}
	exit(9);
}
