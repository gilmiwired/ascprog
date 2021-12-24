#include "aes128.h"
#include <stdio.h>
#include <math.h>

unsigned char Multiply(unsigned char x, unsigned char y)
{
    unsigned char z = 0;
    while (y!=0){
        if(y%2==1){     //bit0が1
            z = z^x;
        }
        y = y>>1;
        if(x>=128){     //bit7が1
            x = x<<1;
            x = x^0x1b;
        }
        else {
            x = x<<1;
        }
    }
    return z;
}

unsigned char Inverse(unsigned char b)
{
    if(b==0){
        return b;
    }
    unsigned char b2,b4,b8,b16,b32,b64,b128,b254,temp;
    b2 = Multiply(b,b);
    b4 = Multiply(b2,b2);
    b8 = Multiply(b4,b4);
    b16 = Multiply(b8,b8);
    b32 = Multiply(b16,b16);
    b64 = Multiply(b32,b32);
    b128 = Multiply(b64,b64);
    temp = Multiply(b128,b64);
    temp = Multiply(temp,b32);
    temp = Multiply(temp,b16);
    temp = Multiply(temp,b8);
    temp = Multiply(temp,b4);
    b254 = Multiply(temp,b2);
    return b254;
}

unsigned char Affine(unsigned char b)
{
    double po=0.0;
    unsigned char bbb[8];   //b´の格納先
    unsigned char ccc[8];   //二進数に変換した引数bの格納先
    unsigned char result=0;

    unsigned char temp = b;
    for(int i=0;i<8;i++){   //引数のbを二進数に変換し、配列に格納
        ccc[i] = temp%2;
        temp = temp>>1;
    }

    //行列の計算
    bbb[0] = (0x1&ccc[0]^0x0&ccc[1]^0x0&ccc[2]^0x0&ccc[3]^0x1&ccc[4]^0x1&ccc[5]^0x1&ccc[6]^0x1&ccc[7])^0x1;
    bbb[1] = (0x1&ccc[0]^0x1&ccc[1]^0x0&ccc[2]^0x0&ccc[3]^0x0&ccc[4]^0x1&ccc[5]^0x1&ccc[6]^0x1&ccc[7])^0x1;
    bbb[2] = (0x1&ccc[0]^0x1&ccc[1]^0x1&ccc[2]^0x0&ccc[3]^0x0&ccc[4]^0x0&ccc[5]^0x1&ccc[6]^0x1&ccc[7])^0x0;
    bbb[3] = (0x1&ccc[0]^0x1&ccc[1]^0x1&ccc[2]^0x1&ccc[3]^0x0&ccc[4]^0x0&ccc[5]^0x0&ccc[6]^0x1&ccc[7])^0x0;
    bbb[4] = (0x1&ccc[0]^0x1&ccc[1]^0x1&ccc[2]^0x1&ccc[3]^0x1&ccc[4]^0x0&ccc[5]^0x0&ccc[6]^0x0&ccc[7])^0x0;
    bbb[5] = (0x0&ccc[0]^0x1&ccc[1]^0x1&ccc[2]^0x1&ccc[3]^0x1&ccc[4]^0x1&ccc[5]^0x0&ccc[6]^0x0&ccc[7])^0x1;
    bbb[6] = (0x0&ccc[0]^0x0&ccc[1]^0x1&ccc[2]^0x1&ccc[3]^0x1&ccc[4]^0x1&ccc[5]^0x1&ccc[6]^0x0&ccc[7])^0x1;
    bbb[7] = (0x0&ccc[0]^0x0&ccc[1]^0x0&ccc[2]^0x1&ccc[3]^0x1&ccc[4]^0x1&ccc[5]^0x1&ccc[6]^0x1&ccc[7])^0x0;

    for(int i=0;i<8;i++){   //二進数を十進数に直す
        result += bbb[i]*pow(2.0,po);
        po++;
    }

    return result;
}


void SubBytes(unsigned char state[4*Nb])
{
    for(int i=0;i<4*Nb;i++){
        state[i] = sbox[state[i]];
    }
}



void MixColumns(unsigned char state[4*Nb])
{
    unsigned char res[4*Nb];
    unsigned char a,b,c,d;
    for(int i=0;i<=12;i+=4){
        a = state[i];
        b = state[i+1];
        c = state[i+2];
        d = state[i+3];
        res[i]   = mbox02[a]^mbox03[b]^c^d;
        res[i+1] = a^mbox02[b]^mbox03[c]^d;
        res[i+2] = a^b^mbox02[c]^mbox03[d];
        res[i+3] = mbox03[a]^b^c^mbox02[d];
    }
    for(int i=0;i<4*Nb;i++){
        state[i] = res[i];
    }
}

