#include <utilities.h>
#include <endian.h>
#include <stdio.h>

int convert_header_to(header_t * header, endianess_t endianess)
{
    int return_value = OK;
    switch(endianess)
    {
        case NETWORK:
            header->magic_number = htobe32(header->magic_number);
            header->size = htobe64(header->size);
            break;
        case HOST:
            header->magic_number = be32toh(header->magic_number);
            header->size = be64toh(header->size);
            break;
        default:
            ERRORPRINT("Unknown ednianess %d\n", endianess);
            return_value = CONVERSION_ERROR;
            break;
    }

    return return_value;
}

int convert_uint32_array_to(uint32_t * array, size_t size, endianess_t endianess)
{
    int return_value = OK;
    switch(endianess)
    {
        case NETWORK:
            for (size_t i = 0; i < size; i++)
            {
                array[i] = htobe32(array[i]);
            }
            break;
        case HOST:
            for (size_t i = 0; i < size; i++)
            {
                array[i] = be32toh(array[i]);
            }
            break;
        default:
            ERRORPRINT("Unknown ednianess %d\n", endianess);
            return_value = CONVERSION_ERROR;
            break;
    }
}