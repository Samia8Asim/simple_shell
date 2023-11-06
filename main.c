#include "shell.h"

/**
 * main - entry point of the program.
 * argc: number of argument .
 * argv: list of argument.
  
 * Return: 0 on success and 1 if any error occur.
 */

int main(int argc, char **argv)
{
	info_t info_init[] = { INFO_INIT };
	int fh = 1;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fh)
			: "r" (fh));

	if (argc == 2)
	{
		fh = open(argv[1], O_RDONLY);
		if (fh == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_init->readfh = fh;
	}
	populate_env_list(info_init);
	read_history(info_init);
	hsh(info_init, argv);
	return (EXIT_SUCCESS);
}
