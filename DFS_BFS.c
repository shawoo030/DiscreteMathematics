#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define _CRT_SECURE_NO_WARNINGS
#define INT_MAX 1000 // 최대 정수
#define TRUE 1
#define FALSE 0
#define INF 1000 //무한대(연결이 없는 경우)


// 1. 깊이 탐색 알고리즘 (스택)
int DFSvisited[50] = {0};        // 방문 여부 체크
int DFS(int here, int v, int adj_graph[50]50]){
      
   if (DFSvisited[here]==0) {
      printf("%d ", here+1);
   }
   DFSvisited[here] = 1;    // 현재 노드 방문 체크 

   int there = 0;
   for(there=0; there<=v-1; there++){    // 모든 인접한 노드를 확인
      if(adj_graph[here][there] == 1 && DFSvisited[there] == 0){   
         // 현재 노드와 인접하고 지금까지 방문하지 않은 노드라면 
         DFS(there,v,adj_graph); // 재귀
      }
   }
   
   return 0;
}


// 2. 너비탐색 알고리즘 (큐)
int queue[50] = {0};
int BFSvisited[50] = {0};
int BFS(int here, int v, int adj_graph[50][50]){

   int front = 0, rear = 0, pop, there;

   queue[0] = here;
   printf("\n%d ",here+1);
   rear ++; // 큐 뒤에 노드가 하나 추가될 때 마다 증가하는 index
   BFSvisited[here]=1; // 현재 노드 방문 체크

   while (front<rear) { // 큐에 추가된 노드가 제거된 노드보다 많다면 -> 큐가 비어있지 않음 
      pop = queue[front]; // 큐의 가장 앞의 노드, 인접 노드를 큐에 다 추가하고 나면 제거되야 할 것
      for (there = 0; there <= v-1; there++) 
      { 
         if (adj_graph[pop][there]==1 && BFSvisited[there]==0) 
         { // here과 인접하고 아직 방문하지 않은 노드를 하나씩 거치면서 큐에 추가
            printf("%d ",there+1); 
            queue[rear] = there; // 인접한 노드로 이동, 큐 뒤에 추가
            rear ++;  //rear index 증가
            BFSvisited[there]=1; // 인접 노드 방문 체크
         }
      }
      front ++; // 큐의 맨 앞 노드가 밖으로 나갔다
      
   }
   // 큐가 비어있으면 while문 들어가지 못하고 종료
   return 0;
} 





// 메인 함수
int main(void) {
    int graph[50][100];
    memset(graph, -1, sizeof(graph[0][0]) * 30 * 100);

    FILE* fp;
    fp = fopen("input1.txt", "r");

    int m = 0;
    while (feof(fp) == 0) {
        char str[100];
        fgets(str, 100, fp);
        char* ptr = strtok(str, " ");
        int n = 0;
        while (ptr != NULL) {
            graph[m][n] = atoi(ptr);
            n++;
            ptr = strtok(NULL, " ");
        }
        m++;
    }
    fclose(fp);

   int read = 0;
   
   for (int TC = 1; TC <= 20; TC++) {
      printf("그래프 [%d]\n", TC);
      printf("------------------------------------\n");
      printf("시작점 : 1\n");

      // 인접행렬 만들기
      int v = graph[read][0];
      //printf("노드 개수:%d\n", v);

      int adj_graph[50][50] = {0};
      for (int i=0; i<v; i++) {
         for (int k = 1; k < v; k++) {
            int adj_node = graph[read + i + 1][k]; 
            if (adj_node != -1) {
               adj_graph[i][adj_node - 1] = 1;
               //printf("adj_graph[%d][%d]:%d\n",i,k,adj_graph[i][k]);
            }
            else break;
         }
      }

      // 리스트 초기화
      for (int i=0; i<=30; i++){
         DFSvisited[i] = 0;
         BFSvisited[i] = 0;
         queue[i] = 0;} 
      
      // 깊이 우선 탐색 실행
      printf("깊이 우선 탐색:\n");
      DFS(0, v, adj_graph);


      // 너비 우선 탐색 실행
      printf("\n너비 우선 탐색:");
      BFS(0, v, adj_graph);

      printf("\n====================================\n\n");

      read += graph[read][0] + 1;
      if (graph[read][0] == -1)
         break;
   }

   return 0;
}