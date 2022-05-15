#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasaVagon;
    bool velosiped;
public:
    Patnik(){}
    
    Patnik(char *ime, int klasaVagon, bool velosiped){
        strcpy(this->ime,ime);
        this->klasaVagon=klasaVagon;
        this->velosiped=velosiped;
    }
    
    Patnik(const Patnik &obj){
        strcpy(ime, obj.ime);
        klasaVagon=obj.klasaVagon;
        velosiped=obj.velosiped;
    }
    
    Patnik &operator= (const Patnik &obj){
        if(this==&obj){
            return *this;
        }
        strcpy(ime, obj.ime);
        klasaVagon=obj.klasaVagon;
        velosiped=obj.velosiped;
        
        return *this;
    }
    
    friend ostream &operator<< (ostream &output, const Patnik &p){
        return output<<p.ime<<endl<<p.klasaVagon<<endl<<p.velosiped<<endl;
    }
    
    bool getBike(){
        return velosiped;
    }
    
    int getKlasa(){
        return klasaVagon;
    }
};

class Voz{
private:
    char destinacija[100];
    Patnik *nizaP;
    int n;
    int maxVelosipedi;
public:
    Voz(){
        nizaP=NULL;
        n=0;
    }
    
    Voz(char *destinacija, int maxVelosipedi){
        n=0;
        strcpy(this->destinacija,destinacija);
        this->nizaP=new Patnik[n];
        this->maxVelosipedi=maxVelosipedi;
        for(int i=0; i<n; i++){
            this->nizaP[i]=nizaP[i];
        }
    }
    
    Voz(const Voz &obj){
        n=obj.n;
        strcpy(destinacija,obj.destinacija);
        this->nizaP=new Patnik[obj.n];
        this->maxVelosipedi=obj.maxVelosipedi;
        for(int i=0; i<obj.n; i++){
            this->nizaP[i]=obj.nizaP[i];
        }
    }
    
    Voz &operator= (const Voz &obj){
        if(this==&obj){
            return *this;
        }
        delete [] nizaP;
        
        n=obj.n;
        strcpy(destinacija,obj.destinacija);
        this->nizaP=new Patnik[obj.n];
        this->maxVelosipedi=obj.maxVelosipedi;
        for(int i=0; i<obj.n; i++){
            this->nizaP[i]=obj.nizaP[i];
        }
        
        return *this;
    }
    
    ~Voz(){
        delete [] nizaP;
    }
    
    // Dodatni operatori
    Voz &operator +=(const Patnik &p){
    int br_bikes=0;
    Patnik *temp=new Patnik [n+1];
    for(int i=0;i<n;i++){
        temp[i]=nizaP[i];
        if(temp[i].getBike()==1) br_bikes++;
    }
    temp[n]=p;
        n++;
    delete [] nizaP;
    nizaP=temp;
    return *this;
    }

    friend ostream & operator<<(ostream &output, const Voz &voz){
    output<<voz.destinacija<<endl;
    for(int i=0;i<voz.n;i++){
        if(voz.maxVelosipedi>0) output<<voz.nizaP[i]<<endl;
        else {
            if(voz.nizaP[i].getBike()==0) output<<voz.nizaP[i]<<endl;
        }
    }
    return output;
    }
    
    void patniciNemaMesto(){
        int prva=0, vtora=0;
        for(int i=0; i<n; i++){
            if(nizaP[i].getBike()){
                if(nizaP[i].getKlasa()==1){
                    prva++;
                }else if(nizaP[i].getKlasa()==2){
                    vtora++;
                }
            }
        }
        
        int ost1=0;
        int ost2=0;
        
        if(prva+vtora<=maxVelosipedi || maxVelosipedi==0){
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
            cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
        }
        else if(prva+vtora>maxVelosipedi){
            if(prva<=maxVelosipedi){
                ost2=maxVelosipedi-(prva+vtora);
                cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<(prva+vtora)-maxVelosipedi<<endl;
            }
            else if(prva>maxVelosipedi){
                ost1=(prva+vtora)-maxVelosipedi;
                
                cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<prva-maxVelosipedi<<endl;
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<vtora<<endl;
            }
        }
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
