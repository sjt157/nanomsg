#include <stdio.h>
#include <stdlib.h>

#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

int main(int argc, char **argv)
{
    if(argc != 3) {
        fprintf(stderr, "usage: %s NAME BIND_URLn", argv[0]);
        exit(-1);
    }
    const char *name = argv[1];
    const char *url = argv[2];

    int sock = nn_socket (AF_SP, NN_SUB);
    if(sock < 0) {
        fprintf(stderr, "fail to create socket: %sn", nn_strerror(errno));
        exit(-1);
    }
    if(nn_setsockopt (sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) {
        fprintf(stderr, "fail to set sorket opts: %sn", nn_strerror(errno));
        exit(-1);
    }

    if (nn_connect(sock, url) < 0) {
        fprintf(stderr, "fail to connect to %s : %sn", url, nn_strerror(errno));
        exit(-1);
    }


    while ( 1 ) {
        char *buf = NULL;
        int bytes = nn_recv (sock, &buf, NN_MSG, 0);
        printf ("CLIENT (%s): RECEIVED %sn", name, buf);
        nn_freemsg (buf);
    }

    nn_shutdown(sock, 0);

    return 0;
}
