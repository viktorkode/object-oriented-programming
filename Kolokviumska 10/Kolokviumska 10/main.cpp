#include <iostream>
#include <limits.h>
#include <cstring>
using namespace std;

typedef struct Igrac {
    char korisnickoIme[15];
    int igracNivo;
    int igracPoeni;
}Igrac;

typedef struct KompjuterskaIgra {
    char imeIgra[20];
    Igrac nizaIgraci[30];
    int brojIgraci;
}KompjuterskaIgra;

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int max=0;
    int maxI=0;
    char najdobraIgra[20];
    for(int i=0; i<n; i++){
        if(lista[i].brojIgraci>=max){
            max=lista[i].brojIgraci;
            maxI=i;
            strcpy(najdobraIgra, lista[i].imeIgra);
        }
    }
    
    int maxPoeni=0;
    int maxNivo;
    char korisnickoNajdobar[15];
    for(int i=0; i<lista[maxI].brojIgraci; i++){
        maxNivo=lista[maxI].nizaIgraci[0].igracPoeni;
        if(lista[maxI].nizaIgraci[i].igracPoeni>maxPoeni){
            maxPoeni=lista[maxI].nizaIgraci[i].igracPoeni;
            strcpy(korisnickoNajdobar, lista[maxI].nizaIgraci[i].korisnickoIme);
        }else if(lista[maxI].nizaIgraci[i].igracPoeni==maxPoeni && lista[maxI].nizaIgraci[i].igracNivo>=maxNivo){
            maxNivo=lista[maxI].nizaIgraci[i].igracNivo;
            strcpy(korisnickoNajdobar, lista[maxI].nizaIgraci[i].korisnickoIme);
        }
    }
    
//    max = 0
//
//    if igracPoeni >= max
//    max = igracPoeni
//
//    igracPoeni 5 >= 0
//    max = 5
//
//    igracPoeni 4 >= 5;
    
    cout << "Najdobar igrac e igracot so korisnicko ime " << korisnickoNajdobar << " koj ja igra igrata " << najdobraIgra;
}

int main(){
    int n;
    KompjuterskaIgra igri[100];
    
    cin>>n;
    
    for(int i=0; i<n; i++){
        cin>>igri[i].imeIgra;
        cin>>igri[i].brojIgraci;
        for(int j=0; j<igri[i].brojIgraci; j++){
            cin>>igri[i].nizaIgraci[j].korisnickoIme >> igri[i].nizaIgraci[j].igracNivo >> igri[i].nizaIgraci[j].igracPoeni;
        }
    }
    
    najdobarIgrac(igri, n);
    
    return 0;
}

//#include<iostream>
//using namespace std;
//
//struct Igrac {
//    char korisnickoIme[15];
//    int nivo;
//    int poeni;
//
//};
//struct KompjuterskaIgra {
//    char ime[20];
//    Igrac lista[30];
//    int n;
//};
//void najdobarIgrac(KompjuterskaIgra *igri,int n) {
//    int indeksNajmnoguIgraci=0;
//    for (int i=1; i<n; i++) {
//        if (igri[i].n>igri[indeksNajmnoguIgraci].n)
//            indeksNajmnoguIgraci=i;
//    }
//
//    KompjuterskaIgra najpopularna=igri[indeksNajmnoguIgraci];
//    int indeksmax=0;
//    for (int i=1; i<najpopularna.n; i++) {
//        if (najpopularna.lista[i].poeni>najpopularna.lista[indeksmax].poeni)
//            indeksmax=i;
//        else if (najpopularna.lista[i].poeni==najpopularna.lista[indeksmax].poeni) {
//            if (najpopularna.lista[i].nivo>najpopularna.lista[indeksmax].nivo)
//                indeksmax=i;
//        }
//    }
//    cout<<"Najdobar igrac e igracot so korisnicko ime ";
//    cout<<najpopularna.lista[indeksmax].korisnickoIme;
//    cout<<" koj ja igra igrata ";
//    cout<<najpopularna.ime;
//}
//int main() {
//    int n,m;
//    char ime[20];
//    cin>>n;
//    KompjuterskaIgra poleigri[100];
//    for (int i=0; i<n; i++) {
//        KompjuterskaIgra nova;
//        cin>>nova.ime>>nova.n;
//        Igrac pole[30];
//        for (int j=0; j<nova.n; j++) {
//            Igrac nov;
//            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
//            nova.lista[j]=nov;
//        }
//        poleigri[i]=nova;
//    }
//
//    najdobarIgrac(poleigri,n);
//    return 0;
//}
