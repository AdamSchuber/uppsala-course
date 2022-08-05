#include <iostream>
using namespace std;

int main() {
    // deklarerar variabler och sätter "default" värden
    int start_nr = 1, start_hour, start_min, start_sec;
    int finish_hour, finish_min, finish_sec;
    int winner_nr, winner_hour = 99, winner_min = 99, winner_sec = 99;
    int contestants = 0;

    // loop för att läsa in tävlande och deras tid
    while (true) {
        
        // läser in startnummer
        cout << "Startnummer? ";
        cin >> start_nr;

        // kollar om inläsningen ska avbrytas
        if (start_nr < 1) {
            break;
        }

        // läser in starttid
        cout << "Starttid? ";
        cin >> start_hour >> start_min >> start_sec;

        // läser in måltid
        cout << "Måltid? ";
        cin >> finish_hour >> finish_min >> finish_sec;

        // beräknar sluttid genom att ta skillanden
        // mellan start och sluttid och anpassa efter
        // 24-timmars formatet!
        if (finish_hour < start_hour) {
            finish_hour = finish_hour + 24;
        }
        finish_hour = finish_hour - start_hour;
        finish_min = finish_min - start_min;
        finish_sec = finish_sec - start_sec;
        if (finish_sec < 0) {
            finish_sec = 60 + finish_sec;
            finish_min = finish_min - 1;
        }
        if (finish_min < 0) {
            finish_min = 60 + finish_min;
            finish_hour = finish_hour - 1;
        }
        if (finish_hour < 0) {
            finish_hour = 24 + finish_hour;
        }

        // verifierar om tävlande har snabbaste
        // tiden hitills och är en temporär vinnare
        if (finish_hour < winner_hour) {
            winner_hour = finish_hour;
            winner_min = finish_min;
            winner_sec = finish_sec;
            winner_nr = start_nr;
        }
        else if (finish_hour == winner_hour && finish_min < winner_min) {
            winner_hour = finish_hour;
            winner_min = finish_min;
            winner_sec = finish_sec;
            winner_nr = start_nr;
        }
        else if (finish_hour == winner_hour && finish_min == winner_min && finish_sec < winner_sec) {
            winner_hour = finish_hour;
            winner_min = finish_min;
            winner_sec = finish_sec;
            winner_nr = start_nr;
        }

        // lägger till en till tävlande
        contestants++;
    }

    // kollar om det finns tävlande
    if (contestants < 1) {
        cout << "Inga tävlande " << endl;
    }
    else {
        // printar vinnare och dens tid
        cout << "Vinnare är startnr: " << winner_nr << endl;
        cout << "Tim: " << winner_hour
            << " Min: " << winner_min
            << " Sek: " << winner_sec << endl;

        // printar antal tävlande
        cout << "Antal tävlande: " << contestants << endl;

    }
    
    cout << "Programmet avslutas" << endl;

    return 0;
}