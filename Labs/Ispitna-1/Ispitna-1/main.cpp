#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    float cena;
public:
    Book() {}
    
    Book(char *ISBN, char *naslov, char *avtor, float cena){
        strcpy(this->ISBN, ISBN);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena=cena;
    }
    virtual float bookPrice() = 0;
    
    bool operator> (Book &b) {
        if(bookPrice()>b.bookPrice()){
            return true;
        }else{
            return false;
        }
    }
    
    friend ostream &operator<< (ostream &out, Book &b) {
        out<<b.ISBN<< ": " << b.naslov << ", " << b.avtor << " " << b.bookPrice() << endl;
        
        return out;
    }

    friend ostream &operator<< (ostream &out, Book *b) {
        out<<b->ISBN<< ": " << b->naslov << ", " << b->avtor << " " << b->bookPrice() << endl;
        
        return out;
    }
    
    void setISBN(char *temp){
        strcpy(ISBN, temp);
    }
    
};

class OnlineBook : public Book {
private:
    char *url;
    int golemina;
public:
    OnlineBook() : Book() {
        url=NULL;
    }
    
    OnlineBook(char *ISBN, char *naslov, char *avtor, float cena, char *url, int golemina) : Book(ISBN, naslov, avtor, cena){
        this->url= new char[strlen(url)+1];
        strcpy(this->url, url);
        
        this->golemina=golemina;
    }
    
    OnlineBook (const OnlineBook &obj) : Book(obj){
        this->url= new char[strlen(obj.url)+1];
        strcpy(url, obj.url);
        
        golemina=obj.golemina;
    }
    
    OnlineBook &operator= (const OnlineBook &obj){
        if(this==&obj){
            return *this;
        }
        
        Book::operator=(obj);
        delete [] url;
        
        this->url= new char[strlen(obj.url)+1];
        strcpy(url, obj.url);
        
        golemina=obj.golemina;
        
        return *this;
    }
    
    ~OnlineBook() {
        delete [] url;
    }
    
    float bookPrice(){
        if(golemina>20){
            return cena+(cena*0.2);
        } else {
            return cena;
        }
    }
};

class PrintBook: public Book {
protected:
    float masa;
    bool zaliha;
public:
    PrintBook() : Book() {}
    
    PrintBook(char *ISBN, char *naslov, char *avtor, float cena, float masa, bool zaliha) : Book(ISBN, naslov, avtor, cena) {
        this->masa=masa;
        this->zaliha=zaliha;
    }
    
    float bookPrice(){
        if(masa>0.7){
            return cena+(cena/100*15);
        }else{
            return cena;
        }
    }
    
};

void mostExpensiveBook (Book** books, int n) {
    int o=0, p=0;
    int najskapa=0;
    int ind = 0;
    for(int i=0; i<n; i++){
        OnlineBook* pok1 = dynamic_cast<OnlineBook*>(books[i]);
        PrintBook* pok2 = dynamic_cast<PrintBook*>(books[i]);
        
        if(pok1){
            o++;
        }
        if(pok2){
            p++;
        }
        if(books[i]->bookPrice()>najskapa){
            najskapa=books[i]->bookPrice();
            ind=i;
        }
    }
    
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << o << endl;
    cout << "Total number of print books: " << p << endl;
    
    cout << "The most expensive book is: \n" << books[ind];
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
        delete[] books;
    return 0;
}
