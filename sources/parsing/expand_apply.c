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
	var = existing_var(cpy, data->env);
	while (var && var[j])
		res[i++] = var[j++];
	return (i);	
}

int between_double(char *res, char **word, s_data *data, int i)
{
    int j;
    char *cpy;
    char *var;

    (*word)++;
    while (*(*word) && *(*word) != 34)
    {
        if (*(*word) == '$')
        {
            (*word)++;
            cpy = malloc(sizeof(char) * (len_var_env(*word) + 1));
            if (!cpy)
                return (printf("echec malloc\n"), 0); // ERREUR
            cpy = ft_strcpy(cpy, *word, len_var_env(*word) + 1);
            var = existing_var(cpy, data->env);
            j = 0;
            while (var && var[j])
                res[i++] = var[j++];
            (*word) = (*word) + len_var_env(*word) - 1;
        }
        else
            res[i++] = *(*word);
        (*word)++;
    }
    return (i);
}
