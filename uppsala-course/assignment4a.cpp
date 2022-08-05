#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26; // A-Z

//--------------------------------------------------------

int berakna_histogram_abs(string const& content, int histogram[]);
void skriv_histogram_abs(int const& num_of_letters, int histogram[]);

//--------------------------------------------------------

int main() {
    int histogram[ANTAL_BOKSTAVER];
    int num_of_letters;

    string content = "";
    cout << "Ge en rad med text: " << endl;
    getline(cin, content);
    
    num_of_letters = berakna_histogram_abs(content, histogram);
    skriv_histogram_abs(num_of_letters, histogram);

    return 0;
}

//--------------------------------------------------------

int berakna_histogram_abs(string const &content, int histogram[]) {
    int num_of_letters = 0, ascii, tmp;

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        histogram[i] = 0;
    }

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
        if (0 <= ascii || ascii <= 26) {
            histogram[ascii]++;
            num_of_letters++;
        }
    }
    
    return num_of_letters;
}

void skriv_histogram_abs(int const& num_of_letters, int histogram[]) {
    char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                        'H', 'I', 'J', 'K', 'L', 'M', 'N',
                        'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                        'V', 'W', 'X', 'Y', 'Z' };
    
    cout << "\nResultat för bokstäverna A-Z" << endl;
    cout << " \nTotala antalet bokstäver: " << num_of_letters << endl;
    cout << "Bokstavsfördelning:\n" << endl;

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        cout << alphabet[i] << ": " << histogram[i] << endl;
    }
}

// Redovisning av uppgiften i ord.