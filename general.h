#ifndef GENERAL
#define GENERAL

typedef unsigned char  byte; // 1byte
typedef unsigned short word; // 2bytes
typedef unsigned long  dword; //4bytes

struct rec16 {
    byte hi;
    byte lo;
};

union record16 {
    rec16 r;
    word rr;
};

#endif // GENERAL

