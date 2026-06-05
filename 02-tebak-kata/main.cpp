#include <iostream>
#include "lib_tebak_kata.h"
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
		/*
		 * INISIALISASI
		 */
		KataGame game;
		game.kata_asli = { "lompat",	"gaya",		  "tanaman",  "bibi",
						   "pencarian", "kesempatan", "hamparan", "bersyukur",
						   "asumsi",	"rahang",	  "pingsan",  "saksi",
						   "rekaman",	"narasumber", "simulasi" };

		//cout << time(0) << endl;
		string kata_rahasia = game.pilihKataAcak();

		// jika belum direset, akan segfault
		for (int i = 0; i < kata_rahasia.size(); ++i)
				game.status_tebakan.push_back(0);

		/*
	     * Memilih tingkat kesulitan
	     */
		log("Tingkat kesulitan: ");
		log("1. Mudah  (8 nyawa, default)");
		log("2. Sedang (6 nyawa)");
		log("3. Sulit  (4 nyawa)");

		switch (input("pilihan")) {
		default:
				log("Pilihan tidak tersedia, kesulitan mudah terpilih");
		case 1:
				game.sisa_nyawa = 8;
				break;
		case 2:
				game.sisa_nyawa = 6;
				break;
		case 3:
				game.sisa_nyawa = 4;
				break;
		};

		log("Jumlah karakter: " + to_string(kata_rahasia.size()));
		log("Sisa nyawa     : " + to_string(game.sisa_nyawa));

		for (int i = 0; i < kata_rahasia.size(); ++i) {
				log("for debug: " + kata_rahasia);

				cout << "Kata: ";
				for (int j = 0; j < kata_rahasia.size(); ++j) {
						if (game.status_tebakan[j] == 1)
								cout << kata_rahasia[j];
						else
								cout << "_";
				}
				cout << endl;

				while (game.status_tebakan[i] == 0) {
						if (tebak("tebak huruf ke-" + to_string(i)) ==
							kata_rahasia[i])
								game.status_tebakan[i] = 1;
				}
		}

		return 0;
}
