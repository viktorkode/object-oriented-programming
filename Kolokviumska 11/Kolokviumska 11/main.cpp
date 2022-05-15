#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
private:
    char *ime;
    bool pol;
    int vozrast;
    
public:
    Ucesnik(){
        ime=NULL;
    }
    
    Ucesnik(char *ime, bool pol, int vozrast){
        this->pol=pol;
        this->vozrast=vozrast;
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
    }
    
    Ucesnik(const Ucesnik &obj){
        pol=obj.pol;
        vozrast=obj.vozrast;
        this->ime=new char[strlen(obj.ime)+1];
        strcpy(ime, obj.ime);
    }
    
    Ucesnik &operator= (const Ucesnik &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] ime;
        
        pol=obj.pol;
        vozrast=obj.vozrast;
        this->ime=new char[strlen(obj.ime)+1];
        strcpy(ime, obj.ime);
        
        return *this;
    }
    
    ~Ucesnik(){}
    
    bool operator >(Ucesnik &u){
        if(this->vozrast>u.vozrast){
            return true;
        }
        else{
            return false;
        }
    }
    
    friend ostream & operator<<(ostream &out, Ucesnik &u){
        out<<u.ime<<endl;
        if(u.pol==0) out<<"zhenski"<<endl;
        else out<<"mashki"<<endl;
        out<<u.vozrast<<endl;
        return out;
    }
    
    int getVozrast(){
        return vozrast;
    }
};

class Maraton {
private:
    char lokacija[100];
    Ucesnik *ucesnik;
    int brojUcesnici;
    
public:
    Maraton(){
        ucesnik=NULL;
    }
    
    Maraton(char *lokacija){
        brojUcesnici=0;
        strcpy(this->lokacija, lokacija);
        this->ucesnik=new Ucesnik[brojUcesnici+1];
        for(int i=0; i<brojUcesnici; i++){
            this->ucesnik[i]=ucesnik[i];
        }
    }
    
    Maraton(const Maraton &obj){
        brojUcesnici=obj.brojUcesnici;
        strcpy(lokacija, obj.lokacija);
        this->ucesnik= new Ucesnik[obj.brojUcesnici+1];
        for(int i=0; i<obj.brojUcesnici; i++){
            ucesnik[i]=obj.ucesnik[i];
        }
    }
    
    Maraton &operator= (const Maraton &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] ucesnik;
        
        brojUcesnici=obj.brojUcesnici;
        strcpy(lokacija, obj.lokacija);
        this->ucesnik= new Ucesnik[obj.brojUcesnici+1];
        for(int i=0; i<obj.brojUcesnici; i++){
            ucesnik[i]=obj.ucesnik[i];
        }
        
        return *this;
    }
    
    ~Maraton(){}
    
    Maraton & operator+=(Ucesnik &u){
        Ucesnik *temp=new Ucesnik[brojUcesnici+1];
        for(int i=0;i<brojUcesnici;i++){
            temp[i]=ucesnik[i];
        }
        temp[brojUcesnici]=u;
        brojUcesnici++;
        //delete [] niza;
        ucesnik=temp;
        return *this;
    }
    
    void pecatiPomladi (Ucesnik &u){
        for(int i=0; i<brojUcesnici; i++){
            if(ucesnik[i].getVozrast()<u.getVozrast()){
                cout << ucesnik[i];
            }
        }
    }
    
    float prosecnoVozrast(){
        float sumV=0;
        for(int i=0; i<brojUcesnici; i++){
            sumV+=ucesnik[i].getVozrast();
        }
        
        return sumV/(float)brojUcesnici;
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
