#include <iostream>
#include <cstring>

using namespace std;

class Trud {
protected:
    char tip;
    int godina;
    
public:
    Trud(){}
    Trud(char tip, int godina){
        this->tip=tip;
        this->godina=godina;
    }
    
    char getTip(){
        return tip;
    }
    
    int getGodina(){
        return godina;
    }
    
    friend istream &operator >> (istream &in, Trud &t) {
        in >> t.godina >> t.tip;
        
        return in;
    }
};

class Student {
protected:
    char ime[30];
    int indeks;
    int godinaUpis;
    int *oceni;
    int n;
    
public:
    Student(){
        oceni=new int[0];
    }
    Student(char *ime, int indeks, int godinaUpis, int *oceni, int n){
        strcpy(this->ime, ime);
        
        this->indeks=indeks;
        this->godinaUpis=godinaUpis;
        
        this->n=n;
        
        this->oceni=new int[n];
        for(int i=0; i<n; i++){
            this->oceni[i]=oceni[i];
        }
    }
    
    Student(const Student &obj){
        strcpy(ime, obj.ime);
        
        indeks=obj.indeks;
        godinaUpis=obj.godinaUpis;
        
        n=obj.n;
        
        oceni=new int[obj.n];
        for(int i=0; i<n; i++){
            oceni[i]=obj.oceni[i];
        }
    }
    
    Student &operator= (const Student &obj){
        if(this==&obj){
            return *this;
        }
        
        strcpy(ime, obj.ime);
        
        indeks=obj.indeks;
        godinaUpis=obj.godinaUpis;
        
        n=obj.n;
        
        delete [] oceni;
        
        oceni=new int[obj.n];
        for(int i=0; i<n; i++){
            oceni[i]=obj.oceni[i];
        }
        
        return *this;
    }
    
    ~Student(){
        delete [] oceni;
    }
    
    // Ostanato
    
    virtual double rang(){
        int sum=0;
        for(int i=0; i<n; i++){
            sum+=oceni[i];
        }
        
        return (float)sum/n;
    }
    
    friend ostream &operator<< (ostream &out, Student &s){
        out << s.indeks << " " << s.ime << " " << s.godinaUpis << " " << s.rang() << endl;
        
        return out;
    }
};

class Exception {
public:
    void message(){
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class PhDStudent : public Student{
private:
    Trud *trudovi;
    int nT;
    static int konferenciski;
    static int spisanija;
    
public:
    PhDStudent(){}
    PhDStudent(char *ime, int indeks, int godinaUpis, int *oceni, int n, Trud *trudovi, int nT) : Student (ime, indeks, godinaUpis, oceni, nT){
        this->n=n;
        this->trudovi= new Trud [nT];
        for(int i=0; i<nT; i++){
            this->trudovi[i]=trudovi[i];
        }
    }
    
    ~PhDStudent(){
        delete [] trudovi;
    }
    
    static void setKonferenciski(int vrednost){
        konferenciski=vrednost;
    }
    
    static void setSpisanija(int vrednost){
        spisanija=vrednost;
    }
    
    double rang(){
        double r=Student::rang();
        
        for(int i=0; i<nT; i++){
            if(trudovi[i].getTip()=='c' || trudovi[i].getTip()=='C'){
                r+=konferenciski;
            } else if (trudovi[i].getTip()=='j' || trudovi[i].getTip()=='J'){
                r+=spisanija;
            }
        }
        
        return r;
    }
    
    PhDStudent &operator+= (Trud &t){
        if(t.getGodina() < godinaUpis){
            throw Exception();
        }else{
            Trud *temp=new Trud[n+1];
            for(int i=0; i<n; i++){
                temp[i]=trudovi[i];
            }
            
            temp[n++]=t;
            delete [] trudovi;
            trudovi=temp;
        }
        
        return *this;
    }
};

int PhDStudent::konferenciski=1;
int PhDStudent::spisanija=3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        try{
        }catch(Exception &m){
            m.message();
        }
        
        
        
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        
        try{
            
        }catch(Exception &m){
            m.message();
        }
        
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        try{
            cin >> t;
        }catch(Exception &m){
            m.message();
        }
        
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;
        
        //postavete gi soodvetnite vrednosti za statickite promenlivi
        
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
