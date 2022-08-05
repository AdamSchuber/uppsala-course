#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// klass och funktions deklarationer

const int MAX_PERSONER = 100;
const int MAX_TRANSAKTIONER  = 100;

class Transaktion {
public:
    Transaktion();
    ~Transaktion();
    string  hamtaNamn();
    double  HamtaBelopp();
    int     hamtaAntalKompisar();
    bool    finnsKompis(string const& namnet);
    bool    lasIn(istream& is);
    void    skrivUt(ostream& os);
    void    skrivTitel(ostream& os);
private:
    string 	datum;
    string 	typ;
    string 	namn;
    double 	belopp;
    int 	antal_kompisar;
    string 	kompisar[MAX_PERSONER];
};

class Person {
public:
    Person();
    Person(string const& namn, double betalat_andras, double skyldig);
    string  hamtaNamn();
    double  hamtabetalat();
    double  hamtaSkyldig();
    void    skrivUt(ostream& os);
private:
    string namn;
    double betalat_andras;
    double skyldig;
};

class PersonLista {
public:
    PersonLista();
    ~PersonLista();
    void    laggTill(Person ny_person);
    void    skrivUtOchFixa(ostream& os);
    double  summaSkyldig();
    double  summaBetalt();
    bool    finnsPerson(string const& namn);
private:
    int     antal_personer;
    Person  personer[MAX_PERSONER];
};

class TransaktionsLista {
public:
    TransaktionsLista();
    ~TransaktionsLista();
    void    lasIn(istream& is);
    void    skrivUt(ostream& os);
    void    laggTill(Transaktion& t);
    double  totalKostnad();
    double  liggerUteMed(string const& namnet);
    double  arSkyldig(string const& namnet);
    PersonLista fixaPersoner();
private:
    int         antal_transaktioner;
    Transaktion transaktioner[MAX_TRANSAKTIONER];
};

int main()
{
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream is("resa.txt");
  transaktioner.lasIn(is);

  //temp  
  cout << "läst in resa" << endl;

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
              PersonLista lista = transaktioner.fixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

//-----------------------------------------------------

Transaktion::Transaktion() 
	: antal_kompisar{0} {}

Transaktion::~Transaktion() {}

string Transaktion::hamtaNamn() {
    return namn;
}

double Transaktion::HamtaBelopp() {
    return belopp;
}

int Transaktion::hamtaAntalKompisar() {
    return antal_kompisar;
}

bool Transaktion::finnsKompis(string const& namnet) {
    // kollar om kompis finns
    for (int i = 0; i < antal_kompisar; i++) {
        if (kompisar[i] == namnet) {
            return true;
        }
    }
	return false;
}

bool Transaktion::lasIn(istream& is) {
	string friends;
 
  // returnerar false om filen har nått sitt slut
  // eller är otillgänglig
	if (is.eof() || !is) {
    return false;
  }

  // läser in alla värden från istream
  is >> datum >> typ >> namn >> belopp >> antal_kompisar;

  // läser precis antalet kompisar så läsningen inte
  // påbörjar nästa rad
	for (int i = 0; i < antal_kompisar; i++) {
	  is >> friends;
	  kompisar[i] = friends;
	}

  return true;
}

void Transaktion::skrivUt(ostream& os) {
  // skickar till ostream i rätt format med setw()
	os << left << setw(8) << datum 
	   << left << setw(8) << typ
	   << left << setw(8) << namn
	   << left << setw(8) << belopp
	   << left << setw(8) << antal_kompisar;
	
	for (int i = 0; i < antal_kompisar; i++) {
		os << setw(8) << kompisar[i];
	}
	os << endl;
}

void Transaktion::skrivTitel(ostream& os) {
	os << "Datum   Typ     Namn    Belopp  Antal och lista av kompisar" << endl;
}

//-----------------------------------------------------

// initsierar klassens variabler till standard värden
Person::Person() 
	: namn{""}, betalat_andras{0.0}, skyldig{0.0} {};

// andra konstruktorn som initsierar klassens variabler från parameter-listan
Person::Person(string const& namn, double betalat_andras, double skyldig) 
	: namn{namn}, betalat_andras{betalat_andras}, skyldig{skyldig} {}

string Person::hamtaNamn() {
	return namn;
}

double Person::hamtabetalat() {
	return betalat_andras;
}

double Person::hamtaSkyldig() {
	return skyldig;
}

void Person::skrivUt(ostream& os) {
  double sum;

	os << namn
	   << " ligger ute med " << betalat_andras
	   << " och är skyldig " << skyldig;

  sum = betalat_andras - skyldig;
  if (sum < 0.0) {
    os << ". Skall lägga " << abs(sum) << " till potten!" << endl;
  }
  else {
    os << ". Skall ha " << sum << " från potten!" << endl;
  }
}

//-----------------------------------------------------

PersonLista::PersonLista() 
	: antal_personer{0} {}

PersonLista::~PersonLista() {}

void PersonLista::laggTill(Person ny_person) {
  // lägger till en ny person i listan och 
  // inkrementerar antal_personer
	personer[antal_personer] = ny_person;
	antal_personer++;
}

void PersonLista::skrivUtOchFixa(ostream& os) {
  // skriver ut alla personers information
	for (int i = 0; i < antal_personer; i++) {
		personer[i].skrivUt(os);
	}
}

double PersonLista::summaSkyldig() {
  // summerar alla personers skyldigheter i en loop
	double owes = 0.0;
	for (int i = 0; i < antal_personer; i++) {
		owes += personer[i].hamtaSkyldig();
	}
	return owes;
}

double PersonLista::summaBetalt() {
  // summerar alla personers betalningar i en loop
	double payed = 0.0;
	for (int i = 0; i < antal_personer; i++) {
		payed += personer[i].hamtabetalat();
	}
	return payed;
}

bool PersonLista::finnsPerson(string const& namn) {
  // kollar om parameter namnet matchar ett namn
  // i personlistan
	for (int i = 0; i < antal_personer; i++) {
		if (personer[i].hamtaNamn() == namn) {
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------

TransaktionsLista::TransaktionsLista()
	: antal_transaktioner{0} {}

TransaktionsLista::~TransaktionsLista() {
  // destruktor för att ta bort de dynamiskt allokerade
  // transaktionerna
  for (int i = 0; i < antal_transaktioner; i++) {
    delete &transaktioner[i];
  }
}

void TransaktionsLista::lasIn(istream& is) {
  // kollar om istream är öppen och tillgänglig
  if (!is) {
    cout << "kan inte läsa fil!" << endl;
  }

  // loopar och läser in nya transaktioner tills
  // istream is inte har något mer att läsa
	while (true) {
    // dynamiskt allokerar nya transaktions objekt
		Transaktion *t = new Transaktion;
		if (!t->lasIn(is)) {
      delete t;
			break;
		}
		else {
      // lägger till transaktionen i listan
			laggTill(*t);
		}
	}
}

void TransaktionsLista::skrivUt(ostream& os) {
  // skriver ut alla transaktioners information på
  // ett snyggt sätt
	os << "Antal trans = " << antal_transaktioner << endl;
  transaktioner[0].skrivTitel(os);
	for (int i = 0; i < antal_transaktioner; i++) {
		transaktioner[i].skrivUt(os);
	}
}

void TransaktionsLista::laggTill(Transaktion& t) {
  // lägger till en ny transaktion och inkrementerar antal_transaktioner
  transaktioner[antal_transaktioner] = t;
  antal_transaktioner++;
}

double TransaktionsLista::totalKostnad() {
  // summerar den totala kostnaden för alla transaktioner
	double cost = 0.0;
	for (int i = 0; i < antal_transaktioner; i++) {
		cost += transaktioner[i].HamtaBelopp();
	}
	return cost;
}

double TransaktionsLista::liggerUteMed(string const& namnet) {
  // summerar hur mycket pengar en individuell person 
  // ligger ute med och returnerar summan
	double sum = 0;
	for (int i = 0; i < antal_transaktioner; i++) {
		if (transaktioner[i].hamtaNamn() == namnet) {
			sum += transaktioner[i].HamtaBelopp() *
				(1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
		}
	}
	return sum;
}

double TransaktionsLista::arSkyldig(string const& namnet) {
  // summerar hur mycket pengar en individuell person
  // är skyldig och returnerar summan
	double sum = 0.0;
	for (int i = 0; i < antal_transaktioner; i++) {
		if (transaktioner[i].finnsKompis(namnet)) {
			sum += transaktioner[i].HamtaBelopp() *
				(1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
		}
	}
	return sum;
}

PersonLista TransaktionsLista::fixaPersoner() {
  // skapar en PersonLista från alla transaktioner
  // där personens namn, betalningar och skyldigheter länkas 
  // till personen
	PersonLista list;
	string curr_name;
    for (int i = 0; i < antal_transaktioner; i++) {
		curr_name = transaktioner[i].hamtaNamn();
		if (!list.finnsPerson(curr_name)) {
			Person p(curr_name, 
                liggerUteMed(curr_name), arSkyldig(curr_name));
			list.laggTill(p);
		}
	}
	return list;
}