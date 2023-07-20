#include<stdio.h>
#include<stdlib.h>

struct node{
    int indegree;
    int futureIndegree;
    int vertex;
    struct node *next;
};

struct graph{
    int numberOfVertices;
    struct node **adjList;
};

struct node* createNode(int V){
    struct node *newV = malloc(sizeof(struct node));
    newV->vertex = V;
    newV->next = NULL;
    newV->indegree = 0;
    return newV;
}

struct graph* createGraph(int nVertices){
    int i;
    struct graph *graph = malloc(sizeof(struct graph));
    graph->adjList = malloc(nVertices*sizeof(struct node));
    graph->numberOfVertices = nVertices;
    for(i=0; i<nVertices; i++){
        
        graph->adjList[i] = createNode(i);
    }
    return graph;
}

void Edge(struct graph *graph, int u, int v){
    struct node* newNode = createNode(v);
    newNode->next = graph->adjList[u]->next;
    graph->adjList[u]->next = newNode;
    
}

void printGraph(struct graph* graph){
    int i,j;
    for(i=0; i<graph->numberOfVertices; i++){
        
        printf("\n");
        struct node* tmp = graph->adjList[i];
        printf("Ders %d nin bagli olduklari: ", i+1);
        while(tmp->next != NULL){
            
            tmp = tmp->next;
            printf("Ders %d  ", tmp->vertex + 1);
        }
        printf("        indegree: %d", graph->adjList[i]->indegree);
    }
}

void findIndegree(struct graph* graph){
    int i,j;
    int indegree;
    for(i=0; i<graph->numberOfVertices; i++){
        
        printf("\n");
        struct node* tmp = graph->adjList[i];
        
        indegree=0;
        while(tmp->next != NULL){
            indegree++;
            tmp = tmp->next;
            
        }

        graph->adjList[i]->indegree = indegree;
        graph->adjList[i]->futureIndegree = indegree;


    }
}

int takeLessons(struct graph* graph, int done){
    int x;
    int i,k;

    for(i=0; i<graph->numberOfVertices; i++){

        if(graph->adjList[i]->indegree == 0){
            graph->adjList[i]->futureIndegree = -1;
            done++;
            printf("\nders %d alindi", graph->adjList[i]->vertex + 1);
            for(k=0; k<graph->numberOfVertices; k++){

                struct node* tmp = graph->adjList[k];
                while(tmp->next != NULL){
                    tmp = tmp->next;
                    if(tmp->vertex == graph->adjList[i]->vertex){
                        x = graph->adjList[k]->futureIndegree;
                        graph->adjList[k]->futureIndegree = x -1;
                    }
                }

            }
            
        }
        
    }

    for(i=0; i<graph->numberOfVertices; i++){
        graph->adjList[i]->indegree = graph->adjList[i]->futureIndegree;
    }

    return done;
}

int main(){
    int **G, N, E, done = 0;
    int i, j, term=0;

    printf("N degerini giriniz: ");
    scanf("%d", &N);

    printf("E degerini giriniz: ");
    scanf("%d", &E);

    struct graph* graph = createGraph(N);

    G = (int**) calloc (N,sizeof(int*));
    if(G==NULL){
		
		return -16;
	}else{
		
		for(i=0;i<N;i++){
			
			G[i] = (int*)malloc(N*sizeof(int));
			if(G[i] == NULL){
				
				return -16;
			}
			
		}	
	}

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d", &G[i][j]);
            if(G[i][j] == 1){
                Edge(graph, i, j);
            }
        }
    }

    findIndegree(graph);
    printGraph(graph);
    printf("\n\n");

    while(done != graph->numberOfVertices){

        printf("\n\n%d. donemde aldigi dersler: ", term+1);
        done = takeLessons(graph, done);
        term++;
        
        
    }

    printf("\n\n\nOkulu %d donemde bitirir.", term);



    return 0;
}