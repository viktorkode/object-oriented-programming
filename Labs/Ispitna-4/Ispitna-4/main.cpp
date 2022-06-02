#include <iostream>
#include <cstring>

using namespace std;

enum Size {
    small, large, family
};

class Pizza {
protected:
    char ime[20];
    char sostojki[100];
    float cena;
    
public:
    Pizza () {}
    
    Pizza (char *ime, char *sostojki, float cena) {
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->cena=cena;
    }
    
//    friend ostream &operator<< (ostream &out, Pizza &p){
//        out << p.ime << ": " << p.sostojki << ", ";
//
//        return out;
//    }
    
    bool operator< (Pizza &p){
        if(price()<p.price()){
            return true;
        }else{
            return false;
        }
    }
    
    virtual float price() = 0;
};

class FlatPizza : public Pizza {
private:
    Size tip;
    
public:
    FlatPizza(){}
    
    FlatPizza(char *ime, char *sostojki, float cena) : Pizza(ime, sostojki, cena){
        tip=small;
    }
    
    FlatPizza(char *ime, char *sostojki, float cena, Size tip) : Pizza(ime, sostojki, cena){
        this->tip=tip;
    }
    
    float price(){
        if(tip==small){
            return cena+cena/100*10;
        }else if(tip==large){
            return cena+cena/100*50;
        }else{
            return cena+cena/100*30;
        }
    }
    
    friend ostream &operator<< (ostream &out, FlatPizza &p){
        
        out << p.ime << ": " << p.sostojki << ", ";
        if(p.tip==small){
            out << "small";
        }else if(p.tip==large){
            out << "large";
        }else{
            out << "family";
        }
        out << " - " << p.price() << endl;
        
        return out;
    }
};

class FoldedPizza : public Pizza {
private:
    bool brasno;
    
public:
    FoldedPizza(){}
    
    FoldedPizza(char *ime, char *sostojki, float cena) : Pizza(ime, sostojki, cena){
        brasno=true;
    }
    
    FoldedPizza(char *ime, char *sostojki, float cena, bool brasno) : Pizza(ime, sostojki, cena){
        this->brasno=brasno;
    }
    
    float price(){
        if(brasno){
            return cena+cena/100*10;
        }else{
            return cena+cena/100*30;
        }
    }
    
    friend ostream &operator<< (ostream &out, FoldedPizza &p){
        
        out << p.ime << ": " << p.sostojki << ", ";
        if(p.brasno){
            out << "wf";
        }else{
            out << "nwf";
        }
        
        out << " - " << p.price() << endl;
        
        return out;
    }
    
    void setWhiteFlour(bool flour){
        brasno=flour;
    }

};

void expensivePizza (Pizza **niza, int n){
    int max=0, ind=0;
    for(int i=0; i<n; i++){
        if(niza[i]->price()>max){
            max=niza[i]->price();
            ind=i;
        }
    }
    
    FlatPizza *pok1=dynamic_cast<FlatPizza*>(niza[ind]);
    FoldedPizza *pok2=dynamic_cast<FoldedPizza*>(niza[ind]);
    
    if(pok1){
        cout << *pok1;
    }
    if(pok2){
        cout << *pok2;
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;
    
  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
    // Test Cast - operator <, price
    int s;
    
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;
      
    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;
        
    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;
        
    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;
    
    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
    // Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);
          
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
