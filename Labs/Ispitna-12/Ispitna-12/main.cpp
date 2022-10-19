#include <iostream>
#include <cstring>

using namespace std;

enum tip { Mobilen, Laptop };

class Device {
private:
    char model[100];
    tip uredTip;
    static double vreme;
    int godina;
    
public:
    Device(){}
    Device(char *model, tip uredTip, int godina) {
        strcpy(this->model, model);
        this->uredTip=uredTip;
        this->godina=godina;
    }
    
    static void setPocetniCasovi(double v){
        vreme=v;
    }
    
    double vremePopravka() {
        double v=vreme;
        if(godina>2015){
            v+=2;
        }
        
        if(uredTip==Laptop){
            v+=2;
        }
        
        return v;
    }
    
    friend ostream &operator << (ostream &out, Device &d){
        out << d.model << endl;
        if(d.uredTip==Mobilen){
            out << "Mobilen ";
        }else if(d.uredTip==Laptop){
            out << "Laptop ";
        }
        out << d.vremePopravka() << endl;
        return out;
    }
    
    int getGodina(){
        return godina;
    }
};

double Device::vreme=1;

class InvalidProductionDate {
public:
    void message(){
        cout << "Невалидна година на производство" << endl;
    }
};

class MobileServis {
private:
    char adresa[100];
    Device *devices;
    int n;
    
public:
    MobileServis(){
        this->devices= new Device[0];
        n=0;
    }
    
    MobileServis(char *adresa) {
        this->devices= new Device[0];
        this->n=0;
        strcpy(this->adresa, adresa);
    }
    
    MobileServis(char *adresa, Device *devices, int n){
        
        strcpy(this->adresa, adresa);
        this->n=n;
        this->devices=new Device[n];
        
        for(int i=0; i<n; i++){
            this->devices[i]=devices[i];
        }
    }
    
    MobileServis(const MobileServis &obj){
        strcpy(adresa, obj.adresa);
        n=obj.n;
        this->devices=new Device[obj.n];
        
        for(int i=0; i<n; i++){
            this->devices[i]=obj.devices[i];
        }
    }
    
    MobileServis &operator= (const MobileServis &s){
        if(this==&s){
            return *this;
        }
        
        delete [] devices;
        n=s.n;
        this->devices= new Device[s.n];
        strcpy(adresa, s.adresa);
        
        for(int i=0; i<s.n; i++){
            devices[i]=s.devices[i];
        }
        
        return *this;
    }
    
    MobileServis &operator += (Device &m){
        if(m.getGodina()>2019 || m.getGodina()<2000){
            throw InvalidProductionDate();
        }else{
            Device *temp=new Device[n+1];
            for(int i=0; i<n; i++){
                temp[i]=devices[i];
            }
            
            temp[n++]=m;
            delete [] devices;
            devices=temp;
        }
        
        return *this;
    }
    
    ~MobileServis(){
        delete [] devices;
    }
    
    void pecatiCasovi(){
        cout << "Ime: " << adresa << endl;
        for(int i=0; i<n; i++){
            cout << devices[i];
        }
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
        }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate &m){
                m.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate &m){
                m.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
         cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate &m){
                m.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }catch(InvalidProductionDate &m){
                m.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

        if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate &m){
                m.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

