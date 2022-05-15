#include <iostream>
using namespace std;

// Dodadi

void dodadi(Gitara d){
    // Se kreira nova dinamicki aloc niza
    Gitara *temp = new Gitara[n+1];
    
    
    // Se vcituvaat starite elementi vo novata niza
    for(int i=0; i<n; i++){
        temp[i]=gitari[i];
    }
    
    
    // Se kazuva deka za n (posledniot element) vrednosta e taa sto e vnesena vo nizata
    temp[n]=d;
    
    // Se brise starata niza
    delete [] gitari;
    
    
    // n++ radi null terminatorot
    n++;
    
    // Starata niza = novata niza
    gitari=temp;
}

void prodadi(Gitara p){
    for(int i=0; i<n; i++){
        if(gitari[i].daliIsti(p)){
            for(int j=i; j<n-1; j++){
                gitari[j]=gitari[j+1];
            }
            n--;
            i--;
        }
    }
}

class Gitara {
private:
    int edna;
    char vtora[20];
    
public:
    // Default konstruktor
    Gitara(){}
    
    Gitara(int edna, char *vtora){
        
    }
    
    Gitara(const Gitara &obj){
        edna=obj.edna;...
    }
    
    Gitara &operator= (const Gitara &obj){
        if(this==&obj){
            return *this;
        }
        
        // Istoto od copy konstruktorot
        
        return *this;
    }
};

char *getIme(){
    return ime;
}

void setIme(char *ime){
    strcpy(this->ime, ime);
}

void setGodini(int godini){
    this->godini=godini;
}
