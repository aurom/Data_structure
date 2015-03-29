typedef struct nodo_queue Qnode;
typedef struct queue_struct Queue;

struct nodo_queue
{
	int element;
	Qnode* prev;
	Qnode* next;
};

struct queue_struct {
	Qnode* head;
	Qnode* tail;
	int count;
};

Qnode* newQnode(int data);
Queue* newQueue();
void enqueue(Queue*,int);
int dequeue(Queue*);
int length(Queue*);