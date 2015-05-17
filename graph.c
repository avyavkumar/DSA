#include <stdio.h>
#include <stdlib.h>

#ifndef _GRAPH_H_
#define _GRAPH_H_

 
typedef enum {UNDIRECTED=0,DIRECTED} graph_type_e;
typedef enum {_BFS,_DFS} search_type_e;
 
/* Adjacency list node*/
typedef struct adjlist_node
{
    int vertex;                /*Index to adjacency list array*/
    int colour;             /*Checks if the node is visited*/
    struct adjlist_node *next; /*Pointer to the next node*/
} adjlist_node_t, *adjlist_node_p;
 
/* Adjacency list */
typedef struct adjlist
{
    int num_members;           /*number of members in the list (for future use)*/
    adjlist_node_t *head;      /*head of the adjacency linked list*/
}adjlist_t, *adjlist_p;
 
/* Graph structure. A graph is an array of adjacency lists.
   Size of array will be number of vertices in graph*/
typedef struct graph
{
    graph_type_e type;        /*Directed or undirected graph */
    int num_vertices;         /*Number of vertices*/
    adjlist_p adjListArr;     /*Adjacency lists' array*/
}graph_t, *graph_p;
 
/* Exit function to handle fatal errors*/
__inline void err_exit(char* msg)
{
    printf("[Fatal Error]: %s \nExiting...\n", msg);
    exit(1);
}
#endif

/* Function to create an adjacency list node*/
adjlist_node_p createNode(int v)
{
    adjlist_node_p newNode = (adjlist_node_p)malloc(sizeof(adjlist_node_t));
    if(!newNode)
        err_exit("Unable to allocate memory for new node");
 
    newNode->vertex = v;
    newNode->next = NULL; 
    newNode->colour=-1;
    return newNode;
}
 
/* Function to create a graph with n vertices; Creates both directed and undirected graphs*/
graph_p createGraph(int n, graph_type_e type)
{
    int i;
    graph_p graph = (graph_p)malloc(sizeof(graph_t));
    if(!graph)
        err_exit("Unable to allocate memory for graph");
    graph->num_vertices = n;
    graph->type = type;

    /* Create an array of adjacency lists*/
    graph->adjListArr = (adjlist_p)malloc(n * sizeof(adjlist_t));
    if(!graph->adjListArr)
        err_exit("Unable to allocate memory for adjacency list array");
 
    for(i = 0; i < n; i++)
    {
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }
    return graph;
}
 
/*Destroys the graph*/
void destroyGraph(graph_p graph)
{
    if(graph)
    {
        if(graph->adjListArr)
        {
            int v;
            /*Free up the nodes*/
            for (v = 0; v < graph->num_vertices; v++)
            {
                adjlist_node_p adjListPtr = graph->adjListArr[v].head;
                while (adjListPtr)
                {
                    adjlist_node_p tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjListArr);
        }
        /*Free the graph*/
        free(graph);
    }
}

/* Adds an edge to a graph*/
void addEdge(graph_t *graph, int src, int dest)
{
    /* Add an edge from src to dst in the adjacency list*/
    adjlist_node_p newNode = createNode(dest);
    newNode->next = graph->adjListArr[src].head;
    graph->adjListArr[src].head = newNode;
    graph->adjListArr[src].num_members++;
 
    if(graph->type == UNDIRECTED)
    {
        /* Add an edge from dest to src also*/
        newNode = createNode(src);
        newNode->next = graph->adjListArr[dest].head;
        graph->adjListArr[dest].head = newNode;
        graph->adjListArr[dest].num_members++;
    }
}
 
/* Function to print the adjacency list of graph*/
void displayGraph(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = graph->adjListArr[i].head;
        printf("\n%d: ", i);
        while (adjListPtr)
        {
            printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}

int check_colour(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = graph->adjListArr[i].head;
        while (adjListPtr)
        {
            if (adjListPtr->colour==1)
                return 1;          
            adjListPtr = adjListPtr->next;
        }
    }
    return 0;
}

void _convert_list(graph_p graph,int n,search_type_e search)
{
   int matrix[n][n];
   int j,k;
   for(j=0;j<n;j++)
    for(k=0;k<n;k++)
        matrix[j][k]=0;
   if(graph->type==UNDIRECTED)
   {
        int i;
        for(i=0;i<graph->num_vertices;i++)
        {
            adjlist_node_p adjListPtr = graph->adjListArr[i].head;
            while(adjListPtr!=NULL)
            {
                matrix[i][adjListPtr->vertex]=1;
                adjListPtr=adjListPtr->next;
            }
        }
   }

   if(graph->type==DIRECTED)
   {
        int i;
        for(i=0;i<graph->num_vertices;i++)
        {
            adjlist_node_p adjListPtr = graph->adjListArr[i].head;
            while(adjListPtr!=NULL)
            {
                matrix[i][adjListPtr->vertex]++;
                adjListPtr=adjListPtr->next;
            }
        }
   }
   
   void print_matrix()
   {
       for(j=0;j<n;j++)
       {
            for(k=0;k<n;k++)
                printf("%d ",matrix[j][k]);
            printf("\n");
       }
   }
   int i;
    
   if(search==_DFS)
    {
        int visited[n*n];
        for(i=0;i<n;i++)
           visited[i]=0;
        void graph_DFS(int i)
        {
            int j;
            printf("\n%d",i);
            visited[i]=1;
            for(j=0;j<n;j++)
                if(!visited[j] && matrix[i][j]==1)
                    graph_DFS(j);
        }
        graph_DFS(5);       //any starting number
    }
    
    if(search==_BFS)
    {
        int q[n*n],visited[n*n],f=0,r=-1;
        for (i=0;i<n;i++) 
        {
            q[i]=0;
            visited[i]=0;
        }
        void graph_BFS(int v) 
        {
            for (i=0;i<n;i++)
                if(matrix[v][i] && !visited[i])
                    q[++r]=i;
            if(f<=r) 
            {
                visited[q[f]]=1;
                graph_BFS(q[f++]);
            }
        }
        graph_BFS(2);             //any starting number 
        printf("\nThe nodes which are reachable are:\n");
        for (i=0;i<n;i++)
        {
          if(visited[i])
            printf("%d\n",i); 
          else
            printf("BFS is not possible\n");
        }
    }
}

/*
void BFS(graph_p graph,int n)
{
    adjlist_node_t *queue[1000];
    adjlist_node_t *temp=NULL;
    int push=0;
    int pop=0;
    int i,j=0;
    for(i=0;i<graph->num_vertices;i++)
    {
        queue[push]=graph->adjListArr[i].head;
        temp=graph->adjListArr[i].head;
        queue[i]->colour=0;
        int _head=graph->adjListArr[i].num_members;
        push++;
        temp=temp->next;
        while(temp!=NULL)
        {
            temp->colour=0;
            queue[push]=temp;
            push++;
            temp=temp->next;
        }
        while((_head-j-1)>0)
        {
            temp=queue[pop];
            temp->colour=1;
            pop++;
            queue[push]=graph->adjListArr[temp->vertex].head;
            queue[push]->colour=0;
            temp=queue[push];
            temp=temp->next;
            int _temp=graph->adjListArr[temp->vertex].num_members;
            while(_temp!=0)
            {
                push++;
                while(temp!=NULL)
                {
                    queue[push]=temp;
                    temp->colour=0;
                    push++;
                    temp=temp->next;
                }
                _temp--;   
            }
            j++;
        }        
    }
}
*/

int main()
{
    graph_p undir_graph = createGraph(6, UNDIRECTED);
    //graph_p dir_graph = createGraph(5, DIRECTED);
    
    addEdge(undir_graph, 0, 1);
    addEdge(undir_graph, 0, 4);
    addEdge(undir_graph, 1, 2);
    addEdge(undir_graph, 1, 3);
    addEdge(undir_graph, 3, 5);
    //addEdge(undir_graph, 1, 4);
    //addEdge(undir_graph, 2, 3);
    //addEdge(undir_graph, 3, 4);
    //addEdge(undir_graph, 4, 5);
    _convert_list(undir_graph,6,_BFS);
    //BFS(undir_graph,6);
    //printf("No error \n");

    //addEdge(dir_graph, 0, 1);
    //addEdge(dir_graph, 0, 4);
    //addEdge(dir_graph, 1, 2);
    //addEdge(dir_graph, 1, 3);
    //addEdge(dir_graph, 1, 4);
    //addEdge(dir_graph, 2, 3);
    //addEdge(dir_graph, 3, 4);
    
    //printf("\nUNDIRECTED GRAPH");
    //displayGraph(undir_graph);
    //destroyGraph(undir_graph);
 
    //printf("\nDIRECTED GRAPH");
    //displayGraph(dir_graph);
    //destroyGraph(dir_graph);
 
    return 0;
}