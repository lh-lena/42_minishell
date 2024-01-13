// https://trusted-weeder-eb7.notion.site/Shell-Bash-6e0f0290a0304dad93a1d25ba15d92fe
// https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_12_01.html
// https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
// https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
// https://www.youtube.com/watch?v=cIBmeEpsMj0&list=PLxIRFba3rzLzxxZMMbrm_-mkI7mV9G0pj
// https://42-cursus.gitbook.io/guide/rank-03/minishell-todo/functions
// https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1
// https://www.geeksforgeeks.org/developing-linux-based-shell/ 
// https://www.cs.princeton.edu/courses/archive/fall15/cos217/asgts/07shell/index.html
// https://www.cs.princeton.edu/courses/archive/fall15/cos217/asgts/07shell/shellsupplementary.html

// https://hackmd.io/@laian/B1A0_LSPn
// https://explainshell.com/
// https://github.com/achrafelkhnissi/minishell/tree/main 


// parser
// https://tomassetti.me/guide-parsing-algorithms-terminology/
// https://www.youtube.com/watch?v=bxpc9Pp5pZM


// pipe
// https://www.cs.uleth.ca/~holzmann/C/system/shell_does_pipeline.pdf

/*
-------------- How to write a (shell) lexer --------------

https://stackoverflow.com/questions/5491775/how-to-write-a-shell-lexer-by-hand
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_10

// ps | grep ls >> file ; make && ./a.out

https://dev.to/harshbanthiya/writing-my-own-minimal-shell-in-c-part-3-the-parsing-process-leading-to-an-execution-tree-42cj 

*/

/*
	Stage 1: Lexical Analysis
	Stage 2: Syntactic Analysis
	Stage 3: Handling Executable Binary Commands
	Stage 4: Handling Shell Built-In Commands
			+ Handling Handle environment variables
	Stage 5: Handling Redirection
	Stage 6: Handling Signals
	Error Handling
	Memory Management

	Parsing a command line
	Building a tree
*/

#include "sh.h"

void	dir_tr(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	printf("first pwd = %s\n", data->pwd);
	chdir(data->argv[1]);
	data->pwd = getcwd(NULL, 0);
	printf("pwd to given directory = %s\n", data->pwd);
}

void	execve_tr(t_data *data)
{
	pid_t	pid;
	int		val;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		val = execve(data->argv[0], data->argv, data->envp);
		if (val == -1)
			perror("Error execve()\n");
	}
	else
		wait(NULL);
}

/*
Allowed func-s:

readline

rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,

printf, malloc, free, write, access, open, read,
close, 

fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,

getcwd, chdir, stat, lstat, fstat, unlink, execve,

dup, dup2, pipe, opendir, readdir, closedir,

strerror, perror, isatty, ttyname, ttyslot, ioctl,

getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs 
*/

/*

*/


/*
% echo $?
// to print previous prompt number
 (exit 1 -> echo $? (1))

ohladkov@c4c1c5:~/Documents/sh$ ls -l [Vv]*
ls: cannot access '[Vv]*': No such file or directory
ohladkov@c4c1c5:~/Documents/sh$ echo $(ls -l)
total 68 -rwxr-xr-x 1 ohladkov 2023_berlin 16864 Dec 26 12:19 a.out -rw-r--r-- 1 ohladkov 2023_berlin 0 Dec 26 13:59 file2.txt -rw-r--r-- 1 ohladkov 2023_berlin 493 Dec 26 13:56 file.txt -rw-r--r-- 1 ohladkov 2023_berlin 2139 Dec 25 17:44 ft_split.c -rw-r--r-- 1 ohladkov 2023_berlin 513 Dec 26 15:23 main.c -rw-r--r-- 1 ohladkov 2023_berlin 1715 Dec 26 15:12 sh.h -rw-r--r-- 1 ohladkov 2023_berlin 1374 Dec 26 15:26 str_utils.c -rw-r--r-- 1 ohladkov 2023_berlin 24816 Dec 26 15:10 tr_sh.c
ohladkov@c4c1c5:~/Documents/sh$ echo "$(ls -l)"
total 68
-rwxr-xr-x 1 ohladkov 2023_berlin 16864 Dec 26 12:19 a.out
-rw-r--r-- 1 ohladkov 2023_berlin     0 Dec 26 13:59 file2.txt
-rw-r--r-- 1 ohladkov 2023_berlin   493 Dec 26 13:56 file.txt
-rw-r--r-- 1 ohladkov 2023_berlin  2139 Dec 25 17:44 ft_split.c
-rw-r--r-- 1 ohladkov 2023_berlin   513 Dec 26 15:23 main.c
-rw-r--r-- 1 ohladkov 2023_berlin  1715 Dec 26 15:12 sh.h
-rw-r--r-- 1 ohladkov 2023_berlin  1374 Dec 26 15:26 str_utils.c
-rw-r--r-- 1 ohladkov 2023_berlin 24816 Dec 26 15:10 tr_sh.c
ohladkov@c4c1c5:~/Documents/sh$ echo hello\!
hello!
ohladkov@c4c1c5:~/Documents/sh$ echo "hello\!"
hello\!
ohladkov@c4c1c5:~/Documents/sh$ echo "\"
> ^C
ohladkov@c4c1c5:~/Documents/sh$ echo \
> ^C
ohladkov@c4c1c5:~/Documents/sh$ echo x\ty
xty
ohladkov@c4c1c5:~/Documents/sh$ echo "x\ty"
x\ty
ohladkov@c4c1c5:~/Documents/sh$ echo -e x\ty
xty
ohladkov@c4c1c5:~/Documents/sh$ echo -e "x\ty"
x	y
ohladkov@c4c1c5:~$ cd x
bash: cd: x: No such file or directory

*/

/*
// https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/dup2.html

int main(int argc, char **argv)
{
	int pid, status;
	int newfd;	// new file descriptor
	char *cmd[] = { "/bin/ls", "-al", "/", 0 };

	if (argc != 2) {
		fprintf(stderr, "usage: %s output_file\n", argv[0]);
		exit(1);
	}
	if ((newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
		perror(argv[1]);	// open failed 
		exit(1);
	}
	printf("writing output of the command %s to \"%s\"\n", cmd[0], argv[1]);

	//  this new file will become the standard output 
	//  standard output is file descriptor 1, so we use dup2 to 
	//  to copy the new file descriptor onto file descriptor 1 
	// dup2 will close the current standard output

	dup2(newfd, 1); 

	// now we run the command. It runs in this process and will have
	// this process' standard input, output, and error

	execvp(cmd[0], cmd);
	perror(cmd[0]);		// execvp failed 
	exit(1);
} */

/*
// https://velog.io/@dogfootbirdfoot/Minishell-function
// https://velog.io/@dogfootbirdfoot/Minishell-Signal 

rl_on_new_line - Повідомте функції оновлення, що ми перемістили на новий (порожній) рядок, зазвичай після виведення нового рядка.

rl_replace_line - Замініть вміст rl_line_buffer текстом. Крапка і позначка, якщо можливо, збережені. Якщо clear_undo не дорівнює нулю, список скасувань, пов’язаний із поточним рядком, очищається.
 void rl_replace_line (const char *text, int clear_undo);

add_history

Розмістіть рядок у кінці списку історії. Поле пов’язаних даних (якщо воно є) має значення NULL. Якщо максимальну кількість записів історії було встановлено за допомогою stifle_history(), і нова кількість записів історії перевищить цей максимум, найстаріший запис історії буде видалено.
Розмістіть рядок у кінці списку історії. Пов’язані поля даних мають значення NULL. Якщо кількість елементів історії перевищує максимальну, старіші елементи видаляються.

Заголовок:#include <readline/history.h>
форма:add_history(const char *string)

wait3

Функція, яка очікує завершення дочірнього процесу та повідомляє про стан і використання ресурсів завершеного процесу.

Заголовок:#include <sys/wait.h>
форма:pid_t wait3(int *statloc, int options, struct rusage *rusage)
фактор:
statloc: містить інформацію про статус завершення дочірнього процесу.
параметри: Ви можете встановити параметри під час перевірки статусу завершення процесу.
rusage: містить інформацію про використання ресурсів дочірніми процесами.
Значення, що повертається: ID процесу в разі успіху, -1 у разі невдачі, виконується з опцією WNOHANG, повертається 0, якщо дочірній процес ще не завершено.
wait4

форма:pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage)
фактор:
pid: очікує лише процес, який відповідає pid.

getcwd

Копіює абсолютний шлях поточного робочого каталогу до buf і повертає покажчик на buf.
Якщо buf дорівнює NULL, виділяється порожнє місце, а розмір ігнорується.
Якщо буфер малий, можуть виникнути помилки, тому зробіть його великим.

Заголовок:#include <unistd.h>
форма:char *getcwd(char *buf, size_t size)
фактор:
char *buf: буфер для зберігання рядка робочого каталогу
size_t size: Розмір буфера
Повернене значення: повертає поточний робочий каталог у разі успіху, повертає вказівник NULL у разі помилки та встановлює errno.

chdir

Змінити поточний робочий каталог.
Ви повинні мати дозвіл на виконання для каталогу (змінити каталог) . Шлях не повинен починатися з "\".

Заголовок:#include <unistd.h>
форма:int chdir(const char *path)
фактор:
const char *шлях: шлях
Значення, що повертається: 0 у разі успіху, -1 у випадку невдачі, зберігається в errno.

stat

Функція, яка отримує статус або інформацію про файл, наприклад його розмір, дозволи, дату створення та дату останньої зміни. Якщо ви передаєте файл, який є символічним посиланням на шлях, ви отримаєте інформацію про вихідний файл. lstatФункція отримує інформацію про сам файл символічного посилання.

Заголовок:#include <sys/stat.h>
форма:int stat(const char *path, struct stat *buf)
фактор:
const char *path: ім'я файлу або відносний/абсолютний шлях до файлу
buf: структура buf для збереження стану та інформації про файл

Інформація про структуру: https://www.it-note.kr/173
Значення, що повертається: 0 у разі успіху, -1 у випадку невдачі, зберігається в errno.

lstat

Вона має ту саму функцію, що й функція stat.
Якщо ви передасте файл символічного посилання до шляху, ви отримаєте інформацію про сам файл символічного посилання.

форма:int lstat(const char *path, struct stat * buf)

fstat

Функція, яка отримує статус файлу або інформацію про файл, таку як розмір відкритого файлу, дозволи на файл, дату створення файлу та дату останньої зміни.

форма:int fstat(int fd, struct stat *buf)
фактор:
fd: дескриптор файлу, створений за допомогою open тощо.
buf: структура buf для збереження стану та інформації про файл
Значення, що повертається: 0 у разі успіху, -1 у випадку невдачі, зберігається в errno

open

Відкрийте файл, щоб використати його. fopen()це функція, що надається бібліотекою C і open()є функцією, що надається Linux.

Заголовок:#include <fcntl.h>
форма:int open (const char *FILENAME, int FLAGS[, mode_t MODE])
взяти на себе:
char *FILENAME: ім'я цільового файлу
int FLAGS: відкрити параметри для файлу
[, mode_t MODE]: права доступу до файлу, визначені під час створення файлу за допомогою параметра O_CREAT.
Значення, що повертається: значення fd (додатне число) у разі успіху, -1 у випадку невдачі.

unlink  - Видалити посилання.

Заголовок:#include <unistd.h>
форма:int unlink(const char *path)
Аргументи: назва посилання, яке потрібно видалити
Повернення: 0 в разі успіху, -1 в разі невдачі.

close

open()Закриває файл, відкритий функцією.

Заголовок:#include <unistd.h>
форма:int close(int fd)
Аргументи: дескриптор файлу
Повернення: 0 в разі успіху, -1 в разі невдачі.
read

open()Читає вміст файлу, відкритого за допомогою функції.

Заголовок:#include <unistd.h>
форма:ssize_t read(int fd, void *buf, size_t n)
взяти на себе:
int fd: дескриптор файлу
void *buf: буфер для читання файлу
size_t n: розмір буфера
Повернення: кількість байтів, прочитаних у разі успіху, -1 у разі помилки.

write

open()Записує у файл, відкритий за допомогою функції.

Заголовок:#include <unistd.h>
форма:ssize_t write(int fd, const void *buf, size_t n)
взяти на себе:
int fd: дескриптор файлу
void *buf: буфер, що містить вміст, який буде записано у файл
size_t n: кількість боїв для запису
Повернення: кількість байтів, записаних у разі успіху, -1 у разі помилки.

waitpid

wait()Подібно функції, він чекає завершення дочірнього процесу. Різниця полягає в тому, що wait() функція звільняється від очікування, коли будь-який із дочірніх процесів завершується, але вона waitpid()чекає, поки не завершиться певний дочірній процес.

Заголовок:#include <sys/wait.h>
форма:pid_t waitpid(pid_t pid, int *status, int options)
взяти на себе:
pid_t pid: PID дочірнього процесу для моніторингу
int *status: інформація про стан виходу дочірнього процесу
int options: параметри для очікування
повернення:
0: коли використовувався WNOHANG і дочірній процес не було припинено
-1 : невдача
PID дочірнього процесу: завершити дочірній процес

wait

Дочекайтеся завершення дочірнього процесу.

Заголовок:#include <sys/wait.h>
форма:pid_t wait(int *status)
Аргументи: інформація про стан виходу дочірнього процесу
Повертає: завершений PID дочірнього процесу

pipe

Створіть трубу та призначте значення fd для труби fildes.

Заголовок:#include <unistd.h>
форма:int pipe(int fildes[2])
Вміст, записаний у fildes[1], кінець запису, можна читати через fildes[0], кінець читання.
dup2Конвеєр може бути реалізований шляхом спрямування stdout до кінця запису та stdin до кінця читання.

dup

Скопіюйте дескриптор файлу. Покажчики читання/запису оригінального дескриптора та скопійованого дескриптора є спільними.

Заголовок:#include <unistd.h>
форма:int dup(int fildes)
Аргументи: дескриптор файлу
Повернення: автоматично призначається та повертається найменше число серед скопійованих чисел fd. У разі помилки повертається -1.

dup2

Скопіюйте файловий дескриптор fd і призначте його fd2. (так що fd2 також вказує на файл, на який вказує fd)

Заголовок:#include <unistd.h>
форма:int dup2(int fildes, int fildes2)

dup() Примітка. Є функції, які створюють копію дескриптора файлу dup2(). dup()Автоматично призначається один невикористаний номер дескриптора, але dup2()ви можете вказати будь-яке число. Якщо вказаний номер уже використовується, файл автоматично закривається та призначається знову.

execve

Змінює процес, який викликав функцію execve, на новий процес.

Заголовок:#include <unistd.h>
форма:int execve(const char *path, char *const argv[], char *const envp[])
взяти на себе:
const char *шлях: повна назва шляху
char *const argv[] : список аргументів
char *const envp[]: список налаштувань
Повернення: -1 у разі невдачі

fork

Створює копію процесу для поточного процесу.

Заголовок:#include <unistd.h>
форма:pid_t fork(void)
повернення:
-1 : невдача
0: дочірній процес дорівнює 0 (щойно створений процес)
Позитивне число: PID створеного дочірнього процесу

strerror

Заголовок:#include <string.h>
форма:char *strerror(int errnum)
повернення:
Повертає вказівник на рядок, що відповідає errnum.
Якщо errnum не визначено, повертається рядок «Невідома помилка: значення аргументу».
errno

Заголовок:#include <sys/errno.h>
форма:extern int errno
Повернути: номер останньої помилки, яка сталася

exit

Припиніть процес.

Заголовок:#include <stdlib.h>
форма:void exit(int status)
Аргумент: int main()ціле число, що відповідає значенню, що повертається функцією
opendir

Відкрити вказаний каталог
Використовується для пошуку файлів і каталогів у певному каталозі.

Заголовок:#include <dirent.h>
форма:DIR *opendir(const char *filename)
Аргументи: відкрити цільовий каталог
повернення:
Покажчик DIR: успіх
NULL: помилка

readdir

opendir()Для відкритого каталогу отримайте інформацію про всі файли та каталоги в ньому.

Заголовок:#include <dirent.h>
форма:struct dirent *readdir(DIR *dirp)
Аргументи: Відкрита інформація каталогу
повернення:
Інформація про файл або каталог: успіх
NULL: помилка
closedir

opendir()Закрийте відкритий каталог.

Заголовок:#include <dirent.h>
форма:int closedir(DIR *dirp)
Аргументи: Відкрита інформація каталогу
повернення:
0: успіх
-1 : невдача

isatty

fdВизначте, чи є посилання на дійсний термінальний пристрій.

Заголовок:#include <unistd.h>
форма:int isatty(int fd)
повернення:
1: Успіх
0: Помилка (встановіть значення помилки на errno)

ttyname

isatty Якщо функція знаходить дійсний пристрій, вона повертає назву пристрою.

Заголовок:#include <unistd.h>
форма:char *ttyname(int fd)
повернення:
Назва пристрою закінчується на null
NULL: помилка

ttyslot

Коли файл пристрою знайдено, повертається його унікальний номер.

Заголовок:#include <unistd.h>
форма:int ttyslot(void)
повернення: номер
0: невдача

ioctl

Функція для отримання інформації про керування обладнанням і стан

Заголовок:#include <sys/ioctl.h>
форма:int ioctl(int fd, unsigned long request, ...)
взяти на себе:
int fd: open значення fd одного пристрою
непідписаний довгий запит: команда, яка надсилається на пристрій

getenv

Знайдіть потрібне значення змінної зі списку змінних середовища.

Заголовок:#include <stdlib.h>
форма:char *getenv(const char *name)
Аргументи: назва змінної середовища для отримання
Повертає: значення змінної середовища типу char*
tcgetattr

Зберігайте властивості терміналу для файлу терміналу fd у termios_p

Заголовок:#include <termios.h>
форма:int tcgetattr(int fd, struct termios *termios_p)
взяти на себе:
const struct termios *termios_p: Адреса для зберігання властивостей терміналу
повернення:
0: успіх
-1: помилка (встановіть значення помилки на errno

tcsetattr

Встановити властивості терміналу для файлу терміналу fd

Заголовок:#include <termios.h>
форма:int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)
взяти на себе:
Значення, які int optional_actions може мати:
TCSANOW: негайно змініть властивості
TCSADRAIN: змінити після завершення передачі
TCSAFLUSH: зміна після завершення надсилання та отримання
const struct termios *termios_p: Адреса для зберігання властивостей терміналу
повернення:
0: успіх
-1: помилка (встановіть значення помилки на errno)

tgetent

bpВитягніть ім’я терміналу, введене в буфер.

Заголовок:
#include <curses.h>
#include <term.h>
форма:int tgetent(char *bp, const char *name)
взяти на себе:
char *bp: це має бути буфер типу char розміром 1024, і він підтримуватиметься, навіть якщо згодом будуть викликані функції tgetnum(), тощо.tgetflga()tgetstr()
const char *name: назва терміналу
повернення:
1: Успіх
0: Немає відповідного елемента (назва терміналу)
-1: база даних не знайдена

tgetflag

idлогічна інформація про те, чи існує в записі терміналу

Заголовок:
#include <curses.h>
#include <term.h>
форма:int tgetflag(char *id)
повернення:
1: існування
0: Не існує

tgetnum

id Числова інформація про те, чи існує в записі терміналу

Заголовок:
#include <curses.h>
#include <term.h>
форма:int tgetnum(char *id)
повернення:
Позитивне число: числова інформація
-1: Не існує

tgetstr

idРядкова інформація про те, чи існує в записі терміналу

Заголовок:
#include <curses.h>
#include <term.h>
форма:char *tgetstr(char *id, char **area)
повернення:
Покажчик на рядок: інформація про рядок (також зберігається в char **області)
NULL: не існує

tgoto

Створює екземпляр параметра з указаною функцією. Повернене значення tputs передається функції.

Заголовок:
#include <curses.h>
#include <term.h>
форма:char *tgoto(const char *cap, int col, int row)
tputs

tgetstr Вивід рядка повернуто з

Заголовок:
#include <curses.h>
#include <term.h>
форма:int tputs(const char *str, int affcnt, int (*putc)(int))
Повертає: tgetstr рядок повертається з

Перенаправлення введення/виведення
<: перенаправлення введення
	Змініть стандартний напрямок введення, підключений до клавіатури, на файл.

<<: перенаправлення введення
	Вхідні дані приймаються, доки не зустрінеться слово, введене як роздільник.

>: перенаправлення виводу
	Якщо файл не існує, він створюється автоматично, а якщо він уже існує, існуючий файл перезаписується.

>>: перенаправлення виводу
	Файл уже існує, а вихідні дані додаються до наявного вмісту, а не перезаписуються.


*/
