#include <iostream>
#include <cstring>

using namespace std;

enum typeC {
    standard, loyal, vip
};

class Customer {
protected:
    char ime[50];
    char email[50];
    typeC tip;
    static int popust;
    const static int pluspopust;
    int brProizvodi;
    
public:
    Customer(){
        tip=standard;
    }
    
    Customer(char *ime, char *email, typeC tip, int brProizvodi){
        strcpy(this->ime, ime);
        strcpy(this->email, email);
        this->tip=tip;
        this->brProizvodi=brProizvodi;
    }
    
    friend ostream &operator<< (ostream &out, Customer &c){
        out << c.ime << endl << c.email << endl << c.brProizvodi << endl;
        
        if(c.tip==standard){
            out << "standard ";
        }else if(c.tip==loyal){
            out << "loyal ";
        }else if(c.tip==vip){
            out << "vip ";
        }
        out << c.funcPopust() << endl;
        
        return out;
    }
    
    int funcPopust(){
        if(tip==loyal){
            return popust;
        }else if(tip==vip){
            return popust+pluspopust;
        }else{
            return 0;
        }
    }
    
    static void setDiscount1(int p){
        popust=p;
    }
    
    static int getPopust(){
        return popust;
    }
    
    bool operator== (Customer &c){
        if(strcmp(email, c.email)==0){
            return true;
        }else{
            return false;
        }
    }
    
    int getBrojProizvodi(){
        return brProizvodi;
    }
    
    typeC getType(){
        return tip;
    }
    
    void setType(typeC t){
        tip=t;
    }
    
    Customer &operator= (const Customer &c){
        if(this==&c){
            return *this;
        }
        
        strcpy(ime, c.ime);
        strcpy(email, c.email);
        tip=c.tip;
        brProizvodi=c.brProizvodi;
        
        return *this;
    }

};

class UserExistsException {
public:
    void message(){
        cout << "The user already exists in the list!" << endl;
    }
};

class FINKI_bookstore {
private:
    Customer *kupuvaci;
    int brKupuvaci;
    
public:
    FINKI_bookstore(){
        kupuvaci=NULL;
    }
    
    FINKI_bookstore &operator+= (Customer &c){
        int flag=0;
        
        for(int i=0; i<brKupuvaci; i++){
            if(kupuvaci[i]==c){
                flag=1;
                throw UserExistsException();
            }
        }
        if(flag==0){
            Customer *temp=new Customer[brKupuvaci+1];
            for(int i=0; i<brKupuvaci; i++){
                temp[i]=kupuvaci[i];
            }
            temp[brKupuvaci]=c;
            
            brKupuvaci++;
            
            delete [] kupuvaci;
            
            kupuvaci=temp;
        }
        
        return *this;
    }
    
    FINKI_bookstore (const FINKI_bookstore &f){
        brKupuvaci=f.brKupuvaci;
        
        this->kupuvaci=new Customer[f.brKupuvaci];
        
        for(int i=0; i<f.brKupuvaci; i++){
            kupuvaci[i]=f.kupuvaci[i];
        }
    }
    
    FINKI_bookstore &operator= (const FINKI_bookstore &f){
        if(this==&f){
            return *this;
        }
        delete [] kupuvaci;
        
        brKupuvaci=f.brKupuvaci;
        
        this->kupuvaci=new Customer[f.brKupuvaci];
        
        for(int i=0; i<f.brKupuvaci; i++){
            kupuvaci[i]=f.kupuvaci[i];
        }
        
        return *this;
    }
    
    ~FINKI_bookstore(){
        delete [] kupuvaci;
    }
    
    void update(){
        for(int i=0; i<brKupuvaci; i++){
            if(kupuvaci[i].getBrojProizvodi() > 5 && kupuvaci[i].getType()==standard) {
                kupuvaci[i].setType(loyal);
            }else if(kupuvaci[i].getBrojProizvodi() > 10 && kupuvaci[i].getType()==loyal) {
                kupuvaci[i].setType(vip);
            }
        }
    }
    
    friend ostream &operator<< (ostream &out, FINKI_bookstore &b) {
        for(int i=0; i<b.brKupuvaci; i++){
            out << b.kupuvaci[i];
        }
        
        return out;
    }
    
    void setCustomers(Customer *c, int n) {
        brKupuvaci=n;
        delete [] kupuvaci;
        
        this->kupuvaci=new Customer[brKupuvaci];
        
        for(int i=0; i<brKupuvaci; i++){
            kupuvaci[i]=c[i];
        }
    }

};

const int Customer::pluspopust=20;
int Customer::popust=10;
#define MAX 50

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
      try {
          fc+=c;
      }
      catch(UserExistsException &c) {
          c.message();
      }

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    
      Customer c(name, email, (typeC) tC, numProducts);
      try {
          fc+=c;
      }
      catch(UserExistsException &c) {
          c.message();
      }
    
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
   
}
