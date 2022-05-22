#include <iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char ime[50];
    int godini;
    int iskustvo;
    
public:
    Employee () {
//        ime=NULL;
    }
    
    Employee (char *ime, int godini, int iskustvo) {
//        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        
        this->godini=godini;
        this->iskustvo=iskustvo;
    }
    
//    Employee (const Employee &obj){
// //       this->ime=new char[strlen(obj.ime)+1];
//        strcpy(ime, obj.ime);
//
//        godini=obj.godini;
//        iskustvo=obj.iskustvo;
//    }
    
//    Employee &operator= (const Employee &obj){
//        if(this==&obj){
//            return *this;
//        }
//
// //       delete [] ime;
// //       this->ime=new char[strlen(obj.ime)+1];
//        strcpy(ime, obj.ime);
//
//        godini=obj.godini;
//        iskustvo=obj.iskustvo;
//
//        return *this;
//    }
//
//    ~Employee () {
////        delete [] ime;
//    }
    virtual double bonus() = 0;
    virtual double plata() = 0;

    
    bool operator== (Employee &obj) {
        if(this->godini==obj.godini && this->bonus()==obj.bonus()){
            return true;
        } else {
            return false;
        }
    }
    
};

class SalaryEmployee : public Employee {
private:
    double osnovnaPlata;
    
public:
    SalaryEmployee() {}
    SalaryEmployee(char ime[], int godini, int iskustvo, double osnovnaPlata) : Employee (ime, godini, iskustvo) {
        this->osnovnaPlata=osnovnaPlata;
    }
    
    double bonus(){
        return (osnovnaPlata/100)*iskustvo;
    }
    
    double plata(){
        return osnovnaPlata+bonus();
    }
};

class HourlyEmployee : public Employee {
private:
    int casovi;
    double plataCas;
    
public:
    HourlyEmployee () : Employee() {}
    HourlyEmployee (char *ime, int godini, int iskustvo, int casovi, double plataCas) : Employee (ime, godini, iskustvo){
        this->casovi=casovi;
        this->plataCas=plataCas;
    }
    
    double bonus(){
        if(casovi>320){
            return (casovi-320)*(plataCas/2);
        } else {
            return 0;
        }
    }
    
    double plata(){
        return (casovi*plataCas)+bonus();
    }
};

class Freelancer : public Employee {
private:
    int proekti;
    double *sumi;
    
public:
    Freelancer () : Employee () {
        sumi=0;
    }
    
    Freelancer (char *ime, int godini, int iskustvo, int proekti, double *sumi) : Employee (ime, godini, iskustvo){
        this->proekti=proekti;
        
        this->sumi=new double[proekti];
        
        for(int i=0; i<proekti; i++){
            this->sumi[i]=sumi[i];
        }
    }
    
    // Copy & = operator ?
    
    double bonus(){
        if(proekti>=5){
            return (proekti-5)*1000;
        } else {
            return 0;
        }
    }
    
    double plata(){
        int sum=0;
        for(int i=0; i<proekti; i++){
            sum+=sumi[i];
        }
        
        return sum+bonus();
    }

    // Destruktor za double
};

class Company {
protected:
    char *imeKompanija;
    int vraboteni;
    Employee **pokazuvaci;
    
public:
    Company () {
        imeKompanija=NULL;
        vraboteni=0;
        pokazuvaci=NULL;
    }
    
    Company (char *imeKompanija) {
        this->imeKompanija=new char[strlen(imeKompanija)+1];
        strcpy(this->imeKompanija, imeKompanija);
        
        pokazuvaci=new Employee*[0];
        this->vraboteni=0;
    }
    
    Company (const Company &obj){
        this->imeKompanija=new char[strlen(obj.imeKompanija)+1];
        strcpy(imeKompanija, obj.imeKompanija);
        
        vraboteni=obj.vraboteni;

        for(int i=0; i<vraboteni; i++){
            pokazuvaci[i]=obj.pokazuvaci[i];
        }
    }
    
    Company &operator+= (Employee *e) {
        Employee **temp=new Employee *[vraboteni+1];
        
        for(int i=0; i<vraboteni; i++){
            temp[i]=pokazuvaci[i];
        }
        
        temp[vraboteni]=e;
        vraboteni++;
        
        delete [] pokazuvaci;
        
        pokazuvaci=temp;
        
        return *this;
    }
    
    double vkupnaPlata(){
        double sum=0;
        for(int i=0; i<vraboteni; i++){
            sum+=pokazuvaci[i]->plata();
        }
        
        return sum;
    }
    
    double filtriranaPlata(Employee *emp){
        double sum=0;
        for(int i=0; i<vraboteni; i++){
            if(*pokazuvaci[i]==*emp){
                sum+=pokazuvaci[i]->plata();
            }
        }
        
        return sum;
    }
    
    void pecatiRabotnici(){
        cout << "Vo kompanijata " << imeKompanija << " rabotat:" << endl;
        int brS=0, brH=0, brF=0;
        
        for(int i=0; i<vraboteni; i++){
            SalaryEmployee *pok1=dynamic_cast<SalaryEmployee *>(pokazuvaci[i]);
            HourlyEmployee *pok2=dynamic_cast<HourlyEmployee *>(pokazuvaci[i]);
            Freelancer *pok3=dynamic_cast<Freelancer *>(pokazuvaci[i]);
            
            if(pok1){
                brS++;
            }
            
            if(pok2){
                brH++;
            }
            
            if(pok3){
                brF++;
            }
        }
        
        cout << "Salary employees: " << brS << endl;
        cout << "Hourly employees: " << brH << endl;
        cout << "Freelancers: " << brF << endl;
    }
};

int main() {

char name[50];
cin >> name;
Company c(name);

int n;
cin >> n;

char employeeName[50];
int age;
int experience;
int type;

for (int i=0; i <n; ++i) {
  cin >> type;
  cin >> employeeName >> age >> experience;

  if (type == 1) {
    int basicSalary;
    cin >> basicSalary;
    c += new SalaryEmployee(employeeName, age, experience, basicSalary);
  }

  else if (type == 2) {
    int hoursWorked;
    int hourlyPay;
    cin >> hoursWorked >> hourlyPay;
    c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
  }

  else {
    int numProjects;
    cin >> numProjects;
    double projects[10];
    for (int i=0; i < numProjects; ++i) {
      cin >> projects[i];
    }
    c += new Freelancer(employeeName, age, experience, numProjects, projects);
  }
}

c.pecatiRabotnici();
cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

delete emp;
}
