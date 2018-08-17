#include <string.h>
#include "ring_buf.h"

void rb_init(t_ring_buf *rb)
{
    rb->head = 0;
    rb->tail = 0;
}

int rb_free_elem(t_ring_buf *rb)
{
    int cnt_free;

    if (rb->head >= rb->tail) {
        cnt_free = RB_SIZE - (rb->head - rb->tail);
    } else {
        cnt_free = rb->tail - rb->head;
    }
    
    return cnt_free;
}

int rb_save_elem(t_ring_buf *rb)
{
    int cnt_save;

    if (rb->head >= rb->tail) {
        cnt_save = rb->head - rb->tail;
    } else {
        cnt_save = RB_SIZE - (rb->tail - rb->head);
    }

    return cnt_save;
}

void rb_write_byte(t_ring_buf *rb, unsigned char c)
{
    if (rb_free_elem(rb) < 1)
        return ;
    rb->data[(rb->head)++] = c;
    rb->head = (rb->head >= RB_SIZE ? 0 : rb->head);
}

unsigned char rb_read_byte(t_ring_buf *rb)
{
    unsigned char c;

    if (!rb_save_elem(rb)) {
        return 0;
    }
    c = rb->data[(rb->tail)++];
    rb->tail = (rb->tail >= RB_SIZE ? 0 : rb->tail);

    return c;
}

void rb_write(t_ring_buf *rb, const unsigned char *s)
{
    if (rb_free_elem(rb) < strlen((const char *)s))
        return ;
    while(*s) {
        rb->data[(rb->head)++] = *s++;
        rb->head = (rb->head >= RB_SIZE ? 0 : rb->head);
    }
}

bool rb_read(t_ring_buf *rb, unsigned char *s)
{
    if (!*s || !rb_save_elem(rb)) {
        return false;
    }
    while (rb_save_elem(rb)) {
        *s++ = rb->data[(rb->tail)++];
        rb->tail = (rb->tail >= RB_SIZE ? 0 : rb->tail);
    }
    
    return true;
}