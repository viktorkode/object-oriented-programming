#include <stdio.h>
#include <limits.h>
#include <string.h>

typedef struct Laptop {
    char firma[100];
    float monitorInchi;
    int touch;
    int cena;
}Laptop;

typedef struct ITStore {
    char prodavnica[100];
    char lokacija[100];
    Laptop dostapnost[100];
    int brojElementiNiza;
}ITStore;

void pecati (ITStore *prodavnica, int n){
    for(int i=0; i<n; i++){
        printf("%s %s\n", prodavnica[i].prodavnica, prodavnica[i].lokacija);
        for(int j=0; j<prodavnica[i].brojElementiNiza; j++){
            printf("%s %g %d\n", prodavnica[i].dostapnost[j].firma, prodavnica[i].dostapnost[j].monitorInchi, prodavnica[i].dostapnost[j].cena);
        }
    }
}

void najeftinaPonuda(ITStore *prodavnica, int n){
    int min=INT_MAX;
    char najeftinIme[100];
    char najeftinLokacija[100];
    for(int i=0; i<n; i++){
        for(int j=0; j<prodavnica[i].brojElementiNiza; j++){
            if(prodavnica[i].dostapnost[j].touch == 1 && prodavnica[i].dostapnost[j].cena<min){
                min=prodavnica[i].dostapnost[j].cena;
                strcpy(najeftinIme, prodavnica[i].prodavnica);
                strcpy(najeftinLokacija, prodavnica[i].lokacija);
            }
        }
    }
    
    printf("Najeftina ponuda ima prodavnicata: \n%s %s\n", najeftinIme, najeftinLokacija);
    printf("Najniskata cena iznesuva: %d", min);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d", &n); //broj na IT prodavnici
    
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0; i<n; i++){
        scanf("%s %s", s[i].prodavnica, s[i].lokacija);
        scanf("%d", &s[i].brojElementiNiza);
        
        for(int j=0; j<s[i].brojElementiNiza; j++){
            scanf("%s %f %d %d", s[i].dostapnost[j].firma, &s[i].dostapnost[j].monitorInchi, &s[i].dostapnost[j].touch, &s[i].dostapnost[j].cena);
        }
    }
    
    
    //pecatenje na site prodavnici
    pecati(s, n);
    
    //povik na glavnata metoda
    najeftinaPonuda(s, n);
    
    return 0;
}
