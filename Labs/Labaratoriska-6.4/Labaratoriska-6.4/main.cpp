#include <iostream>
#include <cstring>

using namespace std;

class Nedviznina {
protected:
    char *adresa;
    int kvadratura;
    int cenaKvadrat;
    
public:
    Nedviznina(){
        this->adresa=new char[0];
    }
    
    Nedviznina(char *adresa, int kvadratura, int cenaKvadrat){
        this->adresa=new char[strlen(adresa)+1];
        strcpy(this->adresa,adresa);
        this->kvadratura=kvadratura;
        this->cenaKvadrat=cenaKvadrat;
    }
    
    Nedviznina(const Nedviznina &obj){
        this->adresa=new char[strlen(obj.adresa)+1];
        strcpy(adresa, obj.adresa);
        kvadratura=obj.kvadratura;
        cenaKvadrat=obj.cenaKvadrat;
    }
    
    Nedviznina &operator= (const Nedviznina &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] adresa;
        this->adresa=new char[strlen(obj.adresa)+1];
        strcpy(adresa, obj.adresa);
        kvadratura=obj.kvadratura;
        cenaKvadrat=obj.cenaKvadrat;
        
        return *this;
    }
    
    ~Nedviznina(){
        delete [] adresa;
    }
    
    double cena(){
        return kvadratura*cenaKvadrat;
    }
    
    void pecati(){
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaKvadrat;
    }
    
    double danokNaImot(){
        return (cena()/100)*5;
    }
    
    char *getAdresa(){
        return adresa;
    }
    
    friend istream &operator>> (istream &in, Nedviznina &obj){
        in >> obj.adresa >> obj.kvadratura >> obj.cenaKvadrat;
        return in;
    }
};

class Vila : public Nedviznina {
private:
    int dnl;
public:
    Vila() : Nedviznina() {}
    
    Vila(char *adresa, int kvadratura, int cenaKvadrat, int dnl) : Nedviznina(adresa, kvadratura, cenaKvadrat){
        this->dnl=dnl;
    }
    
    friend istream &operator>> (istream &in, Vila &obj){
        in >> obj.adresa >> obj.kvadratura >> obj.cenaKvadrat >> obj.dnl;
        return in;
    }
    
    char *getAdresa(){
        return adresa;
    }
    
    void pecati(){
        Nedviznina::pecati();
        cout << ", Danok na luksuz: " << dnl <<endl;
    }
    
    double danokNaImot(){
        return Nedviznina::danokNaImot()+(cena()*dnl/100.0);
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<endl<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
