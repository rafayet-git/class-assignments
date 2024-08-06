#include <stdio.h>
#include <stdlib.h>
struct bankacc
{
	char *name;
	int bal;
	int id;
	struct bankacc *next;
};

void printBank(struct bankacc account)
{
	printf("%s's balance: $%d (ID:%d)",account.name, account.bal, account.id);
}

struct bankacc* makeNewBank(char *n, int b, int d)
{
	struct bankacc *robbed = malloc(sizeof(struct bankacc));
	robbed->name = n;
	robbed->bal = b;
	robbed->id = (d+1);
	robbed->next = NULL;
	return robbed;
}

void print_list(struct bankacc *acc)
{
	printf("{ ");
	for (struct bankacc *i = acc; i != NULL; i=i->next){
		printBank((*i));
		if(i->next != NULL){
			printf(", ");
		}
	}
	printf(" }\n");
}

struct bankacc* free_list (struct bankacc *acc)
{
	struct bankacc *i;
	while(acc != NULL){
		i = acc->next;
		free(acc);
		acc = i;

	}
}

struct bankacc* insert_front(struct bankacc *old, char *n, int b)
{
	struct bankacc *newacc = makeNewBank(n, b, old->id);
	newacc->next = old;
	return newacc;

}

struct bankacc* remove_node(struct bankacc *front, int b)	
{
	struct bankacc *back = front; // change when adding last-in
	if (front->id == b)
	{
		front = front->next;
		free(back);
	} else { for (struct bankacc *i = front->next; i != NULL; i=i->next){
		if (i->id == b){
			back->next = i->next;
			free(i);
			break;
		}
		back = i;
	} }
	return front;
}
