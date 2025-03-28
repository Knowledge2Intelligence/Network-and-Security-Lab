#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Global variables
char output[9];
char key_tmp[11];
char k1[9];
char k2[9];
char l[5];
char r[5];
char binary_tmp[3];
char s0_box[4][4];
char s1_box[4][4];

// Permutation and Switching Constants
const int IP[8] = {1, 5, 2, 0, 3, 7, 4, 6};
const int IPI[8] = {3, 0, 2, 4, 6, 1, 7, 5};
const int EP[8] = {3, 0, 1, 2, 1, 2, 3, 0};
const int P4[4] = {1, 3, 2, 0};
const int P10[10] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
const int P8[8] = {5, 2, 6, 3, 7, 4, 9, 8};
const int SW[8] = {4, 5, 6, 7, 0, 1, 2, 3};

void permute(const char *input, char *output, const int *perm, int size) {
    for (int i = 0; i < size; i++)
        output[i] = input[perm[i]];
    output[size] = '\0';
}

void divide_block(const char *block) {
    strncpy(l, block, 4);
    l[4] = '\0';
    strncpy(r, block + 4, 4);
    r[4] = '\0';
}

int convert_to_decimal(const char *str) {
    if (strcmp(str, "00") == 0) return 0;
    if (strcmp(str, "01") == 0) return 1;
    if (strcmp(str, "10") == 0) return 2;
    if (strcmp(str, "11") == 0) return 3;
    return -1;
}

void convert_to_binary(int num, char *binary) {
    snprintf(binary, 3, "%02d", num);
}

void xor_strings(const char *str1, const char *str2, char *result) {
    for (int i = 0; i < strlen(str1); i++)
        result[i] = (str1[i] == str2[i]) ? '0' : '1';
    result[strlen(str1)] = '\0';
}

void setup_sboxes() {
    int s0_values[16] = {1, 0, 3, 2, 3, 2, 1, 0, 0, 2, 1, 3, 3, 1, 3, 2};
    int s1_values[16] = {0, 1, 2, 3, 2, 0, 1, 3, 3, 0, 1, 0, 2, 1, 0, 3};
    for (int i = 0, k = 0; i < 4; i++)
        for (int j = 0; j < 4; j++, k++) {
            s0_box[i][j] = s0_values[k];
            s1_box[i][j] = s1_values[k];
        }
}

int sbox_lookup(const char *input, int box) {
    char row_str[3] = {input[0], input[3], '\0'};
    char col_str[3] = {input[1], input[2], '\0'};
    int row = convert_to_decimal(row_str);
    int col = convert_to_decimal(col_str);
    return (box == 0) ? s0_box[row][col] : s1_box[row][col];
}

void feistel_function(char *block, const char *subkey) {
    char expanded[9];
    char xor_result[9];
    char sbox_output[5];
    char binary[3];
    
    permute(r, expanded, EP, 8);
    xor_strings(expanded, subkey, xor_result);
    
    int s0 = sbox_lookup(xor_result, 0);
    int s1 = sbox_lookup(xor_result + 4, 1);
    
    convert_to_binary(s0, binary);
    strcpy(sbox_output, binary);
    convert_to_binary(s1, binary);
    strcat(sbox_output, binary);
    
    permute(sbox_output, output, P4, 4);
}

void generate_keys(const char *key) {
    permute(key, key_tmp, P10, 10);
    for (int i = 0; i < 2; i++) {
        char temp = key_tmp[0];
        for (int j = 0; j < 4; j++)
            key_tmp[j] = key_tmp[j + 1];
        key_tmp[4] = temp;
        temp = key_tmp[5];
        for (int j = 5; j < 9; j++)
            key_tmp[j] = key_tmp[j + 1];
        key_tmp[9] = temp;
        if (i == 0)
            permute(key_tmp, k1, P8, 8);
        else
            permute(key_tmp, k2, P8, 8);
    }
}

void encrypt(char *input, const char *key) {
    permute(input, output, IP, 8);
    divide_block(output);
    feistel_function(output, k1);
    xor_strings(l, output, output);
    strcat(output, r);
    permute(output, output, SW, 8);
    divide_block(output);
    feistel_function(output, k2);
    xor_strings(l, output, output);
    strcat(output, r);
    permute(output, output, IPI, 8);
}

int is_binary_string(const char *str) {
    for (int i = 0; i < strlen(str); i++)
        if (str[i] != '0' && str[i] != '1')
            return 0;
    return 1;
}

int main() {
    char input[9], key[11];
    setup_sboxes();
    
    do {
        printf("\nEnter 8-bit plaintext: ");
        scanf("%s", input);
    } while (strlen(input) != 8 || !is_binary_string(input));

    do {
        printf("Enter 10-bit key: ");
        scanf("%s", key);
    } while (strlen(key) != 10 || !is_binary_string(key));

    generate_keys(key);
    encrypt(input, key);
    printf("Ciphertext: %s\n", output);

    return 0;
}
