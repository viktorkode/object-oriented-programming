#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord {
    char ID[12];
    char imeKompanija[50];
    double cenaAkcii;
    double momentalnaCenaAkcija;
    int brojKupeniAkcii;
    
public:
    StockRecord(){}
    
    StockRecord(char *ID, char *imeKompanija, double cenaAkcii, int brojKupeniAkcii){
        strcpy(this->ID,ID);
        strcpy(this->imeKompanija,imeKompanija);
        this->cenaAkcii=cenaAkcii;
        this->brojKupeniAkcii=brojKupeniAkcii;
    }
    
    StockRecord(const StockRecord &obj){
        strcpy(ID, obj.ID);
        strcpy(imeKompanija, obj.imeKompanija);
        cenaAkcii=obj.cenaAkcii;
        momentalnaCenaAkcija=obj.momentalnaCenaAkcija;
        brojKupeniAkcii=obj.brojKupeniAkcii;
    }
    
    StockRecord &operator=(const StockRecord &obj){
        if(this==&obj){
            return *this;
        }
        strcpy(ID, obj.ID);
        strcpy(imeKompanija, obj.imeKompanija);
        cenaAkcii=obj.cenaAkcii;
        momentalnaCenaAkcija=obj.momentalnaCenaAkcija;
        brojKupeniAkcii=obj.brojKupeniAkcii;
        
        return *this;
    }
    
    ~StockRecord(){}

    void setNewPrice(double c){
        momentalnaCenaAkcija=c;
    }
    
    double value(){
        return momentalnaCenaAkcija*brojKupeniAkcii;
    }
    
    double profit(){
        return brojKupeniAkcii*(momentalnaCenaAkcija-cenaAkcii);
    }
    
    friend ostream & operator<<(ostream &out, StockRecord &sc)
{
    out<<sc.imeKompanija<<" "<<sc.brojKupeniAkcii<<" "<<sc.cenaAkcii<<" "<<sc.momentalnaCenaAkcija<<" "<<sc.profit()<<endl;
        return out;
    }
};

class Client {
    char imePrezime[60];
    int ID;
    StockRecord *nizaKompanii;
    int brojObjekti;
    
public:
    Client(){
        nizaKompanii=NULL;
        brojObjekti=0;
    }
    
    Client (char *imePrezime, int ID){
        this->brojObjekti=0;
        strcpy(this->imePrezime, imePrezime);
        this->nizaKompanii=new StockRecord[brojObjekti];
        this->ID=ID;
        
        for(int i=0; i<brojObjekti; i++){
            this->nizaKompanii[i]=nizaKompanii[i];
        }
    }
    
    Client (const Client &obj){
        strcpy(imePrezime, obj.imePrezime);
        this->nizaKompanii=new StockRecord[obj.brojObjekti];
        this->ID=obj.ID;
        this->brojObjekti=obj.brojObjekti;
        
        for(int i=0; i<obj.brojObjekti; i++){
            this->nizaKompanii[i]=obj.nizaKompanii[i];
        }
    }
    
    Client &operator=(const Client &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] nizaKompanii;
        
        strcpy(imePrezime, obj.imePrezime);
        this->nizaKompanii=new StockRecord[obj.brojObjekti];
        this->ID=obj.ID;
        this->brojObjekti=obj.brojObjekti;
        
        for(int i=0; i<obj.brojObjekti; i++){
            this->nizaKompanii[i]=obj.nizaKompanii[i];
        }
        
        return *this;
    }
    
    Client & operator+=(StockRecord sc)
{
    StockRecord *temp=new StockRecord[brojObjekti+1];
    for(int i=0;i<brojObjekti;i++)
    {
        temp[i]=nizaKompanii[i];
    }
    temp[brojObjekti]=sc;
    brojObjekti++;
    delete [] nizaKompanii;
    nizaKompanii=temp;
    return *this;
}
    
    double totalValue(){
        double vkupno=0;
        
        for(int i=0; i<brojObjekti; i++){
            vkupno+=nizaKompanii[i].value();
        }
        
        return vkupno;
    }
    
    friend ostream & operator<<(ostream &out, Client &c)
    {
        out<<c.ID<<" "<<c.totalValue()<<endl;
        for(int i=0;i<c.brojObjekti;i++)
        {
            out<<c.nizaKompanii[i];
        }
        return out;
    }
};


// ne menuvaj vo main-ot

int main(){
    
    int test;
    cin >> test;
    
    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
