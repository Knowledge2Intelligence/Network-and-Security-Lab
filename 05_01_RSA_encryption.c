#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int k, b, bin[20];
    int i;
    long int c, m, e, d, n;
    char ch;
    char in_file[256], out_file[256];
    FILE *in, *out;

    // Get file names securely
    printf("\nEnter input text file name: ");
    fgets(in_file, sizeof(in_file), stdin);
    in_file[strcspn(in_file, "\n")] = 0;  // Remove newline

    printf("\nEnter file name to store encrypted output: ");
    fgets(out_file, sizeof(out_file), stdin);
    out_file[strcspn(out_file, "\n")] = 0;  // Remove newline

    // Open files with error checking
    in = fopen(in_file, "r");
    if (in == NULL) {
        perror("Error opening input file");
        return 1;
    }

    out = fopen(out_file, "w");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);
        return 1;
    }

    printf("\nEnter values of e and n: ");
    if (scanf("%ld%ld", &e, &n) != 2) {
        printf("Invalid input!\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    // Convert e to binary
    i = -1;
    b = e;
    while (b > 0) {
        bin[++i] = b % 2;
        b = b / 2;
    }
    k = i;

    // RSA encryption loop
    while ((m = fgetc(in)) != EOF) {
        d = 1;
        for (i = k; i >= 0; i--) {
            d = (d * d) % n;
            if (bin[i] == 1)
                d = (d * m) % n;
        }
        fputc(d, out);
    }

    printf("\nFile is encrypted successfully.\n");

    // Close files
    fclose(in);
    fclose(out);
    
    return 0;
}
