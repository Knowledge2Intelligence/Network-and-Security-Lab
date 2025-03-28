#include <stdio.h>
#include <string.h>

int main() {
    int i, j, k, m, n, cl;
    char a[10], b[100], c[100];

    // Input polynomial and frame
    printf("\n ENTER POLYNOMIAL: ");
    scanf("%s", a);
    printf("\n ENTER THE FRAME: ");
    scanf("%s", b);

    m = strlen(a);
    n = strlen(b);

    // Remove leading zeros from the polynomial
    for (i = 0; i < m; i++) {
        if (a[i] == '1') {
            m = m - i;
            break;
        }
    }

    // Shift the polynomial
    char adjusted_poly[10];
    for (k = 0; k < m; k++)
        adjusted_poly[k] = a[k + i];

    // Create a copy of b[] in c[] and append m-1 zeros
    cl = n + m - 1;
    for (i = 0; i < n; i++)
        c[i] = b[i];
    for (i = n; i < cl; i++)
        c[i] = '0';
    c[i] = '\0';  // Null-terminate the string

    // Perform CRC division
    for (i = 0; i < n; i++) {
        if (c[i] == '1') {
            for (j = i, k = 0; k < m; k++, j++) {
                if (adjusted_poly[k] == c[j])
                    c[j] = '0';
                else
                    c[j] = '1';
            }
        }
    }

    // Copy original data to the final frame
    for (i = 0; i < n; i++)
        c[i] = b[i];

    printf("\n THE MESSAGE IS: %s", c);
    return 0;
}
