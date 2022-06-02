#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool veteran;
    
public:
    Vozac(){}
    
    Vozac(char *ime, int vozrast, int trki, bool veteran) {
        strcpy(this->ime, ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->veteran=veteran;
    }
    
    friend ostream &operator<< (ostream &out, Vozac &v) {
        out<<v.ime << endl << v.vozrast << endl << v.trki << endl;
        if(v.veteran){
            out << "VETERAN" << endl;
        }
        
        return out;
    }
    
    bool operator== (Vozac &v) {
        if(zarabotuvacka()==v.zarabotuvacka()){
            return true;
        }else{
            return false;
        }
    }
    
    virtual float zarabotuvacka() = 0;
    virtual double danok() = 0;
};

class Avtomobilist : public Vozac {
private:
    float cenaKola;
    
public:
    Avtomobilist(){}
    
    Avtomobilist(char *ime, int vozrast, int trki, bool veteran, float cenaKola) : Vozac(ime, vozrast, trki, veteran) {
        this->cenaKola=cenaKola;
    }
    
    float zarabotuvacka(){
        return cenaKola/5;
    }
    
    double danok(){
        if(trki>10){
            return zarabotuvacka()/100*15;
        }else{
            return zarabotuvacka()/100*10;
        }
    }
};

class Motociklist : public Vozac {
private:
    int hp;
public:
    Motociklist(){}
    
    Motociklist(char *ime, int vozrast, int trki, bool veteran, int hp) : Vozac(ime, vozrast, trki, veteran) {
        this->hp=hp;
    }
    
    float zarabotuvacka(){
        return hp*20;
    }
    
    double danok(){
        if(veteran){
            return zarabotuvacka()/100*25;
        }else{
            return zarabotuvacka()/100*20;
        }
    }
};

int soIstaZarabotuvachka(Vozac** niza, int n, Vozac* v){
    int br=0;
    for(int i=0; i<n; i++){
        if(niza[i]->zarabotuvacka()==v->zarabotuvacka()){
            br++;
        }
    }
    
    return br;
}

// vashiot kod ovde

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
