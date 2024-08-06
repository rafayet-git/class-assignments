#ifndef ACCOUNTS_H
#define ACCOUNTS_H
	struct bankacc {char *name; int bal; struct bankacc *next;};
	void printBank(struct bankacc rob);
	struct bankacc* makeNewBank(char *n, int b, int id);
	void print_list(struct bankacc *a);
	struct bankacc* free_list (struct bankacc *a);
	struct bankacc *insert_front(struct bankacc *o, char *n, int b);
	struct bankacc *remove_node (struct bankacc *o, int b);
#endif
