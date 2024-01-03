// https://www.youtube.com/watch?v=DiNmwwQWl0g&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=12

// two types an error
// 1. 'ping' doesn't exist 
// 2. ping is found, is executed, but it gives an error
/*
int pid;

pid = fork();
if (pid == -1)
	return (1);
if (pid == 0)
{
	// Child process
	int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
	if (err == -1)
	{
		printf("couldn't find program to execute!\n");
		return (2);
	}
}
else
{
	int	wstatus;
	// Parent process
	wait(&wstatus);
	if (WIFEXITED(wstatus))// if true-> normal termination. Program finish execution normally
	{
		int status_code = WEXITSTATUS(wstatus); // value executed with (in main == 0)
		if (status_code == 0)
			printf("Success\n");
		else
			printf("Failure with status code %d\n", status_code);
	}
	printf("Success!\n");
}

return (0);
*/