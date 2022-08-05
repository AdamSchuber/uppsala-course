#include <iostream>
using namespace std;

void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int& n1, int& n2);
int berakna(char const& op, int const& n1, int const& n2);
void skrivResultat(int const& result);

int main() {
    skrivInfo();

    int tal1 = lasEttTal();
    int tal2 = lasEttTal();
    char op = lasOp();

    ordna(tal1, tal2);
    int result = berakna(op, tal1, tal2);

    skrivResultat(result);

    return 0;
}

    // Funktion som skriver ut information om programmets funktion
void skrivInfo() {
    cout << "\nMata in två heltal och välj en operator" << endl;
    cout << "för att beräkna talen mellan dem. En operator väljs" << endl;
    cout << "genom att skriva (a) för addition, (m) för" << endl;
    cout << "multiplication och (k) för kvadratsumman. \n" << endl;
}

    // Läser in ett heltal från användaren 
int lasEttTal() {
    cout << "Mata in ett heltal: ";
    int num;
    cin >> num;
    return num;
}

    // Läser in en operator i form av en karaktär
char lasOp() {
    cout << "Mata in en operator: ";
    char c;
    cin >> c;
    return c;
}   

    // Sorterar talen i storleksordning
void ordna(int& n1, int& n2) {
    if (n1 > n2) {
        int n3 = n2;
        n2 = n1;
        n1 = n3;
    }
}

    // Beräknar talen med den givna operatorn
int berakna(char const& op, int const& n1, int const& n2) {
    int num = 0;
    switch (op) {
        case 'a':
            for (int i = n1; i <= n2; i++) {
                num += i;
            }
        break;
        case 'm':
            for (int i = n1; i <= n2; i++) {
                if (i == n1) {
                    num = i;
                }
                else {
                    num *= i;
                }
            }
        break;
        case 'k':
            for (int i = n1; i <= n2; i++) {
                int tmp = i * i;
                num += tmp;
            }
        break;
        default:
            // Felkod om operator är fel!
            return -1;
    }
    return num;
}

    // Skriver ut resultatet av beräkningen
void skrivResultat(int const& result) {
    cout << "Resultatet av beräkningen blev: "
         << result << endl;
}