#include "../../includes/minishell.h"

void		stock_env(t_struct *st, size_t j, char *str)
{
	st->env = ft_strndup(str, j);
	st->envi = ft_getenv(st->copyenvp, st->env);
}
