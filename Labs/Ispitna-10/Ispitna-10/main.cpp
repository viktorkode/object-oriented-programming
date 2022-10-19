#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class Oglas {
protected:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena;
    
public:
    Oglas(){}
    Oglas(char *naslov, char *kategorija, char *opis, double cena){
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena=cena;
    }
    
    friend ostream &operator<< (ostream &out, Oglas &o){
        
        out << o.naslov << endl << o.opis << endl << o.cena << " evra" << endl;
        return out;
    }
    
    bool operator > (const Oglas &o){
        if(cena>o.cena){
            return 1;
        }else{
            return 0;
        }
    }
    
    double getCena(){
        return cena;
    }
    
    char *getCat(){
        return kategorija;
    }
};

class NegativnaVrednost {
public:
    void message(){
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *oglasi;
    int n;
    
public:
    Oglasnik(){
        this->oglasi=new Oglas[0];
        n=0;
    }
    Oglasnik(char *ime){
        this->n=0;
        strcpy(this->ime, ime);
        this->oglasi=new Oglas[0];
    }
    
    Oglasnik(char *ime, Oglas *oglasi, int n){
        this->oglasi= new Oglas[n];
        strcpy(this->ime, ime);
        this->n=n;
        for(int i=0; i<n; i++){
            this->oglasi[i]=oglasi[i];
        }
    }
    
    Oglasnik(const Oglasnik &cpy){
        strcpy(ime, cpy.ime);
        n=cpy.n;
        
        this->oglasi= new Oglas[cpy.n];
        for(int i=0; i<n; i++){
            oglasi[i]=cpy.oglasi[i];
        }
    }
    
    Oglasnik &operator= (const Oglasnik &obj){
        if(this==&obj){
            return *this;
        }
        
        strcpy(ime, obj.ime);
        n=obj.n;
        
        delete [] oglasi;
        
        this->oglasi= new Oglas[obj.n];
        
        for(int i=0; i<n; i++){
            oglasi[i]=obj.oglasi[i];
        }
        
        return *this;
    }
    
    ~Oglasnik(){
        delete [] oglasi;
    }
    
    // ETC
    
    Oglasnik &operator += (Oglas &from){
        
        int flag=0;
        if(from.getCena()<0){
            flag=1;
            throw NegativnaVrednost();
        }
        
        if(flag==0){
            Oglas *temp = new Oglas[n+1];
            for(int i=0; i<n; i++){
                temp[i]=oglasi[i];
            }
            
            temp[n++] = from;
            delete [] oglasi;
            oglasi=temp;
        }
        
        return *this;
    }
    
    friend ostream &operator << (ostream &out, Oglasnik &o){
        
        out << o.ime << endl;
        for(int i=0; i<o.n; i++){
            out << o.oglasi[i] << endl;
        }
        
        return out;
    }
    
    void oglasiOdKategorija(const char *k){
        for(int i=0; i<n; i++){
            if(strcmp(oglasi[i].getCat(), k)==0){
                cout << oglasi[i] << endl;
            }
        }
    }
    
    void najniskaCena(){
        int min=99999;
        int indeks=0;
        
        for(int i=0; i<n; i++){
            if(oglasi[i].getCena()<min){
                min=oglasi[i].getCena();
                indeks=i;
            }
        }
        
        cout << oglasi[indeks] << endl;
    }
};

// MAIN
int main(){
    
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;
    
    int tip;
    cin>>tip;
    
    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            
            try{
                ogl+=o;
            }catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
          cout<<"-----Test oglasOdKategorija -----" <<endl ;
          cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            
            try{
                ogl+=o;
            }catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
          ogl.oglasiOdKategorija(k);
    
    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
          cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            
            try{
            ogl+=o;
            }catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    
    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
          cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
          ogl.najniskaCena();
    
    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
          cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
        
        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
          ogl.oglasiOdKategorija(k);
        
        cout<<"Oglas so najniska cena:"<<endl;
          ogl.najniskaCena();
    
    }
    
    return 0;
}
