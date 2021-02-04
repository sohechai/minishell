#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>

typedef struct			s_struct
{
	char		**copyenvp;
	char		*oldpwd;
}						t_struct;

t_struct		*ft_initstruct(void);

char			*ft_getenv(char **envp, char *var); // permet d'obtenir le resultat d'une var
void			ft_freestruct(t_struct *st); // free structure
void			ft_freetab(char **tab); // free le tableau alloué dans get absolute path
void			ft_getabsolutepath(char **cmd, t_struct *st); // permet d'avoir le chemin absolu pour ls ls -la etc
void			ft_builtinpwd(void); // exec pwd
void			ft_builtincd(char *path); // exec cd
void			ft_execcmd(char **cmd); // exec cmd != builtin
int				ft_is_built_in(char *cmd); // check si c'est un builtin ou non
void			ft_exec_built_in(char **built_in, t_struct *st); // execute builtin
// static void		ft_exit(); // permet d'exit
int				ft_allocbuffer(char *buffer, char *cwd, t_struct *st, size_t buf_size); // alloue memoire pour le buffer et norme de ftsimplecmd
int				ft_simplecmd(t_struct *st); // boucle pour les commandes sans pipe
char			**ft_copyenv(char **envp); // copie de l'environnement en tab[][] pour unset et export
void			ft_env(char **envp); // printf l'env
void			ft_getoldpwd(t_struct *st); // save le oldpwd
char			**ft_strtokk(char *str, char *sep);
int     		main(int argc, char **argv, char **envp);

#endif