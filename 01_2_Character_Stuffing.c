#include <stdio.h>
#include <stdlib.h>

void charc(void);

int main()  // Use int main() instead of void main()
{
    int choice;
    while (1)
    {
        printf("\n\n1. Character stuffing");
        printf("\n2. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice > 2 || choice < 1)
        {
            printf("\nInvalid option... Please re-enter.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            charc();
            break;
        case 2:
            exit(0);
        }
    }
    return 0;
}

void charc(void)
{
    char c[50], d[100], t[50];  // Increased d[] to avoid overflow
    int i, m, j;

    printf("\nEnter the number of characters: ");
    scanf("%d", &m);
    getchar();  // To consume the leftover newline character

    printf("\nEnter the characters: ");
    for (i = 0; i < m; i++)
    {
        scanf("%c", &c[i]);
    }
    c[m] = '\0';  // Null terminate

    printf("\nOriginal data: ");
    for (i = 0; i < m; i++)
    {
        printf("%c", c[i]);
    }

    // Adding start sequence DLE STX
    d[0] = 'd';
    d[1] = 'l';
    d[2] = 'e';
    d[3] = 's';
    d[4] = 't';
    d[5] = 'x';

    for (i = 0, j = 6; i < m; i++, j++)
    {
        if (c[i] == 'd' && c[i + 1] == 'l' && c[i + 2] == 'e')
        {
            d[j++] = 'd';
            d[j++] = 'l';
            d[j++] = 'e';
            m += 3;
        }
        d[j] = c[i];
    }

    // Adding end sequence DLE STX
    d[j++] = 'd';
    d[j++] = 'l';
    d[j++] = 'e';
    d[j++] = 's';
    d[j++] = 't';
    d[j++] = 'x';
    d[j] = '\0'; // Null terminate

    printf("\n\nTransmitted data: ");
    for (i = 0; i < j; i++)
    {
        printf("%c", d[i]);
    }

    // De-stuffing process
    int k = 0;
    for (i = 6; i < j - 6; i++)
    {
        if (d[i] == 'd' && d[i + 1] == 'l' && d[i + 2] == 'e' &&
            d[i + 3] == 'd' && d[i + 4] == 'l' && d[i + 5] == 'e')
        {
            i += 3;  // Skip stuffed DLE
        }
        t[k++] = d[i];
    }
    t[k] = '\0';  // Null terminate

    printf("\n\nReceived data: ");
    for (i = 0; i < k; i++)
    {
        printf("%c", t[i]);
    }
    printf("\n");
}
