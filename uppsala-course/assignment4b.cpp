
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;
const int ANTAL_SPRAK = 4;

const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};


//--------------------------------------------------------

int berakna_histogram_abs(string const& str, int histogram[]);
void abs_till_rel(int const& num_of_letters, double relative[], int histogram[]);
void plotta_histogram_rel(int const& num_of_letters, double relative[]);
void tolking(double relative[]);
void namn_pa_fil(string& str);
string inlasning(string& str);

//--------------------------------------------------------
// Huvudprogram:
int main() {
    int histogram[ANTAL_BOKSTAVER];
    double relative[ANTAL_BOKSTAVER];
    int num_of_letters;
    string read = "";
    string content;

    // nollställ arrayer
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        histogram[i] = 0;
        relative[i] = 0;
    }

    // Hämta från fil
    cout << "Ange filnamn: " << endl;
    getline(cin,read);
    namn_pa_fil(read);
    content = inlasning(read);

    // kollar om fil finns
    if (content == "no_exist") {
        cout << "\nDet finns ingen fil som heter " << read << endl;
    }
    else {
        num_of_letters = berakna_histogram_abs(content, histogram);

        if (num_of_letters == 0) {
            cout << "\nDet finns inget att beräkna. " << read 
                << " är tom!" << endl;
        }   
        else {
            abs_till_rel(num_of_letters, relative, histogram);
            plotta_histogram_rel(num_of_letters, relative);
            tolking(relative);
        }
    }

    return 0;
}
//--------------------------------------------------------

int berakna_histogram_abs(string const &content, int histogram[]) {
    int num_of_letters = 0, ascii, tmp;

    // kollar varje karaktär om det matchar en bokstav
    // från ASCII tabellen, både stora och små
    for (char const& c : content) {
        ascii = c;
        tmp = ascii;
        tmp -= 97;
        if (tmp < 0) {
            ascii -= 65;
        }
        else {
            ascii = tmp;
        }

        if (0 <= ascii || ascii <= ANTAL_BOKSTAVER) {
            histogram[ascii]++;
            num_of_letters++;
        }
    }

    return num_of_letters;
}

void abs_till_rel(int const& num_of_letters, double relative[], int histogram[]) {
    double ratio;

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        if (histogram[i] != 0) {
            ratio = num_of_letters / histogram[i];
            relative[i] = 100.0 / ratio;
        }
    }
}

void plotta_histogram_rel(int const& num_of_letters, double relative[]) {
    char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                        'H', 'I', 'J', 'K', 'L', 'M', 'N',
                        'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                        'V', 'W', 'X', 'Y', 'Z' };
    int num_of_stars;
    string stars;

    cout << "\nResultat för bokstäverna A-Z" << endl;
    cout << " \nTotala antalet bokstäver: " << num_of_letters << endl;
    cout << "Bokstavsfördelning:\n" << endl;

    // Printar histogramet som sjärnor
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        num_of_stars = relative[i] * 2.0;
        stars = "";
        for (int j = 0; j < num_of_stars; j++) {
            stars += "*";
        }
        cout << alphabet[i] << ": " << stars << endl;
    }
}

void tolking(double relative[]) {
    double sum, difference;
    double probability[ANTAL_SPRAK]; 
    string languages[] = {"engelska", "franska", "svenska", "tyska"};
    string language = "";

    // Beräknar kvadratsumma
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        sum = 0.0;
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            difference = TOLK_HJALP[i][j] - relative[j];
            difference *= difference;
            sum += difference;
        }
        probability[i] = sum;
    }

    double tmp = MAXFLOAT;
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        if (probability[i] < tmp) {
            language = languages[i];
            tmp = probability[i];
        }
    }

    cout << "\nKvadratsumman på de fyra språken: " << endl;
    cout << "engelska: " << probability[0] << endl;
    cout << "franska:  " << probability[1] << endl;
    cout << "svenska:  " << probability[2] << endl;
    cout << "tyska:    " << probability[3] << endl;
    cout << "\nTexten är sannolikt skrivet i språket " << language << "\n" << endl;
}

void namn_pa_fil(string& name) {
    int pos = name.rfind(".txt", string::npos);
    if (pos == string::npos || pos != name.size() - 4) {
        name.append(".txt");
    }
}

string inlasning(string& filename) {
    fstream file;
    string input = "";
    char c;
    file.open(filename, ifstream::in);
    
    if (!file.is_open()) {
        input = "no_exist";
    }
    else {
        while (file.get(c)) {
            input.push_back(c);
        }
        file.close();
    }

    return input;
}

// -------------------------------------------------------
// Rapport om uppgiften
