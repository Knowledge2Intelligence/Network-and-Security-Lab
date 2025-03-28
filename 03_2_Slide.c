#include <stdio.h>

int main() {
    int w, i, f, frames[50];

    printf("Enter window size: ");
    scanf("%d", &w);

    printf("Enter number of frames to transmit: ");
    scanf("%d", &f);

    printf("Enter %d frames: ", f);
    for (i = 0; i < f; i++)  // Fix: Start from index 0
        scanf("%d", &frames[i]);

    printf("\nWith Sliding Window Protocol, the frames will be sent in the following manner (assuming no corruption of frames):\n\n");
    printf("Sender will send %d frames at a time and wait for acknowledgment.\n\n", w);

    for (i = 0; i < f; i++) {
        printf("Sending Frame %d\n", frames[i]);

        // If window limit is reached OR it's the last frame
        if ((i + 1) % w == 0 || i == f - 1) {
            printf("Acknowledgment received for frames up to Frame %d.\n\n", frames[i]);
        }
    }

    return 0;
}
