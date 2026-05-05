

#include "codexion.h"


// int is_first_free(t_heap *heap)
// {
// 	if (heap->heap[0].coder_id)
// 		return 1;
// 	return 0;
// }


t_dongle *first_and_second(t_coder *coder, int i)
{
	t_dongle *first;
	t_dongle *second;

	if (coder->left_dongle->dongle_id < coder->right_dongle->dongle_id)
    {
        first = coder->left_dongle;
        second = coder->right_dongle;
    }
    if (coder->left_dongle->dongle_id > coder->right_dongle->dongle_id)
    {
        second = coder->left_dongle;
        first = coder->right_dongle;
    }
	if (i == 1)
		return first;
	else
		return second;
}



// int safe_print(t_coder *coder, int i)
// {

// }