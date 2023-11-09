#include "shell.h"

/**
 * _myexit - function to exits from the shell
 * @info_init: srtuctre to containing arguments
 * Return: exits with a given status
 */
int _myexit(info_t *info_init)
{
	int check_exit;

	if (info->argv[1])  
	{
		check_exit = _erratoi(info_init->argv[1]);
		if (check_exit == -1)
		{
			info_init->status = 2;
			print_error(info_init, "Illegal number: ");
			_eputs(info_init->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info_init->err_num = _erratoi(info_init->argv[1]);
		return (-2);
	}
	info_init->err_num = -1;
	return (-2);
}

/**
 * _mycd - function that changes the process current directory
 * @info_init: srtuctre to containing arguments
 * Return: 0(success)
 */
int _mycd(info_t *info_init)
{
	int ret_chdir;
	char *str, *dir, buf[1024]

		str = getcwd(buf, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info_init->argv[1])
	{
		dir = _getenv(info_init, "HOME=");
		if (!dir)
			ret_chdir = 
				chdir((dir = _getenv(info_init, "PWD=")) ? dir : "/");
		else
			ret_chdir = chdir(dir);
	}
	else if (_strcmp(info_init->argv[1], "-") == 0)
	{
		if (!_getenv(info_init, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info_init, "OLDPWD=")), _putchar('\n');
		ret_chdir = 
			chdir((dir = _getenv(info_init, "OLDPWD=")) ? dir : "/");
	}
	else
		ret_chdir = chdir(info_init->argv[1]);
	if (ret_chdir == -1)
	{
		print_error(info_init, "can't cd to ");
		_eputs(info_init->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info_init, "OLDPWD", _getenv(info_init, "PWD="));
		_setenv(info_init, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the process current directory
 * @info_init: srtuctre to containing arguments
 * Return: 0(success)
 */
int _myhelp(info_t *info_init)
{
	char **arg_arr;

	arg_arr = info_init->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); 
	return (0);
}
