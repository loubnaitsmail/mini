#include "minishell.h"

static void	update_output(char ***matrix, int fd)
{
    printf("UP_DATE_OUTPUT\n");
	char	**aux;
	char	*temp;
	char	*line;

	aux = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
        printf("line = %s\n", line);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
        //printf("temp = %s\n", temp);
		aux = ft_extend_matrix(aux, temp);
		free(temp);
	}
	ft_free_matrix(matrix);
	*matrix = aux;
    printf("matrix[0] = %s\n", *matrix[0]);
    //printf("matrix[1] = %s\n", *matrix[1]);
}

void	exec_custom(char ***out, char *full, char *args, char **envp)
{
    printf("EXECUTE CMD ARG = %s\n", args);
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		matrix = ft_split(args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, matrix, envp);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[READ_END]);
	close(fd[READ_END]);
}