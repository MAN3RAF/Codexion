


#include "codexion.h"


void write_heap(t_coder *c, t_heap *h, int i)
{
    h->heap[i].coder_id = c->id;
    h->heap[i].deadline = c->last_compile + c->system->time_to_burnout;
    h->heap[i].request_time = get_time_ms();
}

void erase_heap(t_heap *h, int index)
{
    h->heap[index].coder_id = 0;
    h->heap[index].deadline = 0;
    h->heap[index].request_time = 0;
}

void swap(t_heap *heap)
{
    t_node  temp;
    
    temp = heap->heap[0];
    heap->heap[0] = heap->heap[1];
    heap->heap[1] = temp;
}


void handle_heap(t_coder *coder, t_dongle *dongle)
{
    long long   deadline_1;
    long long   deadline_2;
    long long   request_time_1;
    long long   request_time_2;

    if (!dongle->min_heap.heap[0].coder_id)
        write_heap(coder, &dongle->min_heap, 0);
    else
        write_heap(coder, &dongle->min_heap, 1);
    deadline_1 = dongle->min_heap.heap[1].deadline;
    deadline_2 = dongle->min_heap.heap[0].deadline;
    request_time_1 = dongle->min_heap.heap[0].request_time;
    request_time_2 = dongle->min_heap.heap[1].request_time;
    if (!strcmp(coder->system->scheduler, "edf")
        && dongle->min_heap.heap[1].coder_id == coder->id)
    {
        if (deadline_1 < deadline_2)
            swap(&dongle->min_heap);
        if (deadline_1 == deadline_2)
            if (request_time_1 > request_time_2)
                swap(&dongle->min_heap);
    }
}

