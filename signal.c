// https://stackoverflow.com/questions/67743236/how-to-simulate-signals-ctrl-and-ctrlc-like-in-bash-using-c
// https://www.mkssoftware.com/docs/man5/struct_termios.5.asp
// https://bash.cyberciti.biz/guide/Main_Page 

/*
1	SIGHUP	Terminate	Terminal line hangup or parent process terminated
2	SIGINT	Terminate	Interrupt from keyboard (ctrl-c)
3	SIGQUIT	Terminate	Quit from keyboard (ctrl-\)
Ctrl+D is not a signal, it's EOF (End-Of-File). It closes the stdin pipe.
 If read(STDIN) returns 0, it means stdin closed, which means Ctrl+D was hit 
 (assuming there is a keyboard at the other end of the pipe).

To kill background process you can use the kill command and send SIGTERM (terminate command)

Let’s display the process identifier (PID), the parent process identifier (PPID) 
and the process group identifier (PGID) of all the processes associated with 
our shell with the ps command:
	ps -eo "%c: [PID = %p] [PPID = %P] [PGID = %r]" | grep $$
*/

/*
Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

• In interactive mode:
◦ ctrl-C displays a new prompt on a new line. // print "^C" // exit_status = 130
◦ ctrl-D exits the shell. // print "exit"                   // exit_status = 0
◦ ctrl-\ does nothing.                                      // exit_status = 0
*/

#include "sh.h"

// static void	signal_handle(int signum)
// {
// 	// if (signum == SIGINT)
// 	// {
// 	// 	ft_putendl_fd("^Ccc", 2);
// 	// 	// rl_replace_line("", 0);
// 	// }
// 	// if (signum == SIGINT) // && g_sig == 0
// 	// {
// 	// 	rl_replace_line("", 0);
// 	// 	printf("\nMinishell > ");
// 	// }
// 	// else if (signum == SIGINT && g_sig == 1)
// 	// 	printf("\n", signum);
// 	// if child

// 	// if parent 
// }

/* 
void	reset_attr(struct termios *saved)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, saved);
}
*/

void	print_new_line(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handle(int sig_num)
{
	if (sig_num == SIGINT)
		print_new_line();
		
}

// 1. term parent prosess
// 2. handle "Ctrl-C"
// 3. ignore "Ctrl-\"
void	manage_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sig_handle; // Clear the signal mask
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGHUP, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}

/*
DONE:
Ctrl+D:
	- in an empty prompt quit the program: exit_status 0
	- in a promt after we wrote some stuff does nothing: exit_status 0

Ctrl+\:
	- in a promt after we wrote some stuff does nothing: exit_status 0
	- in an empty prompt does nothing: exit_status 0

Ctrl+C:
	- displays a new prompt on a new line: exit_status 
*/




// static void	signal_handle(int signal)
/* {
	// pid_t	pid;

	// (void)context;
	// (void)signal;
	// pid = info->si_pid;
	if (signal == SIGHUP)
		printf("Terminal line hangup or parent process terminated\n");
	else if (signal == SIGINT)
	{
		ft_putendl_fd("^CCC", 1);
		return ;
	}
	// else if (signal == SIGQUIT)
	// {
	// 	return ;
	// }
} */
