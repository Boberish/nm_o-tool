#include "ft_nm.h"


void    load_64(t_nm *nm)
{
    struct  mach_header_64 *header;
    int     header_size;

    header_size = sizeof(struct mach_header_64);
    header = (struct mach_header_64*)nm->file;
    // ft_putnbr(sizeof(header));
    // ft_putnbr(sizeof(header));
    
    nm->header = header;
    
    print_it(nm, header_size);

}