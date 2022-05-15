#include <iostream>
#include <cstring>
using namespace std;

typedef struct Tanc{
    char imeTanc[15];
    char zemja[15];
}Tanc;

typedef struct Tancer{
    char ime[20];
    char prezime[20];
    Tanc tanci[5];
}Tancer;

void tancuvanje(Tancer *t, int n, char *zemja){
    int brTanci=0;
    char temp[15];
    for(int i=0; i<n; i++){
        brTanci=0;
        for(int j=0; j<5; j++){
            if(strcmp(t[i].tanci[j].zemja,zemja)==0){
                brTanci++;
                strcpy(temp, t[i].tanci[j].imeTanc);
                break;
            }
        }
        if(brTanci>0){
            cout << t[i].ime << " " << t[i].prezime << ", " << temp << endl;
        }
    }
}

int main()
{
    int i, j, n;
    char zemja[15];
    Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tanceri[i].ime;
        cin >> tanceri[i].prezime;
        for(j = 0; j < 3; j++){
            cin >> tanceri[i].tanci[j].imeTanc;
            cin >> tanceri[i].tanci[j].zemja;
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
    return 0;
}
