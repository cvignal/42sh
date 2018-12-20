/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:28:17 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 17:55:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddend(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);

char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *str, int c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *dest, const char *src, int n);
char				*ft_strncpy(char *dest, const char *src, unsigned int n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *str, const char *tf, size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_atoi(const char *s);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlen(const char *s);
size_t				ft_nbrlen(int n);
size_t				ft_snbrlen(size_t n);
size_t				ft_strlenw(const wchar_t *s);
unsigned int		ft_strlcat(char *dest, const char *src, unsigned int size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int v, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *mem, int b, size_t len);
void				*ft_realloc(void *old, size_t old_size, size_t new_size);
void				ft_bzero(void *mem, size_t len);
void				ft_memdel(void **ap);
void				ft_putchar(char c);
int					ft_putcharw(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putunbr(unsigned int n);
void				ft_putnbr_fd(int nbr, int fd);
size_t				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
unsigned long long	ft_ullpow(unsigned long long nbr, unsigned long int pow);
long double			ft_ldpow(long double nbr, unsigned long int pow);
size_t				ft_putulnbr_base(unsigned long int nb, const char *base);
size_t				ft_putldnbr_base(long double nb, const char *base,
		unsigned int precision);
size_t				ft_putnbr_base(int nb, const char *base);
size_t				ft_putllnbr_base(long long nb, const char *base);
size_t				ft_putullnbr_base(unsigned long long nb, const char *base);
size_t				ft_putullnbr(unsigned long long nb);
size_t				ft_putllnbr(unsigned long long nb);
size_t				ft_char_size_utf8(unsigned int c);
int					get_next_line(int fd, char **line);
char				*ft_strjoin_free(char *s1, char *s2, int flag);
char				*ft_insert_free(char *str, char *to_insert, size_t index, int flag);

#endif
