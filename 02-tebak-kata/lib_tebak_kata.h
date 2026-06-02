#include <string>
#include <vector>
using namespace std;

struct KataGame {
		string kata_asli[15];
		vector<int> status_tebakan;
		int sisa_nyawa;
		char tebakan_salah[26];
		int jumlah_salah;
};
