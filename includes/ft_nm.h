/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaylor <jaylor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:10:04 by jaylor            #+#    #+#             */
/*   Updated: 2018/12/04 16:29:35 by jaylor           ###   ########.fr       */
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
    uint64_t        addr;
    uint64_t        size;
    uint32_t        offset;
    struct s_node   *left;
    struct s_node   *right;
}                   t_node;

typedef struct      s_nm
{
    void            *file;
    void            *header;
    struct s_node   *root;
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
void    add_segment(t_nm *nm, struct segment_command_64 *segment);
void    bit_masking(int n_type);
/*
**  type_64.c
*/


void    load_64(t_nm *nm);

t_node    *insert_bt(t_node *root, t_node *node);
#endif