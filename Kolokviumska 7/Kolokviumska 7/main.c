#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct Vozenje {
    char imeVozenje[100];
    int vremetraenje;
    float cena;
    int popust;
}Vozenje;

typedef struct ZabavenPark {
    char imePark[100];
    char lokacijaPark[100];
    Vozenje adrenalinkskiVozenje[100];
    int nElementi;
}ZabavenPark;

void najdobarPark(ZabavenPark *info, int n){
//    int max=0, suma=0, i, j, sumaVremetraenje=0, maxVremetraenje=0;
//    char najeftinIme[100], najeftinLokacija[100];
//    int maxI=0;
    
    int maxI=0, i, j, sumPopusti=0, sumVreme=0, maxPopusti=0, maxVreme=0;
    
    for(i=0; i<n; i++){
        sumPopusti=0;
        sumVreme=0;
        
        for(j=0; j<info[i].nElementi; j++){
            if(info[i].adrenalinkskiVozenje[j].popust==1){
                sumPopusti++;
            }
            sumVreme+=info[i].adrenalinkskiVozenje[j].vremetraenje;
        }
        
        if(sumPopusti>maxPopusti){
            maxPopusti=sumPopusti;
            maxI=i;
            maxVreme=sumVreme;
        }else if(sumPopusti==maxPopusti){
            if(sumVreme>maxVreme){
                maxVreme=sumVreme;
                maxI=i;
            }else if(sumVreme==maxVreme){
                maxI=i;
            }
        }
    }
    printf("Najdobar park: %s %s", info[maxI].imePark, info[maxI].lokacijaPark);
}
    
//    for(i=0; i<n; i++){
//        suma=0;
//        sumaVremetraenje=0;
//        for(j=0; j<info[i].nElementi; j++){
//            if(info[i].adrenalinkskiVozenje[j].popust==1){
//                suma++;
//                sumaVremetraenje+=info[i].adrenalinkskiVozenje[j].vremetraenje;
//            }
//        }
//
//        if(suma>max){
//            max=suma;
//            maxI=i;
//        }else if(suma==max){
//            if(sumaVremetraenje>maxVremetraenje){
//                maxVremetraenje=sumaVremetraenje;
//                maxI=i;
//            }
//        }
//    }
//
//    printf("Najdobar park: %s %s", info[maxI].imePark, info[maxI].lokacijaPark);

void print(ZabavenPark *info, int n){
    int i, j;
    for(i=0; i<n; i++){
        printf("%s %s\n", info[i].imePark, info[i].lokacijaPark);
        
        for(j=0; j<info[i].nElementi; j++){
            printf("%s %d %.2f\n", info[i].adrenalinkskiVozenje[j].imeVozenje, info[i].adrenalinkskiVozenje[j].vremetraenje, info[i].adrenalinkskiVozenje[j].cena);
        }
    }
}

int main(){
    int n, i, j;
    scanf("%d", &n);
    
    ZabavenPark vnesi[100];
    for(i=0; i<n; i++){
        scanf("%s %s", vnesi[i].imePark, vnesi[i].lokacijaPark);
        scanf("%d", &vnesi[i].nElementi);
        
        for(j=0; j<vnesi[i].nElementi; j++){
            scanf("%s", vnesi[i].adrenalinkskiVozenje[j].imeVozenje);
            scanf("%d %f %d", &vnesi[i].adrenalinkskiVozenje[j].vremetraenje, &vnesi[i].adrenalinkskiVozenje[j].cena, &vnesi[i].adrenalinkskiVozenje[j].popust);
        }
    }
    
    print(vnesi, n);
    najdobarPark(vnesi, n);
    
    return 0;
}
