#define _CRT_SECURE_NO_WARNINGS 
#define INF 1000000000             // 정점 사이 무한대의 값
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// 다익스트라 알고리즘 함수
void Dijkstra(int v, int read, int graph[50][50]) {
    // 방향 그래프를 저장할 배열 동적 할당
    int** metric = (int**)malloc(sizeof(int*) * v);       
    for (int i = 0; i < v; i++) {
        *(metric + i) = (int*)malloc(sizeof(int) * v);
    }
    // 각 정점으로부터 모든 정점까지 거리를 metric 에 저장
    for (int i = 0; i < v; i++) {
        // 두 정점이 같으면 0, 아니면 INF 저장
        for (int j = 0; j < v; j++) {
            metric[i][j] = INF;
            metric[i][i] = 0;
        }
        for (int k = 0; k < v; k++) {
            if (graph[read + i + 1][2 * k + 1] != -1) {
                metric[i][graph[read + i + 1][2 * k + 1] - 1] = graph[read + i + 1][2 * k + 2];
            }
            else break;
        }
    }

    int not_visit[20];        
    int distance[20];         
    int path[20][30];         
    // 존재하지 않는 값은 모두 -1로 저장
    memset(not_visit, -1, 20 * sizeof(int));
    memset(distance, -1, 20 * sizeof(int));
    memset(path, -1, sizeof(path[0][0]) * 20 * 30);

    // 최단거리 초기화
    distance[0] = 0;
    path[0][0] = 1;
    for (int i = 1; i < v; i++) {
        path[i][0] = 1;
        not_visit[i - 1] = i + 1;
        distance[i] = INF;
    }
    int vstart = 0;           
    int vnext = 0;           
    int dmin = 0;             
    int vnow = 0;            

    // 루프 반복문
    for (int i = 1; i < v; i++) {
        dmin = INF;
        // 최단 거리, 경로, 그 점을 갱신하는 반복문
        for (int j = 0; j < v; j++) {
            if (not_visit[j] != -1) {
                vnow = not_visit[j] - 1;
                // 시작 정점에서 바로 오는 경우가 더 가까우면, 이를 최단경로로 저장
                if (distance[vstart] + metric[vstart][vnow] < distance[vnow]) {
                    distance[vnow] = distance[vstart] + metric[vstart][vnow];
                    // 최적경로 갱신
                    for (int k = 0; k <= i; k++) {
                        if (path[vstart][k] == -1) {
                            path[vnow][k] = vnow + 1;
                            break;
                        }
                        else path[vnow][k] = path[vstart][k];
                    }
                }
                // 최단거리 업데이트 
                if (distance[vnow] < dmin) {
                    dmin = distance[vnow];
                    vnext = vnow;
                }
            }
        }

        // 다음 정점을 시작 정점으로 설정 
        vstart = vnext;
        for (int k = 0; k < v; k++) {
            if (not_visit[k] == vstart + 1) {
                not_visit[k] = -1;
            }
        }
    }

    // 최단경로, 최단거리 출력
    for (int i = 1; i < v; i++) {
        printf("\n정점 [%d] : ", i + 1);
        for (int j = 0; j < v; j++) {
            if (path[i][j + 1] == -1) {
                printf("%d, ", path[i][j]);
                break;
            }
            printf("%d - ", path[i][j]);
        }
        printf("길이 : %d", distance[i]);
    }

    // 이차원 배열 동적할당에 대한 메모리 제거
    for (int i = 0; i < v; i++)
        free(*(metric+i));
    free(metric);
}

// 메인 함수
int main(void) {
    int graph[50][50];
    memset(graph, -1, sizeof(graph[0][0]) * 50 * 50);

    FILE* fp;
    fp = fopen("input2.txt", "r");
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
        printf("시작점 : 1");
        Dijkstra(graph[read][0], read, graph);
        printf("\n====================================\n\n");
        read += graph[read][0] + 1;
        if (graph[read][0] == -1)
            break;
    }
    return 0;
}