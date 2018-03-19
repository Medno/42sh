#include "parser.h"

int	is_redir(t_lex *tmp)
{
	if (ft_strequ(tmp->value, ">") || ft_strequ(tmp->value, "<") ||
			tmp->token == GREATAND || tmp->token == LESSAND ||
			tmp->token == DGREAT || tmp->token == DLESS ||
			tmp->token == CLOBBER || tmp->token == DLESSDASH ||
			tmp->token == LESSGREAT || tmp->token == ANDLESS ||
			tmp->token == ANDGREAT)
		return (1);
	return (0);
}

int	is_rsvword(t_lex *tmp)
{
	if (tmp->token == IF || tmp->token == FI || tmp->token == DO ||
			tmp->token == ELSE || tmp->token == ELIF || tmp->token == DONE ||
			tmp->token == FOR || tmp->token == CASE || tmp->token == ESAC || 
			tmp->token == IN || tmp->token == THEN || tmp->token == UNTIL ||
			tmp->token == WHILE)
		return (1);
	return (0);
}
