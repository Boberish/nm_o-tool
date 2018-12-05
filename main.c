#include "ft_nm.h"

int main(int argc,char **argv)
{
    t_nm    *nm;
    int     i;
    int     fd;
    t_node  *root;
    char    letter;

    nm = (t_nm*)malloc(sizeof(*nm));
    nm->file = NULL;
    nm->header = NULL;
    letter = 'm';
    
    root = (t_node *)malloc(sizeof(*root));
    root->seg_name = &letter;
    root->left = NULL;
    root->right = NULL;
    nm->root = root;

    i = 1;
    parse_args(argc,argv);
    while (i < argc)
    {
        if ((fd = open(argv[i], O_RDONLY)) == -1)
        {
            ft_putstr_fd("Error: problem opening file: ", 2);
            ft_putstr_fd(argv[i], 2);
        }
        load_info(nm, fd);
        i++;
    
    }


}