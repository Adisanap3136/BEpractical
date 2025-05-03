#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 10
int graph[MAX][MAX], visited[MAX];
int n;

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                #pragma omp critical
                {
                    visited[i] = 1;
                    queue[rear++] = i;
                }
            }
        }
    }
}

void dfs(int node) {
    visited[node] = 1;
    printf("%d ", node);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            #pragma omp critical
            dfs(i);
        }
    }
}

int main() {
    int start;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:
");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter starting node: ");
    scanf("%d", &start);

    printf("\nParallel BFS: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    bfs(start);

    printf("\nParallel DFS: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    dfs(start);

    return 0;
}
