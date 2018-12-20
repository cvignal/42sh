/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:36 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/20 19:29:37 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 2048

# include <stdarg.h>
# include <sys/types.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef	struct	s_form
{
	int			width;
	int			prec;
	int			plus;
	int			minus;
	int			sharp;
	int			space;
	int			zero;
	char		c;
	int			zero_nbr;
	int			space_nbr;
	int			length;
	char		size[3];
}				t_form;

typedef struct	s_conv
{
	char		conv;
	char		*(*f_conv)(va_list ap, t_form);
}				t_conv;

typedef struct	s_format
{
	char		conv;
	char		*(*f_form)(char*, t_form);
}				t_format;

typedef struct	s_line
{
	struct s_line	*next;
	int				fd;
	char			*file;
}				t_line;

int				ft_atoi(const char *str);
int				ft_atoi_base(char *str, int base);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strnstr(const char *haystack,
		const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char *c);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstapp(t_list **alst, t_list *new);
t_list			*ft_strsplit_lst(char const *s, char c);
void			*ft_lstfold(t_list *lst, void *(*f)(void *, void *));
void			*ft_realloc(void *src, size_t old_len, size_t new_len);
void			ft_list_sort(t_list **begin_list, int (*cmp)());
void			ft_deltab(char ***table);
char			*ft_strjoin_free(char *s1, char *s2, int flag);
int				ft_sqrt(int a);
char			*ft_ltoa_base(long long nb, int base);
char			*ft_stoa_base(short nb, int base);
unsigned long	ft_power(int base, int power);
int				ft_nb_digits(unsigned long long value, int base);
int				ft_max(int a, int b, int c);
char			*ft_ultoa_base(unsigned long long nb, int base);
char			*ft_dtoa(long double nb, int precision);
size_t			ft_strfindchar(const char *str, char c);
int				get_next_line(const int fd, char **line);
char			*ft_insert_free(char *str, char *to_insert, size_t index, int flag);
void			ft_del_char(char *str, size_t index);
void			ft_delelt(void *content, size_t index);
char			file_type(char *path);
char			**ft_listtotab(t_list *lst, size_t size);

/*
** Printf
*/

int				ft_printf(const char *str, ...);
int				ft_dprintf(int fd, const char *str, ...);
int				ft_sprintf(char *buffer, const char *str, ...);
int				ft_buf_str(char **str, char *buffer);
char			*ft_conv(char *tmp, va_list ap);
int				ft_is_conv(char c);
int				ft_readpercent(char **line, const char **str, va_list ap);
int				ft_readstr(char **line, const char **str);
int				ft_valid_percent(const char **s);
char			*ft_conv_uns(va_list ap, t_form flag);
char			*ft_conv_hexam(va_list ap, t_form flag);
char			*ft_conv_hexa(va_list ap, t_form flag);
char			*ft_conv_octal(va_list ap, t_form flag);
char			*ft_conv_percent(va_list ap, t_form flag);
char			*ft_conv_int(va_list ap, t_form flag);
char			*ft_conv_str(va_list ap, t_form flag);
char			*ft_conv_char(va_list ap, t_form flag);
char			*ft_conv_float(va_list ap, t_form flag);
char			*ft_conv_binary(va_list ap, t_form flag);
int				ft_print_conv(char **str);
int				ft_print_convfd(char **str, int fd);
int				ft_print_str(char **str);
int				ft_print_strfd(char **str, int fd);
char			*ft_form_str(char *str, t_form flag);
char			*ft_form_uns(char *str, t_form flag);
char			*ft_form_int(char *str, t_form flag);
char			*ft_form_ptr(char *str, t_form flag);
char			*ft_form_flo(char *str, t_form flag);
char			*ft_form_minusi(char *str, t_form flag);
char			*ft_form_minuss(char *str, t_form flag);
char			*ft_form_minusu(char *str, t_form flag);
char			*ft_form_minusp(char *str, t_form flag);
char			*ft_form_minusf(char *str, t_form flag);

#endif
