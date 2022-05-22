#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
protected:
    char ekipa[15];
    int porazi;
    int pobedi;
    
public:
    Ekipa(){}
    
    Ekipa(char ekipa[], int pobedi, int porazi){
        strcpy(this->ekipa, ekipa);
        this->porazi=porazi;
        this->pobedi=pobedi;
    }
    
    ~Ekipa(){}
    
    void pecati(){
        cout << "Ime: " << ekipa << " Pobedi: " << pobedi << " Porazi: " << porazi;
    }
};

class FudbalskaEkipa : public Ekipa {
private:
    int crveni;
    int zolti;
    int nereseni;
    
public:
    FudbalskaEkipa() : Ekipa() {}
    
    FudbalskaEkipa(char ekipa[], int pobedi, int porazi, int crveni, int zolti, int nereseni) : Ekipa(ekipa, pobedi, porazi){
        this->crveni=crveni;
        this->zolti=zolti;
        this->nereseni=nereseni;
    }
    
    void pecati(){
        Ekipa::pecati();
        int poeni=pobedi*3+nereseni*1;
        cout << " Nereseni: " << nereseni << " Poeni: " << poeni;
    }
};

int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
    f1.pecati();
    return 0;
}
