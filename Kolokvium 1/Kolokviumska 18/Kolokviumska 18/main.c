#include <stdio.h>

typedef struct SkiLift {
    char imeLift[15];
    int maxKorisnici;
    int funkcija;
}SkiLift;

typedef struct SkiCenter {
    char skiCenter[20];
    char drzava[20];
    SkiLift liftovi[20];
    int brLiftovi;
}SkiCenter;

void najgolemKapacitet(SkiCenter *sc, int n){
    int i, j, sumKapacitet=0, max=0, maxI=0, maxIL=0, maxLiftovi=0, br=0, funkLift=0;
    for(i=0; i<n; i++){
        sumKapacitet=0;
        for(j=0; j<sc[i].brLiftovi; j++){
            if(sc[i].liftovi[j].funkcija==1){
                sumKapacitet+=sc[i].liftovi[j].maxKorisnici;
                funkLift++;
            }
        }
        
        if(sumKapacitet>max){
            max=sumKapacitet;
            maxI=i;
        }else if(sumKapacitet==max){
            if(funkLift>maxLiftovi){
                maxLiftovi=funkLift;
                maxI=i;
            }
        }
    }
    
    printf("%s\n%s\n%d", sc[maxI].skiCenter, sc[maxI].drzava, max);
}

int main(){
    int n, i, j;
    SkiCenter info[100];
    
    scanf("%d", &n);
    
    for(i=0; i<n; i++){
        scanf("%s %s", info[i].skiCenter, info[i].drzava);
        scanf("%d", &info[i].brLiftovi);
        
        for(j=0; j<info[i].brLiftovi; j++){
            scanf("%s %d %d", info[i].liftovi[j].imeLift, &info[i].liftovi[j].maxKorisnici, &info[i].liftovi[j].funkcija);
        }
    }
    
    najgolemKapacitet(info, n);
}

//#include<stdio.h>
//#include<string.h>
//
//typedef struct SkiLift{
//    char ime[20];
//    int max_skijaci;
//    int voUpotreba;
//}skiLift;
//
//typedef struct SkiCenter {
//    char ime[20];
//    char drzava[20];
//    skiLift niza[20];
//    int br_lifts;
//}skiCenter;
//
//int kapacitet(skiCenter sc)
//{
//    int i;
//    int tmp = 0;
//    for (i = 0; i < sc.br_lifts; i++)
//    {
//        if (sc.niza[i].voUpotreba == 1)
//        {
//            tmp += sc.niza[i].max_skijaci;
//        }
//    }
//    return tmp;
//
//}
//void najgolemKapacitet(skiCenter *sc, int n)
//{
//    int tmp, i, j, max, max_ind;
//    max = 0;
//    max_ind = 0;
//    for (i = 0; i < n; i++)
//    {
//        tmp = kapacitet(sc[i]);
//        if ((tmp > max) || (tmp == max&&sc[i].br_lifts > sc[max_ind].br_lifts)) { max = tmp; max_ind = i; }
//    }
//    printf("%s\n%s\n%d\n", sc[max_ind].ime, sc[max_ind].drzava, max);
//}
//
//int main()
//{
//    int i, j, n, broj;
//    skiCenter sc[20];
//    scanf("%d", &n);
//    for (i = 0; i < n; i++){
//        //printf("Ime:");
//        scanf("%s", sc[i].ime);
//        //printf("\nDrzava:");
//        scanf("%s", sc[i].drzava);
//        scanf("%d", &sc[i].br_lifts);
//
//        for (j = 0; j < sc[i].br_lifts; j++){
//            scanf("%s", sc[i].niza[j].ime);
//            scanf("%d", &sc[i].niza[j].max_skijaci);
//            scanf("%d", &sc[i].niza[j].voUpotreba);
//        }
//    }
//    najgolemKapacitet(sc, n);
//
//    return 0;
//}
