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
	char		**sortenv;
	int			i;
	char		*oldpwd;
}						t_struct;

typedef struct	s_mini
{
	char		*line; // stock toute la commande entrée
	char 		**tab_arg; // stock la cmd separe par rapport au ; et |
	char		**cmd; // stock seul la cmd
	char		**echo; // va etre utilise dans la fonction echo
	char		error; // caratere d'erreur a afficher
	int 		*tab_pipe; // savoir si la commande est relier avec la suite par un pipe
	int 		quote;
	int			nquote;
	int			islast;
	int 		op; // pour detecter l'option -n pour echo
	size_t 		semi; // compter le nb de ; et |
}				t_mini;

t_struct			*ft_initstruct(void);
t_mini				*ft_initmini(void);

/*
 ** TOOLS FILES
*/

void				ft_savepwd(t_struct *st);
char				*ft_getenv(char **envp, char *var); // permet d'obtenir le resultat d'une var
void				ft_freestruct(t_struct *st); // free structure
void				ft_freetab(char **tab); // free le tableau alloué dans get absolute path
void				ft_getabsolutepath(char **cmd, t_struct *st); // permet d'avoir le chemin absolu pour ls ls -la etc
int					ft_countenv(char **env);
int					ft_is_built_in(char *cmd); // check si c'est un builtin ou non
void				ft_exec_built_in(t_mini *mi, char **built_in, t_struct *st, size_t n); // execute builtin
int					ft_allocbuffer(char *buffer, char *cwd, t_struct *st, size_t buf_size); // alloue memoire pour le buffer et norme de ftsimplecmd
int					ft_simplecmd(t_struct *st, t_mini *mi, char **envp, size_t n); // boucle pour les commandes sans pipe
char				**ft_copyenv(char **envp); // copie de l'environnement en tab[][] pour unset et export
char				**ft_strtokk(char *str, char *sep);
void				ft_exit(void);
void				ft_printsortenv(t_struct *st);
void				ft_execcmd(char **cmd); // exec cmd != builtin
int     			main(int argc, char **argv, char **envp);

/*
 ** CMD FILES
*/

int					ft_echo(t_mini *mi, size_t n); // fonction pour echo
void				ft_builtinpwd(t_struct *st); // exec pwd
void				ft_builtincd(char *path, t_struct *st); // exec cd
void				ft_env(char **envp); // printf l'env
void				ft_exportenv(char *var, t_struct *st);
char				**ft_unsetenv(char *var, t_struct *st);
/*
 ** PARSING FILES
 */

int					ft_parsing(t_mini *mi);
int					ft_recover_cmd(t_mini *mi); // recupere la cmd ex: echo
int					ft_check_character(t_mini *mi); // check tout la ligne pour analiser les vrais des faux characters
void				str_remove_index(int i, t_mini *mi, char c); // supprime un caractere quand celui-ci est inutile
int					print_prompt_waiting(t_mini *mi, char *str, size_t i); // affiche le prompt pour le multiligne
int					endline(char *str, size_t i); // check si le character est le dernier de la ligne
int 				ft_error(char c, int i); // affiche des messages d'erreur
int					check_pipe(t_mini *mi); // check si les pipes donnes sont bons
int					check_semi(t_mini *mi); // check si les semilicons donnes sont bons
int 				check_redirect(t_mini *mi, size_t i); // check les redirections
void 				ft_reset_mi(t_mini *mi);
void				ft_free_mi(t_mini *mi);
void				clean_spaces_bet(t_mini *mi, size_t n, size_t i);

#endif