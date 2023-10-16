#include "shell.h"

/**
 * input_buf - The buffer chained cmd
 * @info: Parameter structs info
 * @buf: The address of buffers
 * @len: The address of len variables
 *
 * Return: bytes to be read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* when nothing is left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removes all trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Function that gets a line minus the newline
 * @info: parameter structs info
 *
 * Returns: bytes to be read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' cmd chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* Error Of Function */
		return (-1);
	if (len) /*  commands left in the chain buffer */
	{
		j = i; /* This initializes new iterator to current buffers position */
		p = buf + i; /* gets the pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /*This iterates to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increments ++ past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* resets the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*It passes back pointer to current cmd position */
		return (_strlen(p)); /* returns length of current command */
	}

	*buf_p = buf; /* else its not a chain,And passes back buffer from _getline() */
	return (r); /* returns length of buffer from _getline() function */
}

/**
 * read_buf -Its reads buffers
 * @info: parameter structs info
 * @buf: its the buffers 
 * @i: size (s)
 *
 * Returns: r always
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - this function gets the next line of input from STDIN hEADER FILE
 * @info: parameter structS INFO
 * @ptr: address of  stored pointers to buffer, preallocated or NULL
 * @length: size of preallocated pointers to buffer if not NULL
 *
 * Returns: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC_________________ FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler -  it blocks ctrl-C key formart
 * @sig_num: the signal numbers
 *
 * Returns: void always
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

