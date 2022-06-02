#include<iostream>
using namespace std;

class Number {
public:
    virtual double doubleValue();
    virtual int intValue();
    virtual void print();
    
    bool operator== (Number &obj){
        if(this->doubleValue()==obj.doubleValue() && this->intValue()==obj.intValue()){
            return true;
        } else {
            return false;
        }
    }
};

class Integer : public Number {
private:
    int intBroj;
    
public:
    Integer(int intBroj){
        this->intBroj=intBroj;
    }
    
    // METODI OD NUMBER
    
    int intValue(){
        return intBroj;
    }
    
    void print(){
        cout << "Integer: " << intBroj << endl;
    }
};

class Double : public Number {
private:
    double doubleBroj;
    
public:
    Double(int doubleBroj){
        this->doubleBroj=doubleBroj;
    }
    
    // METODI OD NUMBER
    
    double doubleValue(){
        return doubleBroj;
    }
    
    void print(){
        cout << "Double: " << doubleBroj << endl;
    }
};

class Numbers{
private:
    Numbers *broevi;
    int N;
    
public:
    Numbers (){
        broevi=0;
        N=0;
    }
    
    Numbers(Numbers *broevi){
        for(int i=0; i<N; i++){
            this->broevi[i]=broevi[i];
        }
    }
    
    Numbers (const Numbers &obj){
        for(int i=0; i<N; i++){
            broevi[i]=obj.broevi[i];
        }
    }
    
    Numbers &operator+= (Numbers *num) {
        Numbers *temp = new int[size];
    }
    
    //TODO operator =
    
    //TODO destruktor
    
    //TODO operator += (operatorot da prima pointer od objekt od Number, a ne referenca)
    
    //TODO void statistics()
    
    //TODO void integersLessThan (Integer n)
    
    //TODO void doublesBiggerThan (Double n)
};

int main() {
    
    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }
    
    int lessThan;
    double biggerThan;
    
    cin>>lessThan;
    cin>>biggerThan;
    
    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));
    
    return 0;
}
