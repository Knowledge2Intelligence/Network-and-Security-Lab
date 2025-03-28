#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h> // Required for sleep() on Linux/macOS
//#include <windows.h> // Uncomment for Windows, use Sleep(ms) instead

#define MAX_FRAMES 10

int n, r;
struct frame {
    char ack;
    int data;
} frm[MAX_FRAMES];

int sender(void);
void recvack(void);
void resend(void);
void resend1(void);
void goback(void);
void selective(void);
void delay(int seconds);

int main() {
    int c;
    do {
        printf("\n\n1. Selective Repeat ARQ\n2. Go-Back-N ARQ\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                selective();
                break;
            case 2:
                goback();
                break;
            case 3:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please select 1, 2, or 3.\n");
        }
    } while (c != 3);

    return 0;
}

// Implements Go-Back-N ARQ
void goback() {
    sender();
    recvack();
    resend1();
    printf("\nAll packets sent successfully.\n");
}

// Implements Selective Repeat ARQ
void selective() {
    sender();
    recvack();
    resend();
    printf("\nAll packets sent successfully.\n");
}

// Simulates packet transmission
int sender() {
    int i;
    printf("\nEnter the number of packets to be sent: ");
    scanf("%d", &n);

    if (n > MAX_FRAMES) {
        printf("Error: Maximum packet limit is %d.\n", MAX_FRAMES);
        return -1;
    }

    for (i = 1; i <= n; i++) {
        printf("Enter data for packet [%d]: ", i);
        scanf("%d", &frm[i].data);
        frm[i].ack = 'y'; // Initially, assume all packets are received correctly
    }
    return 0;
}

// Simulates receiving acknowledgments
void recvack() {
    int i;
    r = 1 + rand() % n; // Fix: Generate a 1-based random index

    // Simulate a lost packet by marking one as 'n' (not acknowledged)
    frm[r].ack = 'n';

    for (i = 1; i <= n; i++) {
        if (frm[i].ack == 'n') {
            printf("\nThe packet number %d was not received (Lost packet).\n", r);
        }
    }
}

// Resends the lost packet (Selective Repeat ARQ)
void resend() {
    printf("\nResending packet %d...\n", r);
    delay(2);
    frm[r].ack = 'y';
    printf("Packet %d successfully received. Data: %d\n", r, frm[r].data);
}

// Resends all packets from the lost packet onwards (Go-Back-N ARQ)
void resend1() {
    int i;
    printf("\nResending from packet %d...\n", r);
    for (i = r; i <= n; i++) {
        delay(2);
        frm[i].ack = 'y';
        printf("Packet %d successfully received. Data: %d\n", i, frm[i].data);
    }
}

void delay(int seconds) {
    sleep(seconds); // Linux/macOS delay function
}
