/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaylor <jaylor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:10:04 by jaylor            #+#    #+#             */
/*   Updated: 2018/12/10 14:19:23 by jaylor           ###   ########.fr       */
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


typedef struct      s_node
{
    char            *seg_name;
    // char            *sec_name;
    char            type;
    uint8_t         n_sect;
    uint64_t        value;
    struct s_node   *left;
    struct s_node   *right;
}                   t_node;

typedef struct      s_nm
{
    void            *file;
    void            *header;
    struct s_node   *root;
    int             sec_index[3];
}                   t_nm;

/*
**  nm.c
*/

void    open_with_mmap(t_nm *nm,char **argv);

/*
**  utitlies.c
*/
void    usage_txt(void);
size_t  get_fstat(int fd);

/*
**  main.c
*/

int     main(int argc, char **argv);

/*
**  parsing.c
*/

void    parse_args(int argc, char **argv);


/*
**  load_info.c
*/

void     load_info(t_nm *nm, int fd);
int     is_64(uint32_t magic);
int     is_swapped(uint32_t magic);
void     load_header(t_nm *nm, int is_64, int is_swapped);


/*
**  print.c
*/

void    print_it(t_nm *nm, int header_size);
void    symthings(t_nm *nm, int nsyms, int symoff, int stroff);
void    add_segment(t_nm *nm, struct segment_command_64 *segment, char *sec_list, int *len);
char    bit_masking(t_nm *nm, struct nlist_64 *array,  uint8_t n_type, uint8_t n_sect);
/*
**  type_64.c
*/


void    load_64(t_nm *nm);

t_node    *insert_bt(t_node *root, t_node *node);
char    find_sec(t_nm *nm, struct nlist_64 *array, uint8_t type, uint8_t n_sect);
void print_alpha(t_node *curr);
#endif