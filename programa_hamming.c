#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
const unsigned char G_8[8]={0x0D,0x0B,0x08,0x07,0x04,0x02,0x01,0x00};///Matriz generadora



const unsigned char H_8[3]={0xAA,0x66,0x1E}; ///Matriz de paridad
unsigned char H_32[5][4];
unsigned int H_1024[10][32];
unsigned int H_32768[15][1024];

unsigned char G_32[5][4];
unsigned int G_1024[10][32];
unsigned int G_32768[15][1024];

unsigned long tamLVD;

typedef struct retorno{
    bool error;
    unsigned long posicion;
}Retorno_S;

typedef struct nodo{
    struct nodo *ps;
    unsigned char letra;
    bool error;
} Nodo;
typedef struct lista1{
    Nodo *inicial;
    Nodo *ultimo;
} LVD;


typedef struct nodo2{
    struct nodo2 *ps;
    unsigned int letra;
} Nodo32;

typedef struct lista2{
    Nodo32 *inicial;
    Nodo32 *ultimo;
} LVD32;

void inicialiarLVD(LVD *l){
    l->inicial=NULL;
}

void inicialiarLVD32(LVD32 *l){
    l->inicial=NULL;
}

bool altaLVD(unsigned char x,LVD *lista){
    bool exito;
    Nodo *nuevo=(Nodo*)malloc(sizeof(Nodo));
    if(nuevo != NULL){
    exito=true;
    nuevo->letra=x;
    nuevo->ps=NULL;
    if(lista->inicial==NULL){
        lista->inicial=nuevo;
        lista->ultimo=nuevo;
    }else{
        lista->ultimo->ps=nuevo;
        lista->ultimo=nuevo;
    }
    }else{
        exito=false;
    }
    return exito;
}

bool altaLVD32(unsigned int x,LVD32 *lista){
    bool exito;
    Nodo32 *nuevo=(Nodo32*)malloc(sizeof(Nodo32));
    if(nuevo != NULL){
    exito=true;
    nuevo->letra=x;
    nuevo->ps=NULL;
    if(lista->inicial==NULL){
        lista->inicial=nuevo;
        lista->ultimo=nuevo;
    }else{
        lista->ultimo->ps=nuevo;
        lista->ultimo=nuevo;
    }
    }else{
        exito=false;
    }
    return exito;
}


void mostrarLVD(LVD *lista){
    Nodo *cursor=lista->inicial;
    while(cursor!=NULL){
    printf("%c",cursor->letra);
    //printf(", en binario: ");print_binary(cursor->letra);printf("\n");
    cursor=cursor->ps;
}
}
void vaciarLVD(LVD *lista){
    while(lista->inicial!=NULL){
        Nodo *eliminado=lista->inicial;
        lista->inicial=lista->inicial->ps;
        free(eliminado);
    }
}

void vaciarLVD32(LVD32 *lista){
    while(lista->inicial!=NULL){
        Nodo32 *eliminado=lista->inicial;
        lista->inicial=lista->inicial->ps;
        free(eliminado);
    }
}

///getBits: obtiene n bits desde la posicion p, el p se elige como si las posiciones fueran de 7 a 0
unsigned char getBits(unsigned char x, int p, int n){
    return (x>>(p+1-n))& ~(~0<<n);
}
///getBits: obtiene n bits desde la posicion p, el p se elige como si las posiciones fueran de 31 a 0
unsigned int getBits_Int(unsigned int x, int p, int n){
    return (x>>(p+1-n))& ~(~0<<n);
}


///setBits: coloca los últimos n bits de y a la izquierda de x desde la posicion p
unsigned char  setBits(unsigned char x, unsigned char y, int n, int p){
return (x & ((~0 << (p+1)) | (~(~0 << (p+1 - n))))) | ((y & ~(~0 << n)) << (p+1 - n));
}

///setBits: coloca los últimos n bits de y a la izquierda de x desde la posicion p
unsigned int  setBits_Int(unsigned int x, unsigned char y, int n, int p){
return (x & ((~0 << (p+1)) | (~(~0 << (p+1 - n))))) | ((y & ~(~0 << n)) << (p+1 - n));
}


void print_binary(unsigned char c){
 unsigned char i1 = (1 << (sizeof(c)*8-1));
 for(; i1; i1 >>= 1)
      printf("%d",(c&i1)!=0);
}

void print_binary_int(unsigned int c){
 unsigned int i1 = (1 << (sizeof(c)*8-1));
 for(; i1; i1 >>= 1)
      printf("%d",(c&i1)!=0);
}

bool obtener_booleano(int i, long j){

if (i==0){///CONTROL 1
    if ((j%2)==1)
        return true;
    else
        return false;
}

else if (i==1){///CONTROL 2
    if ((j%4)==1 || (j%4)==2 )
        return true;
    else
        return false;
}

else if (i==2){///CONTROL 3
    if ((j%8)>=1 && (j%8)<=4)
        return true;
    else
        return false;
}

else if (i==3){///CONTROL 4
    if ((j%16)>=1 && (j%16)<=8)
        return true;
    else
        return false;
}

else if (i==4){///CONTROL 5
    if ((j%32)>=1 && (j%32)<=16)
        return true;
    else
        return false;
}

else if (i==5){///CONTROL 6
    if ((j%64)>=1 && (j%64)<=32)
        return true;
    else
        return false;
}

else if (i==6){///CONTROL 7
    if ((j%128)>=1 && (j%128)<=64)
        return true;
    else
        return false;
}

else if (i==7){///CONTROL 8
    if ((j%256)>=1 && (j%256)<=128)
        return true;
    else
        return false;
}

else if (i==8){///CONTROL 9
    if ((j%512)>=1 && (j%512)<=256)
        return true;
    else
        return false;
}

else if (i==9){///CONTROL 10
    if ((j%1024)>=1 && (j%1024)<=512)
        return true;
    else
        return false;
}

else if (i==10){///CONTROL 11
    if ((j%2048)>=1 && (j%2048)<=1024)
        return true;
    else
        return false;
}

else if (i==11){///CONTROL 12
    if ((j%4096)>=1 && (j%4096)<=2048)
        return true;
    else
        return false;
}
else if (i==12){///CONTROL 13
    if ((j%8192)>=1 && (j%8192)<=4096)
        return true;
    else
        return false;
}
else if (i==13){///CONTROL 14
    if ((j%16384)>=1 && (j%16384)<=8192)
        return true;
    else
        return false;
}
else if (i==14){
    if ((j%32768)>=1 && (j%32768)<=16384)
        return true;
    else
        return false;
}
}

void matriz_paridad_32(){
    int i;
    for (i=0;i<4;i++){
        H_32[0][i]=0xAA;
    }
    for (i=0;i<4;i++){
        H_32[1][i]=0x66;
    }
    for (i=0;i<4;i++){
        H_32[2][i]=0x1E;
    }
    for (i=0;i<3;i++){//1 3
        H_32[3][i]=0x01;
        i++;
        H_32[3][i]=~(0x01);
    }

    i=0;
    H_32[4][i]=0x00;
    i++;
    H_32[4][i]=0x01;
    i++;
    H_32[4][i]=~(0x00);
    i++;
    H_32[4][i]=~(0x01);

    /*for (i=0;i<5;i++){
        print_binary(H_32[i][0]);printf("\n");
        print_binary(H_32[i][1]);printf("\n");
        print_binary(H_32[i][2]);printf("\n");
        print_binary(H_32[i][3]);printf("\n");
    }*/


}


void matriz_paridad_1024(){//32 de 32 bits c/10 de control
    int i,k,posMatriz,bloque;
    long j;
    int w;
    bool es;
    for (i=0;i<10;i++){//para los 10 bits de control
        bloque=0;
        posMatriz=31;
        for (j=2;j<=1025;j++){//para los 1024 bits
            es=!(obtener_booleano(i,j));
            if (es){
                H_1024[i][bloque]=setBits_Int(H_1024[i][bloque],0x01,1,posMatriz);
            }
            else {
                H_1024[i][bloque]=setBits_Int(H_1024[i][bloque],0x00,1,posMatriz);
            }
            posMatriz--;

            if (posMatriz<0){
                bloque++;
                posMatriz=31;
            }

        }
        /*for (w=0;w<32;w++){
            print_binary_int(H_1024[i][w]);printf("\n");
        }
        system("pause");*/

    }
}


void matriz_paridad_32768(){//1024 de 32 bits c/15 de control
    int posMatriz,bloque,i;
    long j;
    //int w;
    bool es;
    for (i=0;i<15;i++){//para los 15 bits de control
        bloque=0;
        posMatriz=31;
        for (j=2;j<=32769;j++){//para los 1024 bits
            es=!(obtener_booleano(i,j));
            if (es){
                H_32768[i][bloque]=setBits_Int(H_32768[i][bloque],0x01,1,posMatriz);
            }
            else {
                H_32768[i][bloque]=setBits_Int(H_32768[i][bloque],0x00,1,posMatriz);
            }
            posMatriz--;

            if (posMatriz<0){
                bloque++;
                posMatriz=31;
            }

        }
        /*for (w=0;w<1024;w++){
            print_binary_int(H_32768[i][w]);printf("\n");
        }
        system("pause");*/

    }
}





void inicializar_matriz_32(){
int i,posMatriz;
long posGral;
int k;//para señalar bloque de Matriz
unsigned char cero=0x00;
unsigned char uno=~0x00;
bool es=false;
int w,control;
unsigned long temp=tamLVD;
//printf("temp: %i\n",temp);

for(i=0;i<5;i++){
    for (w=0;w<4;w++){//inicializo matriz en cero
        G_32[i][w]=0x00;
    }
    if (i==0){
        k=0;
        posMatriz=7;
    }
    else if(i==1){
        k=0;
        posMatriz=7;
    }
    else if(i==2){
        k=0;
        posMatriz=6;
    }
    else if(i==3){
        k=0;
        posMatriz=3;
    }
    else if(i==4){
        k=1;
        posMatriz=4;
    }
    posGral=1;
    control=pow(2,i);
    while(control<=31){
            es=obtener_booleano(i,posGral);
            if (control==1 || control==2 || control==4 || control==8 || control==16){
                posGral++;
            }
            else {
                    if (es){
                        G_32[i][k]=setBits(G_32[i][k],uno,1,posMatriz);
                        posMatriz--;
                        posGral++;
                    }
                    else {
                        G_32[i][k]=setBits(G_32[i][k],cero,1,posMatriz);
                        posMatriz--;
                        posGral++;

                    }

            }
            control++;
            if (posMatriz<0){
                k++;
                posMatriz=7;
            }
    }
/*printf("Matriz G_32 control %i\n",i+1);
print_binary(G_32[i][0]); printf(" ");print_binary(G_32[i][1]); printf("\n");
print_binary(G_32[i][2]); printf(" ");print_binary(G_32[i][3]); printf("\n\n");*/
}

tamLVD=temp;
}

void inicializar_matriz_1024(){
int i,posMatriz;
long posGral;
int k;//para señalar bloque de Matriz
unsigned char cero=0x00;
unsigned char uno=~0x00;
bool es=false;
int w,control;
unsigned long temp=tamLVD;
//printf("temp: %i\n",temp);

for(i=0;i<10;i++){
    for (w=0;w<32;w++){//inicializo matriz en cero
        G_1024[i][w]=0;
    }
    if (i==0){k=0;posMatriz=31;}
    else if (i==1){k=0;posMatriz=31;}
    else if (i==2){k=0;posMatriz=30;}
    else if (i==3){k=0;posMatriz=27;}
    else if (i==4){k=0;posMatriz=20;}
    else if (i==5){k=0;posMatriz=5;}
    else if (i==6){k=1;posMatriz=6;}
    else if (i==7){k=3;posMatriz=7;}
    else if (i==8){k=7;posMatriz=8;}
    else if (i==9){k=15;posMatriz=9;}
    posGral=1;
    control=pow(2,i);
    while(control<=1023){
            es=obtener_booleano(i,posGral);
            if (control==1 || control==2 || control==4 || control==8 || control==16 || control==32 || control==64 || control==128 || control==256 || control==512){
                posGral++;
            }
            else {
                    if (es){
                        G_1024[i][k]=setBits_Int(G_1024[i][k],uno,1,posMatriz);
                        posMatriz--;
                        posGral++;
                    }
                    else {
                        G_1024[i][k]=setBits_Int(G_1024[i][k],cero,1,posMatriz);
                        posMatriz--;
                        posGral++;

                    }

            }
            control++;
            if (posMatriz<0){
                k++;
                posMatriz=31;
            }
    }
/*printf("Matriz G_1024 control %i\n",i+1);
for (w=0;w<32;w++){
 print_binary_int(G_1024[i][w]);printf("\n");
}
printf("\n");*/
}

tamLVD=temp;
}


void inicializar_matriz_32768(){
int i,posMatriz;
long posGral;
int k;//para señalar bloque de Matriz
unsigned char cero=0x00;
unsigned char uno=~0x00;
bool es=false;
int w;
long control;
unsigned long temp=tamLVD;
//printf("temp: %i\n",temp);

for(i=0;i<15;i++){
    for (w=0;w<1024;w++){//inicializo matriz en cero
        G_32768[i][w]=0;
    }
    if (i==0){k=0;posMatriz=31;}
    else if (i==1){k=0;posMatriz=31;}
    else if (i==2){k=0;posMatriz=30;}
    else if (i==3){k=0;posMatriz=27;}
    else if (i==4){k=0;posMatriz=20;}
    else if (i==5){k=0;posMatriz=5;}
    else if (i==6){k=1;posMatriz=6;}
    else if (i==7){k=3;posMatriz=7;}
    else if (i==8){k=7;posMatriz=8;}
    else if (i==9){k=15;posMatriz=9;}
    else if (i==10){k=31;posMatriz=10;}
    else if (i==11){k=63;posMatriz=11;}
    else if (i==12){k=127;posMatriz=12;}
    else if (i==13){k=255;posMatriz=13;}
    else if (i==14){k=511;posMatriz=14;}
    posGral=1;
    control=pow(2,i);
    while(control<=32767){
            es=obtener_booleano(i,posGral);
            if (control==1 || control==2 || control==4 || control==8 || control==16 || control==32 || control==64 || control==128 || control==256 || control==512 || control==1024 || control==2048 || control==4096 || control==8192 || control==16384){
                posGral++;
            }
            else {
                    if (es){
                        G_32768[i][k]=setBits_Int(G_32768[i][k],uno,1,posMatriz);
                        posMatriz--;
                        posGral++;
                    }
                    else {
                        G_32768[i][k]=setBits_Int(G_32768[i][k],cero,1,posMatriz);
                        posMatriz--;
                        posGral++;

                    }

            }
            control++;
            if (posMatriz<0){
                k++;
                posMatriz=31;
            }
    }
printf("Matriz G_32768 control %i\n",i+1);
for (w=0;w<1024;w++){
 print_binary_int(G_32768[i][w]);printf("\n");
}
system("pause");
printf("\n");
}

tamLVD=temp;
}

/*if (i==0)      {k=0;posMatriz=31;}
    else if (i==1){k=0;posMatriz=31;}
    else if (i==2){k=0;posMatriz=30;}
    else if (i==3){k=0;posMatriz=27;}
    else if (i==4){k=0;posMatriz=20;}
    else if (i==5){k=0;posMatriz=5;}
    else if (i==6){k=1;posMatriz=6;}
    else if (i==7){k=3;posMatriz=7;}
    else if (i==8){k=7;posMatriz=8;}
    else if (i==9){k=15;posMatriz=9;}
    else if (i==10){k=31;posMatriz=10;}
    else if (i==11){k=63;posMatriz=11;}
    else if (i==12){k=127;posMatriz=12;}
    else if (i==13){k=255;posMatriz=13;}
    else if (i==14){k=511;posMatriz=14;}*/

bool generar_Hamming_32768(LVD *texto_original, LVD32 *hamming){
unsigned int bits_informacion[1024];
unsigned int resultado[1024];
unsigned int xor_res;
int i,j,k,l,bits_sobrantes,ultima_pos=7;//ultima_pos me sirve para luego agregar ceros en caso 9
long bits_disponibles;
int pos;
unsigned int and[1024],xor[1024];//and donde guardo los and temporales, xor donde voy a ir colocando el resultado
Nodo *cursor=texto_original->inicial;
int pos32b_info,pos32b_res,nro_info;
long procesados,posGral;
tamLVD--;
int caso=1;
bits_disponibles=tamLVD*8;
for (i=0;i<1024;i++){
    resultado[i]=0;
    and[i]=0;
    xor[i]=0;

}

inicializar_matriz_32768();
while(bits_disponibles!=0){
    for (i=0;i<1024;i++)
        bits_informacion[i]=0;

    if (bits_disponibles<32753){//relleno con ceros
        bits_sobrantes=bits_disponibles;
        caso=9;
        bits_disponibles=32753;

    }
    else{

        switch(caso){
            case 1:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,23);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,15);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,7);
                    cursor=cursor->ps;
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,23);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,1),1,15);

                ultima_pos=6;
                caso++;

            }break;

            case 2:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,6,7),7,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,24);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,16);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,8);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,1),1,0);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,6,7),7,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,24);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,2),2,16);

                ultima_pos=5;
                caso++;

            }break;

            case 3:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,5,6),6,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,25);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,17);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,9);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,2),2,1);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,5,6),6,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,25);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,3),3,17);

                ultima_pos=4;
                caso++;
            }break;

            case 4:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,4,5),5,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,26);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,18);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,10);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,3),3,2);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,4,5),5,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,26);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,4),4,18);

                ultima_pos=3;
                caso++;
            }break;

            case 5:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,3,4),4,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,27);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,19);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,11);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,4),4,3);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,3,4),4,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,27);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,5),5,19);

                ultima_pos=2;
                caso++;

            }break;

            case 6:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,2,3),3,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,28);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,20);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,12);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,5),5,4);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,2,3),3,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,28);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,6),6,20);

                ultima_pos=1;
                caso++;
            }break;

            case 7:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,1,2),2,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,29);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,21);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,13);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,6),6,5);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,1,2),2,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,29);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,7),7,21);

                ultima_pos=0;
                caso++;
            }break;

            case 8:{
                for (i=0;i<1023;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,0,1),1,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,30);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,22);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,14);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,7),7,6);
                }
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,0,1),1,31);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,30);
                cursor=cursor->ps;
                bits_informacion[1023]=setBits_Int(bits_informacion[1023],getBits(cursor->letra,7,8),8,22);

                cursor=cursor->ps;

                ultima_pos=7;
                caso=1;
            }break;

            case 9: {//cantidad insuficiente de bits p/armar bloque
                int pos=31,restantes;

                ///primero, cargo las primeras posiciones, controlando el caso de que hayan sobrado letras completas o parciales
                bits_informacion[0]=setBits_Int(bits_informacion[0],getBits(cursor->letra,ultima_pos,ultima_pos+1),ultima_pos+1,pos);

                pos=pos-(ultima_pos+1);///actualizo pos restando las que agregué en el paso anterior
                i=0;///aclaro que estoy llenando el cero
                cursor=cursor->ps;
                restantes=8;///inicializo restantes para que tome la letra completa

                while (cursor!=NULL){
                    if (pos<0){///esto llega a ser menor a cero cuando el bit de información se me llenó
                        i++;
                        pos=31;
                    }
                    else {
                        if (pos<8){///si tengo menos de 8 posiciones disponibles en bit_info
                            bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,pos+1),pos+1,pos);///saco cantidad de letras para completarlo
                            restantes=8-(pos+1);///cargo restantes con los bits restantes de la letra que me quedaron
                            pos=pos-8;///fuerzo a pasar a llenar el otro bit
                        }
                        else {
                            if (restantes<8){///si me sobraron bits de una letra en las iteraciones anteriores
                                bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,restantes-1,restantes),restantes,pos); ///cargo esos bits que me quedaban
                                pos=pos-restantes;///actualizo pos
                                restantes=8;///ya habiendo cargado las que me quedaban, tengo letras completas
                                cursor=cursor->ps;
                            }
                            else {///caso donde saco letras en limpio
                                bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,pos);
                                pos=pos-8;
                                cursor=cursor->ps;
                            }
                        }
                    }//cierre else pos<0
                }//cierre while cursor!=NULL
            }//cierre case 9
            break;

        }//cierre switch

///INICIA PROCESO DE HAMMING
///coloco los bits de información en resultado para ir armando el bloque de 32768 bits

pos32b_info=31;posGral=1;pos32b_res=31;i=0;nro_info=0;procesados=0;

while(nro_info<1024 && procesados<=32767){

    if (posGral==1 || posGral==2 || posGral==4 || posGral==8 || posGral==16 || posGral==32 || posGral==64 || posGral==128 || posGral==256 || posGral==512 || posGral==1024 || posGral==2048 || posGral==4096 || posGral==8192 || posGral==16384){
        posGral++;
        pos32b_res--;
    }
    else {

        resultado[i]=setBits_Int(resultado[i],getBits_Int(bits_informacion[nro_info],pos32b_info,1),1,pos32b_res);
        pos32b_res--;pos32b_info--;
        posGral++;procesados++;
    }
    if (pos32b_info<0){
            nro_info++;
            pos32b_info=31;
        }


    if (pos32b_res<0){
            i++;
            pos32b_res=31;
        }

}
/* IMPRESIONES POR PANTALLA DE AYUDA
        printf("Res: \n");
        print_binary_int(resultado[0]);printf(" ");print_binary_int(resultado[1]);printf("\n");
        print_binary_int(resultado[2]);printf(" ");print_binary_int(resultado[3]);printf("\n");
        print_binary_int(resultado[4]);printf(" ");print_binary_int(resultado[5]);printf("\n");
        print_binary_int(resultado[6]);printf(" ");print_binary_int(resultado[7]);printf("\n");
        print_binary_int(resultado[8]);printf(" ");print_binary_int(resultado[9]);printf("\n");
        print_binary_int(resultado[10]);printf(" ");print_binary_int(resultado[11]);printf("\n");
        print_binary_int(resultado[12]);printf(" ");print_binary_int(resultado[13]);printf("\n");
        print_binary_int(resultado[14]);printf(" ");print_binary_int(resultado[15]);printf("\n");
        print_binary_int(resultado[16]);printf(" ");print_binary_int(resultado[17]);printf("\n");
        print_binary_int(resultado[18]);printf(" ");print_binary_int(resultado[19]);printf("\n");
        print_binary_int(resultado[20]);printf(" ");print_binary_int(resultado[21]);printf("\n");
        print_binary_int(resultado[22]);printf(" ");print_binary_int(resultado[23]);printf("\n");
        print_binary_int(resultado[24]);printf(" ");print_binary_int(resultado[25]);printf("\n");
        print_binary_int(resultado[26]);printf(" ");print_binary_int(resultado[27]);printf("\n");
        print_binary_int(resultado[28]);printf(" ");print_binary_int(resultado[29]);printf("\n");
        print_binary_int(resultado[30]);printf(" ");print_binary_int(resultado[31]);printf("\n");
        system("pause");
*/

    for (j=0;j<15;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<1024;k++){
                and[k]=G_32768[j][k] & bits_informacion[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<32; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits_Int(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits_Int(xor[k-1],0,1) ^ getBits_Int(xor[k],0,1);
                }
            }
            ///ya con xor_res cargado con el resultado del bit de control correspondiente, lo cargo donde corresponda
            //printf("xor bit control %i: ",j+1); print_binary_int(xor_res);printf("\n");system("pause");

            if (j==0){///si es el primer bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,31);///coloco c1 donde corresponde

            }
            else if (j==1){///si es el segundo bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,30);///coloco c2 donde corresponde

            }
            else if (j==2){///si es el tercer bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,28);///coloco c3
            }
            else if (j==3){///si es el cuarto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,24);///coloco c4
            }
            else if (j==4){///si es el quinto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,16);///coloco c5
            }
            else if (j==5){///si es el sexto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,0);///coloco c6         --> resultado[0] lleno
            }
            else if (j==6){///si es el séptimo bit de control
                resultado[1]=setBits_Int(resultado[1],xor_res,1,1);///coloco c7

            }
            else if (j==7){///si es el octavo bit de control
                resultado[3]=setBits_Int(resultado[3],xor_res,1,0);///coloco c8

            }
            else if (j==8){///si es el noveno bit de control
                resultado[7]=setBits_Int(resultado[7],xor_res,1,0);///coloco c9

            }
            else if (j==9){///si es el décimo bit de control
                resultado[15]=setBits_Int(resultado[15],xor_res,1,0);///coloco c10

            }

            else if (j==10){///si es el bit 11 de control
                resultado[31]=setBits_Int(resultado[31],xor_res,1,0);///coloco c11

            }

            else if (j==11){///si es el bit 12 de control
                resultado[63]=setBits_Int(resultado[63],xor_res,1,0);///coloco c12

            }

            else if (j==12){///si es el 13 bit de control
                resultado[127]=setBits_Int(resultado[127],xor_res,1,0);///coloco c13

            }

            else if (j==13){///si es el 14 bit de control
                resultado[255]=setBits_Int(resultado[255],xor_res,1,0);///coloco c14 8192

            }

            else if (j==14){///si es el 15 bit de control
                resultado[511]=setBits_Int(resultado[511],xor_res,1,0);///coloco c15 16384

            }

}


        ///doy de alta en LVD el bloque de 32768 bits (1024 de 32 bits)
        for (i=0;i<1024;i++){
            altaLVD32(resultado[i],hamming);
            resultado[i]=0;
        }

        bits_disponibles=bits_disponibles-32753;


    }//cierre else

}//cierre while

}//cierre función


bool generar_Hamming_1024(LVD *texto_original, LVD32 *hamming){
unsigned int bits_informacion[32];
unsigned int resultado[32];
unsigned int xor_res;
int i,j,k,l,bits_sobrantes,ultima_pos=7;//ultima_pos me sirve para luego agregar ceros en caso 9
int pos;
unsigned int bits_disponibles;
unsigned int and[32],xor[32];//and donde guardo los and temporales, xor donde voy a ir colocando el resultado
Nodo *cursor=texto_original->inicial;
int pos32b_info,posGral,pos32b_res,nro_info,procesados;
tamLVD--;
int caso=1;
bits_disponibles=tamLVD*8;
for (i=0;i<32;i++){
    resultado[i]=0;
    and[i]=0;
    xor[i]=0;

}
inicializar_matriz_1024();

while(bits_disponibles!=0){
    for (i=0;i<32;i++)
        bits_informacion[i]=0;

    if (bits_disponibles<1013){//relleno con ceros
    ///casos posibles: sobran 1,2,3,4,5,6,7,8,9,10.....1010,1011,1012
        bits_sobrantes=bits_disponibles;
        caso=9;
        bits_disponibles=1013;

    }
    else{

        switch(caso){

            case 1: {

                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,23);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,15);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,7);
                    cursor=cursor->ps;

                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],cursor->letra,8,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],cursor->letra,8,23); //126 letras
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,5),5,15);

                //printf("caso 1 ejecutado ocn exito\n");system("pause");
                ultima_pos=2;
                caso++;

            }break;

            case 2: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,2,3),3,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,28);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,20);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,12);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,5),5,4);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,2,3),3,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,28);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,20);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,2),2,12);

                //printf("caso 2 ejecutado ocn exito\n");system("pause");
                ultima_pos=5;
                caso++;

            }break;

            case 3: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,5,6),6,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,25);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,17);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,9);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,2),2,1);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,5,6),6,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,25);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,7),7,17);

                //printf("caso 3 ejecutado ocn exito\n");system("pause");
                ultima_pos=0;
                caso++;

            }break;

            case 4: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,0,1),1,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,30);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,22);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,14);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,7),7,6);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,0,1),1,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,30);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,22);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,4),4,14);

                //printf("caso 4 ejecutado ocn exito\n");system("pause");
                ultima_pos=3;
                caso++;

            }break;

            case 5: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,3,4),4,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,27);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,19);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,11);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,4),4,3);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,3,4),4,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,27);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,19);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,1),1,11);

                //printf("caso 5 ejecutado ocn exito\n");system("pause");
                ultima_pos=6;
                caso++;

            }break;

            case 6: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,6,7),7,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,24);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,16);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,8);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,1),1,0);
                }

                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,6,7),7,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,24);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,6),6,16);

                //printf("caso 6 ejecutado ocn exito\n");system("pause");
                ultima_pos=1;
                caso++;

            }break;

            case 7: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,1,2),2,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,29);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,21);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,13);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,6),6,5);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,1,2),2,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,29);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,21);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,3),3,13);

                //printf("caso 7 ejecutado ocn exito\n");system("pause");
                ultima_pos=4;
                caso++;

            }break;

            case 8: {
                for (i=0;i<31;i++){
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,4,5),5,31);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,26);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,18);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,8),8,10);
                    cursor=cursor->ps;
                    bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,3),3,2);
                }
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,4,5),5,31);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,26);
                cursor=cursor->ps;
                bits_informacion[31]=setBits_Int(bits_informacion[31],getBits(cursor->letra,7,8),8,18);
                cursor=cursor->ps;

                //printf("caso 8 ejecutado ocn exito\n");system("pause");
                ultima_pos=7;
                caso=1;

            }break;


           case 9: {//cantidad insuficiente de bits p/armar bloque
                int pos=31,restantes;

                ///primero, cargo las primeras posiciones, controlando el caso de que hayan sobrado letras completas o parciales
                bits_informacion[0]=setBits_Int(bits_informacion[0],getBits(cursor->letra,ultima_pos,ultima_pos+1),ultima_pos+1,pos);

                pos=pos-(ultima_pos+1);///actualizo pos restando las que agregué en el paso anterior
                i=0;///aclaro que estoy llenando el cero
                cursor=cursor->ps;
                restantes=8;///inicializo restantes para que tome la letra completa

                while (cursor!=NULL){
                    if (pos<0){///esto llega a ser menor a cero cuando el bit de información se me llenó
                        i++;
                        pos=31;
                    }
                    else {
                        if (pos<8){///si tengo menos de 8 posiciones disponibles en bit_info
                            bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,7,pos+1),pos+1,pos);///saco cantidad de letras para completarlo
                            restantes=8-(pos+1);///cargo restantes con los bits restantes de la letra que me quedaron
                            pos=pos-8;///fuerzo a pasar a llenar el otro bit
                        }
                        else {
                            if (restantes<8){///si me sobraron bits de una letra en las iteraciones anteriores
                                bits_informacion[i]=setBits_Int(bits_informacion[i],getBits(cursor->letra,restantes-1,restantes),restantes,pos); ///cargo esos bits que me quedaban
                                pos=pos-restantes;///actualizo pos
                                restantes=8;///ya habiendo cargado las que me quedaban, tengo letras completas
                                cursor=cursor->ps;
                            }
                            else {///caso donde saco letras en limpio
                                bits_informacion[i]=setBits_Int(bits_informacion[i],cursor->letra,8,pos);
                                pos=pos-8;
                                cursor=cursor->ps;
                            }
                        }
                    }//cierre else pos<0
                }//cierre while cursor!=NULL
            }//cierre case 9
            break;

        }//cierre switch


/*printf("Bits info:\n");
        print_binary_int(bits_informacion[0]);printf(" ");print_binary_int(bits_informacion[1]);printf("\n");
        print_binary_int(bits_informacion[2]);printf(" ");print_binary_int(bits_informacion[3]);printf("\n");
        print_binary_int(bits_informacion[4]);printf(" ");print_binary_int(bits_informacion[5]);printf("\n");
        print_binary_int(bits_informacion[6]);printf(" ");print_binary_int(bits_informacion[7]);printf("\n");
        print_binary_int(bits_informacion[8]);printf(" ");print_binary_int(bits_informacion[9]);printf("\n");
        print_binary_int(bits_informacion[10]);printf(" ");print_binary_int(bits_informacion[11]);printf("\n");
        print_binary_int(bits_informacion[12]);printf(" ");print_binary_int(bits_informacion[13]);printf("\n");
        print_binary_int(bits_informacion[14]);printf(" ");print_binary_int(bits_informacion[15]);printf("\n");
        print_binary_int(bits_informacion[16]);printf(" ");print_binary_int(bits_informacion[17]);printf("\n");
        print_binary_int(bits_informacion[18]);printf(" ");print_binary_int(bits_informacion[19]);printf("\n");
        print_binary_int(bits_informacion[20]);printf(" ");print_binary_int(bits_informacion[21]);printf("\n");
        print_binary_int(bits_informacion[22]);printf(" ");print_binary_int(bits_informacion[23]);printf("\n");
        print_binary_int(bits_informacion[24]);printf(" ");print_binary_int(bits_informacion[25]);printf("\n");
        print_binary_int(bits_informacion[26]);printf(" ");print_binary_int(bits_informacion[27]);printf("\n");
        print_binary_int(bits_informacion[28]);printf(" ");print_binary_int(bits_informacion[29]);printf("\n");
        print_binary_int(bits_informacion[30]);printf(" ");print_binary_int(bits_informacion[31]);printf("\n");

        printf("................................\n");

*/
///INICIA PROCESO DE HAMMING
///coloco los bits de información en resultado para ir armando el bloque de 32 bits
//int pos32b_info,posGral,pos32b_res,nro_info;
pos32b_info=31;posGral=1;pos32b_res=31;i=0;nro_info=0;procesados=0;

while(nro_info<32 && procesados<=1013){
    if (posGral==1 || posGral==2 || posGral==4 || posGral==8 || posGral==16 || posGral==32 || posGral==64 || posGral==128 || posGral==256 || posGral==512){
        posGral++;
        pos32b_res--;
    }
    else {
        if (pos32b_res<0){
            i++;
            pos32b_res=31;
        }

        resultado[i]=setBits_Int(resultado[i],getBits_Int(bits_informacion[nro_info],pos32b_info,1),1,pos32b_res);
        pos32b_res--;pos32b_info--;
        posGral++;procesados++;

        if (pos32b_info<0){
            nro_info++;
            pos32b_info=31;
        }

    }
}
/*
        printf("Res: \n");
        print_binary_int(resultado[0]);printf(" ");print_binary_int(resultado[1]);printf("\n");
        print_binary_int(resultado[2]);printf(" ");print_binary_int(resultado[3]);printf("\n");
        print_binary_int(resultado[4]);printf(" ");print_binary_int(resultado[5]);printf("\n");
        print_binary_int(resultado[6]);printf(" ");print_binary_int(resultado[7]);printf("\n");
        print_binary_int(resultado[8]);printf(" ");print_binary_int(resultado[9]);printf("\n");
        print_binary_int(resultado[10]);printf(" ");print_binary_int(resultado[11]);printf("\n");
        print_binary_int(resultado[12]);printf(" ");print_binary_int(resultado[13]);printf("\n");
        print_binary_int(resultado[14]);printf(" ");print_binary_int(resultado[15]);printf("\n");
        print_binary_int(resultado[16]);printf(" ");print_binary_int(resultado[17]);printf("\n");
        print_binary_int(resultado[18]);printf(" ");print_binary_int(resultado[19]);printf("\n");
        print_binary_int(resultado[20]);printf(" ");print_binary_int(resultado[21]);printf("\n");
        print_binary_int(resultado[22]);printf(" ");print_binary_int(resultado[23]);printf("\n");
        print_binary_int(resultado[24]);printf(" ");print_binary_int(resultado[25]);printf("\n");
        print_binary_int(resultado[26]);printf(" ");print_binary_int(resultado[27]);printf("\n");
        print_binary_int(resultado[28]);printf(" ");print_binary_int(resultado[29]);printf("\n");
        print_binary_int(resultado[30]);printf(" ");print_binary_int(resultado[31]);printf("\n");
        system("pause");
*/

    for (j=0;j<10;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<32;k++){
                and[k]=G_1024[j][k] & bits_informacion[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<32; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits_Int(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits_Int(xor[k-1],0,1) ^ getBits_Int(xor[k],0,1);
                }
            }
            ///ya con xor_res cargado con el resultado del bit de control correspondiente, lo cargo donde corresponda
            //printf("xor bit control %i: ",j+1); print_binary_int(xor_res);printf("\n");system("pause");

            if (j==0){///si es el primer bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,31);///coloco c1 donde corresponde

            }
            else if (j==1){///si es el segundo bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,30);///coloco c2 donde corresponde

            }
            else if (j==2){///si es el tercer bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,28);///coloco c3
            }
            else if (j==3){///si es el cuarto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,24);///coloco c4
            }
            else if (j==4){///si es el quinto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,16);///coloco c5
            }
            else if (j==5){///si es el sexto bit de control
                resultado[0]=setBits_Int(resultado[0],xor_res,1,0);///coloco c6         --> resultado[0] lleno
            }
            else if (j==6){///si es el séptimo bit de control
                resultado[1]=setBits_Int(resultado[1],xor_res,1,0);///coloco c7

            }
            else if (j==7){///si es el octavo bit de control
                resultado[3]=setBits_Int(resultado[3],xor_res,1,0);///coloco c8

            }
            else if (j==8){///si es el noveno bit de control
                resultado[7]=setBits_Int(resultado[7],xor_res,1,0);///coloco c9

            }
            else if (j==9){///si es el décimo bit de control
                resultado[15]=setBits_Int(resultado[15],xor_res,1,0);///coloco c10

            }

}


        ///doy de alta en LVD el bloque de 1024 bits (32 de 32 bits)
        for (i=0;i<32;i++){
            altaLVD32(resultado[i],hamming);
            resultado[i]=0;
        }


        bits_disponibles=bits_disponibles-1013;


    }//cierre else

}//cierre while

}//cierre función

bool generar_Hamming_32(LVD *texto_original, LVD *hamming){
unsigned char bits_informacion[4];
unsigned char resultado[4]={0x00,0x00,0x00,0x00};
unsigned char xor_res;
int i,j,k,l,bits_sobrantes;
unsigned long bits_disponibles;
unsigned char and[4]={0x00,0x00,0x00,0x00},xor[4]={0x00,0x00,0x00,0x00};//and donde guardo los and temporales, xor donde voy a ir colocando el resultado
Nodo *cursor=texto_original->inicial;
tamLVD--;
//printf("tamLVD: %i\n\n",tamLVD);
int caso=1;
bits_disponibles=tamLVD*8;
inicializar_matriz_32();
while(bits_disponibles!=0){

    if (bits_disponibles<26){//relleno con ceros
    ///casos posibles: sobran 2,4,6,8,10,12,14,16,18,20,22 o 24 bits (:
        bits_sobrantes=bits_disponibles;
        caso=5;
        bits_disponibles=26;

    }
    else{
        ///cargo todo con cero para después llenar dependiendo el caso
        bits_informacion[0]=0x00;bits_informacion[1]=0x00;bits_informacion[2]=0x00;bits_informacion[3]=0x00;
        switch(caso){
        case 1:{
            for (i=0;i<3;i++){
                bits_informacion[i]=getBits(cursor->letra,7,8);
                cursor=cursor->ps;
            }
            bits_informacion[3]=setBits(bits_informacion[3],getBits(cursor->letra,7,2),2,7);/// i25 i26 0 0 0 0 0 0
            caso++;
        }
        break;

        case 2:{
            for (i=0;i<3;i++){
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,5,6),6,7);
                cursor=cursor->ps;
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,7,2),2,1);///bloque de 8 armado

            }
            bits_informacion[3]=setBits(bits_informacion[3],getBits(cursor->letra,5,2),2,7);/// i25 i26 0 0 0 0 0 0
            caso++;

        }
        break;

        case 3:{
            for (i=0;i<3;i++){
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,3,4),4,7);
                cursor=cursor->ps;
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,7,4),4,3);///bloque de 8 armado

            }
            bits_informacion[3]=setBits(bits_informacion[3],getBits(cursor->letra,3,2),2,7);/// i25 i26 0 0 0 0 0 0
            caso++;

        }
        break;

        case 4:{

            for (i=0;i<3;i++){
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,1,2),2,7);
                cursor=cursor->ps;
                bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,7,6),6,5);/// bloque de 8 armado

            }
            bits_informacion[3]=setBits(bits_informacion[3],getBits(cursor->letra,1,2),2,7);/// i25 i26 0 0 0 0 0 0
            cursor=cursor->ps;
            caso=1;
        }
        break;

        case 5: {//caso donde sobran bits y debo llenar con ceros

            if (bits_sobrantes<=8){
             bits_informacion[0]=setBits(bits_informacion[0],getBits(cursor->letra,bits_sobrantes-1,bits_sobrantes),bits_sobrantes,7);///pongo al principio los bits restantes
             bits_informacion[1]=0x00;
             bits_informacion[2]=0x00;
             bits_informacion[3]=0x00;
            }
            else {
                int cantidad;
                if (bits_sobrantes>8 && bits_sobrantes<=16){
                    cantidad=bits_sobrantes-8;
                    if (cantidad<8){///debo llenar por partes bit_info[0]
                        bits_informacion[0]=setBits(bits_informacion[0],getBits(cursor->letra,cantidad-1,cantidad),cantidad,7);
                        cursor=cursor->ps;
                        cantidad=8-cantidad;
                        bits_informacion[0]=setBits(bits_informacion[0],getBits(cursor->letra,7,cantidad),cantidad,cantidad-1);///bits_info[0] lleno
                        cantidad=8-cantidad;
                        bits_informacion[1]=setBits(bits_informacion[1],getBits(cursor->letra,cantidad-1,cantidad),cantidad,7);
                        bits_informacion[2]=0x00;
                        bits_informacion[3]=0x00;

                    }
                    else {///caso en el que sobraron 16 bits
                        for (i=0;i<2;i++){
                            bits_informacion[i]=setBits(bits_informacion[i],cursor->letra,8,7);
                            cursor=cursor->ps;
                        }
                        bits_informacion[2]=0x00;
                        bits_informacion[3]=0x00;
                    }

                }//cierre caso de 9 a 16
        //------------------------------------------------------------
                else {///sobraron entre 17 y 24 bits
                    cantidad=bits_sobrantes-16;
                    if (cantidad<8){///si debo llenar parcialmente bits_info[0]
                        for (i=0;i<3;i++){
                            bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,cantidad-1,cantidad),cantidad,7);
                            cantidad=8-cantidad;
                            cursor=cursor->ps;
                            bits_informacion[i]=setBits(bits_informacion[i],getBits(cursor->letra,7,cantidad),cantidad,cantidad-1);
                            cantidad=8-cantidad;
                        }
                        bits_informacion[3]=setBits(bits_informacion[3],getBits(cursor->letra,cantidad-1,cantidad),cantidad,7);
                    }
                    else {///sobraron 24 bits
                        for (i=0;i<3;i++){
                            bits_informacion[i]=setBits(bits_informacion[i],cursor->letra,8,7);
                            cursor=cursor->ps;

                        }
                        bits_informacion[3]=0x00;

                    }//cierre sobran 24

                }//cierre sobran entre 17 y 24
            }//cierre primer else de que no sean <8
        }//cierre case 5

    //printf("\nUltima iteracion\n");
    //print_binary(bits_informacion[0]); printf(" ");print_binary(bits_informacion[1]); printf(" ");
    //print_binary(bits_informacion[2]); printf(" ");print_binary(bits_informacion[3]); printf(" ");
    //printf("\n");
    //system("pause");

        break;

    }//cierre switch caso


///INICIA PROCESO DE HAMMING

//printf("\n\n\nTexto original\n");
//mostrarLVD(texto_original);
//printf("\n");
//system("pause");

        for (j=0;j<5;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<4;k++){
                and[k]=getBits(G_32[j][k],7,8) & bits_informacion[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<8; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits(xor[k-1],0,1) ^ getBits(xor[k],0,1);
                }
            }
            ///ya con xor_res cargado con el resultado del bit de control correspondiente, lo cargo donde corresponda
            //printf("xor: "); print_binary(xor_res);printf("\n");
            if (j==0){///si es el primer bit de control
                resultado[0]=setBits(resultado[0],xor_res,1,7);///coloco c1 donde corresponde

            }
            else if (j==1){///si es el segundo bit de control
                resultado[0]=setBits(resultado[0],xor_res,1,6);///coloco c2 donde corresponde

                ///coloco los bits de información en resultado para ir armando el bloque de 32 bits
                resultado[0]=setBits(resultado[0],getBits(bits_informacion[0],7,1),1,5);///coloco i1 en res
            }
            else if (j==2){///si es el tercer bit de control
                resultado[0]=setBits(resultado[0],xor_res,1,4);///coloco c3

                ///bits de información
                resultado[0]=setBits(resultado[0],getBits(bits_informacion[0],6,3),3,3);///coloco i2,i3,i4 en res
            }
            else if (j==3){///si es el cuarto bit de control
                resultado[0]=setBits(resultado[0],xor_res,1,0);///coloco c4

                ///bits de información
                resultado[1]=setBits(resultado[1],getBits(bits_informacion[0],3,4),4,7);///coloco i5,i6,i7,i8 en res
                resultado[1]=setBits(resultado[1],getBits(bits_informacion[1],7,3),3,3);///coloco i9,i10,i11 en res
            }
            else if (j==4){///si es el quinto bit de control
                resultado[1]=setBits(resultado[1],xor_res,1,0);///coloco c5

                ///bits de información
                resultado[2]=setBits(resultado[2],getBits(bits_informacion[1],4,5),5,7);///coloco i12,i13,i14,i15,i16 en res
                resultado[2]=setBits(resultado[2],getBits(bits_informacion[2],7,3),3,2);///coloco i17,i18,i19 en res
                resultado[3]=setBits(resultado[3],getBits(bits_informacion[2],4,5),5,7);///coloco i20,i21,i22,i23,i24 en res
                resultado[3]=setBits(resultado[3],getBits(bits_informacion[3],7,2),2,2);///coloco i25,i26 en res
                resultado[3]=setBits(resultado[3],(0x00),1,0);///coloco 0 en pos32
            }

        }
        ///doy de alta en LVD el bloque de 32 bits (4 de 8)
        //printf("Bits info: ");
        //print_binary(bits_informacion[0]);printf(" ");print_binary(bits_informacion[1]);printf(" ");print_binary(bits_informacion[2]);printf(" ");print_binary(bits_informacion[3]);printf("\n");
        //printf("Res: ");
        //print_binary(resultado[0]);printf(" ");print_binary(resultado[1]);printf(" ");print_binary(resultado[2]);printf(" ");print_binary(resultado[3]);printf("\n");
        //system("pause");
        altaLVD(resultado[0],hamming);
        altaLVD(resultado[1],hamming);
        altaLVD(resultado[2],hamming);
        altaLVD(resultado[3],hamming);

        bits_disponibles=bits_disponibles-26;
        }//cierre else

}//cierre while
return true;
}



//recibo el texto original, y la LVD hamming que inicialmente se encuentra apuntando a NULL (solo inicializada)
void generar_Hamming_8(LVD *texto_original, LVD *hamming){
    unsigned char bits_de_informacion;
    unsigned char  resultado,and,xor;
    Nodo *cursor=texto_original->inicial;//apunto el cursor al primer caracter
    unsigned long cont=0;
    int i,j,k;
    while(cursor!=NULL && cont<tamLVD-1){//mientras no llegue al final de la LVD
        for(k=0;k<2;k++){
            if(k==0){//primer iteración
                bits_de_informacion=getBits(cursor->letra,3,4); ///Saco los primeros 4 bits de la derecha [ ... 3, 2, 1, 0]
            }else{//2da iteración
                bits_de_informacion=getBits(cursor->letra,7,4); ///Saco los primeros 4 bits de la izquierda [7, 6, 5, 4 ...]
            }
            for(i=7;i>=0;i--){
                and=G_8[i] & bits_de_informacion;///calculo en AND entre los bits de información y la columna de la matriz generadora
                xor=and;///Inicializo el xor y el and
                for(j=1; j<4; j++){ ///Realizo el calculo del XOR
                    and=and >> 1;
                    xor= xor ^ and;
                }
                resultado=setBits(resultado,xor,i+1,7);///Coloco el valor en su posicion
            }
            altaLVD(resultado,hamming);

        }
        cursor=cursor->ps;
        cont++;
}//cierre while


    }



void decodificar_Hamming_8(LVD *hamming, LVD *decodificado){
    unsigned char resultado_parcial, resultado_final;
    unsigned char y,x;
    Nodo *cursor=hamming->inicial;
    while(cursor!=NULL){
    resultado_parcial=0x00;
    resultado_final=0x00;
    int k;
    for(k=0;k<2;k++){
        x=cursor->letra;
        x=x>>1;
        resultado_parcial=getBits(x,2,3);
        x=x>>4;
        y=getBits(x,0,1);
        resultado_parcial=setBits(resultado_parcial,y,5,7);
        if(k==0){
            resultado_final=setBits(resultado_final,resultado_parcial,4,3);
        }else{
            resultado_final=setBits(resultado_final,resultado_parcial,4,7);
        }
        cursor=cursor->ps;
    }
    altaLVD(resultado_final,decodificado);
    }
}



void decodificar_Hamming_32(LVD *hamming, LVD *decodificado){
    Nodo *cursor=hamming->inicial;
    unsigned char aux[4]={0x00,0x00,0x00,0x00};
    int i,caso=1,cant_dec=0;
    //printf("tamLVD: %i",tamLVD);
    while (cursor!=NULL && cant_dec<tamLVD){//get: pos, cant
        switch(caso) {
            case 1: {

                aux[0]=setBits(aux[0],getBits(cursor->letra,5,1),1,7);///saco i1
                aux[0]=setBits(aux[0],getBits(cursor->letra,3,3),3,6);///saco i2 i3 i4
                cursor=cursor->ps;
                aux[0]=setBits(aux[0],getBits(cursor->letra,7,4),4,3);///saco i5 i6 i7 i8


                aux[1]=setBits(aux[1],getBits(cursor->letra,3,3),3,7);///saco i9 i10 i11
                cursor=cursor->ps;
                aux[1]=setBits(aux[1],getBits(cursor->letra,7,5),5,4);///saco i12 i13 i14 i15 i16


                aux[2]=setBits(aux[2],getBits(cursor->letra,2,3),3,7);///saco i17 i18 i19
                cursor=cursor->ps;
                aux[2]=setBits(aux[2],getBits(cursor->letra,7,5),5,4);///saco i20 i21 i22 i23 i24

            }
            break;

            case 2: {

                aux[0]=setBits(aux[0],getBits(cursor->letra,2,2),2,7);///saco i1 i2
                cursor=cursor->ps;
                aux[0]=setBits(aux[0],getBits(cursor->letra,5,1),1,5);///saco i3
                aux[0]=setBits(aux[0],getBits(cursor->letra,3,3),3,4);///saco i4 i5 i6
                cursor=cursor->ps;
                aux[0]=setBits(aux[0],getBits(cursor->letra,7,2),2,1);///saco i7 i8


                aux[1]=setBits(aux[1],getBits(cursor->letra,5,5),5,7);///saco i9 i10 i11 i12 i13
                cursor=cursor->ps;
                aux[1]=setBits(aux[1],getBits(cursor->letra,7,3),3,2);///saco i14 i15 i16


                aux[2]=setBits(aux[2],getBits(cursor->letra,4,5),5,7);///saco i17 i18 i19 i20 i21
                cursor=cursor->ps;
                aux[2]=setBits(aux[2],getBits(cursor->letra,7,3),3,2);///saco i22 i23 i24


            }
            break;

            case 3: {

                aux[0]=setBits(aux[0],getBits(cursor->letra,4,4),4,7);///saco i1 i2 i3 i4
                cursor=cursor->ps;
                aux[0]=setBits(aux[0],getBits(cursor->letra,5,1),1,3);///saco i5
                aux[0]=setBits(aux[0],getBits(cursor->letra,3,3),3,2);///saco i6 i7 i8


                cursor=cursor->ps;
                aux[1]=setBits(aux[1],getBits(cursor->letra,7,7),7,7);///saco i9 i10 i11 i12 i13 i14 i15
                cursor=cursor->ps;
                aux[1]=setBits(aux[1],getBits(cursor->letra,7,1),1,0);///saco i16


                aux[2]=setBits(aux[2],getBits(cursor->letra,6,7),7,7);///saco i17 i18 i19 i20 i21 i22 i23
                cursor=cursor->ps;
                aux[2]=setBits(aux[2],getBits(cursor->letra,7,1),1,0);///saco i24


            }
            break;

            case 4: {

                aux[0]=setBits(aux[0],getBits(cursor->letra,6,6),6,7);///saco i1 i2 i3 i4 i5 i6
                cursor=cursor->ps;


                aux[0]=setBits(aux[0],getBits(cursor->letra,5,1),1,1);///saco i7
                aux[0]=setBits(aux[0],getBits(cursor->letra,3,1),1,0);///saco i8


                aux[1]=setBits(aux[1],getBits(cursor->letra,2,2),2,7);///saco i9 i10
                cursor=cursor->ps;
                aux[1]=setBits(aux[1],getBits(cursor->letra,7,6),6,5);///saco i11 i12 i13 i14 i15 i16

                aux[2]=setBits(aux[2],getBits(cursor->letra,1,1),1,7);///saco i17
                cursor=cursor->ps;
                aux[2]=setBits(aux[2],getBits(cursor->letra,7,7),7,6);///saco i18 i19 i20 i21 i22 i23 i24

                aux[3]=setBits(aux[3],getBits(cursor->letra,0,1),1,7);///saco i25
                cursor=cursor->ps;
                aux[3]=setBits(aux[3],getBits(cursor->letra,7,7),7,6);///saco i26 i27 i28 i29 i30 i31 i32


                cursor=cursor->ps;

            }
            break;
        }//cierre switch

        if (caso==1 || caso==2 || caso==3){
            if (cant_dec+3<=tamLVD){
                    for (i=0;i<3;i++)
                        altaLVD(aux[i],decodificado);

                cant_dec=cant_dec+3;
                }
                else{
                    for (i=0;cant_dec<tamLVD;i++){
                        altaLVD(aux[i],decodificado);
                        cant_dec++;
                    }
                }//cierre else
            caso++;
        }//cierre if

        else{
                if (cant_dec+4<=tamLVD){
                    for (i=0;i<4;i++)
                        altaLVD(aux[i],decodificado);
                    cant_dec=cant_dec+4;
                }

                else{
                    for (i=0;cant_dec<tamLVD;i++){
                        altaLVD(aux[i],decodificado);
                        cant_dec++;
                    }
                }
            caso=1;
        }//cierre else
    }//cierre while


}


void decodificar_Hamming_1024(LVD32 *hamming, LVD *decodificado){
    Nodo32 *cursor=hamming->inicial;
    unsigned char aux;
    int cant_dec=0;
    int posBGral,pos32b,posLetra,ultimaPos=-1;
    while (cant_dec<tamLVD){
            pos32b=31;posBGral=1;
            if (ultimaPos!=-1){
                while (ultimaPos!=-1){///si me quedaron bits p/letra anterior
                        if (posBGral==1 || posBGral==2 || posBGral==4 || posBGral==8 || posBGral==16 || posBGral==32 || posBGral==64 || posBGral==128 || posBGral==256 || posBGral==512){
                        posBGral++;
                        pos32b--;
                        }
                        else {
                            aux=setBits(aux,getBits_Int(cursor->letra,pos32b,1),1,ultimaPos);
                            ultimaPos--;
                            pos32b--;
                            posBGral++;
                        }
                }
                altaLVD(aux,decodificado);///doy de alta la letra que terminé de completar
                cant_dec++;
            }

            posLetra=7;
            while (posBGral<=1023 && cant_dec<tamLVD){

            ///si es de control
                if (posBGral==1 || posBGral==2 || posBGral==4 || posBGral==8 || posBGral==16 || posBGral==32 || posBGral==64 || posBGral==128 || posBGral==256 || posBGral==512){
                posBGral++;
                pos32b--;
                }
                else{///si no es de control, cargo letra

                    if (pos32b<0){
                        cursor=cursor->ps;
                        pos32b=31;
                    }
                    aux=setBits(aux,getBits_Int(cursor->letra,pos32b,1),1,posLetra);
                    posLetra--;
                    pos32b--;
                    posBGral++;

                    if (posLetra<0){
                        altaLVD(aux,decodificado);
                        aux=0x00;
                        cant_dec++;
                        posLetra=7;
                    }


                }
            }//cierre while

            ultimaPos=posLetra;
            cursor=cursor->ps;

 }//cierre while


}


void decodificar_Hamming_32768(LVD32 *hamming, LVD *decodificado){
Nodo32 *cursor=hamming->inicial;
    unsigned char aux;
    int cant_dec=0;
    int posBGral,pos32b,posLetra,ultimaPos=-1;
    while (cant_dec<tamLVD){
            pos32b=31;posBGral=1;
            if (ultimaPos!=-1){
                while (ultimaPos!=-1){///si me quedaron bits p/letra anterior
                        if (posBGral==1 || posBGral==2 || posBGral==4 || posBGral==8 || posBGral==16 || posBGral==32 || posBGral==64 || posBGral==128 || posBGral==256 || posBGral==512 || posBGral==1024 || posBGral==2048 || posBGral==4096 || posBGral==8192 || posBGral==16384){
                        posBGral++;
                        pos32b--;
                        }
                        else {
                            aux=setBits(aux,getBits_Int(cursor->letra,pos32b,1),1,ultimaPos);
                            ultimaPos--;
                            pos32b--;
                            posBGral++;
                        }
                }
                altaLVD(aux,decodificado);///doy de alta la letra que terminé de completar
                cant_dec++;
            }

            posLetra=7;
            while (posBGral<=32768 && cant_dec<tamLVD){

            ///si es de control
                if (posBGral==1 || posBGral==2 || posBGral==4 || posBGral==8 || posBGral==16 || posBGral==32 || posBGral==64 || posBGral==128 || posBGral==256 || posBGral==512 || posBGral==1024 || posBGral==2048 || posBGral==4096 || posBGral==8192 || posBGral==16384){
                posBGral++;
                pos32b--;
                }
                else{///si no es de control, cargo letra

                    if (pos32b<0){
                        cursor=cursor->ps;
                        pos32b=31;
                    }
                    aux=setBits(aux,getBits_Int(cursor->letra,pos32b,1),1,posLetra);
                    posLetra--;
                    pos32b--;
                    posBGral++;

                    if (posLetra<0){
                        altaLVD(aux,decodificado);
                        aux=0x00;
                        cant_dec++;
                        posLetra=7;
                    }


                }
            }//cierre while

            ultimaPos=posLetra;
            cursor=cursor->ps;

 }//cierre while

}



///---------------------------------------------------------------------------------------------///


void insertar_errores_Hamming_8(LVD *lista){
    srand(time(NULL));
    int random = rand();
    int pos;
    Nodo *cursor;
    cursor=lista->inicial;
    while(cursor!=NULL){
        random = rand();
        if((random%5)==2){
            pos=(random%8);
            cursor->letra=cursor->letra ^ setBits(0x00,0x01,1,pos);
            //printf("\nposicion del error %d\n", pos);


        }
        cursor=cursor->ps;


    }

}

void insertar_errores_Hamming_32(LVD *lista){
    srand(time(NULL));
    int random = rand();
    int pos_error,bloque,i;
    Nodo *cursor;
    cursor=lista->inicial;
    int nro_iteracion=0;
    while(cursor!=NULL){
        nro_iteracion++;
        random = rand();
        i=0;
        if((random%5)==2){
            //printf("INSERTAR: bloque de 32 nro: %i\n",nro_iteracion);
            random=rand();
            pos_error=random%32;
            //printf("pos error original: %i\n",pos_error);
            bloque=(int)pos_error/8;//0...31
            pos_error=pos_error%8;
            //printf("error insertado en bloque %i en la pos %i\n",bloque,pos_error);
            while (i<bloque){
                cursor=cursor->ps;
                i++;
            }
            cursor->letra=cursor->letra ^ setBits(0x00,0x01,1,pos_error);
        }
        //ahora llevo el puntero a donde debo
        while(i<4){
            cursor=cursor->ps;
            i++;
        }
    }//cierre while
}


void insertar_errores_Hamming_1024(LVD32 *lista){
    srand(time(NULL));
    int random = rand();
    int pos_error,bloque,i;
    Nodo32 *cursor;
    cursor=lista->inicial;
    //int nro_iteracion=0;
    while(cursor!=NULL){
        //nro_iteracion++;
        random = rand();
        i=0;
        if((random%5)>2){
            random=rand();
            pos_error=random%1024;///0...1023
            bloque=(int)pos_error/32;///0..31
            pos_error=pos_error%32;///31...0
            //printf("error insertado: bloque: %i pos: %i\n",bloque,pos_error);
            while (i<bloque){
                cursor=cursor->ps;
                i++;
            }
            cursor->letra=cursor->letra ^ setBits_Int(0,0x01,1,pos_error);
        }
        //ahora llevo el puntero a donde debo
        while(i<32){
            cursor=cursor->ps;
            i++;
        }
    }//cierre while
}


void insertar_errores_Hamming_32768(LVD32 *lista){
    srand(time(NULL));
    int random = rand();
    int bloque,i;
    unsigned long pos_error;
    Nodo32 *cursor;
    cursor=lista->inicial;
    //int nro_iteracion=0;
    while(cursor!=NULL){
        //nro_iteracion++;
        random = rand();
        i=0;
        if((random%5)>2){
            random=rand();
            pos_error=random%32768;///0...32767
            bloque=(int)pos_error/32;///0..1023
            pos_error=pos_error%32;///31...0
            //printf("INSERTO bloque: %i,pos: %i\n",bloque,pos_error);printf("\n");
            while (i<bloque){
                cursor=cursor->ps;
                i++;
            }
            cursor->letra=cursor->letra ^ setBits_Int(0,0x01,1,pos_error);
        }
        //ahora llevo el puntero a donde debo
        while(i<1024){
            cursor=cursor->ps;
            i++;
        }
    }//cierre while
}



int sindrome_Hamming_8(Nodo *x){
    unsigned char resultado,and,xor;
    resultado=0x00;
    int i,j,retorno;
        for(i=0;i<3;i++){
            and=H_8[i] & x->letra;///Inicializo el xor y el and
            xor=and;
            for(j=1; j<8; j++){ ///Realizo el calculo del XOR
                and=and >> 1;
                xor= xor ^ and;
            }
            resultado=setBits(resultado,xor,3-i,7);///Coxor=0x00;loco el valor en su posicion
        }
        retorno=(int)getBits(resultado,7,3);
        if(retorno==0){
            x->error=false;
        }else{
            x->error=true;
        }
        return retorno;
}


Retorno_S sindrome_Hamming_32(unsigned char bloque[]){
    unsigned char resultado,xor_res;
    unsigned char xor[4],and[4];
    resultado=0x00;
    Retorno_S r;
    int j,k,l;
    unsigned long retorno;
    matriz_paridad_32();
        for (j=0;j<5;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<4;k++){
                and[k]=getBits(H_32[j][k],7,8) & bloque[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<8; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits(xor[k-1],0,1) ^ getBits(xor[k],0,1);
                }
            }
            resultado=setBits(resultado,xor_res,1,j);
        }
        //printf("sindrome: ");print_binary(resultado);printf("\n");
        retorno=(unsigned long)resultado;
        if(retorno==0){
            r.error=false;
            r.posicion=-1;
        }else{
            r.error=true;
            r.posicion=retorno;
        }
        return r;


}


Retorno_S sindrome_Hamming_1024(unsigned int bloque[]){
    unsigned int resultado;
    unsigned char xor_res;
    unsigned int xor[32],and[32];
    resultado=0;
    Retorno_S r;
    int j,k,l;
    unsigned long retorno;
    matriz_paridad_1024();
        for (j=0;j<10;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<32;k++){
                and[k]=H_1024[j][k] & bloque[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<32; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits_Int(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits_Int(xor[k-1],0,1) ^ getBits_Int(xor[k],0,1);
                }
            }
            resultado=setBits_Int(resultado,xor_res,1,j);
        }
        //printf("sindrome: ");print_binary(resultado);printf("\n");
        retorno=(unsigned long)resultado;
        if(retorno==0){
            r.error=false;
            r.posicion=-1;
        }else{
            r.error=true;
            r.posicion=retorno;
        }
        return r;

}


Retorno_S sindrome_Hamming_32768(unsigned int bloque[]){
    unsigned int resultado;
    unsigned char xor_res;
    unsigned int xor[1024],and[1024];
    resultado=0;
    Retorno_S r;
    int j,k,l;
    unsigned long retorno;
    matriz_paridad_32768();
        for (j=0;j<15;j++){///cálculo con matriz sólo para los bits de control
            for (k=0;k<1024;k++){
                and[k]=H_32768[j][k] & bloque[k];
                xor[k]=and[k];///Inicializo el xor y el and
                for(l=1; l<32; l++){ ///Realizo el calculo del XOR
                        and[k]=and[k] >> 1;
                        xor[k]= xor[k] ^ and[k];///voy guardando en el último bit de cada posición en el arreglo de xor el resultado
                }
                ///cálculo del xor general:
                if (k>1){///desde la posición 2, calculo el xor del resultado anterior y el xor de la posición actual
                    xor_res=xor_res ^ getBits_Int(xor[k],0,1);
                }
                else if (k==1){///la primera vez, calculo el xor de las primeras 2 posiciones
                    xor_res= getBits_Int(xor[k-1],0,1) ^ getBits_Int(xor[k],0,1);
                }
            }
            resultado=setBits_Int(resultado,xor_res,1,j);
        }

        retorno=(unsigned long)resultado;
        //printf("sindrome: %i",retorno);printf("\n");
        if(retorno==0){
            r.error=false;
            r.posicion=-1;
        }else{
            r.error=true;
            r.posicion=retorno;
        }
        return r;

}



void corregir_errores_Hamming_8(LVD *lista){
    Nodo *cursor;
    cursor=lista->inicial;
    int pos_corregir;
    while(cursor!=NULL){
        pos_corregir=sindrome_Hamming_8(cursor);
        if(cursor->error){
            cursor->letra= cursor->letra ^ setBits(0x00,0x01,1,8-pos_corregir);
           // printf("\nposicion del sindrome %d\n", pos_corregir);
        }
        cursor=cursor->ps;
    }

}


void corregir_errores_Hamming_32(LVD *lista){
    Nodo *cursor;
    Nodo *cursorAux;
    cursor=lista->inicial;
    cursorAux=lista->inicial;
    int pos_corregir,bloque_corregir=0,i;
    Retorno_S ret;
    unsigned char bloque_aux[4];
    int nro_iteracion=1;
    while(cursor!=NULL){
        //printf("bloque de 32 nro: %i\n",nro_iteracion);
        nro_iteracion++;
        bloque_aux[0]=cursor->letra;
        cursor=cursor->ps;
        bloque_aux[1]=cursor->letra;
        cursor=cursor->ps;
        bloque_aux[2]=cursor->letra;
        cursor=cursor->ps;
        bloque_aux[3]=cursor->letra;

        ret=sindrome_Hamming_32(bloque_aux);
        i=0;
        if(ret.error){
            bloque_corregir=(int)(((ret.posicion)-1)/8);
            pos_corregir=7-(((ret.posicion)-1)%8);

            while(i<bloque_corregir){
                cursorAux=cursorAux->ps;
                i++;
            }
            cursorAux->letra =(cursorAux->letra) ^ setBits(0x00,0x01,1,pos_corregir);
        }

        cursor=cursor->ps;//apunto al siguiente bloque
        cursorAux=cursor;
    }//cierre while

}

void corregir_errores_Hamming_1024(LVD32 *lista){
    Nodo32 *cursor;
    Nodo32 *cursorAux;
    cursor=lista->inicial;
    cursorAux=lista->inicial;
    int pos_corregir,bloque_corregir=0,i;
    Retorno_S ret;
    unsigned int bloque_aux[32];
    int nro=0;
    while(cursor!=NULL){
        //printf("bloque de 32 nro: %i\n",nro_iteracion);
        //nro_iteracion++;
        for (nro=0;nro<32;nro++){
            bloque_aux[nro]=cursor->letra;
            cursor=cursor->ps;
        }

        ret=sindrome_Hamming_1024(bloque_aux);
        i=0;
        if(ret.error){
            bloque_corregir=(int)(((ret.posicion)-1)/32);
            pos_corregir=31-(((ret.posicion)-1)%32);
            //printf("bloque encontrado: %i pos: %i",bloque_corregir,pos_corregir);
            while(i<bloque_corregir){
                cursorAux=cursorAux->ps;
                i++;
            }
            cursorAux->letra =(cursorAux->letra) ^ setBits_Int(0,0x01,1,pos_corregir);
        }

        //cursor=cursor->ps;//apunto al siguiente bloque
        cursorAux=cursor;
    }//cierre while

}


void corregir_errores_Hamming_32768(LVD32 *lista){
    Nodo32 *cursor;
    Nodo32 *cursorAux;
    cursor=lista->inicial;
    cursorAux=lista->inicial;
    int pos_corregir,bloque_corregir=0,i;
    Retorno_S ret;
    unsigned int bloque_aux[1024];
    int nro=0;
    while(cursor!=NULL){
        //printf("bloque de 32 nro: %i\n",nro_iteracion);
        //nro_iteracion++;
        for (nro=0;nro<1024;nro++){
            bloque_aux[nro]=cursor->letra;
            cursor=cursor->ps;
        }

        ret=sindrome_Hamming_32768(bloque_aux);
        i=0;
        if(ret.error){
            bloque_corregir=(int)(((ret.posicion)-1)/32);
            pos_corregir=31-(((ret.posicion)-1)%32);

            while(i<bloque_corregir){
                cursorAux=cursorAux->ps;
                i++;
            }
            cursorAux->letra =(cursorAux->letra) ^ setBits_Int(0,0x01,1,pos_corregir);
        }

        //cursor=cursor->ps;//apunto al siguiente bloque
        cursorAux=cursor;
    }//cierre while

}


//genero una LVD de unsigned char, donde cada uno de ellos es un caracter del archivo
void leer_archivo_txt(LVD *texto_original,char nombre[]){
    FILE *archivo;
    unsigned char auxiliar;
    tamLVD=0;
    //printf("%s", nombre);
    if((archivo=fopen(nombre , "rb")) != NULL){
        while(!feof(archivo)){
            fscanf(archivo,"%c",&auxiliar);
            tamLVD++;
            altaLVD(auxiliar,texto_original); //agrego caracter a la LVD
            //printf("%c",auxiliar);printf("\n");
        }

    }
 fclose(archivo);
}
 void guardar_archivo_txt(LVD *texto_para_guardar, char nombre[]){
    FILE *archivo;
    Nodo *cursor=texto_para_guardar->inicial;
    if((archivo=fopen(nombre , "w")) != NULL){
    while(cursor!=NULL){
        fprintf(archivo,"%c",cursor->letra);
        cursor=cursor->ps;
    }
 }
    fclose(archivo);

 }

 void guardar_archivo_txt32(LVD32 *texto_para_guardar, char nombre[]){
    FILE *archivo;
    Nodo32 *cursor=texto_para_guardar->inicial;
    int i;
    if((archivo=fopen(nombre , "w")) != NULL){
    while(cursor!=NULL){
            fprintf(archivo,"%c",getBits_Int(cursor->letra,31,8));
            fprintf(archivo,"%c",getBits_Int(cursor->letra,23,8));
            fprintf(archivo,"%c",getBits_Int(cursor->letra,15,8));
            fprintf(archivo,"%c",getBits_Int(cursor->letra,7,8));
            cursor=cursor->ps;

    }
 }
    fclose(archivo);

 }

 void prueba2(){
int pos=1,info=0,posInfo=31,k=0;
while (pos<=32768){
    if ( pos==1 || pos==2 || pos==4 || pos==8 || pos==16 || pos==32 || pos==64 || pos ==128 || pos==256 || pos==512 || pos==1024 || pos==2048 || pos==4096 || pos==8192 || pos==16384 || pos==32768){
        printf("bit de control %i\n",pos);
        printf("k= %i    posInfo=%i\n",k,posInfo);
        system("pause");
        pos++;

    }
    else{
        pos++;
        info++;
        posInfo--;
    }
    if (posInfo<0){
        k++;
        posInfo=31;
    }

}

 }


void prueba(){
/*unsigned char x= 0x21;
printf("8 bits\n");
print_binary(x);

printf("\n4 bits de la derecha\n");
print_binary(getBits(x,3,4));

printf("\n4 bits de la izquierda\n");
print_binary(getBits(x,7,4));

unsigned char x1=0x00;
unsigned char y1=0x27;//00100111
printf("\nprueba set bits:\n y1= 00100111    x1= 00000000\n");
//setBits: coloca n bits de y1 a la izquierda de x1 desde la posicion p
print_binary(setBits(x1,getBits(y1,6,2),3,6));
printf("\n");

unsigned char a=0x00;
unsigned char b='b';
unsigned char c='c';
unsigned char d='d';
unsigned char e='e';
unsigned int x2=0;
unsigned int x3=~x2;
unsigned char y2=~0x00;
printf("\nprueba set bits:\n");
print_binary_int(x2);printf("\n");
print_binary(y2);printf("\n");
printf("Res: ");
print_binary_int(setBits_Int(x2,y2,8,31));
printf("\n");
printf("get bits\n");
print_binary(getBits(y2,7,3));
printf("\n prueba get y set p/32: \n");
printf("letra a: "); print_binary(a); printf("\n");
printf("letra b: "); print_binary(b); printf("\n");
printf("letra c: "); print_binary(c); printf("\n");
printf("letra d: "); print_binary(d); printf("\n");
//printf("letra e: "); print_binary(e); printf("\n");

x2=setBits_Int(x2,getBits(b,7,8),8,31);
printf("x2 queda: ");print_binary_int(x2);
printf("\n de x2 tomo desde la pos 31 5 bits y los coloco desde pos7: \n");
a=setBits(a,getBits_Int(x2,31,7),7,7);

//x2=setBits_Int(x2,getBits(c,7,8),8,15);
//x2=setBits_Int(x2,getBits(d,7,8),8,7);
printf("a queda: ");print_binary(a);
printf("\nand:\n");
print_binary_int(x2); printf(" & ");print_binary_int(x3);
printf(" es: ");print_binary_int(x2&x3);*/

unsigned char c=setBits(0x01,0x01,1,7);
int prueba=(int)c;
int x1=15,x2=8;
int res=(int)(x1/x2);
print_binary(c); printf("\nint: %i\n",prueba);
printf("entero de %i / %i: %i\n",x1,x2,res);


}

void mostrar_menu (int hamming_seleccionado){
    system("cls");
    printf ("-----------------------------------------------------------------------\n");
    printf ("MEN%c HAMMING %d\n", 233,hamming_seleccionado);
    printf ("-----------------------------------------------------------------------\n"
            "1. Codificar\n"
            "2. Decodificar\n"
            "3. Insertar error\n"
            "4. Corregir error\n"
            "5. Salir\n"
            "-----------------------------------------------------------------------\n\n");
}


int main(int argc, char *argv[])
{
//printf("hola");
char rutaArchivo[200]="";
//printf("ruta %s",rutaArchivo);
//printf("%s",argv[1]);


//argv[1]="C:\\wamp\\PRUEBA.txt";
strcat(rutaArchivo,argv[1]);
//argv[2]="1";
//argv[3]="1";
char stringNumeroHamming[10]="";
strcat(stringNumeroHamming,argv[2]);
int numeroHamming=atoi(stringNumeroHamming);

char stringNumeroOperacion[10]="";
strcat(stringNumeroOperacion,argv[3]);
int numeroOperacion=atoi(stringNumeroOperacion);

char ruta[100]="";
strcat(ruta,argv[4]);

//printf("ruta: %s hamming: %i op: %i",rutaArchivo,numeroHamming,numeroOperacion);
//prueba2();
//int menu_de_opciones,menu_hamming_8, menu_hamming_32,menu_hamming_1024,menu_hamming_32768;
LVD texto_original;
LVD hamming_8,hamming_32;
LVD32 hamming_1024,hamming_32768;

LVD hamming_8_decodificado,hamming_32_decodificado;
LVD hamming_1024_decodificado,hamming_32768_decodificado;
inicialiarLVD(&texto_original); //Inicializo las listas haciéndolas apuntar a null
inicialiarLVD(&hamming_8);
inicialiarLVD(&hamming_8_decodificado);

inicialiarLVD(&hamming_32);
inicialiarLVD(&hamming_32_decodificado);

inicialiarLVD32(&hamming_1024);
inicialiarLVD(&hamming_1024_decodificado);

inicialiarLVD32(&hamming_32768);
inicialiarLVD(&hamming_32768_decodificado);

//prueba();
//inicializar_matriz_1024();
//printf("Inicializada\n");
//matriz_paridad_32();
//system("pause");



/*do{
system("cls");
printf("---------------\n");
printf("MENU DE OPCIONES\n");
printf("1) Hamming 8 bits\n");
printf("2) Hamming 32 bits\n");
printf("3) Hamming 1024 bits\n");
printf("4) Hamming 32768 bits\n");
printf("5) Salir\n");
printf("---------------\n");
scanf("%d",&menu_de_opciones);fflush(stdin);
*/
//switch(menu_de_opciones){//-------------> VERSIÓN SIN JAVA
switch(numeroHamming){
case 1:{//-------------> VERSIÓN SIN JAVA


    leer_archivo_txt(&texto_original,rutaArchivo);

    generar_Hamming_8(&texto_original,&hamming_8);


    /*do{
    mostrar_menu(8);
    scanf("%d",&menu_hamming_8);fflush(stdin);*/

    //switch(menu_hamming_8){//-------------> VERSIÓN SIN JAVA
    switch (numeroOperacion){

    case 1:{//Caso de codificación//

        //leer_archivo_txt(&texto_original,"original.txt");//----------->VERSION SIN JAVA
        //generar_Hamming_8(&texto_original,&hamming_8);//----------->VERSION SIN JAVA
        guardar_archivo_txt(&hamming_8,strcat(ruta,"hamming8.txt"));

        //printf("El archivo ha sido codificado con exito.\n");//----------->VERSION SIN JAVA
        //system("pause");//----------->VERSION SIN JAVA
    }break;

    case 2:{//--------->VERSION SIN JAVA

        decodificar_Hamming_8(&hamming_8,&hamming_8_decodificado);
        guardar_archivo_txt(&hamming_8_decodificado,strcat(ruta,"decodificado8.txt"));
        //printf("El archivo ha sido decodificado con exito.\n");//--------->VERSION SIN JAVA
        //system("pause");//--------->VERSION SIN JAVA
    }break;

    case 3:{//--------->VERSION SIN JAVA

        insertar_errores_Hamming_8(&hamming_8);
        inicialiarLVD(&hamming_8_decodificado);
        decodificar_Hamming_8(&hamming_8,&hamming_8_decodificado);
        guardar_archivo_txt(&hamming_8_decodificado,strcat(ruta,"decodificado_con_errores_8.txt"));
        //printf("Se han insertado los errores con exito.\n");//--------->VERSION SIN JAVA
        //system("pause");//--------->VERSION SIN JAVA
    }break;

    case 4:{//--------->VERSION SIN JAVA

        corregir_errores_Hamming_8(&hamming_8);
        inicialiarLVD(&hamming_8_decodificado);
        decodificar_Hamming_8(&hamming_8,&hamming_8_decodificado);
        guardar_archivo_txt(&hamming_8_decodificado,strcat(ruta,"decodificado_sin_errores_8.txt"));
        //printf("Se han corregido los errores con exito.\n");//--------->VERSION SIN JAVA
        //system("pause");//--------->VERSION SIN JAVA
    }break;


    }//cierre switch numeroOperacion

    //}while(menu_hamming_8!=5);//--------->VERSION SIN JAVA

//Si elige salir, vacío las listas
vaciarLVD(&texto_original);
vaciarLVD(&hamming_8);
vaciarLVD(&hamming_8_decodificado);


}break;

case 2:{//--------->VERSION SIN JAVA

    leer_archivo_txt(&texto_original,rutaArchivo);
    generar_Hamming_32(&texto_original,&hamming_32);
    /*do{
    mostrar_menu(32);
    scanf("%d",&menu_hamming_32);fflush(stdin);
    */
    //switch(menu_hamming_32){//------->VERSION SIN JAVA
    switch(numeroOperacion){
    case 1:{//Caso de codificación//------->VERSION SIN JAVA


        //leer_archivo_txt(&texto_original,"original.txt");
        //generar_Hamming_32(&texto_original,&hamming_32);
        guardar_archivo_txt(&hamming_32,strcat(ruta,"hamming32.txt"));
        //printf("El archivo ha sido codificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 2:{//------->VERSION SIN JAVA

        decodificar_Hamming_32(&hamming_32,&hamming_32_decodificado);
        guardar_archivo_txt(&hamming_32_decodificado,strcat(ruta,"decodificado32.txt"));
        //printf("El archivo ha sido decodificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 3:{//------->VERSION SIN JAVA

        insertar_errores_Hamming_32(&hamming_32);

        inicialiarLVD(&hamming_32_decodificado);

        decodificar_Hamming_32(&hamming_32,&hamming_32_decodificado);
        guardar_archivo_txt(&hamming_32_decodificado,strcat(ruta,"decodificado_con_errores_32.txt"));
        //printf("Se han insertado los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 4:{//------->VERSION SIN JAVA

        corregir_errores_Hamming_32(&hamming_32);

        inicialiarLVD(&hamming_32_decodificado);

        decodificar_Hamming_32(&hamming_32,&hamming_32_decodificado);
        guardar_archivo_txt(&hamming_32_decodificado,strcat(ruta,"decodificado_sin_errores_32.txt"));
        //printf("Se han corregido los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;


    }//cierre switch

    //}while(menu_hamming_32!=5);//------->VERSION SIN JAVA

//Si elige salir, vacío las listas
vaciarLVD(&texto_original);
vaciarLVD(&hamming_32);
vaciarLVD(&hamming_32_decodificado);

}break;


case 3:{//--------->VERSION SIN JAVA
    leer_archivo_txt(&texto_original,rutaArchivo);
    generar_Hamming_1024(&texto_original,&hamming_1024);

    /*do{
    mostrar_menu(1024);
    scanf("%d",&menu_hamming_1024);fflush(stdin);
*/
    //switch(menu_hamming_1024){//------->VERSION SIN JAVA
    switch(numeroOperacion){
    case 1:{//Caso de codificación//------->VERSION SIN JAVA

        //leer_archivo_txt(&texto_original,"original.txt");
        //generar_Hamming_1024(&texto_original,&hamming_1024);
        guardar_archivo_txt32(&hamming_1024,strcat(ruta,"hamming1024.txt"));
        //printf("El archivo ha sido codificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 2:{//------->VERSION SIN JAVA

        decodificar_Hamming_1024(&hamming_1024,&hamming_1024_decodificado);
        guardar_archivo_txt(&hamming_1024_decodificado,strcat(ruta,"decodificado1024.txt"));
        //printf("El archivo ha sido decodificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 3:{//------->VERSION SIN JAVA

        insertar_errores_Hamming_1024(&hamming_1024);

        inicialiarLVD(&hamming_1024_decodificado);

        decodificar_Hamming_1024(&hamming_1024,&hamming_1024_decodificado);
        guardar_archivo_txt(&hamming_1024_decodificado,strcat(ruta,"decodificado_con_errores_1024.txt"));
        //printf("Se han insertado los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 4:{//------->VERSION SIN JAVA

        corregir_errores_Hamming_1024(&hamming_1024);

        inicialiarLVD(&hamming_1024_decodificado);

        decodificar_Hamming_1024(&hamming_1024,&hamming_1024_decodificado);
        guardar_archivo_txt(&hamming_1024_decodificado,strcat(ruta,"decodificado_sin_errores_1024.txt"));
        //printf("Se han corregido los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    }//cierre switch

    //}while(menu_hamming_1024!=5);//------->VERSION SIN JAVA

//Si elige salir, vacío las listas
vaciarLVD(&texto_original);
vaciarLVD32(&hamming_1024);
vaciarLVD(&hamming_1024_decodificado);

}break;


case 4:{//--------->VERSION SIN JAVA
    leer_archivo_txt(&texto_original,rutaArchivo);
    generar_Hamming_32768(&texto_original,&hamming_32768);

    /*do{
    mostrar_menu(32768);
    scanf("%d",&menu_hamming_32768);fflush(stdin);
*/
    //switch(menu_hamming_32768){//------->VERSION SIN JAVA
    switch(numeroOperacion){
    case 1:{//Caso de codificación//------->VERSION SIN JAVA

        //leer_archivo_txt(&texto_original,"original.txt");
        //generar_Hamming_32768(&texto_original,&hamming_32768);
        guardar_archivo_txt32(&hamming_32768,strcat(ruta,"hamming32768.txt"));
        //printf("El archivo ha sido codificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;
    case 2:{//------->VERSION SIN JAVA

        decodificar_Hamming_32768(&hamming_32768,&hamming_32768_decodificado);
        guardar_archivo_txt(&hamming_32768_decodificado,strcat(ruta,"decodificado32768.txt"));
        //printf("El archivo ha sido decodificado con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 3:{//------->VERSION SIN JAVA

        insertar_errores_Hamming_32768(&hamming_32768);
        inicialiarLVD(&hamming_32768_decodificado);
        decodificar_Hamming_32768(&hamming_32768,&hamming_32768_decodificado);
        guardar_archivo_txt(&hamming_32768_decodificado,strcat(ruta,"decodificado_con_errores_32768.txt"));
        //printf("Se han insertado los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;

    case 4:{//------->VERSION SIN JAVA

        corregir_errores_Hamming_32768(&hamming_32768);

        inicialiarLVD(&hamming_32768_decodificado);

        decodificar_Hamming_32768(&hamming_32768,&hamming_32768_decodificado);
        guardar_archivo_txt(&hamming_32768_decodificado,strcat(ruta,"decodificado_sin_errores_32768.txt"));
        //printf("Se han corregido los errores con exito.\n");//------->VERSION SIN JAVA
        //system("pause");//------->VERSION SIN JAVA
    }break;


    }

    //}while(menu_hamming_32768!=5);//------->VERSION SIN JAVA

//Si elige salir, vacío las listas
vaciarLVD(&texto_original);
vaciarLVD32(&hamming_32768);
vaciarLVD(&hamming_32768_decodificado);

}break;

}//cierre switch de hamming
//}while(menu_de_opciones!=5);


}
