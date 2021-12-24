#include <stdio.h>
#include "aes128.h"

int main(void){
    //SubBytes高速化のためのsboxを作成
    unsigned char sbox[256];
    unsigned char temp;
    unsigned char res;
    unsigned char b=0;
    for(int i=0;i<256;i++){
        temp=Inverse(b);
        res=Affine(temp);
        sbox[i]=res;
        b++;
    }
    printf("unsigned char sbox[256] = {0x%x",sbox[0]);
    for(int i=1;i<=255;i++){
        printf(" ,0x%x",sbox[i]);
    }
    printf("};");
    return 0;
}