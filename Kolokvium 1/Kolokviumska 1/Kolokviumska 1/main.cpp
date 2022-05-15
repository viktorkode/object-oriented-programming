#include <iostream>
#include <cstring>
using namespace std;

enum tip{
    Pop, Rap, Rock
};

class Pesna {
private:
    char *ime;
    int vreme;
    tip tipPesna;
    
public:
    Pesna(){
        ime=NULL;
    }
    
    Pesna(char *ime, int vreme, tip tipPesna){ // Constructor
        this->ime=new char[strlen(ime)+1]; // Aloc na dyn memory
//        this->niza=new int[n] - Za niza
        strcpy(this->ime, ime);
        this->vreme=vreme;
        this->tipPesna=tipPesna;
    }
    ~Pesna(){ // Destruktor
        delete[] ime; // bez [] ako e 1 broj
    }
    
    Pesna (const Pesna &obj){ // Copy constructor
        this->ime=new char[strlen(obj.ime)+1];
        strcpy(ime, obj.ime);
        
        vreme=obj.vreme;
        tipPesna=obj.tipPesna;
    }
    
    Pesna& operator=(const Pesna &obj){ // Ednakvo operator
        if(this==&obj){
            return *this;
        }
        
        delete[] ime;
        
        ime=new char[strlen(obj.ime)+1];
        strcpy(ime, obj.ime);
        
        vreme=obj.vreme;
        tipPesna=obj.tipPesna;
        
        return *this;
    }
    
    void pecati(){
        cout << '"' << ime << '"' << "-" << vreme << "min"<<endl;
    }
    
//    int getMinuti(){
//        return vreme;
//    }
    
    friend class CD;
};

class CD {
    Pesna nizaPesni[10];
    int brojPesni;
    int maxVremetraenjeNaCD;
    
public:
    CD(){}
    
    CD(int maxVremetraenjeNaCD){
        this->maxVremetraenjeNaCD=maxVremetraenjeNaCD;
    }
    
    ~CD(){}
    
    CD (const CD &obj){
        for(int i=0; i<brojPesni;i++){
            nizaPesni[i]=obj.nizaPesni[i];
        }
        brojPesni=obj.brojPesni;
        maxVremetraenjeNaCD=obj.maxVremetraenjeNaCD;
    }
    
    void dodadiPesna(Pesna p){
        int sum=0;
        if(brojPesni<10){
            for(int i=0; i<brojPesni && sum<=maxVremetraenjeNaCD; i++){
                sum+=nizaPesni[i].vreme;
            }
            if(maxVremetraenjeNaCD-sum>=p.vreme){
                nizaPesni[brojPesni]=p;
                brojPesni++;
            }
        }
    }
    
    void pecatiPesniPoTip(tip t){
        for(int i=0; i<brojPesni; i++){
            if(nizaPesni[i].tipPesna == t){
                nizaPesni[i].pecati();
            }
        }
    }
    
    Pesna getPesna(int i){
        return nizaPesni[i];
    }
    
    int getBroj(){
        return brojPesni;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;
    
    int n, minuti, kojtip;
    char ime[50];
    
    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
            for (int i=0;i<n;i++){
                cin >> ime;
                cin >> minuti;
                cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
                Pesna p(ime,minuti,(tip)kojtip);
                omileno.dodadiPesna(p);
            }
            for (int i=0; i<n; i++)
                (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
            for (int i=0;i<n;i++){
                cin >> ime;
                cin >> minuti;
                cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
                Pesna p(ime,minuti,(tip)kojtip);
                omileno.dodadiPesna(p);
            }
            for (int i=0; i<omileno.getBroj(); i++)
                (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
            for (int i=0;i<n;i++){
                cin >> ime;
                cin >> minuti;
                cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
                Pesna p(ime,minuti,(tip)kojtip);
                omileno.dodadiPesna(p);
            }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
            
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
            for (int i=0;i<n;i++){
                cin >> ime;
                cin >> minuti;
                cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
                Pesna p(ime,minuti,(tip)kojtip);
                omileno.dodadiPesna(p);
            }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
            
    }
    
return 0;
}
