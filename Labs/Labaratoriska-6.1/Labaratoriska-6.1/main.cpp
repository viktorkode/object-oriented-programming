#include <iostream>
#include <string.h>

using namespace std;

class NBAPlayer {
protected:
    char *imeIgrac;
    char timIgrac[40];
    double prosecniPoeni;
    double prosecniAsistencii;
    double prosecniSkokovi;
    
public:
    NBAPlayer(){
        imeIgrac=NULL;
    }
    
    NBAPlayer(char *imeIgrac, char timIgrac[], double prosecniPoeni, double prosecniAsistencii, double prosecniSkokovi){
        this->imeIgrac=new char[strlen(imeIgrac)+1];
        strcpy(this->imeIgrac, imeIgrac);
        strcpy(this->timIgrac, timIgrac);
        this->prosecniPoeni=prosecniPoeni;
        this->prosecniAsistencii=prosecniAsistencii;
        this->prosecniSkokovi=prosecniSkokovi;
    }
    
    NBAPlayer(const NBAPlayer &obj){
        this->imeIgrac=new char[strlen(obj.imeIgrac)+1];
        strcpy(imeIgrac, obj.imeIgrac);
        strcpy(timIgrac, obj.timIgrac);
        
        prosecniPoeni=obj.prosecniPoeni;
        prosecniAsistencii=obj.prosecniAsistencii;
        prosecniSkokovi=obj.prosecniSkokovi;
    }
    
    NBAPlayer &operator= (const NBAPlayer &obj){
        if(this==&obj){
            return *this;
        }
        delete [] imeIgrac;
        
        this->imeIgrac=new char[strlen(obj.imeIgrac)+1];
        strcpy(imeIgrac, obj.imeIgrac);
        strcpy(timIgrac, obj.timIgrac);
        
        prosecniPoeni=obj.prosecniPoeni;
        prosecniAsistencii=obj.prosecniAsistencii;
        prosecniSkokovi=obj.prosecniSkokovi;
        
        return *this;
    }
    
    ~NBAPlayer(){
        delete [] imeIgrac;
    }
    
    double rating(){
        return (prosecniPoeni/100)*45 + (prosecniAsistencii/100)*30 + (prosecniSkokovi/100)*25;
    }
    
    void print(){
        cout << imeIgrac << " - " << timIgrac << endl;
        cout << "Points: " << prosecniPoeni << endl;
        cout << "Assists: " << prosecniAsistencii << endl;
        cout << "Rebounds: " << prosecniSkokovi << endl;
        cout << "Rating: " << rating() << endl;
    }
};

class AllStarPlayer : public NBAPlayer {
protected:
    double allstarPoeni;
    double allstarAsistencii;
    double allstarSkokovi;
    
public:
    AllStarPlayer() : NBAPlayer() {}
    
    AllStarPlayer(char *imeIgrac, char timIgrac[], double prosecniPoeni, double prosecniAsistencii, double prosecniSkokovi, double allstarPoeni, double allstarAsistencii, double allstarSkokovi) : NBAPlayer(imeIgrac, timIgrac, prosecniPoeni, prosecniAsistencii, prosecniSkokovi) {
        
        this->allstarPoeni=allstarPoeni;
        this->allstarAsistencii=allstarAsistencii;
        this->allstarSkokovi=allstarSkokovi;
    }
    
    AllStarPlayer(NBAPlayer &igraci, double allstarPoeni, double allstarAsistencii, double allstarSkokovi) : NBAPlayer(igraci){
        this->allstarPoeni=allstarPoeni;
        this->allstarAsistencii=allstarAsistencii;
        this->allstarSkokovi=allstarSkokovi;
    }
    
    AllStarPlayer (const AllStarPlayer &obj) : NBAPlayer(obj){
        allstarPoeni=obj.allstarPoeni;
        allstarAsistencii=obj.allstarAsistencii;
        allstarSkokovi=obj.allstarSkokovi;
    }
    
    AllStarPlayer &operator= (const AllStarPlayer &obj) {
        if(this==&obj){
            return *this;
        }
        
        NBAPlayer::operator=(obj);
        
        allstarPoeni=obj.allstarPoeni;
        allstarAsistencii=obj.allstarAsistencii;
        allstarSkokovi=obj.allstarSkokovi;
        
        return *this;
    }
    
    ~AllStarPlayer(){}
    
    double allStarRating(){
        return (allstarPoeni/100)*30 + (allstarAsistencii/100)*40 + (allstarSkokovi/100)*30;
    }
    
    double rating(){
        return (NBAPlayer::rating() + allStarRating())/2;
    }
    
    void print(){
        NBAPlayer::print();
        
        cout << "All Star Rating: " << allStarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    delete [] players;
    delete [] asPlayers;
}
