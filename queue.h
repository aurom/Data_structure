typedef nodo_queue Qnode;
typedef queue_struct Queue;

struct nodo_queue
{
	int element;
	Qnode* prev;
	Qnode* next;
};

struct queue_struct {
	Qnode* head;
	Qnode* tail;
};

Qnode* newQnode(int data);
Queue* newQueue();
void enqueue(Queue*,int);
int dequeue(Queue*);