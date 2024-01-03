// https://stackoverflow.com/questions/67743236/how-to-simulate-signals-ctrl-and-ctrlc-like-in-bash-using-c
// https://www.mkssoftware.com/docs/man5/struct_termios.5.asp

/*
1	SIGHUP	Terminate	Terminal line hangup or parent process terminated
2	SIGINT	Terminate	Interrupt from keyboard (ctrl-c)
3	SIGQUIT	Terminate	Quit from keyboard (ctrl-\)
Ctrl+D is not a signal, it's EOF (End-Of-File). It closes the stdin pipe.
 If read(STDIN) returns 0, it means stdin closed, which means Ctrl+D was hit 
 (assuming there is a keyboard at the other end of the pipe).


Let’s display the process identifier (PID), the parent process identifier (PPID) 
and the process group identifier (PGID) of all the processes associated with 
our shell with the ps command:
	ps -eo "%c: [PID = %p] [PPID = %P] [PGID = %r]" | grep $$
*/
#include "sh.h"

// static void	handler_sig_quit(int sig)
// {
	// if (sig == SIGINT)
	// 	printf("QUIT\n");
	// if (signum == SIGINT && g_sig == 0)
	// {
	// 	rl_replace_line("", 0);
	// 	ft_printf("\nMinishell > ", signum);
	// }
	// else if (signum == SIGINT && g_sig == 1)
	// 	ft_printf("\n", signum);
	// if child 
	
	// if parent 

// }

// 1. ignore "Ctrl-C"
// 2. ignore "Ctrl-Z"
// 3. ignore "Ctrl-\"
// void	manage_signal(void)
// {
// 	signal(SIGINT, handler_sig_quit);
// 	signal(SIGTSTP, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// static void	handle_signal(int signal, siginfo_t *info, void *context)
// {
// 	printf("Stop not allowed\n");
// }

// void	signals(void)
// {
// 	struct sigaction	sig_action;


// not finished
// 	sig_action.sa_sigaction = handle_signal;
// 	sig_action.sa_flags = SA_RESTART | SA_SIGINFO;
// 	sigemptyset(&sig_action.sa_mask);
// 	// if we had another sigaction set beforhand it would save in the third parametr
// 	if (sigaction(SIGINT, &sig_action, 0) == -1)
// 		perror("Error sigaction");
// 	if (sigaction(SIGQUIT, &sig_action, 0) == -1)
// 		perror("Error sigaction");
// 	if (sigaction(0, &sig_action, 0) == -1)
// 		perror("Error sigaction");
// }