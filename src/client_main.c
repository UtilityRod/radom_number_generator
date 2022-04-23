#include <client_main.h>

int main(void)
{
    // Setup a tcp client and pass through IP address and Port
    tcp_client_t * client = tcp_client_setup("127.0.0.1", "44567");
    // Connect to the server
    int return_value = OK;
    int socket_fd = tcp_client_connect(client);

    if (!ISVALIDSOCKET(socket_fd))
    {
        return_value = INVALID_SOCKET;
        goto teardown;
    }

    // Read the header to figure out how much to read from the message
    header_t header = {0};
    int read_check = tcp_read_all(socket_fd, &header, sizeof(header));

    if (-1 == read_check)
    {
        return_value = READ_ERROR;
        goto teardown;
    }

    int convert_check = convert_header_to(&header, HOST);
    if (-1 == convert_check)
    {
        return_value = CONVERSION_ERROR;
        goto teardown;
    }

    if (header.magic_number != 0xBEEF)
    {
        return_value = INVALID_MAGIC_NUMBER;
        goto teardown;
    }
    
    printf("Magic number is %X\n", header.magic_number);
    printf("Received %ld unisgned 32 bit integers.\n", header.size);
    uint32_t * buffer = calloc(header.size, sizeof(uint32_t));
    memset(buffer, 0, header.size);
    read_check = tcp_read_all(socket_fd, buffer, header.size * sizeof(uint32_t));
    
    if (read_check != -1)
    {
        printf("Array read: ");
        for(size_t i = 0; i < header.size; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }
    else
    {
        return_value = READ_ERROR;
    }

    free(buffer);

teardown:
    tcp_client_teardown(client);
    return return_value;
}