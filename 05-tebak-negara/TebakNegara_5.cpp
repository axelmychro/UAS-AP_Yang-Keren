#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> daftarNegara = {
    "indonesia", "malaysia", "singapura", "thailand", "vietnam", "arab saudi"
};

string buatTebakan(const string& negara) {
    string tebakan = negara;
    
    int jumlahHilang = negara.length() * (40 + rand() % 21) / 100;
    if (jumlahHilang < 1) jumlahHilang = 1;

    int tersembunyi = 0;
    while (tersembunyi < jumlahHilang) {
        int indeksAcak = rand() % negara.length();
        
        if (tebakan[indeksAcak] != ' ' && tebakan[indeksAcak] != '_') {
            tebakan[indeksAcak] = '_';
            tersembunyi++;
        }
    }
    return tebakan;
}

int main() {
    srand(time(0)); 

    cout << "      GAME TEBAK NEGARA       " << endl;

    int skor = 0;
    char lagi;

    do {
        string negara = daftarNegara[rand() % daftarNegara.size()];
        string tebakan = buatTebakan(negara);

        cout << "\nTebak negara: " << tebakan << endl;
        cout << "Negara apakah yang dimaksud? ";

        string jawaban;
        
        if (skor > 0 || lagi == 'y') { 
            cin.ignore(); 
        }
        
        getline(cin, jawaban);

        for (int i = 0; i < jawaban.length(); i++) {
            jawaban[i] = tolower(jawaban[i]);
        }

        if (jawaban == negara) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        } else {
            cout << "Maaf, Jawaban anda salah. Jawaban yang benar: " << negara << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> lagi;

    } while (tolower(lagi) == 'y');

    cout << "\nGame Selesai. Terima kasih! :D" << endl;
    return 0;
}