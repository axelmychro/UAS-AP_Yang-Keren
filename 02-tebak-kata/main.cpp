#include "lib_tebak_kata.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

void log(string msg)
{
		cout << " => " << msg << endl;
}

int input(string msg)
{
		cout << msg << "=";
		int option;
		cin >> option;
		return option;
}

char tebak(string msg)
{
		cout << msg << "=";
		char alfabet;
		cin >> alfabet;
		return alfabet;
}

int main()
{
		char main_lagi;

		do {
				/*
                 * INISIALISASI
                 */
				KataGame game;
				game.kata_asli = { "lompat",   "gaya",		 "tanaman",
								   "bibi",	   "pencarian",	 "kesempatan",
								   "hamparan", "bersyukur",	 "asumsi",
								   "rahang",   "pingsan",	 "saksi",
								   "rekaman",  "narasumber", "simulasi" };

				string kata_rahasia = game.pilihKataAcak();
				game.status_tebakan.clear();
				game.jumlah_salah = 0;

				// jika tidak direset, akan segfault
				for (int i = 0; i < kata_rahasia.size(); ++i) {
						game.status_tebakan.push_back(0);
				}

				/*
                 * Pemilihan tingkat kesulitan
                 */
				system("clear");
				log("Tingkat kesulitan: ");
				log("1. Mudah  (8 nyawa, default)");
				log("2. Sedang (6 nyawa)");
				log("3. Sulit  (4 nyawa)");

				switch (input("pilihan")) {
				case 2:
						game.sisa_nyawa = 6;
						break;
				case 3:
						game.sisa_nyawa = 4;
						break;
				case 1:
				default:
						if (cin.fail()) {
								cin.clear();
								string b;
								cin >> b;
						}
						game.sisa_nyawa = 8;
						break;
				};

				while (true) {
						if (game.sisa_nyawa <= 0) {
								system("clear");
								log("Anda gagal");
								log("Kata rahasia: " + kata_rahasia);
								break;
						}

						bool semua_terbuka = true;
						for (int status : game.status_tebakan) {
								if (status == 0) {
										semua_terbuka = false;
										break;
								}
						}

						if (semua_terbuka) {
								system("clear");
								log("Anda berhasil menebak " + kata_rahasia);
								break;
						}

						system("clear");
						log("for debug: " + kata_rahasia);
						log("Sisa nyawa    : " + to_string(game.sisa_nyawa));

						cout << " => Tebakan salah : ";
						for (int k = 0; k < game.jumlah_salah; ++k) {
								cout << game.tebakan_salah[k] << " ";
						}
						cout << endl;

						cout << " => Kata          : ";
						for (int j = 0; j < kata_rahasia.size(); ++j) {
								if (game.status_tebakan[j] == 1)
										cout << kata_rahasia[j];
								else
										cout << "_";
						}
						cout << "\n\n";

						char huruf_tebakan =
								tebak("Masukkan tebakan huruf Anda");

						bool duplikat = false;

						for (int k = 0; k < game.jumlah_salah; ++k) {
								if (game.tebakan_salah[k] == huruf_tebakan) {
										duplikat = true;
										break;
								}
						}

						for (int j = 0; j < kata_rahasia.size(); ++j) {
								if (kata_rahasia[j] == huruf_tebakan &&
									game.status_tebakan[j] == 1) {
										duplikat = true;
										break;
								}
						}

						if (duplikat) {
								log("Peringatan: Huruf '" +
									string(1, huruf_tebakan) +
									"' sudah pernah ditebak sebelumnya!");
								cout << "Tekan Enter untuk memasukkan huruf lain...";
								cin.ignore();
								cin.get();
								continue;
						}

						bool ditemukan = false;
						for (int j = 0; j < kata_rahasia.size(); ++j) {
								if (kata_rahasia[j] == huruf_tebakan) {
										game.status_tebakan[j] = 1;
										ditemukan = true;
								}
						}

						if (!ditemukan) {
								game.tebakan_salah[game.jumlah_salah] =
										huruf_tebakan;
								game.jumlah_salah += 1;
								game.sisa_nyawa -= 1;
								log("Tebakan Salah!");
						} else {
								log("Tebakan Benar!");
						}
				}

				cout << "\nMain lagi? (y/n)=";
				cin >> main_lagi;

		} while (main_lagi == 'Y' || main_lagi == 'y');
		return 0;
}
