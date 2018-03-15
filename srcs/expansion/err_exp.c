#include "expansion.h"

char	*err_dollar(t_init *init, char *str)
{
	init->dollar = 1;
	ft_printf_fd(2, "42sh: %s: bad substitution\n", str);
	return (NULL);
}
