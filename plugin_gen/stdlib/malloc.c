/* This file was added to msp430-libc in CVS archived within
 * git://mspgcc.git.sourceforge.net/gitroot/mspgcc/historical:
 * 
 * commit 573b30e69c4b57559d68fe048c79cc495f8f8d0c
 * Author: cliechti <cliechti>
 * Date:   Wed Dec 26 03:52:24 2001 +0000
 * 
 *   Initial revision
 *
 * It is not original to msp430-libc, and the contributor cannot
 * recall its source.  The nearest contemporaneous sighting is at:
 *
 *   http://www.mikrocontroller.net/topic/1197
 *
 * but msp430-libc's inclusion pre-dates this.
 *
 * Author, copyright, and license unknown. */

#include <stdlib.h>
#include <sys/crtld.h>

#define XSIZE(x) ((*x)>>1)
#define FREE_P(x) (!((*x)&1))
#define MARK_BUSY(x) ((*x)|=1)
#define MARK_FREE(x) ((*x)&=0xfffe)

void *malloc (size_t size)
{
    static char once = 0;
    size_t * heap_bottom;
    intptr_t kk = (intptr_t) __noinit_end;		/* this will possibly introduce */
    size_t * heap_top = (size_t *)((kk+1)&~1);	/* 1 byte hole between .bss and heap */
    char f = 0;

    if (!once)
    {
        once = 1;
        *heap_top = 0xFFFE;
    }
    heap_bottom = __read_stack_pointer();
    heap_bottom -= 20;
    size = (size+1) >> 1;	/* round to 2 */
    do
    {
        size_t xsize = XSIZE (heap_top);
        size_t * heap_next = &heap_top[xsize + 1];
        if ((xsize<<1)+2 == 0)
        {
            f = 1;
        }
        if (FREE_P (heap_top))
        {
            if (f)
            {
                xsize = heap_bottom - heap_top - 1;
            }
            else if (FREE_P(heap_next))
            {
                *heap_top = ( (XSIZE(heap_next)<<1) + 2 == 0
                              ? 0xfffe
                              : (xsize + XSIZE(heap_next) + 1)<<1);
                continue;
            }
            if (xsize >= size)
            {
                if (heap_top + size + 1 > heap_bottom)
                    break;
                if (f)
                    heap_top[size + 1] = 0xfffe;
                else if (xsize != size)
                    heap_top[size + 1] = (xsize - size - 1) << 1;
                *heap_top = size << 1;
                MARK_BUSY (heap_top);
                return heap_top+1;
            }
        }
        heap_top += xsize + 1;
    }
    while (!f);
    return NULL;
}

void free (void *p)
{
    size_t *t = (size_t*)p - 1;
    MARK_FREE (t);
}

