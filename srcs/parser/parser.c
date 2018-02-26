#include "21sh.h"

int	parser(t_lex *first)
{
	t_lex	*tmp;
	t_ast	*ast;
	int		build;

	build = 1;
	if (first->token != WORD)
	{
		if (first->token != EOI)
			ft_putendl("syntax error");
		build = 0;
	}
	tmp = first;
	while (tmp && build)
	{
		if (tmp->token != WORD && tmp->token != IO_NUMBER 
				&& !ft_strequ(";", tmp->value) && !tmp->next)
		{
			ft_putendl("syntax error");
			build = 0;
		}
		tmp = tmp->next;
	}
	if (build)
	{
		tmp = first;
		ast = build_ast(tmp);
		//print_lex(first);
		print_ast(ast, NULL);
		del_ast(&ast);
	}
	del_lex(first);
	return (0);
}
