#ifndef TIDIER_H
#define TIDIER_H
struct node{
	int key;
	int height;
	struct node *Llink;
	struct node *Rlink;
	struct node *parent;
	int x,y;
	int status;
	int modifier;
	int offset;
	bool thread;
};
struct extreme{
	struct node *address;
	int offset,level;
};
void setup(struct node* T,int level,struct extreme &rmost,struct extreme &lmost);
void petrify(struct node* T,int xpos);
#endif
