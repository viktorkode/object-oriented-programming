#include <iostream>
#include <cstring>
using namespace std;

class Pica {
private:
    char imePica[15];
    int cenaPica;
    char *sostojkiPica;
    int popustPica;
    
public:
    Pica(){
        cenaPica=0;
        sostojkiPica=NULL;
        popustPica=0;
    }
    
    Pica(char * imePica, int cenaPica, char * sostojkiPica, int popustPica){
        strcpy(this->imePica, imePica);
        this->cenaPica=cenaPica;
        this->sostojkiPica=new char [strlen(sostojkiPica)+1];
        strcpy(this->sostojkiPica, sostojkiPica);
        this->popustPica=popustPica;
    }
    
    ~Pica(){
        delete [] sostojkiPica;
    }
    
    Pica(const Pica &obj){
        strcpy(imePica, obj.imePica);
        cenaPica=obj.cenaPica;
        sostojkiPica=new char [strlen(obj.sostojkiPica)+1];
        strcpy(sostojkiPica, obj.sostojkiPica);
        popustPica=obj.popustPica;
    }
    
    Pica &operator= (const Pica &obj){
        if(this==&obj){
            return * this;
        }
        delete [] sostojkiPica;
        
        strcpy(imePica, obj.imePica);
        cenaPica=obj.cenaPica;
        sostojkiPica=new char [strlen(obj.sostojkiPica)+1];
        strcpy(sostojkiPica, obj.sostojkiPica);
        popustPica=obj.popustPica;
        
        return * this;
    }
    
    void pecati(){
        cout << imePica << " - " << sostojkiPica << ", " << cenaPica;
    }
    
    bool istiSe(Pica p){
        if(strcmp(sostojkiPica, p.sostojkiPica)==0){
            return true;
        }else{
            return false;
        }
    }
    
    int getPopust(){
        return popustPica;
    }
    
    int getCena(){
        return cenaPica;
    }
    
};

class Picerija {
private:
    char imePicerija[15];
    Pica *nizaPici;
    int nPici;
    
public:
    Picerija(){
        nizaPici=NULL;
        nPici=0;
    }
    
    Picerija(char *imePicerija){
        strcpy(this->imePicerija, imePicerija);
        nPici=0;
        nizaPici=NULL;
    }
    
    ~Picerija(){
        delete [] nizaPici;
    }
    
    Picerija(const Picerija &obj){
        strcpy(imePicerija, obj.imePicerija);
        nPici=obj.nPici;
        this->nizaPici=new Pica[nPici];
        for(int i=0; i<nPici; i++){
            nizaPici[i]=obj.nizaPici[i];
        }
    }
    
    Picerija &operator= (const Picerija &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] nizaPici;
        
        strcpy(imePicerija, obj.imePicerija);
        nPici=obj.nPici;
        this->nizaPici=new Pica[nPici];
        for(int i=0; i<nPici; i++){
            nizaPici[i]=obj.nizaPici[i];
        }
        
        return *this;
    }
    
    Picerija &operator+= (Pica p){
        int flag=0;
        for(int i=0;i<nPici;i++)
        {
            if(this->nizaPici[i].istiSe(p)==true) flag=1;

        }
        if(!flag)
        {
            Pica *temp=new Pica[nPici+1];
            for(int i=0;i<nPici;i++)
            {
                temp[i]=nizaPici[i];
            }
            temp[nPici]=p;
            nPici++;
            delete [] nizaPici;
            nizaPici=temp;
        }
        return *this;
    }
    
    void dodadi(Pica p){
        int flag=0;
        for(int i=0; i<nPici; i++){
            if(nizaPici[i].istiSe(p)){
                flag=1;
            }
        }
        if(flag==0){
            Pica *temp=new Pica[nPici+1];
            
            for(int i=0; i<nPici; i++){
                temp[i]=nizaPici[i];
            }
            
            delete [] nizaPici;
            temp[nPici]=p;
            nPici++;
            
            nizaPici=temp;
        }
    }
    
    void piciNaPromocija(){
        for(int i=0; i<nPici; i++){
            if(nizaPici[i].getPopust()>0 && nizaPici[i].getPopust()<=100){
                nizaPici[i].pecati();
                int cenaSoPopust=(nizaPici[i].getCena()/100.0)*nizaPici[i].getPopust();
                cout << " " << nizaPici[i].getCena()-cenaSoPopust << endl;
            }
        }
    }
    
    char *getIme(){
        return imePicerija;
    }
    
    void setIme(char *ime){
        strcpy(imePicerija, ime);
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
