#include "so_long.h"

int borders_check(char **map)
{
    int i;
    int j;

    j = 0;
    i = 0;

    while (map[i])
    {
        if (i == 0 || map[i+1] == NULL)
            {
                while (map[i][j])
                {
                    if (map[i][j] != '1')
                        return (0);
                    j++;
                }
            }
        else
        {
            if (map[i][0] != '1' || map[i][ft_strlen(map[i])-1] != '1')
                return (0);
        }
        i++;
    }
    return (1);
}
int a_map_brick(char c)
    {
        int i;
        int p_found;
        char *s;

        p_found = 0;
        i = 0;
        s = "01CPE";
        
        while (s[i])
            {   
                if (c == s[i])
                    return (1);
                i++;
            }
        printf("\t[%c]\n", c);
        return (0);
}
int check_map_bricks(char **map)
{
    int i;
    int j;
    int p_found;
    
    p_found = 0;
    i = -1;
    while (map[i++])
    {
        j = 0;  
        if (ft_strlen(map[i]) != ft_strlen(map[0]))
            return (0);
        while (map[i][j])
        {
            if (map[i][j] == 'P')
                {
                    if (p_found)
                        return (0);
                    p_found = 1;    
                }
            if (!a_map_brick(map[i][j]))
                return (0);
            j++;
        }
    }
    return (1);
}
int check_map(char **map)
{
    if (!borders_check(map))
        exit(0);
    return (0);
}



 