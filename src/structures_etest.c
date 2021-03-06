// ================
// Structures etest
// ================
//
// Testing data-structures
//
// Project includes
// ================
//
// .. code-block:: cpp
//
#include "structures.h"
#include "common.h"

// System includes
// ===============
//
// .. code-block:: cpp
//

// Queue
// =====
//
// .. code-block:: cpp
//

// Declarations
// ------------
//
// .. code-block:: cpp
//
struct ch_test_queue_s;
typedef struct ch_test_queue_s ch_test_queue_t;
struct ch_test_queue_s {
    int i;
    ch_test_queue_t* next;
    ch_test_queue_t* qend;
};

//
// Runner
// ------
//
// .. code-block:: cpp
//
int
ch_test_queue()
{
    ch_test_queue_t test_data[5];
    ch_test_queue_t* queue = NULL;
    for(int i = 0; i < 5; i++) {
        ch_test_queue_t* t = &test_data[i];
        CH_QQ_ITEM_INIT(t);
        t->i = i;
    }
    for(int i = 0; i < 2; i++) {
        CH_QQ_DEQUEUE(queue);
        TA(queue == NULL, "Empty dequeue failed");
        CH_QQ_ENQUEUE(queue, &test_data[0]);
        TA(queue == &test_data[0], "Empty enqueue failed");
        CH_QQ_DEQUEUE(queue);
        TA(queue == NULL, "First dequeue failed");
        CH_QQ_ENQUEUE(queue, &test_data[0]);
        TA(queue == &test_data[0], "Empty enqueue failed");
        CH_QQ_ENQUEUE(queue, &test_data[1]);
        TA(queue == &test_data[0], "Enqueue failed");
        TA(CH_TR_QEND(queue) == &test_data[1], "Enqueue failed");
        CH_QQ_ENQUEUE(queue, &test_data[2]);
        TA(queue == &test_data[0], "Enqueue failed");
        TA(CH_TR_QEND(queue) == &test_data[2], "Enqueue failed");
        TA(test_data[0].next != NULL, "Enqueue failed");
        TA(test_data[0].qend != NULL, "Enqueue failed");
        CH_QQ_DEQUEUE(queue);
        TA(queue == &test_data[1], "Dequeue failed");
        TA(test_data[0].next == NULL, "Dequeue failed");
        TA(test_data[0].qend == NULL, "Dequeue failed");
        TA(CH_TR_QEND(queue) == &test_data[2], "Dequeue failed");
        CH_QQ_DEQUEUE(queue);
        TA(queue == &test_data[2], "Dequeue failed");
        TA(CH_TR_QEND(queue) == &test_data[2], "Dequeue failed");
        CH_QQ_DEQUEUE(queue);
        TA(queue == NULL, "Dequeue failed");
    }
    return 0;
}

// Main Runner
// ===========
//
// .. code-block:: cpp

int
main()
{
    return ch_test_queue();
}
