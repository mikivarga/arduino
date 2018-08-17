#ifndef RING_BUF_H
#define RING_BUF_H

#include <stdbool.h>

#define RB_SIZE 100

typedef struct  s_ring_buf
{
    int head;
    int tail;
    volatile unsigned char data[RB_SIZE];
}               t_ring_buf;

void            rb_init(t_ring_buf *rb);
int             rb_free_elem(t_ring_buf *rb);
int             rb_save_elem(t_ring_buf *rb);
void            rb_write_byte(t_ring_buf *rb, unsigned char c);
unsigned char   rb_read_byte(t_ring_buf *rb);
void            rb_write(t_ring_buf *rb, const unsigned char *s);
bool            rb_read(t_ring_buf *rb, unsigned char *s);

#endif