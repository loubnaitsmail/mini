#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

typedef struct s_prompt
{
    t_list  *cmds;
    char    **envp;
    pid_t   pid;
    int     status;
}               t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

# define READ_END 0
# define WRITE_END 1

//matrix
char    **ft_dup_matrix(char **envp);
char    **ft_extend_matrix(char **in_envp, char *new_str);
int     ft_matrixlen(char **envp);
void    ft_free_matrix(char ***out_adrr);
char	**ft_matrix_replace_in(char ***big, char **small, int n);

//environement
char    **mini_setenv(char *var, char *str_val, char **envp, int size_n);
char    *mini_getenv(char *var, char **envp, int size_n);

//libft
int     ft_strchr_i(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char *ft_strcpy(char *dest, char *src);
int	ft_strchars_i(const char *s, char *set);


//prompt
char	*mini_getprompt(t_prompt prompt);
static char	*get_user(t_prompt prompt);

//custom_cmd
void	exec_custom(char ***out, char *full, char *args, char **envp);

//parse args
void	*check_args(char *out, t_prompt *p);

//ft_cmdtrim
char	**ft_cmdtrim(char const *s, char *set);

//ft_cmdsubsplit
char	**ft_cmdsubsplit(char const *s, char *set);
//static char	**ft_fill_array(char **aux, char *s, char *set, int i[3]);
//static int	ft_count_words(char *s, char *set, int count);

//expand
char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *str, t_prompt *prompt);
static char	*get_substr_var(char *str, int i, t_prompt *prompt);

//fill node
t_list	*fill_nodes(char **args, int i);

//strim all
char	*ft_strtrim_all(char const *s1, int squote, int dquote);

//list
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newnode);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int	ft_lstsize(t_list *lst);

//get_params infile, outfile, full_path
//int	get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_infile2(t_mini *node, char **args, int *i);


#endif