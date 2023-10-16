#include "shell.h"

/**
 * interactive -Will return true if shell is in interactive mode
 * @info:Its the struct address
 *  
 * Return: 1 if interactive mode, 0 otherwise
 **/
int interactive(info_t *info)
{
		return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimeter
 * @c:     char to check
 * @delim: Delimeter string
 * Return: 1 when true, 0 when false
 *
 **/
int is_delim(char c, char *delim)
{
		while (*delim)
					if (*delim++ == c)
									return (1);
			return (0);
}

/**
 * _isalpha - checks for all alphabetic character
 * @c:     Character to input
 * Return: 1 when c is alphabetic,  otherwise 0
 * 
 **/

int _isalpha(int c)
{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
					return (1);
			else
						return (0);
}

/**
 * _atoi - This converts strings to an integer
 * @s:     Strings to be converted
 * Return: 0 if no numbers in strings, converted number otherwise
 **/

int _atoi(char *s)
{
		int i, sign = 1, flag = 0, output;
			unsigned int result = 0;

				for (i = 0; s[i] != '\0' && flag != 2; i++)
						{
									if (s[i] == '-')
													sign *= -1;

											if (s[i] >= '0' && s[i] <= '9')
														{
																		flag = 1;
																					result *= 10;
																								result += (s[i] - '0');
																										}
													else if (flag == 1)
																	flag = 2;
														}

					if (sign == -1)
								output = -result;
						else
									output = result;

							return (output);
}


