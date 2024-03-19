#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;

class Transaktion;
class Person;
class PersonLista;
class TransaktionsLista;

class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string *kompisar;
public:
    Transaktion();
    ~Transaktion();
    Transaktion &operator=(const Transaktion &t);
    string hamtaNamn() const;
    double hamtaBelopp() const;
    int hamtaAntalKompisar() const;
    bool finnsKompis(const string &namnet) const;
    bool lasIn(istream &is);
    void skrivUt(ostream &os) const;
    void skrivTitel(ostream&os) const;
};
class Person            //från A-delen, kopierad
{
private:
    string namn;
    double betalt_andras;   //Ligger ute med totalt
    double skyldig;         //Skyldig totalt

public:
    Person();
    Person(const string &namn,double betalt_andras,double skyldig);
    double hamtaBetalt();
    double hamtaSkyldig();
    string hamtaNamn();                 //egen selektor för namn, ska vara OK.
    void skrivUt(ostream &os);

};
class PersonLista
{
private:
    int antal_personer;
    Person *personer;
public:
    PersonLista();
    ~PersonLista();
    PersonLista &operator=(const PersonLista &p);
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig() const;
    double summaBetalat() const;
    bool finnsPerson(const string &namn);
};
class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion *transaktioner;
public:
    TransaktionsLista();
    ~TransaktionsLista();
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad() const;
    double liggerUteMed(const string &namn);
    double arSkyldig(const string &namnet);
    PersonLista FixaPersoner();
};

//Klass Transaktion
Transaktion::Transaktion()
:datum(" "),typ(" "),namn(" "),belopp(0),antal_kompisar(0),kompisar(0)
{}

Transaktion::~Transaktion()
{
    delete[] kompisar;
}

Transaktion& Transaktion::operator=( const Transaktion& t)
{
  if (this != &t)
    {
      delete[] kompisar;
      datum          = t.datum;
      typ            = t.typ;
      namn           = t.namn;
      belopp         = t.belopp;
      antal_kompisar = t.antal_kompisar;
      kompisar       = new string[antal_kompisar];
      for (int i=0; i < antal_kompisar; i++)
            kompisar[i] = t.kompisar[i];
    }
  return *this;
}
string Transaktion::hamtaNamn() const
{
    return namn;
}
double Transaktion::hamtaBelopp() const
{
    return belopp;
}
int Transaktion::hamtaAntalKompisar() const
 {
     return antal_kompisar;
 }
bool Transaktion::finnsKompis(const string &namnet) const
{
    bool finns=false;
    for(int i=0;i<antal_kompisar;i++)
    {
        if(kompisar[i]==namnet)
        {
            finns=true;
            break;
        }
    }
return finns;
}
bool Transaktion::lasIn(istream &is)
{
    is>>datum>>typ>>namn>>belopp>>antal_kompisar;
    kompisar=new string [antal_kompisar];
    for(int i=0;i<antal_kompisar;i++)
        is>>kompisar[i];
    return !is.eof();
}
void Transaktion::skrivUt(ostream &os) const
{
    os<<datum<<" "<<typ<<" "<<namn<<" "<<belopp<<" "<<antal_kompisar;
    for(int i=0;i<antal_kompisar;i++)
        os<<" "<<kompisar[i];
}
void Transaktion::skrivTitel(ostream &os) const
{
    os<<"Datum  Typ  Namn  Belopp  Antalet kompisar  Namn:"<<endl;
}
//Class person
Person::Person()        //Standardkonstuktor
:namn(""),betalt_andras(0),skyldig(0)
{}

Person::Person(const string &namn, double betalt_andras,double skyldig)     //Överlagrad konstruktor
:namn(namn),betalt_andras(betalt_andras),skyldig(skyldig)
{}
//Selektorer
double Person::hamtaBetalt()
{
    return betalt_andras;
}
double Person::hamtaSkyldig()
{
    return skyldig;
}
string Person::hamtaNamn()
{
    return namn;
}
//Enda metoden i klassen är skrivUt
void Person::skrivUt(ostream &os)
{

    cout<<namn<<" ligger ute med "<<betalt_andras<<" och är skyldig "<<skyldig;
    if(betalt_andras>skyldig)
        cout<<". "<<namn<<" skall ha "<<betalt_andras-skyldig<<" från potten!"<<endl;
    if(skyldig>betalt_andras)
        cout<<". "<<namn<<" skall betala "<<skyldig-betalt_andras<<" till potten!"<<endl;
}


//personlista
PersonLista::PersonLista()
:antal_personer(0),personer(0)
{}
PersonLista::~PersonLista()
{
    delete[] personer;
}
PersonLista &PersonLista::operator=(const PersonLista &p)
{
    if(this!=&p)
    {
        delete [] personer;
        antal_personer=p.antal_personer;
        personer=new Person[antal_personer];
        for(int i=0;i<antal_personer;i++)
            personer[i]=p.personer[i];
    }
    return *this;
}
void PersonLista::laggTill(Person ny_person)
{
    Person *temp=new Person[antal_personer+1];
    for(int i=0;i<antal_personer;i++)
        temp[i]=personer[i];
    temp[antal_personer++]=ny_person;
    delete[] personer;
    personer=temp;
}
void PersonLista::skrivUtOchFixa(ostream &os)
{
    double summa;
    for(int i=0;i<antal_personer;i++)
    {
        personer[i].skrivUt(os);
        summa=personer[i].hamtaBetalt()-personer[i].hamtaSkyldig();
    }
if(summa==0)
    cout<<"Betalningar och skulder går jämnt upp!"<<endl;
}
double PersonLista::summaSkyldig() const
{
    double sum=0;
    for(int i=0;i<antal_personer;i++)
        sum+=personer[i].hamtaSkyldig();
    return sum;
}
double PersonLista::summaBetalat() const
{
    double sum=0;
    for(int i=0;i<antal_personer;i++)
        sum+=personer[i].hamtaBetalt();
    return sum;
}
bool PersonLista::finnsPerson(const string &namn)
{
    bool finns=false;
    for(int i=0;i<antal_personer;i++)
    {
        if(personer[i].hamtaNamn()==namn)
        {
            finns=true;
            break;
        }
    }
return finns;
}

//class TransaktionsLista
TransaktionsLista::TransaktionsLista()
:antal_transaktioner(0),transaktioner(0)
{}
TransaktionsLista::~TransaktionsLista()
{
    delete[] transaktioner;
}
void TransaktionsLista::lasIn(istream &is)
{
    Transaktion t;
    while(t.lasIn(is))
        laggTill(t);
}
void TransaktionsLista::skrivUt(ostream &os)
{
    os<<"Antal transaktioner: "<<antal_transaktioner<<endl;
    Transaktion t;
    t.skrivTitel(os);
    for(int i=0;i<antal_transaktioner;i++)
        transaktioner[i].skrivUt(os);
}
void TransaktionsLista::laggTill(Transaktion &t)
{
    Transaktion *temp=new Transaktion[antal_transaktioner+1];
    for(int i=0;i<antal_transaktioner;i++)
        temp[i]=transaktioner[i];
    temp[antal_transaktioner++]=t;
    delete[] transaktioner;
    transaktioner=temp;
}
double TransaktionsLista::totalKostnad() const
{
    double sum=0;
    for(int i=0;i<antal_transaktioner;i++)
        sum+=transaktioner[i].hamtaBelopp();
    return sum;
}
double TransaktionsLista::liggerUteMed(const string &namn)
 {
   double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namn)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
   return summa;
 }
double TransaktionsLista::arSkyldig(const string &namn)
{
    double sum=0;
    for(int i=0;i<antal_transaktioner;i++)
    {
        if(transaktioner[i].finnsKompis(namn))
            sum+=transaktioner[i].hamtaBelopp()/(transaktioner[i].hamtaAntalKompisar()+1);
    }
}
PersonLista TransaktionsLista::FixaPersoner()
{
    PersonLista fixa;
    for(int i=0;i<antal_transaktioner;i++)
    {
        string namn=transaktioner[i].hamtaNamn();
        if(!fixa.finnsPerson(namn))
        {
            fixa.laggTill(Person(namn,liggerUteMed(namn),arSkyldig(namn)));
        }
    }
return fixa;
}





int main()
{
   TransaktionsLista transaktioner;
  std::ifstream     is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivTitel(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ar_skyldig = transaktioner.arSkyldig(namn);
              if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;
              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}
