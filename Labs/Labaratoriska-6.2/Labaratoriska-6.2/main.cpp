#include <iostream>

using namespace std;

class Kvadrat {
protected:
    double a;
    
public:
    Kvadrat(){}
    
    Kvadrat(double a){
        this->a=a;
    }
    
    Kvadrat(const Kvadrat &obj){
        a=obj.a;
    }
    
    double perimetar() {
        return 4*a;
    }
    
    double plostina() {
        return a*a;
    }
    
    void pecati() {
        cout << "Kvadrat so dolzina a=" << a << " ima plostina P=" << plostina() << " i perimetar L=" << perimetar() << endl;
    }
};

class Pravoagolnik : public Kvadrat { //da se vmetni nasleduvanjeto
    protected:
    double x;
    double y;
    
    
    public:
    Pravoagolnik () : Kvadrat() {}
    
    Pravoagolnik (double a, double x, double y) : Kvadrat(a){
        this->a=a;
        this->x=x;
        this->y=y;
    }
    Pravoagolnik (const Kvadrat &k, double x, double y) : Kvadrat(k) {
        this->x=x;
        this->y=y;
    }
    
    Pravoagolnik (const Pravoagolnik &obj) : Kvadrat(obj){
        x=obj.x;
        y=obj.y;
    }
    
    double perimetar(){
        int x1;
        if(x==y){
            x1=a+x;
            return 4*x1;
        }else{
            return 2*(a+x)+2*(a+y);
        }
    }
    
    double plostina(){
        int x2;
        if(x==y){
            x2=a+x;
            return x2*x2;
        }else{
            return (a+x)*(a+y);
        }
    }
    
    void pecati(){
        if(x==y){
            return Kvadrat::pecati();
        } else {
            cout << "Pravoagolnik so strani: " << a+x << " i " << a+y << " ima plostina P=" << plostina() << " i perimetar L=" << perimetar() << endl;
        }
    }
    //TODO prepokrivanje na metodite perimetar, plostina i pecati od klasata Kvadrat
};

int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;
    
    cin>>n;
    
    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];
    
    for (int i=0;i<n;i++){
        cin>>a;
        
        kvadrati[i] = Kvadrat(a);
    }
    
    for (int i=0;i<n;i++){
        cin>>x>>y;
        
        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}
