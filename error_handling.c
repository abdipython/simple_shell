#include "shell.h"

/**
 ** _eputs -This prints an input string
 ** @str:The string to be printed
 **
 ** Returns: Nothing
 ***/
void _eputs(char *str)
{
		int i = 0;

			if (!str)
						return;
				while (str[i] != '\0')
						{
									_eputchar(str[i]);
											i++;
												}
}

/**
 *_eputchar -it writes the character c to stderr
 * @c: character to print
 *    
 * Return: If successful 1.
 * On error, -1 is returned, error number is set appropriately.
 *
 **/
int _eputchar(char c)
{
		static int i;
			static char buf[WRITE_BUF_SIZE];

				if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
						{
									write(2, buf, i);
											i = 0;
												}
					if (c != BUF_FLUSH)
								buf[i++] = c;
						return (1);
}

/**
 ** _putfd -This writes the character c to given file_descriptor
 * @c: character to print
 * @fd: The file-descriptor to write to
 * 
 * Return: if successful 1.
 * On error, -1 is returned, and errno is set appropriately.
 *
 * */
int _putfd(char c, int fd)
{
		static int i;
			static char buf[WRITE_BUF_SIZE];

				if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
						{
									write(fd, buf, i);
											i = 0;
												}
					if (c != BUF_FLUSH)
								buf[i++] = c;
						return (1);
}

/**
 *  _putsfd -  it prints an input string
 * @str: string to be printed
 * @fd: the file-descriptor to write to
 *     
 * Returns: the number of chars input
 *
 * */
int _putsfd(char *str, int fd)
{
		int i = 0;

			if (!str)
						return (0);
				while (*str)
						{
									i += _putfd(*str++, fd);
										}
					return (i);
}

