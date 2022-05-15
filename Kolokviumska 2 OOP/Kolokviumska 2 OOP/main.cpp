#include <iostream>
using namespace std;

class List{
    int *listaBroevi;
    int brojBroeviOdLista;
public:
    
    List(){
        listaBroevi=NULL;
        brojBroeviOdLista=0;
    }
    
    List(int *listaBroevi, int brojBroeviOdLista){
        this->listaBroevi=new int[brojBroeviOdLista];
        for(int i=0; i<brojBroeviOdLista; i++){
            this->listaBroevi[i]=listaBroevi[i];
        }
        this->brojBroeviOdLista=brojBroeviOdLista;
    }
    
    ~List(){
        delete[] listaBroevi;
    }
    
    List(const List &obj){
        this->listaBroevi=new int[obj.brojBroeviOdLista];
        for(int i=0; i<obj.brojBroeviOdLista; i++){
            this->listaBroevi[i]=obj.listaBroevi[i];
        }
        this->brojBroeviOdLista=obj.brojBroeviOdLista;
    }
    
    List & operator= (const List &obj){
        if(this==&obj){
            return *this;
        }
        
        delete[] listaBroevi;
        
        this->listaBroevi=new int[obj.brojBroeviOdLista];
        for(int i=0; i<obj.brojBroeviOdLista; i++){
            this->listaBroevi[i]=obj.listaBroevi[i];
        }
        brojBroeviOdLista=obj.brojBroeviOdLista;
        
        return *this;
    }
    
    int sum(){
        int suma=0;
        for(int i=0; i<brojBroeviOdLista; i++){
            suma+=listaBroevi[i];
        }
        
        return suma;
    }
    
    double average(){
        float avg=0;
        
        avg=sum()/(double)brojBroeviOdLista;
        
        return avg;
    }
    
    void pecati(){
        cout << brojBroeviOdLista << ": ";
        for(int i=0; i<brojBroeviOdLista; i++){
            cout << listaBroevi[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }
    
    int getBroeviOdLista(){
        return brojBroeviOdLista;
    }
};

class ListContainer {
    List *nizaListi;
    int vkupnoListi;
    int brojObidi;
    
public:
    ListContainer(){
        nizaListi=NULL;
        vkupnoListi=0;
        brojObidi=0;
    }
    
    ListContainer(List *nizaListi, int vkupnoListi, int brojObidi){
        this->nizaListi=new List[vkupnoListi];
        for(int i=0; i<vkupnoListi; i++){
            this->nizaListi[i]=nizaListi[i];
        }
        this->vkupnoListi=vkupnoListi;
        this->brojObidi=brojObidi;
    }
    
    ListContainer(const ListContainer &obj){
        this->nizaListi=new List[obj.vkupnoListi];
        for(int i=0; i<obj.vkupnoListi; i++){
            nizaListi[i]=obj.nizaListi[i];
        }
        vkupnoListi=obj.vkupnoListi;
        brojObidi=obj.brojObidi;
    }
    
    ~ListContainer(){
        delete[] nizaListi;
    }
    
    ListContainer & operator= (const ListContainer &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] nizaListi;
        
        this->nizaListi=new List[obj.vkupnoListi];
        for(int i=0; i<obj.vkupnoListi; i++){
            nizaListi[i]=obj.nizaListi[i];
        }
        vkupnoListi=obj.vkupnoListi;
        brojObidi=obj.brojObidi;
        
        return *this;
    }
    
    int sum(){
        int suma=0;
        for(int i=0; i<vkupnoListi; i++){
            suma+=nizaListi[i].sum();
        }
        
        return suma;
    }
    
    double average(){
        double avg=0, vkupnoN=0;
        
        for(int i=0; i<vkupnoListi; i++){
            vkupnoN+=nizaListi[i].getBroeviOdLista();
        }
        avg=sum()/(double)vkupnoN;
        
        return avg;
    }
    
    int failedAttempts=0;
    void addNewList(List l){
        int flag=0;
        
        for(int i=0; i<vkupnoListi; i++){
            if(l.sum()==nizaListi[i].sum()){
                flag=1;
                failedAttempts++;
                break;
            }
        }
        if(flag==0){
            List *temp=new List[vkupnoListi+1];
            
            for(int i=0; i<vkupnoListi; i++){
                temp[i]=nizaListi[i];
            }
            temp[vkupnoListi]=l;
            
            vkupnoListi++;
            delete [] nizaListi;
            nizaListi=temp;
        }
    }
    
    void print(){
        if(vkupnoListi!=0){
            for(int i=0; i<vkupnoListi; i++){
                cout << "List number: " << i+1 << " List info: ";
                nizaListi[i].pecati();
            }
            cout<< "Sum: " << sum() << " Average: " << average() << endl;
            cout<< "Successful attempts: " << vkupnoListi << " Failed attempts: " << failedAttempts << endl;
        }else{
            cout << "The list is empty" <<endl;
        }
    }
};

int main() {
    
    ListContainer lc;
    int N;
    cin>>N;
    
    for (int i=0;i<N;i++) {
        int n;
        int niza[100];
        
        cin>>n;
       
        for (int j=0;j<n;j++){
            cin>>niza[j];
            
        }
       
        List l=List(niza,n);
    
        lc.addNewList(l);
    }
    
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}
