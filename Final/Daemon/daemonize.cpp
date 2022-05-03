/*
 * daemonize.c * This example daemonizes a process, writes a few log messages, * sleeps 20 seconds and terminates afterwards.  */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "log.h"

string to_string(int i)                                                                                                                {                                                                                                                                              char text[20];                                                                                                                         sprintf(text, "%d", i);                                                                                                                return string(text);                                                                                                           }

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

void sigusr1(int signo, siginfo_t *si, void *data )
{
	(void)signo;
	(void)data;
	char t[20];
	int k = si->si_uid;
	sprintf(t, "%d", (int)si->si_uid);
	string uid = string(t);
	string msg = "signal sigusr1 " +  uid;
	syslog(LOG_NOTICE, msg.c_str());
	entry("user id " + uid, "   ", "login");
}
void sigusr2(int signo, siginfo_t *si, void *data )
{
	(void)signo;
	(void)data;
	char t[20];
	sprintf(t, "%d", (int)si->si_uid);
	string uid = string(t);
	string msg = "signal sigusr2 " +  uid;
	syslog(LOG_NOTICE, msg.c_str());
	entry("user id " + uid, "   ", "logout");
}

int main()
{
    skeleton_daemon();


	struct sigaction sa1, sa2;
	memset(&sa1, 0, sizeof(sa1));
	sa1.sa_flags = SA_SIGINFO;
	sa1.sa_sigaction = sigusr1;
	if( sigaction(SIGUSR1, &sa1, 0) == -1 )
	{
		syslog(LOG_NOTICE, "sigaction usr1 error");
	}
	else
	{
		syslog(LOG_NOTICE, "sigaction  usr1 succes");
	}
	
	memset(&sa2, 0, sizeof(sa2));
	sa2.sa_flags = SA_SIGINFO;
	sa2.sa_sigaction = sigusr2;
	if( sigaction(SIGUSR2, &sa2, 0) == -1 )
		syslog(LOG_NOTICE, "sigaction usr2 error");
	else
		syslog(LOG_NOTICE, "sigaction  usr2 succes");
	
	/*
	if( signal(SIGUSR1, handler) == SIG_ERR )
	{
		syslog(LOG_NOTICE, "sigusr1 error");
	}
	else
	{
		syslog(LOG_NOTICE, "sigusr1 success");
	}

	if( signal(SIGUSR2, handler) == SIG_ERR )
	{
		syslog(LOG_NOTICE, "sigusr2 error");
	}
	else
	{
		syslog(LOG_NOTICE, "sigusr2 success");
	}
	*/

    while (1)
    {
        syslog (LOG_NOTICE, "First daemon started.");
        sleep (20);
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
