#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
using namespace std;


struct Kendaraan {
    string platMobil;
    string merkMobil;
    string warnaMobil;
    chrono::time_point<chrono::steady_clock> waktuMasuk;
};

struct Petugas {
    string nama;
    string id;
};

const int KAPASITAS_MAKS = 20;
vector<Kendaraan*> daftarParkir; 
Petugas petugas;

void cetakGaris(char c = '=', int panjang = 80) {
    for (int i = 0; i < panjang; i++) cout << c;
    cout << endl;
}

void cetakTengah(const string& teks, int lebar = 80) {
    int spasi = (lebar - (int)teks.size()) / 2;
    if (spasi > 0) cout << string(spasi, ' ');
    cout << teks << endl;
}

string formatDurasi(chrono::time_point<chrono::steady_clock> waktuMasuk) {
    auto sekarang = chrono::steady_clock::now();
    auto durasi = chrono::duration_cast<chrono::seconds>(sekarang - waktuMasuk).count();

    int jam = durasi / 3600;
    int menit = (durasi % 3600) / 60;
    int detik = durasi % 60;

    return to_string(jam) + " jam " + to_string(menit) + " menit " + to_string(detik) + " detik";
}

long long getDurasiDetik(chrono::time_point<chrono::steady_clock> waktuMasuk) {
    auto sekarang = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::seconds>(sekarang - waktuMasuk).count();
}

void tampilkanHeader() {
    cetakGaris('=');
    cetakGaris('-');
    cetakTengah("S E L A M A T   D A T A N G");
    cetakTengah("DI PORTAL PARKIR KHUSUS MOBIL");
    cetakTengah("MALL PRIENAL");
    cetakGaris('-');
    cetakGaris('=');
}

void inputPetugas() {
    tampilkanHeader();
    cout << endl;
    cout << "Kami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini." << endl;
    cout << endl;
    cout << "Masukkan nama : ";
    getline(cin, petugas.nama);
    cout << "Masukkan ID   : ";
    getline(cin, petugas.id);
}

void tampilkanMenuUtama() {
    cout << endl;
    cetakGaris('=');
    cout << "Nama Petugas : " << petugas.nama << endl;
    cout << "ID Petugas   : " << petugas.id << endl;
    cetakGaris('-');
    cetakTengah("TERIMA KASIH ATAS KERJASAMANYA !");
    cetakTengah("- S E L A M A T   B E R T U G A S -");
    cetakGaris('=');
    cout << endl;
    cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
    cout << "1. Tambahkan Daftar Kendaraan" << endl;
    cout << "2. Tampilkan Daftar Kendaraan" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "Masukkan opsi : ";
}

void tambahKendaraan() {
    int jumlah;
    cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlah;
    cin.ignore();

    if ((int)daftarParkir.size() + jumlah > KAPASITAS_MAKS) {
        cout << "Maaf, parkiran hanya dapat memuat " << KAPASITAS_MAKS << " mobil." << endl;

        int sisaSlot = KAPASITAS_MAKS - (int)daftarParkir.size();
        if (sisaSlot <= 0) {
            cout << "Parkiran sudah penuh!" << endl;
            return;
        }
        jumlah = sisaSlot;
        cout << "Hanya " << jumlah << " mobil yang dapat ditambahkan." << endl;
    }

    for (int i = 1; i <= jumlah; i++) {
        Kendaraan* k = new Kendaraan();
        cout << endl;
        cout << "Mobil ke " << i << endl;
        cout << "Masukkan plat mobil  : ";
        getline(cin, k->platMobil);
        cout << "Masukkan merk mobil  : ";
        getline(cin, k->merkMobil);
        cout << "Masukkan warna mobil : ";
        getline(cin, k->warnaMobil);
        k->waktuMasuk = chrono::steady_clock::now();
        daftarParkir.push_back(k);
    }
}

void tampilkanKendaraan() {
    if (daftarParkir.empty()) {
        cout << "Tidak ada kendaraan yang sedang parkir." << endl;
        return;
    }

    cetakGaris('=');
    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :" << endl;
    cetakGaris('=');

    for (int i = 0; i < (int)daftarParkir.size(); i++) {
        Kendaraan* k = daftarParkir[i];
        cout << endl;
        cout << "Mobil ke-" << (i + 1) << endl;
        cetakGaris('-');
        cout << "Plat mobil  : " << k->platMobil << endl;
        cout << "Merk mobil  : " << k->merkMobil << endl;
        cout << "Warna mobil : " << k->warnaMobil << endl;
        cout << "Waktu parkir: " << formatDurasi(k->waktuMasuk) << endl;
        cetakGaris('-');
    }
}

void pembayaran() {
    if (daftarParkir.empty()) {
        cout << "Tidak ada kendaraan yang sedang parkir." << endl;
        return;
    }


    tampilkanKendaraan();

    string platCari;
    cout << endl;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    cin.ignore();
    getline(cin, platCari);


    int index = -1;
    for (int i = 0; i < (int)daftarParkir.size(); i++) {
   
        string platDB = daftarParkir[i]->platMobil;
        string platInput = platCari;
        transform(platDB.begin(), platDB.end(), platDB.begin(), ::toupper);
        transform(platInput.begin(), platInput.end(), platInput.begin(), ::toupper);

        if (platDB == platInput) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "PLAT TIDAK DITEMUKAN !" << endl;

        cout << endl;
        cout << "Masukkan plat mobil yang ingin dibayar : ";
        getline(cin, platCari);

        for (int i = 0; i < (int)daftarParkir.size(); i++) {
            string platDB = daftarParkir[i]->platMobil;
            string platInput = platCari;
            transform(platDB.begin(), platDB.end(), platDB.begin(), ::toupper);
            transform(platInput.begin(), platInput.end(), platInput.begin(), ::toupper);

            if (platDB == platInput) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "PLAT TIDAK DITEMUKAN !" << endl;
            return;
        }
    }

 
    Kendaraan* k = daftarParkir[index];
    long long durasiDetik = getDurasiDetik(k->waktuMasuk);
   
    long long menitParkir = max(1LL, durasiDetik / 60);
    long long biaya = menitParkir * 2000;

    cout << "B I A Y A   P A R K I R : Rp" << biaya << endl;


    delete daftarParkir[index];
    daftarParkir.erase(daftarParkir.begin() + index);
}


int main() {
    inputPetugas();
    system("cls");
    int opsi;
    do {
        tampilkanMenuUtama();
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                tambahKendaraan();
                break;
            case 2:
                tampilkanKendaraan();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                cout << endl;
                cetakGaris('=');
                cetakTengah("Terima kasih, " + petugas.nama + "!");
                cetakTengah("Sampai jumpa dan selamat beristirahat.");
                cetakGaris('=');
                break;
            default:
                cout << "Opsi tidak valid. Silahkan pilih 1-4." << endl;
                break;
        }
    } while (opsi != 4);

    for (Kendaraan* k : daftarParkir) {
        delete k;
    }
    daftarParkir.clear();

    return 0;
}