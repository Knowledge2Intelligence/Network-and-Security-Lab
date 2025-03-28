#include <stdio.h>
#include <limits.h>

int main() {
    int u, v, num, i, j, l, k, n;
    int s[10], min, cost[10][10], dist[10], path[10];

    printf("\n ENTER THE TOTAL NUMBER OF NODES: ");
    scanf("%d", &n);

    printf("\n ENTER THE ADJACENCY MATRIX (Use -1 for no connection):\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
            if (i == j)
                cost[i][j] = 0;  // Distance to self is always zero
            else if (cost[i][j] == -1)
                cost[i][j] = INT_MAX;  // No connection treated as infinity
        }
    }

    printf("\n ENTER THE DESTINATION NODE NUMBER: ");
    scanf("%d", &v);

    // Initialize distances and path
    for (i = 1; i <= n; i++) {
        s[i] = 0;  // All nodes unvisited
        path[i] = v;
        dist[i] = cost[v][i];  // Initial distances from destination
    }
    dist[v] = 0;  // Distance to itself is zero

    // Dijkstra's Algorithm
    for (num = 2; num <= n; num++) {
        min = INT_MAX;
        u = -1;

        // Find the unvisited node with the smallest distance
        for (i = 1; i <= n; i++) {
            if (!s[i] && dist[i] < min) {
                u = i;
                min = dist[i];
            }
        }

        if (u == -1) break; // No more reachable nodes

        s[u] = 1;  // Mark node as visited

        // Update distance values
        for (i = 1; i <= n; i++) {
            if (!s[i] && cost[u][i] != INT_MAX && dist[i] > (min + cost[u][i])) {
                dist[i] = min + cost[u][i];
                path[i] = u;
            }
        }
    }

    // Print path matrix
    printf("\nPATH MATRIX:\n");
    printf("\nDISTANCE   NODE   PATH\n");
    for (i = 1; i <= n; i++) {
        printf("\n %6d   %4d   ", dist[i], i);
        j = i;
        do {
            printf(" --> %d ", path[j]);
            u = path[j];
            j = u;
        } while (u != v);
    }
    
    printf("\n");
    return 0;
}
