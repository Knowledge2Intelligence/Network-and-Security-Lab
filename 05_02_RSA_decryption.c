#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Needed for string functions

int main() {
    int k, b, bin[20];
    int i;
    long int c, m, d, n;
    char ch;
    char in_file[256], out_file[256];
    FILE *in, *out;

    // Get file names securely
    printf("\nEnter ciphertext file name: ");
    fgets(in_file, sizeof(in_file), stdin);
    in_file[strcspn(in_file, "\n")] = 0;  // Remove newline

    printf("\nEnter file name to store decrypted output: ");
    fgets(out_file, sizeof(out_file), stdin);
    out_file[strcspn(out_file, "\n")] = 0;  // Remove newline

    // Open files with error handling
    in = fopen(in_file, "r");
    if (in == NULL) {
        perror("Error opening ciphertext file");
        return 1;
    }

    out = fopen(out_file, "w");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);
        return 1;
    }

    printf("\nEnter values of d and n: ");
    if (scanf("%ld%ld", &d, &n) != 2) {
        printf("Invalid input!\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    // Convert d to binary
    i = -1;
    b = d;
    while (b > 0) {
        bin[++i] = b % 2;
        b = b / 2;
    }
    k = i;

    // RSA decryption loop
    while ((m = fgetc(in)) != EOF) {
        c = 1;
        for (i = k; i >= 0; i--) {
            c = (c * c) % n;
            if (bin[i] == 1)
                c = (c * m) % n;
        }
        fputc(c, out);
    }

    printf("\nFile is decrypted successfully.\n");

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
