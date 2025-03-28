#include <stdio.h>
#include <string.h>

int main() {
    int i, j, k, m, n, cl;
    char a[10], c[100];

    // Input polynomial and received CRC frame
    printf("\n ENTER POLYNOMIAL: ");
    scanf("%s", a);
    printf("\n ENTER THE CRC FRAME: ");
    scanf("%s", c);

    m = strlen(a);
    cl = strlen(c);

    // Remove leading zeros from the polynomial
    for (i = 0; i < m; i++) {
        if (a[i] == '1') {
            m = m - i;
            break;
        }
    }

    // Adjust polynomial to remove leading zeros
    char adjusted_poly[10];
    for (k = 0; k < m; k++)
        adjusted_poly[k] = a[k + i];

    n = cl - m + 1;

    // Perform CRC verification
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

    // Check if remainder is all zeros
    for (i = 0; i < cl; i++) {
        if (c[i] == '1') {
            printf("\n THERE IS SOME ERROR IN THE MESSAGE.");
            return 0;
        }
    }

    printf("\n MESSAGE IS CORRECT.");
    return 0;
}
