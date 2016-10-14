class RandomTree{

		/** Creating a new Node*/
		public: static struct node* newNode(int key)
		{
		    struct node* node = (struct node*)
		    malloc(sizeof(struct node));
		    node->key   = key;
		    node->Llink  = NULL;
		    node->Rlink  = NULL;
		    node->parent = NULL;
		    return(node);
		}

		/** Inserting a node into predefined binary tree*/
		static struct node* insert(struct node* node, int key)
		{
		    
		    if (node == NULL)
			return(newNode(key));
		    
		    if (key < node->key)
			node->Llink  = insert(node->Llink, key);
		    else
			node->Rlink = insert(node->Rlink, key);

		    
		    node->thread = false;
		    return node;
		}
};

