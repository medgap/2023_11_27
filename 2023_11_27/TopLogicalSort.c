#include<stdio.h>
#include<stdlib.h>

#define MAX 32767

typedef struct Graph{
    char* vexs;
    int vexNum;
    int** arcs;
    int arcNum;
}Graph;

typedef struct Node
{
    /* data */
    int data;
    struct Node* next;
}Node;

Node* initStack(){
    Node* stack = (Node*)malloc(sizeof(Node));
    stack->data = 0;
    stack->next = NULL;
    return stack;
}

void push(Node* stack, int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = stack->next;
    node->data = data;
    stack->next = node;
    stack->data++;
}

int isEmpty(Node* node){
    if(node->next == NULL)
        return 1;
    return 0;
}

int pop(Node* stack){
    if(!isEmpty(stack)){
        Node* node = stack->next;
        int data = node->data;
        stack->next = node->next;
        free(node);
        stack->data--;
        return data;
    }
    else{
        return -1;
    }
}

Graph* initGraph(int vexNum){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char) * vexNum);
    G->arcs = (int**)malloc(sizeof(int*) * vexNum);
    for(int i = 0; i < vexNum; i++){
        G->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    G->arcNum = 0;
    G->vexNum = vexNum;
    return G;
}

void createGraph(Graph* G, char* vexs, int* arcs){
    for(int i = 0; i < G->vexNum; i++){
        G->vexs[i] = vexs[i];
        for(int j = 0; j < G->vexNum; j++){
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if(G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
                G->arcNum++;
        }
    }
    G->arcNum /= 2;
}

void DFS(Graph* G, int* visited, int index){
    printf("%c\t",G->vexs[index]);
    visited[index] = 1;
    for(int i = 0; i < G->vexNum; i++){
        if(!visited[i] && G->arcs[index][i] > 0 && G->arcs[index][i] != MAX)
            DFS(G, visited, i);
    }
}

int* getInDegrees(Graph* G){
    int* degrees = (int*)malloc(sizeof(int) * G->vexNum);
    for(int i = 0; i < G->vexNum; i++){
        degrees[i] = 0;
    }
    for(int i = 0; i < G->vexNum; i++){
        for(int j = 0; j < G->vexNum; j++){
            if(G->arcs[i][j] != 0){
                degrees[j] = degrees[j] + 1;
            }
        }
    }
    return degrees;
}

void toplogicalSort(Graph* G){
    int index = 0;
    Node* stack = initStack();
    //top数组用来记录要输出的索引
    int* top = (int*)malloc(sizeof(int) * G->vexNum);
    int* degrees = getInDegrees(G);
    for(int i = 0; i < G->vexNum; i++){
        if(degrees[i] == 0)
            push(stack, i);
    }
    while(!isEmpty(stack)){
        //依旧是度为0 的点出栈(索引)
        int vex = pop(stack);
        top[index++] = vex;
        for(int i = 0; i < G->vexNum; i++){
            if(G->arcs[vex][i]){
                degrees[i] = degrees[i] - 1;
                if(degrees[i] == 0)
                //度为0的点进栈
                    push(stack, i);
            }
        }
    }
    for (int i = 0; i < index; i++) {
        printf("%c ", G -> vexs[top[i]]);
    }
    printf("\n");
}

int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    createGraph(G, "abcdef", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    toplogicalSort(G);
    return 0;
}