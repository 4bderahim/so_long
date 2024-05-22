#include "so_long.h"
int ft_strlen(char const *s)
{
    int i ;
    i = 0;
    while (s[i])
        {
            i++;
        }
    return (i);
}
void	*ft_calloc(size_t count, size_t size)
{
	char	*all;
	size_t	tmp;
    size_t i;
	if (count == 0 || size == 0)
	{
		all = (char *)malloc(count * size);
        all[0] = 0;
		return (all);
	}
	tmp = count * size;
	if ((tmp / size) != count)
		return (NULL);
	all = (char *)malloc(count * size);
	if (!all)
		return (NULL);
    i = 0;
    while (i < count*size)
    {
        all[i] = 0;
        i++;
    }
	return (all);
}

void	join_the_two_strings(char *all, char const *s1, char const *s2)
{
	size_t	i;
	int		j;

	i = 0;
	while (s1[i])
	{
		all[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		all[i] = s2[j];
		i++;
		j++;
	}
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*allocated;
	size_t	string_len;

	if (!s1 || !s1)
		return (NULL);
	string_len = ft_strlen(s1) + ft_strlen(s2);
	allocated = (char *)malloc(string_len + 1);
	if (!allocated)
		return (NULL);
	join_the_two_strings(allocated, s1, s2);
	allocated[string_len] = '\0';
    free(s1);
	return (allocated);
}
char *map_reader(int fd)
{
    char *sp;
    char *map;
    int c;
    map = (char *) malloc(1);
    if (!map)
        return (NULL);
    map[0] = 0;
    c = 1;
    while (c != 0)
    {
        sp = (char *) ft_calloc(101,1);
        if (!sp)
            return (NULL);
        c = read(fd, sp, 100);
        if (c == -1)
            exit(0);
        map = ft_strjoin(map, sp);
        free(sp);
    }
    return (map);
}