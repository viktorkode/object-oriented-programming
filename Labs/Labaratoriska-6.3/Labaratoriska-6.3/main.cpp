#include <iostream>
#include <cstring>

using namespace std;

class Lekar {
protected:
    int faksimilDoktor;
    char ime[10];
    char prezime[20];
    double pocetnaPlata;
    
public:
    Lekar(){}
    
    Lekar(int faksimilDoktor, char ime[], char prezime[], double pocetnaPlata){
        this->faksimilDoktor=faksimilDoktor;
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->pocetnaPlata=pocetnaPlata;
    }
    
    Lekar (const Lekar &obj){
        faksimilDoktor=obj.faksimilDoktor;
        strcpy(ime, obj.ime);
        strcpy(prezime, obj.prezime);
        pocetnaPlata=obj.pocetnaPlata;
    }
    
    void pecati(){
        cout << faksimilDoktor << ": " << ime << " " << prezime << endl;
    }
    
    double plata(){
        return pocetnaPlata;
    }
};

class MaticenLekar : public Lekar {
private:
    int brojPacienti;
    double *kotizacii;
    
public:
    MaticenLekar () : Lekar (){
        kotizacii=NULL;
    }
    
    MaticenLekar(int faksimil, char ime[], char prezime[], double pocetnaPlata, int brojPacienti, double *kotizacii) : Lekar (faksimil, ime, prezime, pocetnaPlata) {
        this->brojPacienti=brojPacienti;
        this->kotizacii=new double[brojPacienti];
        
        for(int i=0; i<brojPacienti; i++){
            this->kotizacii[i]=kotizacii[i];
        }
    }
    
    MaticenLekar(Lekar &obj, int brojPacienti, double *kotizacii) : Lekar (obj) {
        this->brojPacienti=brojPacienti;
        this->kotizacii=new double[brojPacienti];
        
        for(int i=0; i<brojPacienti; i++){
            this->kotizacii[i]=kotizacii[i];
        }
    }
    
    MaticenLekar (const MaticenLekar &obj) : Lekar(obj) {
        brojPacienti=obj.brojPacienti;
        this->kotizacii=new double[brojPacienti];
        
        for(int i=0; i<brojPacienti; i++){
            kotizacii[i]=obj.kotizacii[i];
        }
    }
    
    MaticenLekar &operator= (const MaticenLekar &obj){
        if(this==&obj){
            return *this;
        }
        Lekar::operator=(obj);
        
        brojPacienti=obj.brojPacienti;
        delete [] kotizacii;
        this->kotizacii=new double[brojPacienti];
        
        for(int i=0; i<brojPacienti; i++){
            kotizacii[i]=obj.kotizacii[i];
        }
        
        return *this;
    }
    
    ~MaticenLekar(){
        delete [] kotizacii;
    }
    
    double vkKotizacii(){
        double vkKot=0;
        for(int i=0; i<brojPacienti; i++){
            vkKot+=kotizacii[i];
        }
        
        return vkKot/brojPacienti;
    }
    
    void pecati(){
        Lekar::pecati();
        
//        double vkKot=0;
//        for(int i=0; i<brojPacienti; i++){
//            vkKot+=kotizacii[i];
//        }
        
        cout << "Prosek na kotizacii: " << vkKotizacii() << endl;
    }
    
    double plata(){
        return Lekar::plata() + (vkKotizacii()/100)*30;
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;
    
    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];
    
    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }
    
    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }
    
    delete [] lekari;
    delete [] maticni;
    
    return 0;
}
