#include <iostream>
#include <iomanip>
using namespace std;

int SegitigaPascal(int n, int kolom) {
    if (kolom == 0 || kolom == n){
        return 1;
    }
    return SegitigaPascal(n -1, kolom - 1) + SegitigaPascal(n- 1, kolom);
}

void cetakSegitigaPascal(int tingkat){
    for (int baris = 0; baris < tingkat; ++baris){

     for (int kolom = 0; kolom <= baris; ++kolom){
        cout << SegitigaPascal(baris, kolom) <<" ";
    }
    cout << endl;
     }
}

int main() {
    int tingkat = 3;
    cetakSegitigaPascal(tingkat);
    return 0;
}
