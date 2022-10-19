#include <iostream>
#include <cstring>

using namespace std;

class SMS {
protected:
    double cena;
    char broj[15];
    
public:
    SMS(){}
    SMS(char *broj, double cena){
        this->cena=cena;
        strcpy(this->broj, broj);
    }
    
    virtual double SMS_cena(){
        return cena;
    }
    
    friend ostream &operator << (ostream &out, SMS &sms){
        out << "Tel: " << sms.broj << " - cena: " << sms.SMS_cena() << "den." << endl;
        return out;
    }
    
    virtual ~SMS(){}
};

class RegularSMS : public SMS {
    char *tekst;
    bool roaming;
    static int r;
    
public:
    RegularSMS(){
        this->tekst=new char[0];
    }
    RegularSMS(char *broj, double cena, char *tekst, bool roaming) : SMS (broj, cena) {
        this->tekst=new char[strlen(tekst)+1];
        strcpy(this->tekst, tekst);
        
        this->roaming=roaming;
    }
    
    RegularSMS(const RegularSMS &obj){
        this->tekst=new char[strlen(obj.tekst)+1];
        strcpy(tekst, obj.tekst);
        
        roaming=obj.roaming;
    }
    
    RegularSMS &operator= (RegularSMS &s){
        if(this==&s){
            return *this;
        }
        
        delete [] tekst;
        this->tekst=new char[strlen(s.tekst)+1];
        strcpy(tekst, s.tekst);
        
        roaming=s.roaming;
        
        return *this;
    }
    
    double SMS_cena(){
        double dolzina=strlen(tekst)/160;
        double price=SMS::SMS_cena();
        int d=dolzina+1;
        if(roaming==1){
            price=(price+price*r/100)*d;
        }else if(roaming==0){
            price=(price+price*18/100)*d;
        }
        
        return price;
    }
    
    static void set_rProcent(int broj){
        r=broj;
    }
    
    friend ostream &operator << (ostream &out, RegularSMS &r){
        out << "Tel: " << r.broj << " - cena: " << r.SMS_cena() << "den."<< endl;
        
        return out;
    }
};

int RegularSMS::r=300;

class SpecialSMS : public SMS {
    bool humanitarna;
    static int s;
    
public:
    SpecialSMS(){}
    SpecialSMS(char *broj, double cena, bool humanitarna) : SMS (broj, cena) {
        this->humanitarna=humanitarna;
    }
    
    double SMS_cena(){
        double c=SMS::SMS_cena();
        if(humanitarna==0){
            c=c+(c/100)*s;
        }else if(humanitarna==1){
            return c;
        }
        
        return c;
    }
    
    static void set_sProcent(int broj){
        s=broj;
    }
    
    friend ostream &operator << (ostream &out, SpecialSMS &s){
        out << "Tel: " << s.broj << " - cena: " << s.SMS_cena() << "den."<< endl;
        return out;
    }
};

void vkupno_SMS(SMS **poraka, int n){
    int s=0, r=0;
    double sumS=0, sumR=0;
    for(int i=0; i<n; i++){
        RegularSMS *reg=dynamic_cast<RegularSMS*>(poraka[i]);
        SpecialSMS *spc=dynamic_cast<SpecialSMS*>(poraka[i]);
        
        if(reg){
            r++;
            sumR+=reg->SMS_cena();
        }
        if(spc){
            s++;
            sumS+=spc->SMS_cena();
        }
    }
    
    cout << "Vkupno ima " << r << " regularni SMS poraki i nivnata cena e: " << sumR << endl;
    cout << "Vkupno ima " << s << " specijalni SMS poraki i nivnata cena e: " << sumS << endl;
}

int SpecialSMS::s=150;

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;
                
                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            sms1 = new RegularSMS(tel, cena, msg, roam);
            cout << *sms1;
        
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cin >> p;
            RegularSMS::set_rProcent(p);
            sms2 = new RegularSMS(tel, cena, msg, roam);
            cout << *sms2;
        
        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
            cin >> tel;
            cin >> cena;
            cin >> hum;
            sms1 = new SpecialSMS(tel, cena, hum);
            cout << *sms1;
        
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cin >> p;
            SpecialSMS::set_sProcent(p);
            sms2 = new SpecialSMS(tel, cena, hum);
            cout << *sms2;
        
        delete sms1, sms2;
    }
    
    return 0;
}
