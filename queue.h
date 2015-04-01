#ifndef QUEUE_H
#define QUEUE_H
#define TRUE 1
#define FALSE 0

	typedef void (*printData)(void*);
	typedef struct nodo_queue Qnode;
	typedef struct queue_struct Queue;

	struct nodo_queue
	{
		void* element;
		Qnode* prev;
		Qnode* next;
	};

	struct queue_struct {
		Qnode* head;
		Qnode* tail;
		int count;
		int e_size;
		printData print;
	};

	Qnode* newQnode();
	Queue* newQueue(int, printData);
	void enqueue(Queue*,void*);
	void* dequeue(Queue*);
	int q_length(Queue*);
	int is_qempty(Queue*);
	void printQueue(Queue*);
#endif // QUEUE_H
