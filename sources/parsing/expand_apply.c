#include "../../headers/exec.h"
#include "../../libft/libft.h"

int between_simple(char *res, char **word, int i)
{
	(*word)++;
	while (*(*word) && *(*word) != 39)
	{
		res[i] = *(*word);
		(*word)++;
        i++;
	}
    return (i);
}

int out_of_quotes(char *res, char **word, s_data *data, int i)
{
	int j;
	char *cpy;
	char *var;

	j = 0;
	(*word)++;
	cpy = malloc(sizeof(char) * (len_var_env(*word) + 1));
	if (!cpy)
		return (printf("echec malloc\n"), 0);
	cpy = ft_strcpy(cpy, *word, len_var_env(*word) + 1);
	if (**word == '?')
        var = ft_itoa(data->exit_status);
    else
        var = existing_var(cpy, data->env);
    while (var && var[j])
        res[i++] = var[j++];
    return (i);	
}

int between_double(char *res, char **word, s_data *data, int i)
{
    (*word)++;
    while (*(*word) && *(*word) != 34)
    {
        if (*(*word) == '$')
        {
            i = out_of_quotes(res, word, data, i);
            (*word) = (*word) + len_var_env(*word) - 1;
        }
        else
            res[i++] = *(*word);
        (*word)++;
    }
    return (i);
}
