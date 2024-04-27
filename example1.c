/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graphraf*/
#include <stdlib.h>                                                                                                                                                                                                                                                                                        
#include <stdio.h>

typedef struct Node
{
  int data;
  struct Node *next;
} NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    

typedef struct graph
{
    int vertices;
    int *visited;
    struct Node **adjancency_list;
} GPH;

typedef struct s
{
    int top;
    int scap;
    int *arr;
} STACK;

NODE *create_node(int vertices)
{
    NODE *newNode=malloc(sizeof(NODE));
    newNode->data=vertices;
    newNode->next=NULL;
    return newNode;
}

void add_edgraphe(GPH *graph,int src,int dest)
{
    NODE *newNode=create_node(dest);
    newNode->next=graph->adjancency_list[src];
    graph->adjancency_list[src]=newNode;
    newNode=create_node(src);
    newNode->next=graph->adjancency_list[dest];
    graph->adjancency_list[dest]=newNode;
}

GPH *create_graph(int vertices)
{
    int i;
    GPH *graph=malloc(sizeof(GPH));
    graph->vertices=vertices;
    graph->adjancency_list=malloc(sizeof(NODE *));
    graph->visited=malloc(sizeof(int) *vertices);

    for (int i=0;i<vertices;i++)
    {
        graph->adjancency_list[i]=NULL;
        graph->visited[i]=0;
    } 
    return graph;
}

STACK *create_s(int scap)
{
    STACK *s=malloc(sizeof(STACK));
    s->arr=malloc(scap*sizeof(int));
    s->top = -1;
    s->scap=scap;
    return s;
}

void push(int pshd,STACK *s)
{
    s->top = s->top+1;
    s->arr[s->top] = pshd;
}

void DFS(GPH *graph,STACK *s,int v_nr)
{   
    if(graph->adjancency_list[v_nr] == NULL) return;
    NODE *adj_list = graph->adjancency_list[v_nr];
    NODE *aux = adj_list;
    graph->visited[v_nr] = 1;
    push(v_nr,s);
    while (aux != NULL)
    {
        int con_ver=aux->data;
        if (graph->visited[con_ver] == 0)
        {
            DFS(graph,s,con_ver);
        }
        aux=aux->next;
    }
}

void insert_edges(GPH *graph,int edgraph_nr,int nrv)
{
    int src,dest,i;
    printf("adauga graphului %d munchii (de la 0 la %d)\n", edgraph_nr, nrv-1);
    for (i=0 ; i<edgraph_nr;i++)
    {
        scanf("%d%d",&src,&dest);
        add_edgraphe(graph,src,dest);
    }
}

void wipe(GPH *graph, int nrv)
{
    for (int i=0;i<nrv;i++)
    {
        graph->visited[i] = 0;
    }
}  

int* canbe_reached(GPH *graph, int nrv)// 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe_reached = calloc(nrv, sizeof(int)); 
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {   
        STACK *s1 = create_s(2 * nrv);
        DFS(graph, s1, i);
        wipe(graph, nrv);
        if(s1->top >= 0)
        {
            canbe_reached[i]= 1;
        }  
       
    } 
    return canbe_reached;
}
                                                                                                                                                                                                                                                                                                                                    

int main()
{

int nrv;
int edgraph_nr;

printf("cate noduri are graphul?");
scanf("%d", &nrv);

printf("cate muchii are graphul?");
scanf("%d", &edgraph_nr);

GPH *graph = create_graph(nrv);

insert_edges(graph, edgraph_nr, nrv);

int* canbe = canbe_reached(graph, nrv);

printf("\n");
for(int i=0 ; i < nrv ; i++)
{
    printf("%d ", canbe[i]);
}

}
