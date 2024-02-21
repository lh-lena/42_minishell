TODO:


1.
$ <
$ cat ||
$ ||



error handling:

== 1 ==
minishell$ cta | ls
arr_utils.c  expand_str.c           helpers.c      return_state
arr_utils.o  expand_str.o           helpers.o      run_cmd_utils.c
cd.c         expand_str_utils_2.c   heredoc.c      run_cmd_utils.o
EXPECTED: 
ohladkov@c4c1c5:~/Documents/cpp$ cta | ls
Module_00  Module_02  Module_04  Module_06  Module_08
Module_01  Module_03  Module_05  Module_07  README.md
Command 'cta' not found, did you mean:
...
== 2 ==
minishell$ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
Invalid file name
bye
EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell (copy)$ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
bash: ./outfiles/outfile01: No such file or directory

== 3 ==
minishell$ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
File not found
Invalid file name
arr_utils.c export.o minishell_tester

EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell (copy)$ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
bash: missing: No such file or directory

== 4 ==
minishell$ cat >./test_files/invalid_permission <missing 
File not found
Invalid file name
^C(stuck)
EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell (copy)$ cat >./test_files/invalid_permission <missing 
bash: ./test_files/invalid_permission: No such file or directory
ohladkov@c4c1c5:~$ echo $?
1

minishell$ cat >./test_files/invalid_permission <
zsh: segmentation fault (core dumped)  ./minishell
ohladkov@c4c1c5:~$ cat >./test_files/invalid_permission <
bash: syntax error near unexpected token `newline'
ohladkov@c4c1c5:~$ echo $?
2
== 5 ==
minishell$ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
Invalid file name
hi
bye

EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell (copy)$ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
bye
bash: ./outfiles/outfile01: No such file or directory

== 6 ==
minishell$ cat , free.c
cat: ,: No such file or directory
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */

EXPECTED: 
ohladkov@c4c1c5:~$ cat , free.c
cat: ,: No such file or directory
cat: free.c: No such file or directory

== 7 ==
minishell$ <
bash: No such file or directory
EXPECTED: 
ohladkov@c4c1c5:~$ <
bash: syntax error near unexpected token `newline'


== 8 ==
minishell$ >
Invalid file name
EXPECTED: 
ohladkov@c4c1c5:~$ >
bash: syntax error near unexpected token `newline'

== 9 == 
minishell$ echo hi 2> testfile
hi 2> testfile
EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell2$ echo hi 2> testfile
hi

== 10 ==
minishell$ echo hi 2>> testfile
hi 2>> testfile
EXPECTED: 
ohladkov@c4c1c5:~/Documents/minishell2$ echo hi 2>> testfile
hi

== 11 ==
minishell$ ls >>./test_files/invalid_permission
Invalid file name
arr_utils.c  execute.o             get_path.c             main.c            sh.h
arr_utils.o  exit.c                get_path.o             main.o            signal.c
cd.c         exit.o                get_replaced_string.c  Makefile          si
EXPECTED:
ohladkov@c4c1c5:~/Documents/minishell2$ ls >>./test_files/invalid_permission
bash: ./test_files/invalid_permission: No such file or directory
ohladkov@c4c1c5:~/Documents/minishell2$ echo $?
1






--------------------------------------------
== 1 ==
