/* Generic heap data structure -- header.
 * Copyright (C) 2009 Chris Hall (GMCH), Highwayman
 *.
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _ZEBRA_HEAP_H
#define _ZEBRA_HEAP_H

#include "vector.h"

/* Macro in case there are particular compiler issues.    */
#ifndef Inline
  #define Inline static inline
#endif

typedef int heap_cmp(p_vector_item* a, p_vector_item*) ;

enum heap_state {
  Heap_Has_Backlink  = 0x01,    /* Set if backlink set  */
};

struct heap
{
  heap_cmp* cmp ;

  enum heap_state state ;
  unsigned int backlink_offset ;

  struct vector v ;
};

typedef struct heap* heap;

typedef vector_index heap_backlink_t ;

/* Prototypes. */

extern heap heap_init_new(heap h, vector_index size, heap_cmp* cmp,
                            int with_backlink, unsigned int backlink_offset) ;
#define heap_init_new_simple(h, size, cmp) \
  heap_init_new(h, size, cmp, 0, 0)
#define heap_init_new_backlinked(h, size, cmp, off) \
  heap_init_new(h, size, cmp, 1, off)

extern heap heap_re_init(heap h, vector_index size, heap_cmp* cmp,
			    int with_backlink, unsigned int backlink_offset) ;
#define heap_re_init_simple(h, size, cmp) \
  heap_re_init(h, size, cmp, 0, 0)
#define heap_re_init_backlinked(h, size, cmp, off) \
  heap_re_init(h, size, cmp, 1, off)

extern heap heap_reset(heap h, int free_structure) ;
extern p_vector_item heap_ream(heap h, int free_structure) ;

/* Reset heap and free the heap structure.	*/
#define heap_reset_free(h) heap_reset(h, 1) ;
/* Reset heap but keep the heap structure.	*/
#define heap_reset_keep(h) heap_reset(h, 0) ;
/* Ream out heap and free the heap structure.	*/
#define heap_ream_free(h) heap_ream_out(h, 1) ;
/* Ream out heap but keep the heap structure.	*/
#define heap_ream_keep(h) heap_ream_out(h, 0) ;

extern void heap_push_item(heap h, p_vector_item p_v) ;
extern p_vector_item heap_pop_item(heap h) ;
extern p_vector_item heap_top_item(heap h) ;
extern void heap_update_top_item(heap h) ;

extern void heap_delete_item(heap h, p_vector_item p_v) ;
extern void heap_update_item(heap h, p_vector_item p_v) ;

extern void heap_push_vector(heap h, vector v, int move_vector) ;
#define heap_push_vector_copy(h, v) \
  heap_push_vector(h, v, 0)
#define heap_push_vector_move(h, v) \
  heap_push_vector(h, v, 1)
extern vector heap_pop_vector(vector v, heap h, int move_heap) ;
#define heap_pop_vector_copy(v, h)  \
  heap_pop_vector(v, h, 0)
#define heap_pop_vector_move(v, h)  \
  heap_pop_vector(v, h, 1)

extern vector heap_vector(heap h, int unset_heap_order) ;

#endif /* _ZEBRA_HEAP_H */
