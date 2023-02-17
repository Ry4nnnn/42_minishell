#include "minishell.h"

void	print_export_x(t_mini *mini)
{
	t_list	*env_list;
	t_env	*env_node;

	env_list = mini->envp;
	while (env_list->next != NULL)
	{
		env_node = (t_env *)env_list->content;
		printf ("declare -x ");
		printf ("%s=\"%s\"\n", env_node->key, env_node->value);
		env_list = env_list->next;
	}
}

int	valid_key(char *key)
{
	if (ft_isalpha(*key) == 0 && *key != '_')
		return (0);
	while (*(++key) != '\0')
	{
		if (ft_isalnum(*key) == 0 && *key != '_')
			return (0);
	}
	return (1);
}

void	ft_export(t_mini *mini, char **key)
{
	int	i;

	i = 1;
	if (key[i] == NULL)
		return (print_export_x(mini));
	while (key[i] != NULL)
	{
		if (valid_key(key[i]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", *(key++));
			// free()
		}
		i++;
	}
}
