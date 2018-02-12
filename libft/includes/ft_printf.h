/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:22:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 08:56:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <locale.h>
# include <stdio.h>
# include "libft.h"
# define ARG_NAME "spdiouxcSDOUXCaAbBeEfFgGHIJkKmMnNPqQrRtTvVwWyYZ%"

typedef struct	s_dope
{
	char		*brackets;
	char		*dope;
}				t_dope;

typedef struct	s_colors
{
	t_dope		t_blue;
	t_dope		t_black;
	t_dope		t_white;
	t_dope		t_red;
	t_dope		t_green;
	t_dope		t_mage;
	t_dope		t_yellow;
	t_dope		t_cyan;
	t_dope		b_blue;
	t_dope		b_black;
	t_dope		b_white;
	t_dope		b_red;
	t_dope		b_green;
	t_dope		b_mage;
	t_dope		b_yellow;
	t_dope		b_cyan;
	t_dope		bold;
	t_dope		underscore;
	t_dope		eoc;
}				t_colors;

typedef struct	s_flags
{
	int			percent;
	char		letter;
	int			hash;
	int			space;
	int			zero;
	int			minus;
	int			plus;
	int			width;
	int			point;
	int			precision;
	int			apo;
	int			wildcard;
	int			lfd;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
}				t_flags;

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
char			**ft_str_parse(char *str);
t_flags			ft_flags(char *str, va_list list);
t_flags			ft_check_flags_d(t_flags flags, char *str);
t_flags			ft_checkout_wildcard(t_flags flags, char *str, va_list list);
t_flags			check_prec_with_wc(t_flags flags, char *str);
t_colors		colors_brackets(void);
int				ft_handle_d(t_flags flags, char **str, va_list list);
int				ft_handle_c(t_flags flags, char **str, va_list list);
int				ft_handle_base(t_flags flags, char **str, va_list list);
int				ft_handle_s(t_flags flags, char **str, va_list list);
int				ft_handle_f(t_flags flags, char **str, va_list list);
int				ft_handle_percent(t_flags flags, char **str);
int				ft_handle_binary(t_flags flags, char **str, va_list list);
int				ft_convert_str(char **str, char **array, va_list list,
				t_colors colors);
char			*ft_ltoa(long long n, int apo);
char			*ft_untoa(unsigned long long n, int apo);
char			*ft_ldtoa(long double n, int prec, int apo);
char			*ft_dtoa(double n, int prec, int apo);
char			*ft_str_join(char *s1, char *s2, int size1, int size2);
char			*ft_handle_d_positive(t_flags flags, char *str);
char			*ft_handle_hash(t_flags flags, char *str);
char			*ft_width_base(t_flags flags, char *str, char c);
char			*ft_width_d_base(t_flags flags, char *str);
char			*ft_width_d(t_flags flags, char *str);
char			*str_put_zero(char *str, int length);
int				handle_wchar_ret(wint_t c);
char			*handle_width_cs(t_flags flags, char *str, int len);
char			*ft_convert_wct(wint_t c);
int				handle_wchar_ret_nocurmax(wint_t c);
int				ft_handle_return_s(wchar_t *content, t_flags flags);
int				handle_color(char **str, t_colors colors);
char			**ft_parse_brackets(char *str, t_colors colors);
int				is_valid(char *str, t_colors colors);

#endif
