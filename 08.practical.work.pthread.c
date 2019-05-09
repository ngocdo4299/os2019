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
	char type;  // 0=burito, 1=taco
	int amount; 
	char unit;  
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
void initBurito(item *smt) {
	smt->type = 0;
	smt->amount = 0;
	smt->unit = 0;
}

void initTaco(item *smt)
{
	smt->type = 1;
	smt->amount = 0;
	smt->unit = 1;
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
	printf("First = %d\n", first);
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
	printf("Last = %d\n", last);
	return;
}

void *producerThread(void* param)
{
	item *burito, beef;
	burito = &beef;
	printf("3 buritoes served in 60 seconds\n");
	initBurito(burito);
	produce(burito);
	produce(burito);
	produce(burito);
	pthread_exit(NULL);
}

void *consumerThread(void* param)
{
	printf("Comsuming 2 buritoes\n");
	consume();
	consume();
	pthread_exit(NULL);	
}

int main()
{
	pthread_t tid;
	printf("This is the main thread speaking\n");
	printf("Creating producerThread ...\n");
	pthread_create(&tid, NULL,producerThread, NULL);
	pthread_join(tid, NULL);
	printf("Creating consumerThread ...\n");
	pthread_create(&tid, NULL,consumerThread, NULL);
	pthread_exit(NULL);
}
