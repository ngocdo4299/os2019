#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10


typedef struct {
  char type; 
  int amount; 
  char unit; 
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

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

item* initItem(char type, int amount, char unit){
  item* i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;
  return i;
}

int main(){
  item* X = initItem('A',1,'B');
  item* Y = initItem('C',2,'D');
  printf("Initial log:\nfirst = %d\tlast = %d\n\n", first, last);
  printf("Producing and consuming...\n");
  produce(X);
  produce(Y);
  consume();
  return 0;
}
