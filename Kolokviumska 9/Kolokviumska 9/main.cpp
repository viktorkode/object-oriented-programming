#include <iostream>
#include <limits.h>
#include <cstring>
using namespace std;

typedef struct Laptop {
    char firma[100];
    float monitorInchi;
    bool touch;
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
        cout << prodavnica[i].prodavnica << " " << prodavnica[i].lokacija;
        for(int j=0; j<prodavnica[i].brojElementiNiza; j++){
            cout << prodavnica[i].dostapnost[j].firma << " " << prodavnica[i].dostapnost[j].monitorInchi << " " << prodavnica[i].dostapnost[j].cena;
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
    
    cout << "Najeftina ponuda ima prodavnicata: " << najeftinIme << " " << najeftinLokacija << endl;
    cout << "Najniskata cena iznesuva: " << min;
}

int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici
    
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0; i<n; i++){
        cin >> s[i].prodavnica >> s[i].lokacija;
        cin >> s[i].brojElementiNiza;
        
        for(int j=0; j<s[i].brojElementiNiza; j++){
            cin >> s[i].dostapnost[j].firma >> s[i].dostapnost[j].monitorInchi >> s[i].dostapnost[j].touch >> s[i].dostapnost[j].cena;
        }
    }
    
    
    //pecatenje na site prodavnici
    pecati(s, n);
    
    //povik na glavnata metoda
    najeftinaPonuda(s, n);
    
    return 0;
}

//Решение:
//
//#include <iostream>
//using namespace std;
//
//struct Laptop{
//    char firma[100];
//    float golemina;
//    bool touch;
//    int cena;
//
//    void print();
//
//};
//
//void Laptop::print(){
//    cout << firma << " " << golemina << " " << cena << endl;
//
//}
//
//struct ITStore{
//    char ime[100];
//    char lokacija[100];
//    Laptop lp[100];
//    int n;
//
//    void print();
//};
//
//void ITStore::print() {
//    cout << ime << " " << lokacija << endl;
//    for(int i = 0; i < n; i++){
//        lp[i].print();
//    }
//}
//
//int najmalaCena(ITStore its){
//    int min, f = 0;
//    for(int i = 0; i<its.n; i++){
//        if(its.lp[i].touch){
//            if(!f){
//                min = its.lp[i].cena;
//                f=1;
//            }
//            else if(its.lp[i].cena<min)
//                min = its.lp[i].cena;
//        }
//    }
//
//    return min;
//
//}
//
//void najeftina_ponuda(ITStore its[], int n){
//    int min = najmalaCena(its[0]);
//    int minI = 0;
//    for(int i = 0; i<n; i++){
//        if(najmalaCena(its[i]) < min){
//            min = najmalaCena(its[i]);
//            minI = i;
//        }
//    }
//
//    cout << "Najeftina ponuda ima prodavnicata: " << endl;
//    cout << its[minI].ime << " " << its[minI].lokacija << endl;
//    cout << "Najniskata cena iznesuva: " << najmalaCena(its[minI]) << endl;
//}
//
//
//int main() {
//    ITStore s[100];
//    int n;
//    cin >> n; //broj na IT prodavnici
//
//    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
//    for(int i = 0; i < n; i++){
//        cin >> s[i].ime;
//        cin >> s[i].lokacija;
//        cin >> s[i].n;
//            for(int j = 0; j < s[i].n; j++){
//                cin >> s[i].lp[j].firma;
//                cin >> s[i].lp[j].golemina;
//                cin >> s[i].lp[j].touch;
//                cin >> s[i].lp[j].cena;
//        }
//
//    }
//
//
//    //pecatenje na site prodavnici
//
//    for(int i = 0; i<n; i++){
//        s[i].print();
//    }
//
//
//    //povik na glavnata metoda
//
//    najeftina_ponuda(s,n);
//
//    return 0;
//}
