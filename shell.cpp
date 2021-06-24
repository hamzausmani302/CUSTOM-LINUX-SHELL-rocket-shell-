#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>

#define N 16

using namespace std;
bool run_simple_commands(char *args[], int n);

char cmds[N][21] = {"banner", "cd", "exit", "help", "compile", "listdir", "whoisuser", "ip", "fpa", "replace", "fs", "halt", "sort", "rshell", "dummyfile", "man"};

char desc[N][100] = {
	"display our rocket shell banner",
	"to navigate to a folder",
	"exit out of rocket shell",
	"see the description of supported commands",
	"compile filees automatically on extension[.c , .cpp , .py]",
	"list directories only",
	"display current user",
	"get ip address of the host system",
	"full permsision to all files in the directory",
	"replace text in file",
	"display file system data",
	"halt the system for certain time to avoid sleep",
	"sort the given numbers in ascending or descending",
	"open multiple instances of shell",
	"create specidifed number of dummy files of txt extension"};

char usage[N][50] = {
	"banner",
	"cd {path}",
	"exit",
	"help",
	"compile filename.c",
	"listdir",
	"whoisuser",
	"ip",
	"fpa {path}",
	"replace {filename} {text} {substitute}",
	"fs -l",
	"halt 30 ----> 30 seconds pause",
	"sort -a/-d {Numbers} ----> Quantity of Numbers < 10",
	"rshell 2 ---->  2 shells",
	"dummyfile 3 ----> 3 dummy.txt files"};

void label()
{
	char arr[10][80] =
		{
			"...........|...........		MADE BY : \n",
			"........../.\\..........		MUHAMMAD IBAD SALEEM 19k-0220\n",
			".........|...|.........		ALI HAMZA USMANI 19k-0146\n",
			".........|.O.|.........\n",
			".........|...|.........\n",
			".ROCKET...\\./...SHELL..\n",
			"........../.\\..........\n",
			"........./ooo\\.........\n",
			".........|ooo|.........\n",
			".........|o.o|.........\n",

		};
	system("clear");

	for (int i = 0; i < 10; i++)
	{
		cout << "\t\t" << arr[i];
	}
	cout << endl;
	cout << endl;
}

int handle_greater_sign(char *args[], int n)
{
	char result[100] = "";
	int i = 0;

	int size = 0;
	while (args[size] != NULL)
	{

		size++;
	}

	while (i < n)
	{
		strcat(&result[0], args[i]);
		strcat(&result[0], " ");

		i++;
	}

	FILE *fd = popen(result, "r");
	char buffer[100];
	char res[200] = "";
	while (!feof(fd))
	{
		if (fgets(buffer, 100, fd) != NULL)
		{
			strcat(res, buffer);
		}
	}

	pclose(fd);

	ofstream file;
	file.open(args[n + 1]);

	file << res << endl;

	return 0;
}

int handle_append_operation(char *args[], int n)
{
	char result[100] = "";
	int i = 0;

	int size = 0;
	while (args[size] != NULL)
	{

		size++;
	}

	while (i < n)
	{
		strcat(&result[0], args[i]);
		strcat(&result[0], " ");

		i++;
	}

	FILE *fd = popen(result, "r");
	char buffer[100] = "";
	char res[200] = "";
	while (!feof(fd))
	{
		if (fgets(buffer, 100, fd) != NULL)
		{
			strcat(res, buffer);
		}
	}

	ofstream file;
	file.open(args[n + 1]);

	char buff[200] = "";
	strcat(buff, res);

	strcat(buff, buff);
	cout << buff << endl;
	file << buff;
	pclose(fd);

	file.close();

	return 0;
}

int caller(char *args[], int n)
{
	int i = 0;
	while (args[i] != NULL)
	{

		if (strcmp(args[i], ">") == 0)
		{

			handle_greater_sign(args, i);
			sleep(1);
			return 1;
		}
		else if (strcmp(args[i], ">>") == 0)
		{
			handle_append_operation(args, i);
			sleep(1);
			return 1;
		}

		i++;
	}
	return -1;
}

size_t getsizeoffile(const char *filename)
{
	struct stat fi;
	if (stat(filename, &fi) != 0)
	{
		return -1;
	}
	return fi.st_size;
}

void concat(char *c1, char c2[], char c3[])
{
	int s1 = strlen(c2);
	int s2 = strlen(c3);
	int i = 0;
	int x = 0;
	for (int i = 0; i < s1; i++)
	{
		c1[i] = c2[i];
		x = i;
		s1++;
	}

	c1[s1++] = ':';
	c1[s1++] = '-';
	for (int i = 0; i < s2; i++)
	{
		c1[s1 + i] = c3[i];
		x = i;
	}

	c1[x] = '\0';
}

char *crntpath(char output[])
{
	//char *path=NULL;
	char user[20];
	char path[50];
	char *path1 = &path[0];
	int size = 50;
	path1 = getcwd(path1, size);

	strcpy(output, getenv("USER"));
	strcat(output, ":~");
	strcat(output, path);
	strcat(output, ">>>");
	return &output[0];
}

bool take_input(char *buffer)
{
	char output[80];
	char *tmp = readline(crntpath(output));
	if (strlen(tmp) == 0 || tmp == NULL)
	{

		return false;
	}
	else
	{
		add_history(tmp);
		strcpy(buffer, tmp);
		return true;
	}
	cout << endl;
}
bool ispipeexist(char *args[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(args[i], "|") == 0)
		{
			return true;
		}
	}
	return false;

	//for custom commands
}
void getindexofpipe(char *args[], int nargs, int *indexofpipe)
{
	for (int i = 0; i < nargs - 1; i++)
	{
		if (strcmp(args[i], "|") == 0)
		{
			*indexofpipe = i;
			return;
		}
	}
}
//this is for future to handle mulitple pipes
int getnumberofpipes(char *args[], int nargs)
{
	int count = 0;
	for (int i = 0; i < nargs - 1; i++)
	{
		if (strcmp(args[i], "|") == 0)
		{
			count++;
		}
	}
	return count;
}

void copy(char *args[], char *dest[], int start, int limit)
{
	int j = 0;
	for (int i = start; i < limit; i++)
	{
		dest[j] = args[i];
		j++;
	}
}

void run_piped_commands(char *args[], int nargs)
{
	//seperate command using | strsep
	int pipefd[2];
	int indexofpipe;
	pipe(pipefd);
	getindexofpipe(args, nargs, &indexofpipe);
	//cout << endl <<  "index of pipe=  "<< indexofpipe << endl;

	//array for first command
	char *p1args[10];
	//array for second command
	char *p2args[10];
	copy(args, p1args, 0, indexofpipe);
	copy(args, p2args, indexofpipe + 1, nargs);
	p1args[indexofpipe] = NULL;
	p2args[nargs - indexofpipe - 1] = NULL;
	int i = 0;

	//run commands in exec
	pid_t c1 = fork();
	pid_t c2;
	if (c1 == 0)
	{

		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execvp(p1args[0], p1args) < 0)
		{
			cout << "command not found " << endl;
		}
	}
	else if (c1 > 0)
	{
		//sleep(1);
		c2 = fork();
		if (c2 == 0)
		{

			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(p2args[0], p2args) < 0)
			{
				cout << "command not found " << endl;
			}
		}
		else
		{
			wait(NULL);
			sleep(1);
		}
	}
	else
	{
		cout << "error forking " << endl;
	}
}

void help()
{
	cout << "\n***WELCOME TO ROCKET SHELL HELP MANUAL\n-Use the shell at your own risk...\nList of Commands supported:\n>cd \n>ls\n>exit\n>all other general commands available in UNIX shell\n>pipe handling\n>improper space handling";
	cout<<endl;
	for (int i = 0; i < N; i++)
	{
		cout << i << ") " << cmds[i] << endl
			 << "\t" << desc[i] << endl;
	}
	cout << endl;
}

bool compile(char *extn, int len)
{
	char tmp[50];
	strcpy(tmp, extn);
	char *args[4];
	int i = 0;
	char *spl = NULL;
	while ((spl = strsep(&extn, ".")) != NULL)
	{
		args[i] = spl;
		i++;
	}
	int j = 0;

	char *cmdargs[10] = {NULL};

	if (args[1] != NULL)
	{
		//cout << args[1] << endl;
		if (strcmp(args[1], "c") == 0)
		{
			char gcc[4] = "gcc";
			char o[3] = "-o";
			cmdargs[0] = &gcc[0];

			cmdargs[1] = &tmp[0];

			cmdargs[2] = &o[0];
			cmdargs[3] = args[0];

			cmdargs[4] = NULL;

			if (run_simple_commands(cmdargs, 5))
			{
				cout << "Compilation Successful" << endl;
			}
			else
			{
				cout << "error compiling" << endl;
				return false;
			}
		}
		else if (strcmp(args[1], "py") == 0)
		{
			char gcc[7] = "python";
			cmdargs[0] = &gcc[0];
			cmdargs[1] = &tmp[0];
			cmdargs[2] = NULL;
			if (run_simple_commands(cmdargs, 3))
			{
				cout << "Compilation Successful" << endl;
			}
			else
			{
				cout << "error compiling" << endl;
				return false;
			}
		}
		else if (strcmp(args[1], "cpp") == 0)
		{
			char gcc[4] = "g++";
			char o[3] = "-o";
			cmdargs[0] = &gcc[0];

			cmdargs[1] = &tmp[0];

			cmdargs[2] = &o[0];
			cmdargs[3] = args[0];

			cmdargs[4] = NULL;

			if (run_simple_commands(cmdargs, 5))
			{

				cout << "Compilation Successful" << endl;
				//return true;
			}
			else
			{
				cout << "error compiling" << endl;
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
void *alam(void *args)
{
	int *val = (int *)args;
	int i = 0;
	cout << "timer set for " << *val << " seconds" << endl;
	while (i < *val)
	{
		i++;
	};
	cout << "ended timer" << endl;
	return NULL;
}

void sig_handler(int signum)
{
	cout << "alarm is set " << signum << endl;
}
void run_own_command(char *args[], int num, char *cmd)
{
	//cout << "init"<<endl;

	if (strcmp(args[0], "cd") == 0)
	{
		chdir(args[1]);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		label();
		sleep(2);
		system("clear");

		cout << "Closing and opening the new terminal" << endl;
		sleep(2);

		system("exit");

		exit(0);
	}
	else if (strcmp(args[0], "help") == 0)
	{
		cout << "help" << endl;
		help();
	}
	else if (strcmp(args[0], "compile") == 0)
	{

		if (args[1] == NULL || strcmp(args[1], "") == 0)
		{
			cout << "Invalid Command\n";
			return;
		}
		char *tmp = args[1];
		compile(tmp, strlen(tmp));
	}
	else if (strcmp(args[0], "listdir") == 0)
	{

		struct dirent *files;
		char path[50] = "";
		char *tmp = strcpy(&path[0], getcwd(&path[0], sizeof(path)));
		if (args[1] != NULL && strcmp(args[1], " ") != 0 && strcmp(args[1], "") != 0)
		{
			strcat(tmp, "/");
			strcat(tmp, args[1]);
		}

		DIR *srcdir = opendir(tmp);
		if (srcdir == NULL)
		{
			perror("opendir");
			return;
		}

		while ((files = readdir(srcdir)) != NULL)
		{
			struct stat st;

			if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0)
				continue;

			if (fstatat(dirfd(srcdir), files->d_name, &st, 0) < 0)
			{
				continue;
			}

			if (S_ISDIR(st.st_mode))
			{
				cout << files->d_name << endl;
			}
		}
		closedir(srcdir);
	}
	else if (strcmp(args[0], "whoisuser") == 0)
	{
		char *user = getenv("USER");
		cout << "You are currently logged in as " << user << endl;
	}
	else if (strcmp(args[0], "ip") == 0)
	{

		char getip[50] = "/ip.sh";
		args[0] = &getip[0];
		//cout << args[1f];
		args[1] = NULL;
		if (run_simple_commands(args, 2))
		{
		}
		else
		{
			cout << "error fetching network interface " << endl;
		}
	}
	else if (strcmp(args[0], "fpa") == 0)
	{

		char tmp[50] = "/fpa.sh";
		args[0] = &tmp[0];
		if (run_simple_commands(args, 2))
		{
		}
		else
		{
			cout << "errorr  ";
		}
	}
	else if (strcmp(args[0], "replace") == 0)
	{
		char scrname[50] = "/replace.sh";
		args[0] = &scrname[0];
		if (run_simple_commands(args, 5))
		{
		}
	}
	else if (strcmp(args[0], "fs") == 0)
	{
		size_t s;
		if (args[1] == NULL)
		{
			return;
		}
		if (strcmp(args[1], "") == 0)
		{
			return;
		}

		if (strcmp(args[1], "-l") == 0)
		{
			struct dirent *files;
			char path[50] = "";
			char *tmp = strcpy(&path[0], getcwd(&path[0], sizeof(path)));

			DIR *srcdir = opendir(tmp);
			if (srcdir == NULL)
			{
				perror("opendir");
				return;
			}
			cout << "name";
			for (int i = 0; i < 44; i++)
			{
				cout << " ";
			}
			cout << "size" << endl;

			while ((files = readdir(srcdir)) != NULL)
			{
				struct stat st;

				if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0)
					continue;

				if (fstatat(dirfd(srcdir), files->d_name, &st, 0) < 0)
				{
					continue;
				}

				//  if (S_ISDIR(st.st_mode)) {
				s = getsizeoffile(files->d_name);

				cout << files->d_name;

				for (int i = 0; i < 50 - strlen(files->d_name); i++)
				{
					cout << " ";
				}
				cout << s << "B" << endl;
				//}
			}
			closedir(srcdir);
			return;
		}
		s = getsizeoffile(args[1]);

		if (s != -1)
		{
			cout << s << " BYTES" << endl;
		}
		else
		{

			if (args[1] != NULL)
			{
				cout << "'" << args[1] << "' "
					 << " file donot exist" << endl;
			}
			else
			{
				cout << "no input file" << endl;
			}
		}
	}
	else if (strcmp(args[0], "halt") == 0)
	{

		int val = atoi(args[1]);
		cout << "alarm set" << endl;
		for (int i = 0; i < val; i++)
		{
			sleep(1);
		}
		cout << "alarm ended" << endl;
	}
	else if (strcmp(args[0], "sort") == 0)
	{
		int i = 2;

		while (args[i] != NULL)
		{

			i++;
		}
		if (i != 2)
		{
			int *numbers = new int[i];
			i = 2;
			while (args[i] != NULL)
			{
				numbers[i - 2] = atoi(args[i]);
				i++;
			}

			for (int j = 0; j < i - 2; j++)
			{
				for (int k = 0; k < i - 3 && k > -1; k++)
				{
					if (numbers[k] > numbers[k + 1])
					{
						swap(numbers[k], numbers[k + 1]);
					}
				}
			}

			//for (int j = 0; j < i - 2; j++)
			//{
				//cout << numbers[j] << endl;
		//	}

			if (strcmp(args[1], "-d") == 0)
			{
				for (int j = i - 3; j >= 0; j--)
				{
					cout << numbers[j] << "  ";
				}
				cout << endl;
			}
			else if (strcmp(args[1], "-a") == 0)
			{
				for (int j = 0; j < i - 2; j++)
				{
					cout << numbers[j] << "  ";
				}
				cout << endl;
			}
		}
	}
	else if (strcmp(args[0], "banner") == 0)
	{
		label();
		sleep(1);
	}
	else if (strcmp(args[0], "rshell") == 0)
	{
		char cmnd_path[11] = "./open.sh";
		args[0] = &cmnd_path[0];
		int num = 1;
		if (args[1] != NULL)
		{
			num = atoi(args[1]);
		}
		//args[1] = NULL;
		cout << num << endl;
		for (int i = 0; i < num; i++)
		{
			run_simple_commands(args, 2);
		}
	}
	else if (strcmp(args[0], "dummyfile") == 0)
	{
		int num = 1;
		if (args[1] != NULL)
		{

			num = atoi(args[1]);
		}
		for (int i = 0; i < num; i++)
		{
			cout << "num = " << num;
			char cm[10] = "touch";
			char cm1[10] = "dummy";
			string s = to_string(i);
			char const *ptr = s.c_str();
			strcat(cm1, ptr);
			strcat(cm1, ".txt");
			args[0] = &cm[0];
			args[1] = &cm1[0];
			args[2] = NULL;
			run_simple_commands(args, 3);
		}
	}
}

int is_command_in_array(char *args[], int num)
{
	int j = 0;
	if (strcmp(args[0], "man") == 0)
	{
		if (args[1] == NULL || strcmp(args[1], "") == 0)
		{
			return 0;
		}
		for (int i = 0; i < N - 1; i++)
		{
			if (strcmp(args[1], cmds[i]) == 0)
			{
				cout << args[1] << endl
					 << "\t" << desc[i] << "\n\t"
					 << "examples : " << usage[i] << endl
					 << endl;
				return 1;
			}
		}
	}

	for (int i = 0; i < N - 1; i++)
	{
		if (strcmp(args[0], cmds[i]) == 0)
		{

			run_own_command(args, num, args[0]);

			return 1;
		}
	}

	return 0;
}

void sanitize(char *args[], char *dest[], int *newnum)
{
	int i = 0;
	int j = 0;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "") != 0)
		{
			dest[j++] = args[i];
			//strcpy(dest[j++] , args[i] );
		}
		i++;
	}
	*newnum = j;
}

void parse(char *cmd, char *args[], int *num)
{

	char *owncommands[3] = {&cmd[0], &cmd[1], &cmd[2]};

	//cusomt commands
	char *spl;
	char *tmp = cmd;
	int i = 0;
	while ((spl = strsep(&tmp, " ")) != NULL)
	{
		args[i] = spl;
		i++;
	}
	//check if commadn exist
	int newnum = 0;
	args[i] = NULL;
	char *fargs[20] = {NULL};
	sanitize(args, fargs, &newnum);

	int temp = 0;

	*num = newnum; //
	if (caller(fargs, *num) != -1)
	{
		return;
	}

	//check for our own commands
	if (is_command_in_array(fargs, *num) == 1)
	{
		return;
	}
	//cout << "exit called2" << endl;
	//check for pipe

	if (ispipeexist(fargs, *num))
	{
		run_piped_commands(fargs, *num);
	}
	else
	{
		//cout <<  "right";
		if (!run_simple_commands(fargs, *num))
		{
			cout << "No such command exist\n";
		}
	}
}

bool run_simple_commands(char *args[], int n)
{

	pid_t pid = fork();

	if (pid == 0)
	{
		//cout <<  endl << args[1] <<endl;
		if (execvp(args[0], args) < 0)
		{
			return false;
		}
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	cout << endl;
	return true;
}

void clear_arr(char *ptr, int size)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = '\0';
	}
}

int main()
{
	bool running = true;
	//
	//
	label();
	while (running)
	{

		char input[50];
		if (take_input(&input[0]))
		{

			char *args[15] = {NULL};
			char *fargs[15] = {NULL};

			int numargs = 0;

			parse(&input[0], args, &numargs);

			if (numargs == 0)
			{
			}
			//cout << "n arguments = " << numargs <<endl;

			for (int i = 0; i < numargs; i++)
			{
				//cout << args[i] << endl;
			}
		}
		else
		{
			//clear_arr(&input[0] , sizeof(input));
		}
	}

	return 0;
}
