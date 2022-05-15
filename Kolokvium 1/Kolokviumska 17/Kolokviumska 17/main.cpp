#include <iostream>
#include <cstring>
using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *ime_os;
    float verzija;
    Tip tip;
    float golemina;
    
public:
    // Default konstruktor
    OperativenSistem(){
        ime_os=NULL;
        verzija=0;
        golemina=0;
    }
    
    // Konstruktor so parametri
    OperativenSistem(char *ime_os, float verzija, Tip tip, float golemina){
        this->ime_os=new char[strlen(ime_os)+1];
        strcpy(this->ime_os, ime_os);
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
    }
    
    // Copy konstruktor
    OperativenSistem(const OperativenSistem &obj){
        this->ime_os=new char[strlen(obj.ime_os)+1];
        strcpy(ime_os, obj.ime_os);
        
        verzija=obj.verzija;
        tip=obj.tip;
        golemina=obj.golemina;
    }
    
    ~OperativenSistem(){
        delete [] ime_os;
    }
    
    OperativenSistem & operator=(const OperativenSistem &obj){
        if(this==&obj){
            return *this;
        }
        delete [] ime_os;
        this->ime_os=new char[strlen(obj.ime_os)+1];
        strcpy(ime_os, obj.ime_os);
        
        verzija=obj.verzija;
        tip=obj.tip;
        golemina=obj.golemina;
        
        return *this;
    }
    
    bool ednakviSe(const OperativenSistem &os){
        if(strcmp(ime_os, os.ime_os)==0 && verzija==os.verzija && tip==os.tip && golemina==os.golemina){
            return true;
        }
        
        return false;
    }
    
    bool istaFamilija(const OperativenSistem &sporedba){
        if(strcmp(ime_os, sporedba.ime_os)==0 && tip==sporedba.tip){
            return true;
        }
        
        return false;
    }
    
    int sporediVerzija(const OperativenSistem &os){
        if(verzija==os.verzija){
            return 0;
        }else if(os.verzija>verzija){
            return -1;
        }else{
            return 1;
        }
    }
    
    void pecati(){
        cout << "Ime: " << ime_os;
        cout << " Verzija: " << verzija;
        cout << " Tip: " << tip;
        cout << " Golemina:" << golemina << "GB" << endl;
    }
    
};

class Repozitorium {
private:
    char repoIme[20]; // IME
    OperativenSistem *nizaOS; // NIZA
    int brojOSvoREPO; // N
    
public:
    Repozitorium(const char *ime){
        strcpy(this->repoIme, ime);
        brojOSvoREPO=0;
        nizaOS=NULL;
    }
    
    ~Repozitorium(){
        delete [] nizaOS;
    }
    
    Repozitorium(const Repozitorium &obj){
        strcpy(this->repoIme, obj.repoIme);
        this->nizaOS=new OperativenSistem[obj.brojOSvoREPO];
        for(int i=0; i<obj.brojOSvoREPO; i++){
            nizaOS[i]=obj.nizaOS[i];
        }
        
        brojOSvoREPO=obj.brojOSvoREPO;
    }
    
    Repozitorium &operator= (const Repozitorium &obj){
        if(this==&obj){
            return *this;
        }
        delete [] nizaOS;
        strcpy(this->repoIme, obj.repoIme);
        this->nizaOS=new OperativenSistem[obj.brojOSvoREPO];
        for(int i=0; i<obj.brojOSvoREPO; i++){
            nizaOS[i]=obj.nizaOS[i];
        }
        
        brojOSvoREPO=obj.brojOSvoREPO;
        
        return *this;
    }
    
    void izbrishi(const OperativenSistem &operativenSistem){
        int brojac=0;
        for(int i=0; i<brojOSvoREPO; i++){
            if(nizaOS[i].ednakviSe(operativenSistem)==false){
                brojac++;
            }
        }
        OperativenSistem *temp=new OperativenSistem[brojac];
        int j=0;
        for(int i=0; i<brojOSvoREPO; i++){
            if(nizaOS[i].ednakviSe(operativenSistem)==false){
                temp[j++]=nizaOS[i];
            }
        }
        delete [] nizaOS;
        nizaOS=temp;
        brojOSvoREPO=brojac;
    }
    
    void dodadi(const OperativenSistem &nov){
        int flag=0, j=0;
        for(int i=0; i<brojOSvoREPO; i++){
            if(nizaOS[i].istaFamilija(nov)==true && nizaOS[i].sporediVerzija(nov)==-1){
                nizaOS[i]=nov;
                flag=1;
            }
        }
        if(flag==0){
            OperativenSistem *temp=new OperativenSistem[brojOSvoREPO+1];
            for(int i=0; i<brojOSvoREPO; i++){
                temp[j++]=nizaOS[i];
            }
            delete [] nizaOS;
            temp[brojOSvoREPO++]=nov;
            nizaOS=temp;
        }
    }
    
    void pecatiOperativniSistemi(){
        cout << "Repozitorium: " << repoIme << endl;
        for(int i=0; i<brojOSvoREPO; i++){
            nizaOS[i].pecati();
        }
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
