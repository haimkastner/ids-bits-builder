namespace IDSBuilder
{
#ifndef IDS_BITS_STRUCTURES
#define IDS_BITS_STRUCTURES

/* Represent one byte, as char type or the 8 bits with binary value (0/1) */
union Byte {
    struct
    {
        unsigned bit0 : 1;
        unsigned bit1 : 1;
        unsigned bit2 : 1;
        unsigned bit3 : 1;
        unsigned bit4 : 1;
        unsigned bit5 : 1;
        unsigned bit6 : 1;
        unsigned bit7 : 1;
    } bits;

    char value;
};

/* Represent 2 bytes (2*8 bits) known as 'WORD', as 2 chars or short int*/
union WordBytes {

    struct Bytes
    {
        char byte0;
        char byte1;
    } bytes;

    short int value;
};

/* Represent 4 bytes (4*8 bits) known as 'DWORD', as 4 chars or int or float */
union DwordBytes {

    struct Bytes
    {
        char byte0;
        char byte1;
        char byte2;
        char byte3;
    } bytes;

    int value;
    float floatValue;
};

/* Represent 8 bytes (8*8 bits) known as 'QWORD', as 8 chars or lon long int or double float */
union QwordBytes {
    struct Bytes
    {
        char byte0;
        char byte1;
        char byte2;
        char byte3;
        char byte4;
        char byte5;
        char byte6;
        char byte7;
    } bytes;

    long long int value;
    double floatValue;
};

#endif

} // namespace IDSBuilder