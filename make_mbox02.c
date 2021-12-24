#include <stdio.h>
#include "aes128.h"

int main(void){
    //MixColumns高速化のためのmbox02を作成
    unsigned char mbox02[256];
    unsigned char res;
    unsigned char b=0;
    for(int i=0;i<256;i++){
        res=Multiply(b, 0x02);
        mbox02[i]=res;
        b++;
    }
    printf("unsigned char mbox02[256] = {0x%x",mbox02[0]);
    for(int i=1;i<=255;i++){
        printf(" ,0x%x",mbox02[i]);
    }
    printf("};");
    return 0;
}