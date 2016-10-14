#include<iostream>

#define MINSEP 50

using namespace std;

class Tidy{

//status flags ::  first = 0, left = 1, right =2
/* Iterative Method*/

/**The first tree traversal finds out the offset (modifier) for each node.*/
	

	/** Function to set the height of all the nodes in the tree*/
	public: static	void SetHeight(struct node *T,int h){
		    if(T!=NULL){
			T->offset = 0;
			T->thread = false;
			T->height = h;
			SetHeight(T->Llink,h+1);
			SetHeight(T->Rlink,h+1);
		    }
		}
	/** Sets the parents of each node*/
		static void SetParent(nd* p){
			if(p!=NULL){
				if(p->Llink!=NULL) p->Llink->parent = p;
				if(p->Rlink!=NULL) p->Rlink->parent = p;
				SetParent(p->Llink);
				SetParent(p->Rlink);
			}
		}
	/** Scaling the X and Y coordinates*/
		static void SetXY(nd* p){
			if(p!=NULL){
				p->x = p->x*50;
				p->y = p->y*100;
				SetXY(p->Llink);
				SetXY(p->Rlink);
			}
		}
	/** Function To generate Tidy Tree*/
	 static void tidyTree(node *root){
		 int modifier[100000];
		 int next_pos[100000];
		 int i;
		 int place;;
		 int h;
		 bool is_leaf;
		 int modifier_sum;
		 for(i=0;i<100000;i++) modifier[i] = 0;
		 for(i=0;i<100000;i++) next_pos[i] = 1;
		 node *current =root;
		 current->status = 0;
		 while(current!=NULL){
		  switch(current->status){
		    case 0: 	current->status = 1;
				if(current->Llink!=NULL){
					current = current->Llink;
					current->status= 0;
				}
		  		break;
		   case 1:	current->status = 2;
				if(current->Rlink!=NULL){
					current = current->Rlink;
					current->status = 0;
				}
				break;
		   case 2:	h = current->height;
				is_leaf = (current->Llink==NULL)&&(current->Rlink==NULL);
		
				if(is_leaf)
					place = next_pos[h];
				else if(current->Llink==NULL)
					place = current->Rlink->x-1;
				else if(current->Rlink==NULL)
					place = current->Llink->x+1;
				else
					place = (current->Llink->x + current->Rlink->x)/2;
		

				modifier[h] = max(modifier[h],next_pos[h]-place);
		
				if(is_leaf)
					current->x = place;
				else 	
					current->x = place + modifier[h];
				next_pos[h] = current->x+2;
				current->modifier = modifier[h];	
				current = current->parent;
				break;
		    }
		  }
		  
		  current = root;
		  current->status = 0;
		  modifier_sum = 0;
		  while(current!=NULL){
		   switch(current->status){
		    case 0:	current->x = current->x + modifier_sum;
				modifier_sum = modifier_sum + current->modifier;
				current->y = 2*current->height + 1;
				current->status = 1;
				if(current->Llink!=NULL){
					current = current->Llink;
					current->status = 0;
				}
				break;
		   case 1:	current->status = 2;
				if(current->Rlink!=NULL){
					current = current->Rlink;
					current->status=0;
				}
				break;
		   case 2:	modifier_sum = modifier_sum - current->modifier;
				current = current->parent;
				break;
		  }
		 }
		

		
	}
	
};



class Tidier{
			/** Finds the offset for each node which is used to calculate the x-coordinate
			Traverses the tree and creates threads as and when necessary.*/
			
			public:   static void setup(struct node *T,int LEVEL,struct extreme &rmost,struct extreme &lmost)
			{
			    struct node *L;
			    struct node *R;
			    struct extreme LL,RR,LR,RL;
			    int cursep,
			    rootsep,
			    loffsum,roffsum;
			    if(T==NULL)
			    {
				lmost.level=-1;
				rmost.level=-1;
			    }
			    else
			    {
				T->y = LEVEL;
				L= T->Llink;
				R= T->Rlink;
				setup(L,LEVEL+100,LR,LL);
				setup(R,LEVEL+100,RR,RL);
				if(R==NULL && L==NULL)
				{
				    rmost.address= T;
				    lmost.address= T;
				    rmost.level=LEVEL;
				    lmost.level=LEVEL;
				    rmost.offset=0;
				    lmost.offset=0;
				    T->offset=0;
				}
				else
				{
				    cursep=MINSEP;
				    rootsep=MINSEP;
				    loffsum=0;
				    roffsum=0;
				    while(L!=NULL && R!=NULL)
				    {
					if(cursep<MINSEP)
					{
					    rootsep=rootsep+(MINSEP-cursep);
					    cursep=MINSEP;
					}
					if(L->Rlink!=NULL)
					{
					    loffsum=loffsum+L->offset;
					    cursep=cursep-L->offset;
					    L=L->Rlink;
					}
					else
					{
					    loffsum=loffsum-L->offset;
					    cursep=cursep+L->offset;
					    L=L->Llink;
					}
					if(R->Llink!=NULL)
					{
					    roffsum=roffsum-R->offset;
					    cursep=cursep-R->offset;
					    R=R->Llink;
					}
					else
					{
					    roffsum=roffsum+R->offset;
					    cursep=cursep+R->offset;
					    R=R->Rlink;
					}
				    }
				    T->offset=(rootsep+1)/2;
				    loffsum=loffsum-T->offset;
				    roffsum=roffsum+T->offset;
				    
				    if(RL.level>LL.level || T->Llink==NULL)
				    {
					lmost=RL;
					lmost.offset=lmost.offset+T->offset;
				    }
				    else
				    {
					lmost=LL;
					lmost.offset=lmost.offset-T->offset;
				    }
				    
				    if(LR.level > RR.level || T->Rlink==NULL)
				    {
					rmost=LR;
					rmost.offset=rmost.offset-T->offset;
				    }
				    else
				    {
					rmost=RR;
					rmost.offset=rmost.offset+T->offset;
				    }
				    
				    if(L!=NULL && L!=T->Llink)
				    {
					RR.address->thread=true;
					RR.address->offset=abs(RR.offset+T->offset-loffsum);
					if(loffsum-T->offset <= RR.offset)
					{
					    RR.address->Llink=L;
					}
					else
					{
					    RR.address->Rlink=L;
					}
				    }
				    else if(R!=NULL && R!=T->Rlink)
				    {
					LL.address->thread=true;
					LL.address->offset=abs(LL.offset - T->offset - roffsum);
					if(roffsum+T->offset >= LL.offset)
					{
					    LL.address->Rlink=R;
					}
					else
					{
					    LL.address->Llink=R;
					}
				    }
				}
			    }
			}
			

			public: static void petrify(struct node *T,int xpos)
			{
			    if(T!=NULL)
			    {
				T->x=xpos;
				if(T->thread)
				{
				    T->thread=false;
				    T->Rlink=NULL;
				    T->Llink=NULL;
				}
				petrify(T->Llink,xpos-T->offset);
				petrify(T->Rlink,xpos+T->offset);
			    }
			}


};
