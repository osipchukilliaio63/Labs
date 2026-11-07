#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MAX_QUEUE 100

typedef struct {
    char name[10];
    int burst_time;
    int remaining_time;
    int quantum;
    int waiting_time;
} Process;

typedef struct {
    int data[MAX_QUEUE];
    int head;
    int tail;
    int count;
} Queue;

void init_queue(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool is_empty(Queue *q) {
    return q->count == 0;
}

bool is_full(Queue *q) {
    return q->count == MAX_QUEUE;
}

void enqueue(Queue *q, int val) {
    if (is_full(q)) return;
    q->data[q->tail] = val;
    q->tail = (q->tail + 1) % MAX_QUEUE;
    q->count++;
}

int dequeue(Queue *q) {
    if (is_empty(q)) return -1;
    int val = q->data[q->head];
    q->head = (q->head + 1) % MAX_QUEUE;
    q->count--;
    return val;
}

int peek_front(Queue *q) {
    if (is_empty(q)) return -1;
    return q->data[q->head];
}


int main() {
    int n;
    printf("[Реалізація: Кільцевий масив]\nВведіть кількість процесів: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) return 1;

    Process proc[MAX_PROCESSES];
    Queue q;
    init_queue(&q);

    for (int i = 0; i < n; i++) {
        printf("\nПроцес %d:\n", i + 1);
        printf("  Назва: ");
        scanf("%s", proc[i].name);
        printf("  Тривалість: ");
        scanf("%d", &proc[i].burst_time);
        printf("  Квант: ");
        scanf("%d", &proc[i].quantum);

        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;

        enqueue(&q, i);
    }

    int current_time = 0;
    int completed_count = 0;
    char completion_order[MAX_PROCESSES][10];


    while (!is_empty(&q)) {
        int idx = dequeue(&q);
        Process *p = &proc[idx];

        int exec_time = (p->remaining_time < p->quantum) ? p->remaining_time : p->quantum;
        current_time += exec_time;
        p->remaining_time -= exec_time;

        if (p->remaining_time == 0) {
            strcpy(completion_order[completed_count], p->name);
            completed_count++;
            p->waiting_time = current_time - p->burst_time;
        } else {
            enqueue(&q, idx);
        }
    }

    printf("\nПорядок завершення: ");
    for (int i = 0; i < completed_count; i++) {
        printf("%s%s", completion_order[i], (i < completed_count - 1) ? " -> " : "\n");
    }

    int total_waiting = 0;
    for (int i = 0; i < n; i++) {
        printf("  Процес %s: час очікування = %d\n", proc[i].name, proc[i].waiting_time);
        total_waiting += proc[i].waiting_time;
    }
    printf("Середній час очікування: %.2f\n", (double)total_waiting / n);

    return 0;
}
