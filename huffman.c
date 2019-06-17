#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
typedef struct nodo{
    unsigned char dato;
    float probabilidad;
    struct nodo *hijo_derecho;
    struct nodo *hijo_izquierdo;
} Nodo;

typedef struct lista{
    Nodo *dato[256];
    int fin;
}LI;
typedef struct b{
    unsigned char dato[4];
}Bits;
typedef struct a{
    unsigned char letra;
    Bits bits;
    int cantidad_de_bits;
} Alfabeto;
Alfabeto alfabeto[256];

void guardar_alfabeto(char nombre_archivo[]){
    FILE *archivo;
    if((archivo=fopen(nombre_archivo,"w"))!=NULL){
        int i;
        for(i=0; i<256; i++){
            if(alfabeto[i].cantidad_de_bits!=0){
                fprintf(archivo,"%c",alfabeto[i].letra);
                fprintf(archivo,"%c",alfabeto[i].bits.dato[0]);
                fprintf(archivo,"%c",alfabeto[i].bits.dato[1]);
                fprintf(archivo,"%c",alfabeto[i].bits.dato[2]);
                fprintf(archivo,"%c",alfabeto[i].bits.dato[3]);
                fprintf(archivo,"%d",alfabeto[i].cantidad_de_bits);



            }


        }
        fclose(archivo);
    }


}

void leer_alfabeto(char nombre_archivo[]){
    FILE *archivo;
    Alfabeto aux;
    if((archivo=fopen(nombre_archivo,"r"))!=NULL){
        while(!feof(archivo)){
            fscanf(archivo,"%c",&aux.letra);
            fscanf(archivo,"%c",&aux.bits.dato[0]);
            fscanf(archivo,"%c",&aux.bits.dato[1]);
            fscanf(archivo,"%c",&aux.bits.dato[2]);
            fscanf(archivo,"%c",&aux.bits.dato[3]);
            fscanf(archivo,"%d",&aux.cantidad_de_bits);
            alfabeto[aux.letra]=aux;


        }
        fclose(archivo);

    }


}

void vaciar_alfabeto(){
    int i;
    for(i=0; i<256; i++){
        alfabeto[i].cantidad_de_bits=0;
        alfabeto[i].letra=0x00;
        alfabeto[i].bits.dato[0]=0x00;
        alfabeto[i].bits.dato[1]=0x00;
        alfabeto[i].bits.dato[2]=0x00;
        alfabeto[i].bits.dato[3]=0x00;

    }


}


///getBits: obtiene n bits desde la posicion p, las posiciones van de 0 a 7
unsigned char getBits(unsigned char x, int p, int n){
    return (x>>(p+1-n))& ~(~0<<n);
}
///setBits: coloca n bits de y a la izquierda de x desde la posicion p
unsigned char  setBits(unsigned char x, unsigned char y, int n, int p){
return (x & ((~0 << (p+1)) | (~(~0 << (p+1 - n))))) | ((y & ~(~0 << n)) << (p+1 - n));
}

void print_binary(unsigned char c){
 unsigned char i1 = (1 << (sizeof(c)*8-1));
 for(; i1; i1 >>= 1)
      printf("%d",(c&i1)!=0);
}

void inicializar_alfabeto(Nodo *raiz, int p, Bits acumulador){
    if(raiz!=NULL){
        int maximo;
        if((p%8)==0){
            maximo=((int)ceil(((double)p)/8))+1;
        }else{
            maximo=(int)ceil(((double)p)/8);
        }
        if(raiz->hijo_izquierdo==NULL){
            alfabeto[raiz->dato].letra=raiz->dato;
            alfabeto[raiz->dato].cantidad_de_bits=p;
            alfabeto[raiz->dato].bits=acumulador;

        }
        inicializar_alfabeto(raiz->hijo_izquierdo,p+1,acumulador);

        acumulador.dato[maximo-1]=setBits(acumulador.dato[maximo-1],0x01,1,p%8);
        inicializar_alfabeto(raiz->hijo_derecho,p+1,acumulador);

    }

}
void inicializar_Huffman(LI *lista){
    unsigned char dato_inicial=0x00;
    lista->fin=0;
    for(int i=0; i<256 ;i++){
        Nodo *nuevo=(Nodo*)malloc(sizeof(Nodo));
        if(nuevo!=NULL){
            nuevo->dato=dato_inicial;
            nuevo->hijo_derecho=NULL;
            nuevo->hijo_izquierdo=NULL;
            lista->dato[i]=nuevo;
            lista->fin++;

        }
        dato_inicial++;

    }
}
void calcular_probabilidad(LI *lista,char texto_original[]){
    FILE *archivo_lectura;
    unsigned char letra_actual;
    int cantidad[256];
    long int total=0;
    float probabilidades[256];
    for(int i=0;i<256;i++){
    cantidad[i]=0;
    probabilidades[i]=0.0;
    }
    //cantidad[3]=1;///AGREGO EL EOF
    if((archivo_lectura=fopen(texto_original , "r"))!=NULL){
        while(!feof(archivo_lectura)){
            fscanf(archivo_lectura,"%c",&letra_actual);
            if(letra_actual>=0 && letra_actual<=256){
                cantidad[letra_actual]++;
                total++;
            }

        }
        fclose(archivo_lectura);
        for(int i=0; i<256; i++){
            probabilidades[i]=((float)cantidad[i])/total;
           // printf("p: %f ", probabilidades[i]);
            }
        lista->fin=0;
        for(int i=0; i<256; i++){
            if(probabilidades[i]!=0.0){
                Nodo *nuevo=(Nodo*)malloc(sizeof(Nodo));
                if(nuevo!=NULL){
                    nuevo->dato=(unsigned char)(i);
                    nuevo->hijo_derecho=NULL;
                    nuevo->hijo_izquierdo=NULL;
                    nuevo->probabilidad=probabilidades[i];
                    lista->dato[lista->fin]=nuevo;
                    lista->fin++;
                    int j=lista->fin-1;
                    Nodo *aux;
                    while(j>0 && lista->dato[j]->probabilidad > lista->dato[j-1]->probabilidad ){
                        aux=lista->dato[j-1];
                        lista->dato[j-1]=lista->dato[j];
                        lista->dato[j]=aux;
                        j--;

                    }

        }
            }

        }
    }


}
void crear_arbol_Huffman(LI *lista){
    int cursor;
    Nodo *aux;
    while(lista->fin>1){
        ///SUMO PROBABILIDADES Y ARMO EL ARBOL
        Nodo *nuevo=(Nodo*)malloc(sizeof(Nodo));
        if(nuevo!=NULL){
            nuevo->hijo_izquierdo=lista->dato[lista->fin-2];
            nuevo->hijo_derecho=lista->dato[lista->fin-1];
            nuevo->probabilidad=nuevo->hijo_izquierdo->probabilidad + nuevo->hijo_derecho->probabilidad;
            ///nuevo->dato='#'; ///uso el numeral # como caracter nulo
            lista->dato[lista->fin-2]=nuevo;
            lista->fin--;
        }
        ///ORDENO LA NUEVA LISTA
        cursor=lista->fin-1;
        while(cursor>0 && (lista->dato[cursor]->probabilidad >= lista->dato[cursor-1]->probabilidad)  ){
            aux=lista->dato[cursor-1];
            lista->dato[cursor-1]=lista->dato[cursor];
            lista->dato[cursor]=aux;
            cursor--;        }

    }
}
void mostrar_arbol(Nodo *n){
    if(n != NULL){
            printf("%c %f\n",n->dato,n->probabilidad);

            if(n->hijo_izquierdo==NULL){
                printf("Hijo Izquierdo: Vacio\n");
            }
            else{
                printf("Hijo Izquierdo: %c %f\n",n->hijo_izquierdo->dato,n->hijo_izquierdo->probabilidad);
            }
            if(n->hijo_derecho == NULL){
                printf("Hijo derecho: Vacio\n\n");
            }
            else{
                printf("Hijo derecho: %c %f\n",n->hijo_derecho->dato,n->hijo_derecho->probabilidad);
            }
            printf("\n------------------------------------------\n\n");

            mostrar_arbol(n->hijo_izquierdo);
            mostrar_arbol(n->hijo_derecho);

    }

}


void comprimir_Huffman(char nombre_texto_original[], char nombre_texto_comprido[]){
    unsigned char valor_comprimido=0x00;
    unsigned char valor_caracter_actual;
    int bits_disponibles=8;
    FILE *archivo_escritura;
    FILE *archivo_lectura;
    if((archivo_escritura=fopen(nombre_texto_comprido , "w")) != NULL && (archivo_lectura=fopen(nombre_texto_original , "r")) != NULL ){
        int i=0;
        int maximo=0;
        int cantidad=0;
        while(!feof(archivo_lectura)){

            if(i==maximo){
                fscanf(archivo_lectura,"%c",&valor_caracter_actual);
                maximo=(int)floor(((double)alfabeto[valor_caracter_actual].cantidad_de_bits)/8);
                i=0;
                if(i==maximo){
                    cantidad=alfabeto[valor_caracter_actual].cantidad_de_bits;
                }else{
                    cantidad=8;
                }

            }else{
                i++;
                if(i==maximo){
                    cantidad=alfabeto[valor_caracter_actual].cantidad_de_bits-cantidad;
                }else{
                    cantidad+=8;
                }
            }

            /*getchar();
            printf("\n i %d maximo %d cantidad %d letra actual %c bits acumulador",i,maximo,cantidad,valor_caracter_actual);
            print_binary(valor_comprimido);
            printf("\n");*/



            if(bits_disponibles>0){
                valor_comprimido=setBits(valor_comprimido,alfabeto[valor_caracter_actual].bits.dato[i],bits_disponibles,7);
                bits_disponibles=bits_disponibles-cantidad;


            }
            if(bits_disponibles==0){
                fprintf(archivo_escritura,"%c",valor_comprimido);
                bits_disponibles=8;
                valor_comprimido=0x00;


            }
            if(bits_disponibles<0){
                fprintf(archivo_escritura,"%c",valor_comprimido);
                valor_comprimido=0x00;
                valor_comprimido=setBits(valor_comprimido,alfabeto[valor_caracter_actual].bits.dato[i]>>cantidad+bits_disponibles ,(-1)*bits_disponibles,(-1)*bits_disponibles-1);
                bits_disponibles=8+bits_disponibles;

            }

        }
        if(bits_disponibles>0){
            fprintf(archivo_escritura,"%c",valor_comprimido);


        }
        fclose(archivo_escritura);
        fclose(archivo_lectura);
    }


}

void descomprimir_Huffman(char nombre_texto_comprimido[], char nombre_texto_descomprimido[], Nodo *raiz){
    unsigned char valor_caracter_actual;
    unsigned char dato;
    int i=0;
    int prueba=0;
    Nodo *cursor;
    FILE *archivo_escritura;
    FILE *archivo_lectura;
    if((archivo_escritura=fopen(nombre_texto_descomprimido , "w")) != NULL && (archivo_lectura=fopen(nombre_texto_comprimido , "r")) != NULL ){
        fscanf(archivo_lectura,"%c",&valor_caracter_actual);
        cursor=raiz;
        while(!feof(archivo_lectura) && (cursor->dato!=0x03) ){
            cursor=raiz;
            prueba++;
            while(cursor->hijo_izquierdo!=NULL){
                dato=getBits(valor_caracter_actual,i,1);

                /*printf("\n");
                print_binary(dato);*/


                i++;
                if(dato==0x01){
                    cursor=cursor->hijo_derecho;
                }else{
                    cursor=cursor->hijo_izquierdo;
                }
                if(i==8){
                i=0;
                fscanf(archivo_lectura,"%c",&valor_caracter_actual);
                }
            }
            fprintf(archivo_escritura,"%c",cursor->dato);

           /* getchar();
            printf("\n %c \n",cursor->dato);*/


        }
        fclose(archivo_escritura);
        fclose(archivo_lectura);
        }



}

void prueba(){
/**LI huffman,arbol;
inicializar_Huffman(&huffman);


calcular_probabilidad(&huffman,"original.txt");

for(int i=0; i<huffman.fin; i++){
printf("%c %f\n",huffman.dato[i]->dato,huffman.dato[i]->probabilidad);
}

arbol=huffman;

crear_arbol_Huffman(&arbol);
mostrar_arbol(arbol.dato[0]);
Bits acumulador;
for(int i=0;i<4;i++){
    acumulador.dato[i]=0x00;
}
inicializar_alfabeto(arbol.dato[0],0,acumulador);

 for(int i=0; i<256; i++){
printf("%c %d ", alfabeto[i].letra, alfabeto[i].cantidad_de_bits);
print_binary(alfabeto[i].bits.dato[3]);
print_binary(alfabeto[i].bits.dato[2]);
print_binary(alfabeto[i].bits.dato[1]);
print_binary(alfabeto[i].bits.dato[0]);
printf("\n");
}
comprimir_Huffman("original.txt","comprimido.txt");
descomprimir_Huffman("comprimido.txt","descomprimido.txt",arbol.dato[0]);

**/
for(int i=0; i<256; i++){
printf("%c %d ", alfabeto[i].letra, alfabeto[i].cantidad_de_bits);
print_binary(alfabeto[i].bits.dato[3]);
print_binary(alfabeto[i].bits.dato[2]);
print_binary(alfabeto[i].bits.dato[1]);
print_binary(alfabeto[i].bits.dato[0]);
printf("\n");
}

}

int main(int argc, char *argv[])
{

char menu_de_opciones[4]="";
strcat(menu_de_opciones,argv[2]);
LI huffman,arbol;
inicializar_Huffman(&huffman);
char original[100]="";
char compactado[100]="";
char descompactado[100]="";
char tabla[100]="";

strcat(original,argv[1]);
original[strlen(original)-1]='t';
original[strlen(original)-2]='x';
original[strlen(original)-3]='t';

strcat(compactado,original);
compactado[strlen(compactado)-1]='F';
compactado[strlen(compactado)-2]='U';
compactado[strlen(compactado)-3]='H';

strcat(descompactado,original);
descompactado[strlen(descompactado)-1]='U';
descompactado[strlen(descompactado)-2]='H';
descompactado[strlen(descompactado)-3]='D';

strcat(tabla,original);
tabla[strlen(tabla)-1]='L';
tabla[strlen(tabla)-2]='B';
tabla[strlen(tabla)-3]='T';




switch(menu_de_opciones[0]){

    case '1':{
        ///COMPRACTAR


        calcular_probabilidad(&huffman,original); ///CALCULO PROBABILIDAD

        arbol=huffman;
        crear_arbol_Huffman(&arbol);

        Bits acumulador;
        for(int i=0;i<4;i++){
            acumulador.dato[i]=0x00;
        }

        inicializar_alfabeto(arbol.dato[0],0,acumulador);
        //prueba();


        comprimir_Huffman(original,compactado);
        //prueba();

        guardar_alfabeto(tabla);
        //leer_alfabeto("tabla.txt");
        //prueba();

    }break;
    case '2':{
        ///DESCOMPACTAR







        calcular_probabilidad(&huffman,original);


        arbol=huffman;
        crear_arbol_Huffman(&arbol);

        Bits acumulador;
        for(int i=0;i<4;i++){
            acumulador.dato[i]=0x00;
        }
        inicializar_alfabeto(arbol.dato[0],0,acumulador);




        descomprimir_Huffman(compactado,descompactado,arbol.dato[0]);



    }break;
    case '3':{
        ///VER EN PANTALLA
        FILE *archivo;
        unsigned char aux;
        char nombre_archivo[30]="";
        strcat(nombre_archivo,argv[1]);


        if((archivo=fopen(nombre_archivo,"r"))!=NULL){
        while(!feof(archivo)){
            fscanf(archivo,"%c",&aux);
            printf("%c",aux);


            }
        fclose(archivo);
        printf("\n");




        }


    }break;
    /**case '4':{
        FILE *archivo_original;
        FILE *archivo_comprimido;
        unsigned char aux;
        char nombre_archivo[30]="";
        strcat(nombre_archivo,argv[1]);
        char comprimido[30]="";
        strcat(comprimido,"HUF-");




        strcat(comprimido,nombre_archivo);
        if(((archivo_original=fopen(nombre_archivo,"r"))!=NULL) && ((archivo_comprimido=fopen(comprimido,"r"))!=NULL) ){
            fseek(archivo_original, 0L, SEEK_END);
            fseek(archivo_comprimido, 0L, SEEK_END);
            int size_original=ftell(archivo_original);
            int size_comprimido=ftell(archivo_comprimido);
            printf("El tamaño del archivo original es %d bytes \n",size_original );
            printf("El tamaño del archivo comprimido es %d bytes \n", size_comprimido);
            printf("El archivo comprimido es un %f %% mas pequeño que el archivo original\n",100-((100*((float)size_comprimido))/(float)size_original));

            fseek(archivo_comprimido, 0L, SEEK_SET);
            fseek(archivo_original, 0L, SEEK_SET);
            fclose(archivo_comprimido);
            fclose(archivo_original);
            }


    }break;**/

}














}
