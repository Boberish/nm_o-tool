#include "ft_nm.h"


void    load_64(t_nm *nm)
{
    struct  mach_header_64 *header;
    int     header_size;
    int     ncmds;

    header = (struct mach_header_64*)nm->file;
    header_size = sizeof(struct mach_header_64);
    nm->header = header;
    ncmds = ((struct mach_header_64*)(nm->header))->ncmds; 
    print_it(nm, header_size, ncmds);

}

void    load_32(t_nm *nm)
{
    // struct  mach_header *header;
    int     header_size;
    int     ncmds;

    // header = (struct mach_header *)nm->file;
    header_size = sizeof(struct mach_header);
    nm->header = (struct mach_header *)nm->file;
    ncmds = ((struct mach_header*)(nm->header))->ncmds;
    print_it(nm, header_size, ncmds);

}