/*
 * daemonize.c * This example daemonizes a process, writes a few log messages, * sleeps 20 seconds and terminates afterwards.  */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "log.h"

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

void handler( int signalNumber )
{
	if( signalNumber == SIGUSR1 )
	{
		syslog(LOG_NOTICE, "sigusr1 called");
		entry("poorna", "admin", "login");
	}
	else if( signalNumber == SIGUSR2 )
	{
		syslog(LOG_NOTICE, "sigusr2 called");
		entry("poorna", "admin", "logout");
	}
}

int main()
{
    skeleton_daemon();

	if( signal(SIGINT, handler) == SIG_ERR )
	{
		syslog(LOG_NOTICE, "signal error");
	}
	else
	{
		syslog(LOG_NOTICE, "signal success");
	}

    while (1)
    {
        syslog (LOG_NOTICE, "First daemon started.");
        sleep (20);
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
