#include <string>
#include <vector>
using namespace std;

struct KataGame {
		vector<string> kata_asli;
		vector<int> status_tebakan;
		int sisa_nyawa;
		char tebakan_salah[26];
		int jumlah_salah;
};
