
int *ft_get_red(void)
{
    static int stat;

    return &stat;
}

void ft_set_read(int st)
{
    int *stat = ft_get_red();

    *stat = st;
}


var = 1;