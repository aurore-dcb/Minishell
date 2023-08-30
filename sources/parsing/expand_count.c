#include "../../headers/exec.h"
#include "../../libft/libft.h"

char *existing_var(char *var, char **env)
{
	int i;
	char *res;
	
	i = 0;
	if (!var)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], var, ft_strlen(var)))
		{
			res = ft_trim(env[i], ft_strlen(var) + 1);
			if (!res)
				return (free(var), NULL);
			return (free(var), res);
		}
		i++;
	}
	return (NULL);
}

int len_var_env(char *s)
{
	int len;

	len = 0;
	if (*s == '?')
		return (1);
	while (*s && (*s == '_' || ft_isalnum(*s)))
	{
		len++;
		s++;
	}
	return (len);
}

int count_between_simple(char **s)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 39)
	{
		n++;
		(*s)++;
	}
	return (n);
}
int find_variable(char *s, s_data *data)
{
    int n;
    char *cpy;
    char *res;

	if (*s == '?') //exit status
	{
		printf("exit_status = %d\n-> len = %d\n",data->exit_status, size_nb(data->exit_status));
		return (size_nb(data->exit_status));
	}
    cpy = malloc(sizeof(char) * (len_var_env(s) + 1));
	if (!cpy)
		return (printf("echec malloc\n"), 0); // ERREUR
    cpy = ft_strcpy(cpy, s, len_var_env(s) + 1);
    res = existing_var(cpy, data->env);
	n = ft_strlen(res);
    return (n);
}

int count_between_double(char **s, s_data *data)
{
	int n;

	n = 0;
	(*s)++;
	while (*(*s) && *(*s) != 34)
	{
		if (*(*s) == '$')
		{
			(*s)++;
            n += find_variable(*s, data);
			(*s) = (*s) + len_var_env(*s) - 1;
		}
		else
			n++;
		(*s)++;
	}
	return (n);
}
