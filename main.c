#include "ft_nm.h"

int main(int argc,char **argv)
{
   ft_nm(argc, argv);
}

int ft_nm(int argc,char **argv)
{
    t_nm    *nm;
    int     i;
    
    nm = (t_nm*)malloc(sizeof(*nm));
    if (!nm)
        return(ft_error_msg("malloc error"));
    i = 1;
    parse_args(argc,argv);
    nm->argv = argv;
    while (i < argc)
    {
        init_all(nm);
        if (argc > 2)
        {
            ft_printf("\n%s:\n", argv[i]);
        }
        if ((nm->fd = open(argv[i], O_RDONLY)) == -1)
        {
            ft_putstr_fd("Error: problem opening file: ", 2);
            ft_putstr_fd(argv[i], 2);
            return (1);
        }
        load_file(nm);
        load_info(nm);
    
        i++;
    
    }


}

int    init_all(t_nm *nm)
{
    t_node  *root;
    char    *dumb;

    
    nm->magic = 0;
    nm->header = NULL;
    dumb = "mzzz";
    root = (t_node *)malloc(sizeof(*root));
    root->seg_name = dumb;
    root->value = 999999;
    root->n_sect = 0;
    root->type = 36;
    root->left = NULL;
    root->right = NULL;
    nm->root = root;
    // nm->root = NULL;
    nm->sec_index[0] = -1;
    nm->sec_index[1] = -1;
    nm->sec_index[2] = -1;
}