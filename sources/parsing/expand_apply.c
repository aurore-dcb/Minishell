#include "../../headers/exec.h"
#include "../../libft/libft.h"

void between_simple(char **res, char **s)
{
	(*s)++;
	while (*(*s) && *(*s) != 39)
	{
		*(*res) = *(*s);
		(*s)++;
        (*res)++;
	}
    // return (res);
}