#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
//       const static int pp;
   public:
    Karticka(){};
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
    virtual int tezinaProbivanje(){
        int br=0;
        int temp=pin;
        while(temp){
            br++;
            temp/=10;
        }
        
        return br;
    }
    
    friend ostream &operator<< (ostream &out, Karticka &k){
        out << k.smetka << ": " << k.tezinaProbivanje() << endl;
        
        return out;
    }
    
    char *getSmetka(){
        return smetka;
    }
    
    void setDopolnitelenPin(bool dpin){
        povekjePin=dpin;
    }
    
    bool getDopolnitelenPin(){
        return povekjePin;
    }
    
    virtual ~Karticka(){}
};

class OutOfBoundException {
public:
    void message(){
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class SpecijalnaKarticka : public Karticka{
private:
    int *pinovi;
    int n;
    const static int p;
    
public:
    SpecijalnaKarticka(){
        pinovi=0;
        n=0;
    }
    
    SpecijalnaKarticka(char *smetka, int pin) : Karticka(smetka, pin){
        this->pinovi=new int[0];
        this->n=0;
        povekjePin=true;
    }
    
    SpecijalnaKarticka(char *smetka, int pin, int *pinovi, int n) : Karticka(smetka, pin){
        this->pinovi=new int[n];
        for(int i=0; i<n; i++){
            this->pinovi[i]=pinovi[i];
        }
        this->n=n;
    }
    
    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+n;
    }
    
    SpecijalnaKarticka &operator+= (int pin){
        int flag=0;
        
        for(int i=0; i<n; i++){
            if(n>=p){
                throw OutOfBoundException();
            }
        }
        
        if(flag==0){
            int *temp=new int[n+1];
            for(int i=0; i<n; i++){
                temp[i]=pinovi[i];
            }
            temp[n]=pin;
            n++;
            delete [] pinovi;
            pinovi=temp;
        }
        
        return *this;
    }
    
    SpecijalnaKarticka &operator= (const SpecijalnaKarticka &s){
        if(this==&s){
            return *this;
        }
        
        delete [] pinovi;
        n=s.n;
        this->pinovi=new int[s.n];
        
        for(int i=0; i<s.n; i++){
            pinovi[i]=s.pinovi[i];
        }
        
        return *this;
    }
    
    friend ostream &operator<< (ostream &out, SpecijalnaKarticka &k){
        out << k.smetka << ": " << k.tezinaProbivanje() << endl;
        
        return out;
    }
    
    ~SpecijalnaKarticka(){
        delete [] pinovi;
    }
    
    
};

const int SpecijalnaKarticka::p=4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
    
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    
    static void setLIMIT(int limit){
        LIMIT=limit;
    }

    void pecatiKarticki(){
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite: " << endl;
        for(int i=0; i<broj; i++){
            if(karticki[i]->tezinaProbivanje()<=LIMIT){
                cout << *karticki[i];
            }
        }
    }
    
    void dodadiDopolnitelenPin(char *smetka, int novPin){
        for(int i=0; i<broj; i++){
            if(strcmp(smetka, karticki[i]->getSmetka())==0){
                SpecijalnaKarticka *pok=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(pok){
                    *pok+=novPin;
                }
            }
        }
    }
    
};

int Banka::LIMIT=7;

int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
//for (int i=0;i<n;i++) delete niza[i];
//delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;
   
   komercijalna.dodadiDopolnitelenPin(smetka,pin);
   
}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
