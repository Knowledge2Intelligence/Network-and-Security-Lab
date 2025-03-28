#include <stdio.h>

int main() {
    int l1, bit[101], count = 0, i, choice;

    printf("Enter the length of data stream: ");
    scanf("%d", &l1);

    printf("\nEnter the data stream (0s and 1s only): ");
    for (i = 0; i < l1; i++) {
        scanf("%d", &bit[i]);
        if (bit[i] == 1) {
            count++;
        }
    }

    printf("\nNumber of 1's: %d", count);
    printf("\nEnter the choice to implement parity bit:");
    printf("\n1 - Sender side\n2 - Receiver side\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Sender Side
            if (count % 2 == 0) {
                bit[l1] = 0; // Even parity
            } else {
                bit[l1] = 1;
            }

            printf("\nThe data stream after adding parity bit is: ");
            for (i = 0; i <= l1; i++) {
                printf("%d", bit[i]);
            }
            break;

        case 2: // Receiver Side
            if (count % 2 == 0) {
                printf("\nThere is no error in the received data stream.");
            } else {
                printf("\nThere is an error in the received data stream.");
            }
            break;

        default:
            printf("\nInvalid choice.");
            break;
    }

    return 0;
}
