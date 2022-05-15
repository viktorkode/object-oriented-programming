#include <iostream>
#include <cstring>
using namespace std;

class Gitara {
private:
    char seriskiBroj[25];
    double nabavnaCena;
    int godinaProiz;
    char tip[40];
    
public:
    Gitara(){}
    
    Gitara(char *tip, char *seriskiBroj, int godinaProiz, double nabavnaCena){
        strcpy(this->tip,tip);
        strcpy(this->seriskiBroj,seriskiBroj);
        this->godinaProiz=godinaProiz;
        this->nabavnaCena=nabavnaCena;
    }
    
    Gitara(const Gitara &obj){
        strcpy(tip,obj.tip);
        strcpy(seriskiBroj,obj.seriskiBroj);
        godinaProiz=obj.godinaProiz;
        nabavnaCena=obj.nabavnaCena;
    }
    
    bool daliIsti(Gitara &g){
        if(strcmp(seriskiBroj,g.seriskiBroj)==0){
            return true;
        }else{
            return false;
        }
    }
    
    void pecati(){
        cout << seriskiBroj << " " << tip << " " << nabavnaCena << endl;
    }
    
    double getVrednost(){
        return nabavnaCena;
    }
    
    char *getSeriski(){
        return seriskiBroj;
    }
    
    int getGodina(){
        return godinaProiz;
    }
    
    char *getTip(){
        return tip;
    }
};

class Magacin {
private:
    char magacin[30];
    char lokacija[60];
    Gitara *gitari;
    int n;
    int godinaMagacin;
    
public:
    Magacin(){
        gitari=NULL;
        n=0;
    }
    
    Magacin(char *magacin, char *lokacija, int godinaMagacin=0){
        n=0;
        this->gitari=new Gitara[n];
        strcpy(this->magacin,magacin);
        strcpy(this->lokacija,lokacija);
        this->godinaMagacin=godinaMagacin;
    }
    
    Magacin(const Magacin &obj){
        n=obj.n;
        this->gitari=new Gitara[obj.n];
        for(int i=0; i<n; i++){
            gitari[i]=obj.gitari[i];
        }
        strcpy(magacin,obj.magacin);
        strcpy(lokacija,obj.lokacija);
        godinaMagacin=obj.godinaMagacin;
    }
    
    Magacin &operator= (const Magacin &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] gitari;
        
        n=obj.n;
        this->gitari=new Gitara[obj.n];
        for(int i=0; i<n; i++){
            gitari[i]=obj.gitari[i];
        }
        strcpy(magacin,obj.magacin);
        strcpy(lokacija,obj.lokacija);
        godinaMagacin=obj.godinaMagacin;
        
        return *this;
    }
    
    ~Magacin(){
        delete [] gitari;
    }
    
    double vrednost(){
        double vrednost=0;
        for(int i=0; i<n; i++){
            vrednost+=gitari[i].getVrednost();
        }
        
        return vrednost;
    }
    
    void dodadi(Gitara d){
        Gitara *temp=new Gitara[n+1];
        
        for(int i=0; i<n; i++){
            temp[i]=gitari[i];
        }
        
        temp[n]=d;
        
        delete [] gitari;
        
        n++;
        gitari=temp;
    }
    
    void prodadi(Gitara p){
        for(int i=0;i<n;i++){
            if(gitari[i].daliIsti(p)){
                for(int j=i; j<n-1;j++){
                    gitari[j]=gitari[j+1];
                }
                n--;
                i--;
            }
        }
    }
    
    void pecati(bool daliNovi){
        cout << magacin << " " << lokacija << endl;
        for(int i=0; i<n; i++){
            if(daliNovi==true && gitari[i].getGodina()>godinaMagacin){
                gitari[i].pecati();
            }
            else if(daliNovi==false){
                gitari[i].pecati();
            }
        }
    }
};

int main() {
// se testira zadacata modularno
int testCase;
cin >> testCase;

int n, godina;
float cena;
char seriski[50],tip[50];

if(testCase == 1) {
    cout << "===== Testiranje na klasata Gitara ======" << endl;
    cin>>tip;
    cin>>seriski;
    cin >> godina;
    cin >> cena;
    Gitara g(tip,seriski, godina,cena);
    cout<<g.getTip()<<endl;
    cout<<g.getSeriski()<<endl;
    cout<<g.getGodina()<<endl;
    cout<<g.getVrednost()<<endl;
} else if(testCase == 2){
    cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
    Magacin kb("Magacin1","Lokacija1");
    kb.pecati(false);
}
else if(testCase == 3) {
    cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
    Magacin kb("Magacin1","Lokacija1",2005);
    cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
    kb.pecati(true);
}

else if(testCase == 4) {
    cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
    Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
    kb.pecati(false);
    kb.prodadi(brisi);
    kb.pecati(false);
}
else if(testCase == 5) {
    cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
    Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
    kb.pecati(true);
    kb.prodadi(brisi);
    cout<<"Po brisenje:"<<endl;
    Magacin kb3;
    kb3=kb;
    kb3.pecati(true);
}
else if(testCase ==6)
    {
    cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
    Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
    cout<<kb.vrednost()<<endl;
    kb.prodadi(brisi);
    cout<<"Po brisenje:"<<endl;
    cout<<kb.vrednost();
    Magacin kb3;
    kb3=kb;
    }
return 0;
}
