/*
    Copyright (c) 2012 250bpm s.r.o.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include <stddef.h>

#include "list.h"

void sp_list_init (struct sp_list *self)
{
    self->first = NULL;
    self->last = NULL;
}

void sp_list_term (struct sp_list *self)
{
    self->first = NULL;
    self->last = NULL;
}

int sp_list_empty (struct sp_list *self)
{
    return self->first ? 0 : 1;
}

struct sp_list_item *sp_list_begin (struct sp_list *self)
{
    return self->first;
}

struct sp_list_item *sp_list_end (struct sp_list *self)
{
    return NULL;
}

struct sp_list_item *sp_list_prev (struct sp_list *self,
    struct sp_list_item *it)
{
    return it ? it->prev : self->last;
}

struct sp_list_item *sp_list_next (struct sp_list *self,
    struct sp_list_item *it)
{
    return it->next;
}

void sp_list_insert (struct sp_list *self, struct sp_list_item *item,
    struct sp_list_item *it)
{    
    item->prev = it ? it->prev : self->last;
    item->next = it;
    if (item->prev)
        item->prev->next = item;
    if (item->next)
        item->next->prev = item;
    if (!self->first || self->first == it)
        self->first = item;
    if (!it)
        self->last = item;   
}

struct sp_list_item *sp_list_erase (struct sp_list *self,
    struct sp_list_item *item)
{
    if (item->prev)
        item->prev->next = item->next;
    else
        self->first = item->next;
    if (item->next)
        item->next->prev = item->prev;
    else
        self->last = item->prev;
    return item->next;
}
