#include<iostream>
#include <cstring>
#include <limits.h>
using namespace std;

typedef struct Voz{
    char relacija[50];
    float pominatiKilometri;
    int brojPatnici;
}Voz;

typedef struct ZeleznickaStanica{
    char grad[20];
    Voz nizaVozovi[30];
    int brojVozovi;
}ZeleznickaStanica;

void najkratkaRelacija(ZeleznickaStanica*zStanica, int n, char* grad){
    int min=INT_MAX;
    char tempRelacija[50];
    for(int i=0; i<n; i++){
        if(strcmp(zStanica[i].grad, grad)==0){
            for(int j=0; j<zStanica[i].brojVozovi; j++){
                if(zStanica[i].nizaVozovi[j].pominatiKilometri <= min){
                    min=zStanica[i].nizaVozovi[j].pominatiKilometri;
                    strcpy(tempRelacija, zStanica[i].nizaVozovi[j].relacija);
                    
                }
            }
        }
    }
    
    cout << "Najkratka relacija: " << tempRelacija << " (" << min << " km)" << endl;
}

int main(){
    
    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    Voz voz;
    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>> zStanica[i].grad >> zStanica[i].brojVozovi;
        for(int j=0; j<zStanica[i].brojVozovi; j++){
            cin >> zStanica[i].nizaVozovi[j].relacija >> zStanica[i].nizaVozovi[j].pominatiKilometri >> zStanica[i].nizaVozovi[j].brojPatnici;
        }
    }
    
    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
