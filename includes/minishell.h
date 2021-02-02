#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <limits.h>
# include <signal.h>

typedef struct	s_env
{
	char	**env;
	char	*oldpwd;
}				t_env;

char			*ft_getenv(char **envp, char *var);
void			ft_freestruct(t_env *st);
void			ft_freetab(char **tab);
void			ft_getabsolutepath(char **cmd, t_env *st);
void			ft_builtinpwd(void);
void			ft_builtincd(char *path);
void			ft_execcmd(char **cmd);
int				ft_is_built_in(char *cmd);
void			ft_exec_built_in(char **built_in, t_env *st, char **envp);
char			**ft_splits(char *raw_cmd, char *limit);
// static void		ft_exit();
int				ft_allocbuffer(char *buffer, char *cwd, t_env *st, size_t buf_size);
int				ft_simplecmd(t_env *st, char **envp);
void			ft_env(char **envp);
int     		main(int argc, char **argv, char **envp);

t_env			*ft_initstruct(void);
#endif