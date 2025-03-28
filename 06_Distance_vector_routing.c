#include <stdio.h>
#include <limits.h>  // For INT_MAX

#define MAX 50

int dist[MAX][MAX], temp[MAX][MAX], n;

// Function prototype
void dvr();

int main() {
    int i, j, x;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    printf("\nEnter the distance matrix (enter 999 for no direct path):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if (dist[i][j] == 999)  // Replace 999 with INT_MAX for unreachable paths
                dist[i][j] = INT_MAX;
            if (i == j) 
                dist[i][j] = 0;  // Distance to itself is always zero
            temp[i][j] = j;  // Initialize next-hop table
        }
    }

    // Run DVR algorithm before update
    dvr();

    // Updating the cost between two nodes
    printf("\nEnter value of i & j (nodes to update cost): ");
    scanf("%d%d", &i, &j);
    printf("Enter the new cost: ");
    scanf("%d", &x);
    
    dist[i][j] = x;
    dist[j][i] = x; // Assuming an undirected graph

    printf("\nAfter update:\n\n");
    dvr();

    return 0;
}

// Distance Vector Routing Algorithm (Floyd-Warshall)
void dvr() {
    int i, j, k;

    // Apply Floyd-Warshall algorithm to find the shortest paths
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    temp[i][j] = temp[i][k];  // Update next-hop router
                }
            }
        }
    }

    // Print distance vector table
    for (i = 0; i < n; i++) {
        printf("\nState value for router %d:\n", i + 1);
        for (j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX)
                printf("\tNode %d via %d Distance: INF", j + 1, temp[i][j] + 1);
            else
                printf("\tNode %d via %d Distance: %d", j + 1, temp[i][j] + 1, dist[i][j]);
        }
        printf("\n");
    }
}
