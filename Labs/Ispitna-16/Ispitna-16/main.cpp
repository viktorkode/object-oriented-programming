#include <iostream>
#include <cstring>

using namespace std;

class Transport {
private:
    char *destinacija;
    int cena;
    int rastojanie;
    
public:
    Transport(){
        this->destinacija=new char[0];
    }
    Transport(char *destinacija, int cena, int rastojanie) {
        this->destinacija=new char[strlen(destinacija)+1];
        strcpy(this->destinacija, destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }
    
    Transport(const Transport &obj) {
        this->destinacija=new char[strlen(obj.destinacija)+1];
        strcpy(this->destinacija, obj.destinacija);
        this->cena=obj.cena;
        this->rastojanie=obj.rastojanie;
    }
    
    Transport &operator= (const Transport &obj) {
        if(this==&obj){
            return *this;
        }
        
        delete [] destinacija;
        
        this->destinacija=new char[strlen(obj.destinacija)+1];
        strcpy(this->destinacija, obj.destinacija);
        this->cena=obj.cena;
        this->rastojanie=obj.rastojanie;
        
        return *this;
    }
    
    virtual ~Transport(){
        delete [] destinacija;
    }
    
    virtual void setDestinacija(char *dest){
        destinacija=dest;
    }
    
    virtual void setCena(int cen){
        cena=cen;
    }
    
    virtual void setRastojanie(int rast){
        rastojanie=rast;
    }
    
    int getCena(){
        return cena;
    }
    
    int getRastojanie(){
        return rastojanie;
    }
    
    char *getDestinacija(){
        return destinacija;
    }
    
    virtual int cenaTransport(){
        return cena;
    }
    
    bool operator < (Transport &t){
        if(getRastojanie()<t.getRastojanie()){
            return true;
        }else{
            return false;
        }
    }
    
    friend ostream &operator<< (ostream &out, Transport &t) {
        out << t.destinacija << " " << t.rastojanie << " " << t.cenaTransport() << endl;
        return out;
    }
};

class AvtomobilTransport : public Transport {
    bool soferA;
    
public:
    AvtomobilTransport(char *destinacija, int cena, int rastojanie, bool soferA) : Transport(destinacija, cena, rastojanie) {
        this->soferA=soferA;
    }
    
    void setSofer(bool s1){
        soferA=s1;
    }
    
    int cenaTransport(){
        int price=getCena();
        
        if(soferA==true){
            price+=price/100*20;
        }else{
            return price;
        }
        
        return price;
    }
    
    friend ostream &operator<< (ostream &out, AvtomobilTransport &a) {
        out << a.getDestinacija() << " " << a.getCena() << " " << a.getRastojanie() << endl;
        return out;
    }
};

class KombeTransport : public Transport{
    bool soferB;
    int lugje;
    
public:
    KombeTransport(char *destinacija, int cena, int rastojanie, int lugje) : Transport(destinacija, cena, rastojanie) {
        this->lugje=lugje;
    }
    
    KombeTransport(char *destinacija, int cena, int rastojanie, bool soferB, int lugje) : Transport(destinacija, cena, rastojanie) {
        this->soferB=soferB;
        this->lugje=lugje;
    }
    
    void setSofer(bool s2){
        soferB=s2;
    }
    
    void setLugje(int l){
        lugje=l;
    }
    
    int cenaTransport(){
        int price=getCena();
        price=price-(lugje*200);
        
        return price;
    }
    
    friend ostream &operator<< (ostream &out, KombeTransport &k) {
        out << k.getDestinacija() << " " << k.getCena() << " " << k.getRastojanie() << endl;
        return out;
    }
};

void sort(Transport **niza, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++){
            if(*niza[j+1]<*niza[j]){
                Transport *temp=niza[j];
                niza[j]=niza[j+1];
                niza[j+1]=temp;
            }
        }
    }
}

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport ponuda){
    sort(ponudi, n);
    for(int i=0; i<n; i++){
        if(ponuda.getCena() < ponudi[i]->getCena()){
            cout << *ponudi[i];
        }
    }
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
