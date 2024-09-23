#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

// Struct untuk menyimpan data riwayat kunjungan dokter
struct Kunjungan {
    int id;
    string namaPasien;
    string namaDokter;
    string tanggalKunjungan;
};

// Fungsi untuk menambahkan data kunjungan baru
void tambahKunjungan(Kunjungan* kunjunganList, int* jumlahKunjungan) {
    cout << "=== Tambah Kunjungan ===" << endl;
    cout << "ID: ";
    cin >> kunjunganList[*jumlahKunjungan].id;
    cin.ignore(); 
    cout << "Nama Pasien: ";
    getline(cin, kunjunganList[*jumlahKunjungan].namaPasien);
    cout << "Nama Dokter: ";
    getline(cin, kunjunganList[*jumlahKunjungan].namaDokter);
    cout << "Tanggal Kunjungan (DD-MM-YYYY): ";
    getline(cin, kunjunganList[*jumlahKunjungan].tanggalKunjungan);

    (*jumlahKunjungan)++;
}

// Fungsi untuk menampilkan semua riwayat kunjungan
void tampilkanKunjungan(Kunjungan* kunjunganList, int jumlahKunjungan) {
    cout << "=== Riwayat Kunjungan Dokter ===" << endl;
    if (jumlahKunjungan == 0) {
        cout << "Tidak ada kunjungan yang tercatat." << endl;
    } else {
        for (int i = 0; i < jumlahKunjungan; i++) {
            cout << "ID: " << kunjunganList[i].id << endl;
            cout << "Nama Pasien: " << kunjunganList[i].namaPasien << endl;
            cout << "Nama Dokter: " << kunjunganList[i].namaDokter << endl;
            cout << "Tanggal Kunjungan: " << kunjunganList[i].tanggalKunjungan << endl;
            cout << "---------------------------------------" << endl;
        }
    }
    sleep(3);
}

// Fungsi untuk mengupdate data kunjungan
void updateKunjungan(Kunjungan* kunjunganList, int jumlahKunjungan) {
    int idCari;
    cout << "Masukkan ID kunjungan yang ingin di-update: ";
    cin >> idCari;

    for (int i = 0; i < jumlahKunjungan; i++) {
        if (kunjunganList[i].id == idCari) {
            cout << "Nama Pasien baru: ";
            cin.ignore(); 
            getline(cin, kunjunganList[i].namaPasien);
            cout << "Nama Dokter baru: ";
            getline(cin, kunjunganList[i].namaDokter);
            cout << "Tanggal Kunjungan baru (DD-MM-YYYY): ";
            getline(cin, kunjunganList[i].tanggalKunjungan);
            cout << "Data berhasil di-update!" << endl;
            return;
        }
    }

    cout << "Kunjungan dengan ID " << idCari << " tidak ditemukan." << endl;
}

// Fungsi untuk menghapus data kunjungan
void hapusKunjungan(Kunjungan* kunjunganList, int* jumlahKunjungan) {
    int idCari;
    cout << "Masukkan ID kunjungan yang ingin dihapus: ";
    cin >> idCari;

    for (int i = 0; i < *jumlahKunjungan; i++) {
        if (kunjunganList[i].id == idCari) {
            for (int j = i; j < (*jumlahKunjungan) - 1; j++) {
                kunjunganList[j] = kunjunganList[j + 1];
            }
            (*jumlahKunjungan)--;
            cout << "Data berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "Kunjungan dengan ID " << idCari << " tidak ditemukan." << endl;
}

int main() {
    const int MAX_KUNJUNGAN = 100;
    Kunjungan kunjunganList[MAX_KUNJUNGAN]; 
    int jumlahKunjungan = 0; 
    int pilihan;
    do {
        cout << "+-------------------------------------+" << endl;
        cout << "| Pencatatan Riwayat Kunjungan Dokter |" << endl;
        cout << "+-------------------------------------+" << endl;
        cout << "1. Tambah Kunjungan" << endl;
        cout << "2. Tampilkan Kunjungan" << endl;
        cout << "3. Update Kunjungan" << endl;
        cout << "4. Hapus Kunjungan" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); 

        switch (pilihan) {
            case 1:
                tambahKunjungan(kunjunganList, &jumlahKunjungan);
                break;
            case 2:
                tampilkanKunjungan(kunjunganList, jumlahKunjungan);
                break;
            case 3:
                updateKunjungan(kunjunganList, jumlahKunjungan);
                break;
            case 4:
                hapusKunjungan(kunjunganList, &jumlahKunjungan);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    return 0;
}
