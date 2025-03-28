#include <stdio.h>
#include <math.h>

int input[32];
int code[32];

int ham_calc(int position, int c_l);

int main() {
    int n, i, p_n = 0, c_l, j, k, error_pos = 0;

    // Input Data Word
    printf("Please enter the length of the Data Word: ");
    scanf("%d", &n);
    printf("Please enter the Data Word:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }

    // Calculate number of parity bits required
    i = 0;
    while (n > (1 << i) - (i + 1)) {
        p_n++;
        i++;
    }

    c_l = p_n + n; // Total length of code word

    // Insert parity bits at positions 2^k (1, 2, 4, 8, ...)
    j = k = 0;
    for (i = 0; i < c_l; i++) {
        if (i == ((1 << k) - 1)) { // Check for parity positions
            code[i] = 0;
            k++;
        } else {
            code[i] = input[j];
            j++;
        }
    }

    // Compute parity bits
    for (i = 0; i < p_n; i++) {
        int position = (1 << i);
        int value = ham_calc(position, c_l);
        code[position - 1] = value;
    }

    // Display Code Word
    printf("\nThe calculated Code Word is: ");
    for (i = 0; i < c_l; i++)
        printf("%d", code[i]);
    printf("\n");

    // Receiving the Code Word
    printf("Please enter the received Code Word:\n");
    for (i = 0; i < c_l; i++)
        scanf("%d", &code[i]);

    // Check for errors
    error_pos = 0;
    for (i = 0; i < p_n; i++) {
        int position = (1 << i);
        int value = ham_calc(position, c_l);
        if (value != 0)
            error_pos += position;
    }

    // Error correction or validation
    if (error_pos == 0)
        printf("The received Code Word is correct.\n");
    else {
        printf("Error detected at bit position: %d\n", error_pos);
        code[error_pos - 1] ^= 1; // Flip the bit to correct the error
        printf("Corrected Code Word: ");
        for (i = 0; i < c_l; i++)
            printf("%d", code[i]);
        printf("\n");
    }

    return 0;
}

// Function to calculate parity bit value
int ham_calc(int position, int c_l) {
    int count = 0, i, j;
    i = position - 1;

    while (i < c_l) {
        for (j = i; j < i + position && j < c_l; j++) {
            if (code[j] == 1)
                count++;
        }
        i += 2 * position;
    }

    return (count % 2);
}
