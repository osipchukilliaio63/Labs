#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[10];
    int burst_time;
    int remaining_time;
    int quantum;
    int completion_time;
} Process;

typedef struct Node {
    int process_index;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

void init_queue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

bool is_empty(Queue *q) {
    return q->head == NULL;
}

bool is_full(Queue *q) {
    return false;
}

void enqueue(Queue *q, int process_index) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->process_index = process_index;
    new_node->next = NULL;

    if (is_empty(q)) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

int dequeue(Queue *q) {
    if (is_empty(q)) return -1;

    Node* temp = q->head;
    int res = temp->process_index;

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
    return res;
}

int peek_front(Queue *q) {
    if (is_empty(q)) return -1;
    return q->head->process_index;
}

int main() {
    Process p[] = {
        {"P1", 10, 10, 3, 0},
        {"P2", 4,  4,  2, 0},
        {"P3", 7,  7,  4, 0}
    };
    int n = sizeof(p) / sizeof(p[0]);

    Queue q;
    init_queue(&q);

    for (int i = 0; i < n; i++) {
        enqueue(&q, i);
    }

    int current_time = 0;
    printf("--- Simulation Start (Linked List) ---\n");

    while (!is_empty(&q)) {
        int idx = dequeue(&q);

        int exec_time = (p[idx].remaining_time < p[idx].quantum)
                        ? p[idx].remaining_time
                        : p[idx].quantum;

        int start_time = current_time;
        current_time += exec_time;
        p[idx].remaining_time -= exec_time;

        printf("[%d -> %d] Process %s executed for %d units. (Remaining: %d)\n",
               start_time, current_time, p[idx].name, exec_time, p[idx].remaining_time);

        if (p[idx].remaining_time > 0) {
            enqueue(&q, idx);
        } else {
            p[idx].completion_time = current_time;
            printf(">> Process %s FINISHED at time %d\n", p[idx].name, current_time);
        }
    }

    printf("\n--- Calculation Results ---\n");
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        int waiting_time = p[i].completion_time - p[i].burst_time;
        total_waiting_time += waiting_time;
        printf("Process %s: Completion Time = %d, Waiting Time = %d\n",
               p[i].name, p[i].completion_time, waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f time units.\n", total_waiting_time / n);
    return 0;
}

