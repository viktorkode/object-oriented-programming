#include <iostream>
#include <cstring>
using namespace std;

class Koncert {
private:
    char naziv[20];
    char lokacija[20];
    static double popust;
    double cenaBilet;
    
public:
    Koncert(){}
    Koncert(char *naziv, char *lokacija, double cenaBilet){
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cenaBilet=cenaBilet;
    }
    
    char *getIme(){
        return naziv;
    }
    
    static void setSezonskiPopust(double p){
        popust=p;
    }
    
    static double getSezonskiPopust(){
        return popust;
    }
    
    virtual double cena(){
        return cenaBilet-cenaBilet*popust;
    }
};

class ElektronskiKoncert : public Koncert {
private:
    char *dj;
    double duration;
    bool period;
    
public:
    ElektronskiKoncert(char *naziv, char *lokacija, double cenaBilet, char *dj, double duration, bool period) : Koncert(naziv, lokacija, cenaBilet){
        this->dj= new char [strlen(dj)+1];
        strcpy(this->dj, dj);
        
        this->duration=duration;
        this->period=period;
    }
    
    ElektronskiKoncert(const ElektronskiKoncert &obj){
        this->dj= new char [strlen(obj.dj)+1];
        strcpy(dj, obj.dj);
        duration=obj.duration;
        period=obj.period;
    }
    
    ElektronskiKoncert &operator= (const ElektronskiKoncert &obj){
        if(this==&obj){
            return *this;
        }
        delete [] dj;
        
        this->dj= new char [strlen(obj.dj)+1];
        strcpy(dj, obj.dj);
        duration=obj.duration;
        period=obj.period;
        
        return *this;
    }
    
    ~ElektronskiKoncert(){
        delete [] dj;
    }
    
    double cena(){
        double price=Koncert::cena();
        
        if(duration>7){
            price+=360;
        }else if(duration>5){
            price+=150;
        }
        
        if(period==true){
            price-=50;
        }else{
            price+=100;
        }
        
        return price;
    }
};

void najskapKoncert(Koncert **koncerti, int n){
    double maxCena=0;
    int index=0;
    int ek=0;
    
    for(int i=0; i<n; i++){
        if(koncerti[i]->cena() > maxCena){
            maxCena=koncerti[i]->cena();
            index=i;
        }
        ElektronskiKoncert *pok=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        
        if(pok){
            ek++;
        }
        
    }
    cout << "Najskap koncert: " << koncerti[index]->getIme() << " " << koncerti[index]->cena()<<endl;
    cout << "Elektronski koncerti: " << ek << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    int flag=0;
    int index=0;
    
    for(int i=0; i<n; i++){
        if(elektronski==true){
            ElektronskiKoncert *pok=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if(pok){
                if(strcmp(naziv, koncerti[i]->getIme())==0){
                    index=i;
                    flag=1;
                }
            }
        }else{
            if(strcmp(naziv, koncerti[i]->getIme())==0){
                index=i;
                flag=1;
            }
        }
    }
    
    if(flag==1){
        cout<< koncerti[index]->getIme() << " " << koncerti[index]->cena() << endl;
        return true;
    }else{
        return false;
    }
}

double Koncert::popust=0.2;

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
            cin>>naziv>>lokacija>>cenaBilet;
            Koncert k1(naziv,lokacija,cenaBilet);
            cout<<"Kreiran e koncert so naziv: "<<k1.getIme()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
            Koncert k1(naziv,lokacija,cenaBilet);
            cout<<"Osnovna cena na koncertot so naziv "<<k1.getIme()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getIme()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getIme()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
              Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
            cin>>elektronski;
            if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
              Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
            najskapKoncert(koncerti,4);
        }

    return 0;
}
