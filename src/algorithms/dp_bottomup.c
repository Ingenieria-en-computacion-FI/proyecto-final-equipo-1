#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}
int dp_knapsack_processes(int ram_disponible, int pesos_memoria[], int prioridades[], int n) {
    int i, w;
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((ram_disponible + 1) * sizeof(int));
    }
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= ram_disponible; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; 
            } 
            else if (pesos_memoria[i - 1] <= w) {
                dp[i][w] = max(
                    prioridades[i - 1] + dp[i - 1][w - pesos_memoria[i - 1]], 
                    dp[i - 1][w]                                             
                );
            } 
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    int mejor_valor = dp[n][ram_disponible];
    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return mejor_valor; 
}
