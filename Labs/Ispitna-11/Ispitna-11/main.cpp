#include<iostream>
#include<string.h>
using namespace std;

class Delo {
private:
    char ime[50];
    int godina;
    char zemja[50];
    
public:
    Delo(){}
    Delo(char *ime, int godina, char *zemja){
        strcpy(this->ime, ime);
        this->godina=godina;
        strcpy(this->zemja, zemja);
    }
    
    bool operator == (Delo &d){
        if(strcmp(ime, d.ime)==0){
            return 1;
        }else{
            return 0;
        }
    }
    
    int getGodina(){
        return godina;
    }
    
    char *getZemja(){
        return zemja;
    }
    
    char *getIme(){
        return ime;
    }
};

class Pretstava {
private:
    Delo delo;
    int n;
    char data[15];
    
public:
    Pretstava(){}
    Pretstava(Delo delo, int n, char *data){
        this->delo=delo;
        this->n=n;
        strcpy(this->data, data);
    }
    
    virtual double cena(){
    int N, M;
        if(delo.getGodina() >= 1900 ){
            M=50;
        }else if(delo.getGodina() < 1800){
            M=100;
        }else{
            M=75;
        }
        
        if(strcmp(delo.getZemja(), "Rusija")==0){
            N=150;
        }else if(strcmp(delo.getZemja(), "Italija")==0){
            N=100;
        }else{
            N=80;
        }
        
        return N+M;
    }
    
    int getBrojKarti(){
        return n;
    }
    
    Delo getDelo(){
        return delo;
    }
};

class Balet : public Pretstava {
private:
    static double price;
    
public:
    Balet() : Pretstava() {}
    Balet(Delo delo, int n, char *data) : Pretstava(delo, n, data) {}
    
    double cena(){
        return Pretstava::cena() + price;
    }
    
    static void setCenaBalet(double cenaBalet){
        price=cenaBalet;
    }
};

class Opera : public Pretstava {
public:
    Opera() : Pretstava() {}
    Opera(Delo delo, int n, char *data) : Pretstava(delo, n, data) {}
    
    double cena(){
        return Pretstava::cena();
    }
};

double prihod(Pretstava **pretstavi, int n){
    double sum=0;
    for(int i=0; i<n; i++){
        sum+=pretstavi[i]->cena()*pretstavi[i]->getBrojKarti();
    }
    
    return sum;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo &delo1){
    int br=0;
    for(int i=0; i<n; i++){
        if(pretstavi[i]->getDelo()==delo1){
            br++;
        }
    }
    
    return br;
}

double Balet::price=150;

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;
    
    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;
        
    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;
    
    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();
        
        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
    
    }break;
    
    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        
        }
        cout<<prihod(pole,n);
    }break;
    
    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;
        
    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        
        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;
    
    };


return 0;
}
