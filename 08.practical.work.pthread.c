#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>


#define BUFFER_SIZE 10
int pid=-1;
typedef struct product
{
	char type;  
	int amount; 
	char unit;  
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
void initFirst(item *smt) {
	smt->type = 0;
	smt->amount = 0;
	smt->unit = 0;
}

void initSecond(item *smt)
{
	smt->type = 2;
	smt->amount = 2;
	smt->unit = 2;
}
void print(){
  printf("first = %d\t last = %d\n", first, last);
  return;
}
void produce(item *i)
{
	while ((first + 1) % BUFFER_SIZE == last)
	{
		printf("No free buffer item!\n");
		return;
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	print();
}
item *consume()
{
	item *i = malloc(sizeof(item));
	while (first == last)
	{
		printf("Nothing to consume!\n");
	}
	memcpy(i, &buffer[last], sizeof(item));
	i->amount -= 1;
	last = (last + 1) % BUFFER_SIZE;
	print();
	return i;
}

void *producerThread(void* param)
{
	item *First, f;
	First = &f;
	printf("1 is added\n");
	initFirst(First);
	produce(First);
	produce(First);
	produce(First);
	pthread_exit(NULL);
}

void *consumerThread(void* param)
{
	printf("Comsuming twice\n");
	consume();
	consume();
	pthread_exit(NULL);	
}

int main()
{
	pthread_t tid;
	printf("ProduceThread created\n");
	pthread_create(&tid, NULL,producerThread, NULL);
	pthread_join(tid, NULL);
	printf("ConsumerThread created\n");
	pthread_create(&tid, NULL,consumerThread, NULL);
	pthread_exit(NULL);
}
