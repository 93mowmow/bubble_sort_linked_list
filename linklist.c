#include <stdio.h>
struct node {
    int number;
    struct node *next;
};
typedef struct node Node;

void ShowNode(Node *);
void InitialNode(Node *);
void InsertList(Node **,int);
void InsertSortList(Node **HeadPtr,int num);
void DeleteList(Node **,int);
int ShowList(Node *);
int Search(Node *,int);
void Bubble_sort(Node **,int);

int main()
{
    char ch;
	int no_of_nodes = 0;
	Node *N, *L, *List;
    //node *K;
    int target,locn;
    N = (Node *) malloc( sizeof(Node) );
    N->number = 5;
    N->next = (Node *) malloc( sizeof(Node) );
    N->next->number = 10;
    ShowNode(N);
    ShowNode(N->next);
    L = N->next;
    ShowNode(L);
    InitialNode(L);
    ShowNode(N->next);
    L->next = (Node *) malloc( sizeof(Node) );
    L = L->next;
    InitialNode(L);
    L->number = 15;
    ShowNode(N->next->next);
    puts("---List---\n");
    List = NULL;
    InsertList(&List,20);
	InsertList(&List,10);
    InsertList(&List,15);
    InsertList(&List,50);
    InsertList(&List,90);
    InsertList(&List,5);
    no_of_nodes = ShowList(List);
	printf("Number of nodes = %d\n",no_of_nodes);
	
	Bubble_sort(&List,no_of_nodes);
	no_of_nodes = ShowList(List);
	
    while(1)
    {
        puts("Please input the data to search (-999 to stop):");
        scanf("%d",&target);
        locn = Search(List,target);
        if( target == -999 )
            break;
        if( locn == -1 )
            puts("Target not found!\n");
        else
            printf("Target %d is found at position %d\n",target,locn);
    } // end of while(1) [Searching data]
    ShowList(List);
	
	
	while(1)
    {
        puts("Please input the data to delete (-999 to stop):");
        scanf("%d",&target);
		
		if( target == -999 )
        break;
		
		locn = Search(List,target);
		if( locn == -1 ){
		puts("Target not found!\n");
		continue;
		}
        
		DeleteList(&List,target);
        printf("Target %d is deleted\n",target);
			
		ShowList(List);	
    } // end of while(1) delete
    
	
	ShowList(List);	
	
	ch = getchar();
	
} // end of main function
void ShowNode(Node *node)
{
    printf("Node number = %d, next = %x\n",node->number,node->next);
} // end of function ShowNode

int ShowList(Node *node)
{
   int counter = 0;
   if(node==NULL){
   printf("Empty list!!\n");
   return 0;
   }
   // To do: Show each node of the list
   while( node != NULL )
   {
        counter++;
		ShowNode( node );
        node = node->next;
   }
   
   return counter;
} // end of function ShowList

void InitialNode(Node *node)
{
    node->number = 0;
    node->next = NULL;
} // end of function InitialNode

void InsertSortList(Node **HeadPtr,int num)
{
    Node *newNode;
    Node *Current;
    // initialize the new node 
    newNode = (Node *) malloc( sizeof(Node) );
    InitialNode(newNode);
    newNode->number = num;
    // insert the new node at the end of the list
    if ( *HeadPtr == NULL )  // Empty List
        *HeadPtr = newNode;  // The new node is the only node in the list
    else  // The list is not empty
    {
         Current = *HeadPtr;  // start from the head of the list
         if( num < Current->number )
         {
             newNode->next = Current;
             *HeadPtr = newNode;
             return;
         }
         
		 while( Current->next != NULL && Current->next->number < num )
             Current = Current->next;
			 
         newNode->next = Current->next;
         Current->next = newNode;
         /*
         while( Current->next != NULL ) // finds the tail of the list
              Current = Current->next;
         Current->next = newNode; // insert the new node
         */
    }
} // end of function InsertList

//Sequential insert
void InsertList(Node **HeadPtr,int num)
{
    Node *newNode;
    Node *Current;
    // initialize the new node 
    newNode = (Node *) malloc( sizeof(Node) );
    InitialNode(newNode);
    newNode->number = num;
    // insert the new node at the end of the list
    if ( *HeadPtr == NULL )  // Empty List
        *HeadPtr = newNode;  // The new node is the only node in the list
    else  // The list is not empty
    {
         Current = *HeadPtr;  // start from the head of the list
         
         while( Current->next != NULL ) // finds the tail of the list
              Current = Current->next;
         Current->next = newNode; // insert the new node
         
    }
} // end of function InsertList

// function: Search
// return the position of the search target
// if the target is not in the list, returns -1
int Search(Node *node,int target)
{
    int locn = 0;
    while( node != NULL && node->number != target )
    {
         locn++;
         node = node->next;
    } // end of while
    if( node == NULL )
        return -1;
    return locn;
    // return (node==NULL)?-1:locn;
} // end of function Search

void DeleteList(Node **HeadPtr,int num)
{
    
    Node *Current;
	Node *tmp;
    
   	Current=*HeadPtr;
	// target is the head of list
    if ( Current->number ==num ){
	    if(Current->next==NULL){
        *HeadPtr=NULL;
		free(Current);
		}
		else{
		*HeadPtr=Current->next;
		free(Current);
		}

	}		
    else  // not the head
    {
         Current = *HeadPtr;  // start from the head of the list

         while( Current->next != NULL && Current->next->number != num )
             Current = Current->next;
			 
         if(Current->next->next == NULL){
		 tmp=Current->next;
		 Current->next=NULL;
		 free(tmp);
		 }
		 else{
		 tmp=Current->next;
		 Current->next=tmp->next;
		 free(tmp);
		 }

    }
	
	
} // end of function DeleteList

void Bubble_sort(Node **HeadPtr,int no_of_nodes)
{
    int i = 0;
	Node *parent;
	Node *Current;
	Node *swap_node;
    
	Current = *HeadPtr;
	
	if(no_of_nodes <= 1)
		return;
	
	for( i = 0; i < no_of_nodes; i++){
		
		Current = *HeadPtr;
		
		while( Current->next != NULL ){
			swap_node = Current->next;
			
			if (Current == *HeadPtr){
				if ( Current->number > swap_node->number )
				{	
					Current->next = swap_node->next;
					swap_node->next = Current;
					*HeadPtr = swap_node;
				}
			} else {
				if ( Current->number > swap_node->number )
				{	
					Current->next = swap_node->next;
					swap_node->next = Current;
					parent->next = swap_node;
				}			
			}
			parent = Current;
			Current = Current->next;
			
			if(Current == NULL)
				break;
			
		} 
	
	
	}// end of for

} // end of function Search
