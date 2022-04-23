#include <server_main.h>

enum {ARRAY_SZ = 25};

int main(void)
{
    uint32_t buffer[ARRAY_SZ];
    time_t t;
    srand((unsigned)time(&t));
    for(int i = 0; i < ARRAY_SZ; i++)
    {
        uint32_t random_num = rand();
        buffer[i] = random_num % 100;
    }
    
    // Setup server to listen on a given port
    tcp_server_t * server = tcp_server_setup("44567");
    size_t size = 10;
    // Header to send to the client
    header_t header = { .magic_number = 0xBEEF,
                        .size = ARRAY_SZ };
    int convert_check = convert_header_to(&header, NETWORK);

    int send_check = 0;
    if (convert_check != -1)
    {
        // Accept a connection and send data over
        int client_socket_fd = tcp_server_accept(server);
        
        if (ISVALIDSOCKET(client_socket_fd))
        {
            tcp_send_all(client_socket_fd, &header, sizeof(header));
            send_check = tcp_send_all(client_socket_fd, buffer, ARRAY_SZ * sizeof(uint32_t));
        }
    }

    if (send_check == ARRAY_SZ * sizeof(uint32_t))
    {
        printf("Sent %d unsigned 32 bit integers to client.\n", ARRAY_SZ);
    }
    else
    {
        ERRORPRINT("%d Could not send data to client.", send_check);
    }
    
    tcp_server_teardown(server);
}