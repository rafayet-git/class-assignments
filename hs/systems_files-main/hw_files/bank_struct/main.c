#include "accounts.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int main()
{
	srand(time(NULL));
	struct bankacc *bank = makeNewBank("Billybob", rand(), 0);
	printf(" Init bank with first account: \n");
	print_list(bank);
	bank = insert_front(bank, "Glass", rand());
	bank = insert_front(bank, "Monitor", rand());
	bank = insert_front(bank, "Track", rand());	
	bank = insert_front(bank, "Tractor", rand());
	printf("\n Add 4 accounts to front\n");
	print_list(bank);
	bank = remove_node(bank, 5);
	printf("\n Remove first account\n");
	print_list(bank);
	bank = remove_node(bank, 1);
	printf("\n Remove last account\n");
	print_list(bank);
	bank = remove_node(bank, 3);	
	printf("\n Remove middle account\n");
	print_list(bank);
	bank = free_list(bank);
	printf("\n Free Bank\n");
	print_list(bank);
	return 0;
}


