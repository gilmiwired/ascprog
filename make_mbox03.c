#include <stdio.h>
#include "aes128.h"

int main(void){
    //MixColumns高速化のためのmbox03を作成
    unsigned char mbox03[256];
    unsigned char res;
    unsigned char b=0;
    for(int i=0;i<256;i++){
        res=Multiply(b, 0x03);
        mbox03[i]=res;
        b++;
    }
    printf("unsigned char mbox03[256] = {0x%x",mbox03[0]);
    for(int i=1;i<=255;i++){
        printf(" ,0x%x",mbox03[i]);
    }
    printf("};");
    return 0;
}