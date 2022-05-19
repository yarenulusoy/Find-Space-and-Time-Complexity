#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include <limits.h>
#include <process.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include<conio.h>
#include <errno.h>

/*
*Pelin Ozdemir 210201102
*Suheda Yaren Ulusoy 200201128
*
*/



int satir_bos_mu(char *data);
int dosya_icerik_kontrolu();
char* sabit_big_o();
char* ustel_big_o();
char* recursive_big_o();
int gecen_sure_hesapla();
void calisma_zamani_yazdir(int for_ici_islemler[10],int sabit);
void calisma_zamani();
void alan_karmasikligi();
void alan_karmasikligi_yazdir();
void menu();


int dosya_icerik_kontrolu(){
  FILE *file;
  file=fopen("data.txt","r+");
  int c_kodu=0;
  char *data=malloc(255*sizeof(char));

    while(fgets(data, 255, file)){

          if((strstr(data,"#include <stdio.h>") )!=NULL){
            printf("Program c ile yazilmis\n");
            c_kodu=1;
            break;

          }



    }
   if(c_kodu != 1){
     printf("C kodu degil");
   }

 free(data);
 fclose(file);

  return 0;
}

int gecen_sure_hesapla(){
    FILE *f=fopen("kod.c","w");
    FILE *file=fopen("data.txt","r");
    char *data=malloc(sizeof(char)*255);
    while(fgets(data,255,file)){
      fprintf(f,data);
    }
    clock_t begin = clock();
    system("kod.exe");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Gecen sure %f saniye.", time_spent);



    return 0;
}
char* sabit_big_o(){
  FILE *file;
  file=fopen("data.txt","r+");
  char *sonuc=malloc(sizeof(char) * sizeof(int) * 4 + 1);
  char *data=malloc(255*sizeof(char));
  sonuc="0";

    while(fgets(data, 255, file)){

        if((strstr(data,"while") )==NULL && (strstr(data,"}")==NULL || strstr(data,";")!=NULL ) && (satir_bos_mu(data)!=1)){
         sonuc="O(1)";
        }


    }

 free(data);
 fclose(file);
 return sonuc;

}

char* ustel_big_o(){
  FILE *file;
  file=fopen("data.txt","r+");
  int a=0,if_parantez=0,for_parantez=0,temp=0,i=0;//a kapanan suslu parantezler
  char *kontrol=malloc(255*sizeof(char));
  char *sonuc=malloc(sizeof(char) * sizeof(int) * 4 + 1);
  char *data=malloc(255*sizeof(char));
    while(fgets(data, 255, file)){
        if(((strstr(data,"for") )!=NULL || (strstr(data,"while") )!=NULL || (strstr(data,"do") )!=NULL )  && strstr(data,"}")==NULL && strstr(data,"{")!=NULL ){


           for_parantez++;
           kontrol[i]='f';
           i++;
          if(a>0){
            a=0;
          }

        }
        else if (( (strstr(data,"if") )!=NULL && strstr(data,"{")!=NULL) ||  ( (strstr(data,"else if"))!=NULL && strstr(data,"{")!=NULL) || ((strstr(data,"else") )!=NULL && strstr(data,"{")!=NULL)
        && for_parantez>0){
           if_parantez++;
           kontrol[i]='i';
           i++;

        }

       else if(strstr(data,"}")!=NULL){

                if((kontrol[i-1])=='f'){
                  for_parantez--;
                  i--;
                  a++;
                  if(a>=temp){
                    temp=a;
                  }
                }
                else  if((kontrol[i-1])=='i'){
                  if_parantez--;
                  i--;

             }

        }



    }

free(kontrol);
free(data);
fclose(file);

if(temp>0){

 sprintf(sonuc,"%d",temp);

return sonuc;
}
else{
  sonuc="0";
  return sonuc;
}

}

int kelimeBul(char * str, char * kelime)
{
    int i, j, bul, kelimesayisi;
    int uzunluk, arananuzunluk;

    uzunluk = strlen(str);
    arananuzunluk = strlen(kelime);

    kelimesayisi = 0;

    for(i=0; i <= uzunluk-arananuzunluk; i++)
    {

        bul = 1;
        for(j=0; j<arananuzunluk; j++)
        {
            if(str[i + j] != kelime[j])
            {
                bul = 0;
                break;
            }
        }

        if(bul == 1)
        {
            kelimesayisi++;
        }
    }


    return kelimesayisi;
}

void alan_karmasikligi_yazdir(int toplam_char_dizi_boyut[10],int toplam_double_dizi_boyut[10],int toplam_int_dizi_boyut[10],int toplam_sabit,int recursive){

   for(int i=0;i<10;i++){
    if(toplam_char_dizi_boyut[i]!=0){

      printf("2n^%d+",toplam_char_dizi_boyut[i]);
    }
    if(toplam_double_dizi_boyut[i]!=0){

      printf("8n^%d+",toplam_double_dizi_boyut[i]);
    }
    if(toplam_int_dizi_boyut[i]!=0){

      printf("4n^%d+",toplam_int_dizi_boyut[i]);
    }

  }
  if(recursive>0){
    printf("n^%d+",recursive);
  }
  printf("%d",toplam_sabit);

}

void alan_karmasikligi(){
  FILE *file;
  file=fopen("data.txt","r+");
  int toplam_int_dizi_boyut[10]={0,0,0,0,0,0,0,0,0,0};
  int toplam_char_dizi_boyut[10]={0,0,0,0,0,0,0,0,0,0};
  int toplam_double_dizi_boyut[10]={0,0,0,0,0,0,0,0,0,0};
  int kac_defa_int=0,dizi_say_int=0,toplam_int=0,toplam_int_dizi=0,boyut_int=0;
  int kac_defa_char=0,dizi_say_char=0,toplam_char=0,toplam_char_dizi=0,char_boyut=0;
  int kac_defa_double=0,dizi_say_double=0,toplam_double=0,toplam_double_dizi=0,double_boyut=0;
  int kac_defa=0,dizi_say=0;
  int toplam_sabit=0;
  int recursive=0;
  char *data=malloc(255*sizeof(char));
    while(fgets(data, 255, file)){
        if(((strstr(data,"int") )!=NULL || (strstr(data,",") )!=NULL || (strstr(data,"float") )!=NULL || (strstr(data,"long") )!=NULL)  && strstr(data,";") !=NULL &&
        strstr(data,"for")==NULL && strstr(data,"while")==NULL && strstr(data,"printf")==NULL ){
             if(strstr(data,"[") == NULL){
                 kac_defa_int=kelimeBul(data,",");
                 kac_defa_int++;
                 toplam_int+=kac_defa_int;
               }
             else if(strstr(data,"[") != NULL){
                 kac_defa_int=kelimeBul(data,",");
                 dizi_say_int=kelimeBul(data,"[");
                 toplam_int+=kac_defa_int;
                 toplam_int_dizi+=dizi_say_int;

            }


        }
       else if(((strstr(data,"char") )!=NULL || (strstr(data,",") )!=NULL || (strstr(data,"bool") )!=NULL)  && strstr(data,";") !=NULL &&
        strstr(data,"for")==NULL && strstr(data,"while")==NULL && strstr(data,"printf")==NULL ){
           if(strstr(data,"[") == NULL){
                 kac_defa_char=kelimeBul(data,",");
                 kac_defa_char++;
                 toplam_char+=kac_defa_char;
               }
             else if(strstr(data,"[") != NULL){
                kac_defa_char=kelimeBul(data,",");
                dizi_say_char=kelimeBul(data,"[");
                toplam_char+=kac_defa_char;
                toplam_char_dizi+=dizi_say_char;
            }

        }

        else if(((strstr(data,"double") )!=NULL || (strstr(data,",") )!=NULL )  && strstr(data,";") !=NULL &&
        strstr(data,"for")==NULL && strstr(data,"while")==NULL && strstr(data,"printf")==NULL ){
            if(strstr(data,"[") == NULL){
                 kac_defa_double=kelimeBul(data,",");
                 kac_defa_double++;
                 toplam_double+=kac_defa_double;
               }
             else if(strstr(data,"[") != NULL){
                kac_defa_double=kelimeBul(data,",");
                dizi_say_double=kelimeBul(data,"[");
                toplam_double+=kac_defa_double;
                toplam_double_dizi+=dizi_say_double;
            }

        }

        else if((strstr(data,"(")!=NULL )&& (strstr(data,")")!=NULL) && (strstr(data,";")!=NULL) && (strstr(data,"return")!=NULL) ){

           recursive++;
        }
        toplam_char_dizi_boyut[toplam_char_dizi]=toplam_char_dizi;
        toplam_double_dizi_boyut[toplam_double_dizi]=toplam_double_dizi;
        toplam_int_dizi_boyut[toplam_int_dizi]=toplam_int_dizi;




    }

toplam_sabit=toplam_int*4+toplam_char*2+toplam_double*8;
alan_karmasikligi_yazdir(toplam_char_dizi_boyut,toplam_double_dizi_boyut,toplam_int_dizi_boyut,toplam_sabit,recursive);
free(data);
fclose(file);


}

void calisma_zamani_yazdir(int for_ici_islemler[10],int sabit){

  for(int i=0;i<10;i++){
    if(for_ici_islemler[i]!=0){

      printf("%dn^%d+",for_ici_islemler[i],(i));
    }
  }
  printf("%d",sabit);


}

int satir_bos_mu(char *data){


while(*data==' ' || *data=='\t' || *data=='\n' || *data=='\r')
 data++;

if(*data=='\0')
  return 1;
else
{
    return 0;
}

 return 0;
}




void calisma_zamani(){
  FILE *file;
  file=fopen("data.txt","r+");
  int a=0,ustel=0,parantez_sayisi=0,sabit=0,if_parantez=0,for_parantez=0,temp=0,i=0;//a kapanan suslu parantezler
  int for_ici_islemler[10]={0,0,0,0,0,0,0,0,0,0};
  char *kontrol=malloc(255*sizeof(char));
  char *data=malloc(255*sizeof(char));


     while(fgets(data, 255, file)){

        if(((strstr(data,"for") )!=NULL || (strstr(data,"while") )!=NULL || (strstr(data,"do") )!=NULL )  && strstr(data,"}")==NULL &&  strstr(data,"{")!=NULL ){
           for_parantez++;
           for_ici_islemler[for_parantez]++;

           kontrol[i]='f';
           i++;
          if(a>0){
            a=0;
          }

        }
        else if (( (strstr(data,"if") )!=NULL && strstr(data,"{")!=NULL) ||  ( (strstr(data,"else if"))!=NULL && strstr(data,"{")!=NULL) || ((strstr(data,"else") )!=NULL && strstr(data,"{")!=NULL)
        && for_parantez>0){
           if_parantez++;
           kontrol[i]='i';
           i++;
           for_ici_islemler[for_parantez]++;






        }
        else if (((strstr(data,"for") )==NULL || (strstr(data,"while") )==NULL || (strstr(data,"do") )==NULL ||(strstr(data,"if") )
        ==NULL || (strstr(data,"else if"))==NULL|| ((strstr(data,"else") )==NULL ) ) && strstr(data,"}")==NULL && for_parantez >0 && (satir_bos_mu(data)!=1))
        {

               for_ici_islemler[for_parantez]++;

        }

       else if(strstr(data,"}")!=NULL){
                parantez_sayisi++;
                if((kontrol[i-1])=='f'){
                  for_parantez--;
                  i--;
                  a++;
                  if(a>=temp){
                    temp=a;
                  }
                }
                else  if((kontrol[i-1])=='i'){

                  if_parantez--;
                  i--;

             }

        }
        else if ((strstr(data,"if") )!=NULL || (strstr(data,"else if") )!=NULL || (strstr(data,"else") )!=NULL || (strstr(data,"switch") )!=NULL || (strstr(data,"case") )!=NULL  || (strstr(data,";") !=NULL) && for_parantez ==0 && if_parantez==0)
        {
          sabit++;

        }
     }

free(kontrol);
free(data);
fclose(file);
calisma_zamani_yazdir(for_ici_islemler,sabit);


}


char* recursive_big_o(){
 FILE *file;
 char *fonksiyon_adi=malloc(255*sizeof(char));
 char *son=malloc(255*sizeof(char));
 file=fopen("data.txt","r+");
 char *sonuc=malloc(255*sizeof(char));
 sonuc="0";
 char *data=malloc(255*sizeof(char));

    while(fgets(data, 255, file)){

     if(((strstr(data,"(")!=NULL )&& (strstr(data,")")!=NULL) && (strstr(data,";")!=NULL)) && (strstr(data,"return")!=NULL)){

         son=strrchr(data,'(');
         if((strstr(son,"/")!=NULL )){
           sonuc="log(n)";

         }
         else if((strstr(son,"-")!=NULL ) ){
           sonuc="n";

         }
       }


   }

return sonuc;
}

void menu(){
    char* ustel=malloc(255*sizeof(char));
    char* sabit=malloc(255*sizeof(char));
    char* recursive=malloc(255*sizeof(char));
    ustel=ustel_big_o();
    sabit=sabit_big_o();
    recursive=recursive_big_o();
    int cevap=0;

    printf("*****Islem Seciniz*****\n");
    printf("1-Zaman karmasikligi\n");
    printf("2-Alan karmasikligi\n");
    printf("3-Calisma zamani\n");
    printf("4-Dosya kontrolu\n");
    scanf("%d",&cevap);

    switch(cevap){
        case 1:
           if(ustel !="0"){
             printf("Zaman karmasikligi: O(N^%s)\n",ustel);
              }
           else if (recursive !="0"){
             printf("Zaman karmasikligi: %s \n",ustel);
              }
           else if (sabit!="0"){
             printf("Zaman karmasikligi: %s \n",sabit);
             }

           break;

        case 2:

           alan_karmasikligi();

           break;

        case 3:

          calisma_zamani();

           break;

        case 4:

         dosya_icerik_kontrolu();


           break;


    }
   free(ustel);
   free(sabit);
   free(recursive);

}



int main(int argc,char* argv[]){

  menu();
  return 0;
}
