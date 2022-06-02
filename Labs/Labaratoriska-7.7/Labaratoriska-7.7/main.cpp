#include<cstring>
#include<iostream>

using namespace std;

class Secret{
public:
    virtual double simpleEntropy();
    virtual int total();
};

//preoptovaruvanje na operator ==

//preoptovaruvanje na operator !=

class DigitSecret : public Secret { //da se dopolni so izraz za nasleduvanje
private:
    int nizaC[100];
    int n;
    
public:
    DigitSecret () : Secret() {}
    
    DigitSecret (int nizaC[], int n) : Secret() {
        this->n=n;
        
        for(int i=0; i<n; i++){
            this->nizaC[i]=nizaC[i];
        }
    }
    
    int total(){
        return n;
    }
    
    double simpleEntropy(){
        int br=0, vkupno=0;
        
        for(int i=0; i<n; i++){
            br=0;
            for(int j=0; j<n; j++){
                if(nizaC[i]==nizaC[j]){
                    br++;
                }
            }
            
            if(br==1){
                vkupno++;
            }
        }
        
        return (double)vkupno/n;
    }
    
    //preoptovaruvanje na operatorot za pechatenje <<
    
    
};

class CharSecret : public Secret { //da se dopolni so izraz za nasleduvanje
    private:
    char bukva[100];
    
    public:
    CharSecret() : Secret() {}
    
    CharSecret(char bukva[]) : Secret() {}
    
    int total(){
        return sizeof(bukva);
    }
    
    double simpleEntropy(){
        return
    }
    
    
};

//void process(Secret ** secrets, int n){}

//void printAll (Secret ** secrets, int n) {}


int main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "Constructors" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
          cout << "operator <<" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
          cout << "== and !=" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
          cout << "Secret processor" << endl;
        int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
        int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }
    
    return 0;
}
