#define _CRT_SECURE_NO_WARNINGS
#include "KISA_SHA256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mySHA(unsigned char* plain, unsigned char* encrypt) {
    unsigned int plain_leng = 0;
    plain_leng = strlen((char*)plain);
    memset(encrypt, 0x00, sizeof(encrypt));
    SHA256_Encrpyt(plain, plain_leng, encrypt);
}