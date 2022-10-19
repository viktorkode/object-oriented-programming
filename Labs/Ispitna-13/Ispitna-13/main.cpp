#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:
    char *ime;
    char korisnik[50];
    int h;
    int w;
    
public:
    Image(char *ime="untitled", char *korisnik="unknown", int h=800, int w=800){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->korisnik, korisnik);
        
        this->h=h;
        this->w=w;
    }
    
    Image(const Image &obj){
        this->ime=new char[strlen(obj.ime)+1];
        strcpy(this->ime, obj.ime);
        strcpy(this->korisnik, obj.korisnik);
        
        this->h=obj.h;
        this->w=obj.w;
    }
    
    Image &operator= (const Image &obj){
        if(this==&obj){
            return *this;
        }
        
        delete [] ime;
        
        this->ime=new char[strlen(obj.ime)+1];
        strcpy(this->ime, obj.ime);
        strcpy(this->korisnik, obj.korisnik);
        
        this->h=obj.h;
        this->w=obj.w;
        
        return *this;
    }
    
    virtual ~Image(){
        delete [] ime;
    }
    
    virtual int fileSize(){
        return h*w*3;
    }
    
    friend ostream &operator << (ostream &out, Image &i){
        
        out << i.ime << " " << i.korisnik << " " << i.fileSize() << endl;
        
        return out;
    }
    
    virtual bool operator > (Image &i){
        if(fileSize() > i.fileSize()){
            return true;
        }else{
            return false;
        }
    }
};

class TransparentImage : public Image {
    bool transparent;

public:
    TransparentImage(char *ime="untitled", char *korisnik="unknown", int h=800, int w=800, bool transparent=true) : Image(ime, korisnik, h, w) {
        this->transparent=transparent;
    }
    
    ~TransparentImage(){}
    
    int fileSize(){
        if(transparent==true){
            return h*w*4;
        }else{
            return h*w+(h*w)/8;
        }
    }
    
    friend ostream &operator << (ostream &out, TransparentImage &i){
        
        out << i.ime << " " << i.korisnik << " " << i.fileSize() << endl;
        
        return out;
    }
    
    bool operator > (TransparentImage &t){
        if(fileSize()>t.fileSize()){
            return true;
        }else{
            return false;
        }
    }
};

class Folder {
    char folderName[255];
    char folderAuthor[50];
    Image *images[100];
    int n;
    
public:
    Folder(){}
    
    Folder(char *folderName, char *folderAuthor="unknown"){
        strcpy(this->folderName, folderName);
        strcpy(this->folderAuthor, folderAuthor);
    }
    
    int folderSize(){
        int sum=0;
        for(int i=0; i<n; i++){
            sum+=images[i]->fileSize();
        }
        
        return sum;
    }
    
    Image *getMaxFile(){
        int max=0;
        int indeks=0;
        for(int i=0; i<n; i++){
            if(images[i]->fileSize()>max){
                max=images[i]->fileSize();
                indeks=i;
            }
        }
        
        return images[indeks];
    }
    
    Folder &operator += (Image &t){
        if(n<100){
            images[n++]=&t;
        }
        
        return *this;
    }
    
    friend ostream &operator << (ostream &out, Folder &f) {
        out << f.folderName << " " << f.folderAuthor << endl;
        out << "--" << endl;
        for(int i=0; i<f.n; i++){
            out << *f.images[i];
        }
        out << "--" << endl;
        out << "Folder size: " << f.folderSize() << endl;
        
        return out;
    }
    
    Image *operator[] (int k){
        return images[k];
    }
};

Folder &max_folder_size(Folder *folderi, int n){
    int max=0;
    int indeks=0;
    
    for(int i=0; i<n; i++){
        if(folderi[i].folderSize()>max){
            max=folderi[i].folderSize();
            indeks=i;
        }
    }
    
    return folderi[indeks];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
