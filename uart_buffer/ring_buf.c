#include <string.h>
#include "ring_buf.h"

void rb_init(t_ring_buf *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

// head == tail means both full and empty
int rb_free_elem(t_ring_buf *rb)
{
    return (rb->tail + RB_SIZE - rb->head) % RB_SIZE;
}

int rb_has_saved_elem(t_ring_buf *rb)
{
    return (rb->head + RB_SIZE - rb->tail) % RB_SIZE;
}

void rb_write_byte(t_ring_buf *rb, unsigned char c)
{
    if (rb_free_elem(rb) < 1)
        return ;
    rb->data[rb->head++] = c;
    rb->head %= RB_SIZE;
}

unsigned char rb_read_byte(t_ring_buf *rb)
{
    unsigned char c;

    if (!rb_has_saved_elem(rb)) {
        return 0;
    }
    c = rb->data[rb->tail++];
    rb->tail %= RB_SIZE;

    return c;
}

void rb_write(t_ring_buf *rb, const unsigned char *s)
{
    if (rb_free_elem(rb) < strlen((const char *)s))
        return ;
    while (*s) {
        //Code duplication
        rb->data[(rb->head)++] = *s++;
        rb->head %= RB_SIZE;
    }
}

bool rb_read(t_ring_buf *rb, unsigned char *s)
{
    if (!*s || !rb_save_elem(rb)) {
        return false;
    }
    while (rb_save_elem(rb)) {
        //Code duplication
        *s++ = rb->data[rb->tail++];
        rb->tail %= RB_SIZE;
    }
    
    return true;
}