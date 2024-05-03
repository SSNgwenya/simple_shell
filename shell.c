#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	/* Some operations are performed with fd */
	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fd)
			: "r"(fd));

	/* Check if the program is run with an argument */
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY); /* Attempt to open file */
		if (fd == -1)
		{
			/* Handle file open errors */
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
		info->readfd = fd; /* Assign the file descriptor to read from */
	}

	populate_env_list(info); /* Populate environment list */
	read_history(info); /* Read command history */
	hsh(info, argv); /* Start the shell */

	return (EXIT_SUCCESS);
}
