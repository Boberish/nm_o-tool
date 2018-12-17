/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaylor <jaylor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:10:04 by jaylor            #+#    #+#             */
/*   Updated: 2018/12/17 14:31:00 by jaylor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/includes/libft.h"
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/swap.h>
# include <mach-o/fat.h>
# include <ar.h>


typedef struct      s_node
{
    char            *seg_name;
    // char            *sec_name;
    uint8_t         type;
    uint8_t         n_sect;
    uint64_t        value;
    struct s_node   *left;
    struct s_node   *right;
}                   t_node;

typedef struct      s_nm
{
    uint32_t        magic;
    short           is_64;
    short           is_swapped;
    void            *file;
    void            *end;
    void            *header;
    struct s_node   *root;
    int             sec_index[3];
    int             f_size;
    int             fd;
    short           if_fat;
    char            **argv;
}                   t_nm;

/*
**  nm.c
*/

void    open_with_mmap(t_nm *nm,char **argv);
int load_file(t_nm *nm);

/*
**  utitlies.c
*/
void    usage_txt(void);
size_t  get_fstat(int fd);

/*
**  main.c
*/

int     main(int argc, char **argv);
int    init_all(t_nm *nm);
int ft_nm(int argc,char **argv);

/*
**  parsing.c
*/

void    parse_args(int argc, char **argv);


/*
**  load_info.c
*/

int     load_info(t_nm *nm);
int     is_64(uint32_t magic);
int     is_swapped(uint32_t magic);
int     check_magic(t_nm *nm);
void    load_32(t_nm *nm);


/*
**  print.c
*/

void    print_it(t_nm *nm, int header_size, size_t ncmds);
void    symthings_64(t_nm *nm, int nsyms, int symoff, int stroff);
void    add_segment_64(t_nm *nm, struct segment_command_64 *segment,  int *len);
void    add_segment_32(t_nm *nm, struct segment_command *segment, int *len);
char    bit_masking(t_nm *nm, void *array,  unsigned char n_type, uint8_t n_sect);
void    symthings_32(t_nm *nm, int nsyms, int symoff, int stroff);
void    print_inside(t_nm *nm, short t, t_node *curr);
/*
**  type_64.c
*/


void    load_64(t_nm *nm);

t_node    *insert_bt(t_node *root, t_node *node);
char    find_sec(t_nm *nm, struct nlist_64 *array, uint8_t type, uint8_t n_sect);
int normal_magic(t_nm *nm);
int check_arch(t_nm *nm);
int    ft_error_msg(char *msg);
void print_alpha(t_nm *nm, t_node *curr);
#endif