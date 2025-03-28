#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // For sleep() in UNIX/Linux, use Sleep() for Windows

#define TIMEOUT 5
#define MAX_SEQ 1
#define TOT_PACKETS 8

#define inc(k) ((k < MAX_SEQ) ? (k++) : (k = 0))

typedef struct {
    int data;
} packet;

typedef struct {
    int kind;
    int seq;
    int ack;
    packet info;
    int err;
} frame;

typedef enum { frame_arrival, err, timeout, no_event } event_type;

frame DATA;
char turn = 's';  // 'r' for receiver, 's' for sender
int DISCONNECT = 0;
int i = 1;  // Data to be sent by sender

void from_network_layer(packet *buffer);
void to_network_layer(packet *buffer);
void to_physical_layer(frame *s);
void from_physical_layer(frame *buffer);
void wait_for_event_sender(event_type *e);
void wait_for_event_receiver(event_type *e);
void sender();
void receiver();

int main() {
    srand(time(NULL));  // Seed the random number generator
    while (!DISCONNECT) {
        sender();
        sleep(1);  // Delay for readability (use Sleep(1000) for Windows)
        receiver();
    }
    return 0;
}

/* SENDER FUNCTION */
void sender() {
    static int frame_to_send = 0;
    static frame s;
    packet buffer;
    event_type event;
    static int flag = 0;

    if (flag == 0) {
        from_network_layer(&buffer);
        s.info = buffer;
        s.seq = frame_to_send;
        printf("SENDER   : Info = %d, Seq No = %d\n", s.info.data, s.seq);
        turn = 'r';
        to_physical_layer(&s);
        flag = 1;
    }

    wait_for_event_sender(&event);
    if (turn == 's') {
        if (event == frame_arrival) {
            from_network_layer(&buffer);
            inc(frame_to_send);
            s.info = buffer;
            s.seq = frame_to_send;
            printf("SENDER   : Info = %d, Seq No = %d\n", s.info.data, s.seq);
            turn = 'r';
            to_physical_layer(&s);
        }
        if (event == timeout) {
            printf("SENDER   : TIMEOUT! Resending frame\n");
            turn = 'r';
            to_physical_layer(&s);
        }
    }
}

/* RECEIVER FUNCTION */
void receiver() {
    static int frame_expected = 0;
    frame r, s;
    event_type event;

    wait_for_event_receiver(&event);
    if (turn == 'r') {
        if (event == frame_arrival) {
            from_physical_layer(&r);
            if (r.seq == frame_expected) {
                to_network_layer(&r.info);
                inc(frame_expected);
            } else {
                printf("RECEIVER : Duplicate frame received, ACK resent\n");
            }
            turn = 's';
            to_physical_layer(&s);
        }
        if (event == err) {
            printf("RECEIVER : ERROR detected, asking for retransmission\n");
            turn = 's';  // Sender should retransmit
        }
    }
}

/* NETWORK LAYER SIMULATIONS */
void from_network_layer(packet *buffer) {
    buffer->data = i;
    i++;
}

void to_network_layer(packet *buffer) {
    printf("RECEIVER : Packet %d received, ACK sent\n", buffer->data);
    if (i > TOT_PACKETS) {
        DISCONNECT = 1;
        printf("\nDISCONNECTED: Transmission complete.\n");
    }
}

/* PHYSICAL LAYER SIMULATIONS */
void to_physical_layer(frame *s) {
    s->err = rand() % 4;  // 1/4 probability of error
    DATA = *s;
}

void from_physical_layer(frame *buffer) {
    *buffer = DATA;
}

/* EVENT HANDLING FUNCTIONS */
void wait_for_event_sender(event_type *e) {
    static int timer = 0;
    if (turn == 's') {
        timer++;
        if (timer == TIMEOUT) {
            *e = timeout;
            printf("SENDER   : ACK not received => TIMEOUT\n");
            timer = 0;
            return;
        }
        *e = (DATA.err == 0) ? err : frame_arrival;
    }
}

void wait_for_event_receiver(event_type *e) {
    if (turn == 'r') {
        *e = (DATA.err == 0) ? err : frame_arrival;
    }
}
