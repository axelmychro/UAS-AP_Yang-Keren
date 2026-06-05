#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

struct KataGame {
		vector<string> kata_asli;
		vector<int> status_tebakan;
		int sisa_nyawa = 0;
		char tebakan_salah[26];
		int jumlah_salah = 0;

		string pilihKataAcak()
		{
				srand(time(0));
				int angka_acak = rand() % kata_asli.size() + 0;
				return kata_asli[angka_acak];
		}
};
