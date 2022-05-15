#include <stdio.h>
#include <string.h>

typedef struct Pacient {
    char pacient[100];
    int osiguran;
    int brPregledi;
}Pacient;

typedef struct MaticenDoktor {
    char doktor[100];
    int brPacienti;
    Pacient pacienti[200];
    float cena;
}MaticenDoktor;

void najuspesen_doktor(MaticenDoktor *doktor, int n){
//    int i, j, br, max=0, isti=0, najdobarI=0, sumPregledi;
//    float vkSum = 0;
//    float temp;
//    for(i=0; i<n; i++){
//        br=0;
//        for(j=0; i<doktor[i].brPacienti; i++){
//            if(doktor[i].pacienti[j].osiguran==0){
//                br+=doktor[i].pacienti[j].brPregledi;
//            }
//        }
//        temp=br*doktor[i].cena;
//        if(temp>max){
//            max=temp;
//            najdobarI=i;
//            vkSum=temp;
//        }else if(temp==max){
//            isti++;
//        }
//
//    }
//
//    if(isti>1){
//        max=0;
//        for(i=0; i<n; i++){
//            sumPregledi=0;
//            for(j=0; j<doktor[i].brPacienti; j++){
//                sumPregledi+=doktor[i].pacienti[j].brPregledi;
//            }
//
//            if(sumPregledi>max){
//                max=sumPregledi;
//                najdobarI=i;
//                vkSum=(doktor[i].brPacienti)*(doktor[i].cena);
//            }
//        }
//    }
    
    int i, j, maxI=0, vkPregledi=0, br=0, max2=0;
    float sum1, temp1, max=0, sum2=0;
    char najdoktor[100];
    
    for(i=0; i<n; i++){
        sum1=0;
        sum2=0;
        temp1=0;
        br=0;
        for(j=0; j<doktor[i].brPacienti; j++){
            if(doktor[i].pacienti[j].osiguran==0){
                sum1+=doktor[i].pacienti[j].brPregledi;
                br++;
            }
            sum2+=doktor[i].pacienti[j].brPregledi;
        }
        
        temp1=sum1*doktor[i].cena;
        
        if(temp1>max){
            max=temp1;
            maxI=i;
            vkPregledi=sum2;
            if(br>0){
                strcpy(najdoktor, doktor[i].doktor);
            }
        }else if(temp1==max){
            if(sum2>vkPregledi){
                vkPregledi=sum2;
                strcpy(najdoktor, doktor[i].doktor);
            }
        }
    }
    
    printf("%s %.2f %d", najdoktor, doktor[maxI].brPacienti*doktor[maxI].cena, vkPregledi);
}

int main()
{
    int i, j, n;
    MaticenDoktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //ime na doktor
        scanf("%s", md[i].doktor);
        //broj na pacienti
        scanf("%d", &md[i].brPacienti);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].brPacienti; j++){
            scanf("%s", md[i].pacienti[j].pacient);
            scanf("%d", &md[i].pacienti[j].osiguran);
            scanf("%d", &md[i].pacienti[j].brPregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}
