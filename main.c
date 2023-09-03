#include "shell.h"

int main(void)
{
	char **cmds = NULL;

	/**
	if (!(_init(*cmds)))
		return (-1);
	*/

	write(STDOUT_FILENO, "$ ", 2);
	while (1)
	{
		get_cmds(cmds);
		/**
		check_cmd();
		execute();
		**/
	}
	return (0);
}
/**
void _init(char *cmds)
{
	 # Need to know how long each string for the command is
}
*/

/**
 * get_cmd - Function that gets user input, tokenizes inputs, and
 * appends inputs to the end of strings stored in PATH
 * Return: pointer to array of strings where strings are potential commands
 */
void get_cmds(char **cmds)
{
	char *tokens = NULL;

	get_input(tokens);
	/**
	paths =	get_path();
	append_tokens(cmds, paths, tokens);
	*/

}

void get_input(char *tokens)
{
	int n = 0;
	char *tmp;

	n = _getline(&tmp, STDOUT_FILENO);
	printf("Bytes read: %d\nString: %s\n", n, tmp);
	_strtok(tmp, ' ');
	/**
	 * Struct needed? String ptr and number of characters?
	 * OR double ptr with array of ptrs to char array?
	 */
}
