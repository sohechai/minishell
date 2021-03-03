/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:00:29 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/03 15:20:00 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SIMPLERED 1
# define DOUBLERED 2
# define LEFTRED 3
# define STDIN 0
# define STDOUT 1
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
# include <errno.h>
# include <dirent.h>

typedef struct		s_struct
{
	char			**copyenvp;
	char			**files;
	char			**parsecmd;
	char			**command;
	char			*oldpwd;
	char			*printerror;
	char			*newfd;
	char			*pathfile;
	int				i;
	int				index;
	int				exitstatus;
	int				redirection;
	int				oldstdout;
	int				stop;
	int				fdinput;
	pid_t			pid;
	// t_mini
	char 		**tab_arg;
	char		**cmd;
	char		**echo;
	char		*line;
	char		error;
	int 		*tab_pipe;
	int			*tab_red;
	int 		quote;
	int			nquote;
	int			islast;
	int 		op;
	int 		fd;
	int			nbackslash;
	int			nredir;
	size_t 		semi;
}					t_struct;

// typedef struct		s_mini
// {
	
// }					t_mini;

t_struct			*ft_initstruct(void);
// t_mini				*ft_initmini(void);

/*
 ** TOOLS FILES
*/

void				ft_savepwd(t_struct *st);
char				*ft_getenv(char **copyenvp, char *var);
void				ft_freestruct(t_struct *st);
void				ft_freeloop(t_struct *st);
void				ft_freetab(char **tab);
void				ft_getabsolutepath(char **cmd, t_struct *st);
int					ft_countenv(char **env);
int					ft_is_built_in(char *cmd);
int					ft_exec_built_in(char **built_in, t_struct *st);
int					ft_allocbuffer(char *buffer, char *cwd, t_struct *st,
						size_t buf_size);
int					ft_simplecmd(t_struct *st, size_t n);
char				**ft_strtokk(char *str, char *sep);
int					ft_exit(char *cmd, t_struct *st);
int					ft_printsortenv(t_struct *st);
void				ft_execcmd(t_struct *st, char *command, char **cmd);
void				ft_cdwithargs(char **built_in, t_struct *st);
void				ft_saveoldpwd(t_struct *st);
void				ft_savepwd(t_struct *st);
void				ft_exportloop(char **built_in, t_struct *st);
void				ft_unsetloop(char **built_in, t_struct *st);
void				ft_sigint(int signum);
void				ft_sigquit(int signum);
int					ft_checkvarisok(char *var);
int					ft_checkvarismissing(char *var, t_struct *st);
char				*ft_getvar(char *var);
int					ft_indexuntilfile(char *str, t_struct *st);
int					ft_redirection(char *cmd, t_struct *st);
int					ft_strlenuntilredir(char *str);
void				ft_redirectbuiltin(t_struct *st);
void				ft_comebacktostdout(t_struct *st);
int					ft_checkfile(char *cmd, t_struct *st);
int					ft_lenoffile(char *cmd);
void				ft_execpipe(char *cmd, t_struct *st);
int					ft_pipecmd(t_struct *st, size_t n);
int					ft_checkquote(char *str);
int					main(int argc, char **argv, char **envp);

/*
 ** AURBUCHE FILES
*/

int					ft_echo(t_struct *st, char **cmd);
int					is_env(t_struct *st, char *str, size_t i, size_t n);
char				*new_str(char *tmp, char *src, size_t i);
int					re_env(t_struct *st, char *str, size_t i,
						size_t n);
size_t				print_quote(t_struct *st, char *cmd, size_t i, char c);
void				option(t_struct *st, size_t i, size_t n);
char				**remove_quote(char **cmd, size_t n);
int					is_option(t_struct *st, char *str, size_t i);
char				**rechange_character(char **cmd, size_t i, size_t n);

/*
 ** CMD FILES
*/

int					ft_builtinpwd(t_struct *st);
int					ft_builtincd(char *path, t_struct *st);
void				ft_env(char **envp, t_struct *st);
int					ft_exportenv(char *var, t_struct *st);
char				**ft_unsetenv(char *var, t_struct *st);

/*
 ** PARSING FILES
*/

int					ft_parsing(t_struct *st, size_t i);
int					ft_recover_cmd(t_struct *st); // recupere la cmd ex: echo
int					ft_check_character(t_struct *st); // check tout la ligne pour analiser les vrais des faux characters
void				str_remove_index(int i, t_struct *st, char c); // supprime un caractere quand celui-ci est inutile
int					print_prompt_waiting(t_struct *st, char *str, size_t i); // affiche le prompt pour le multiligne
int					endline(char *str, size_t i); // check si le character est le dernier de la ligne
int 				ft_error(char c, int i); // affiche des messages d'erreur
int					check_pipe(t_struct *st); // check si les pipes donnes sont bons
int					check_semi(t_struct *st); // check si les semilicons donnes sont bons
int 				check_redirect(t_struct *st, size_t i, size_t n); // check les redirections
void 				ft_reset_mi(t_struct *st);
void				ft_free_mi(t_struct *st);
void				clean_spaces_bet(t_struct *st, size_t n, size_t i);
int					check_nquote(char *str, size_t i);
int					change_char_in_dquote(t_struct *st, size_t i, size_t n);
size_t				advance(char *str, size_t i, char c);
void				change_real_char(t_struct *st, size_t n, size_t i);
size_t				ft_change_char(char c, t_struct *st, size_t i, size_t n);

#endif
