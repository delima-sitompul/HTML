#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

// Struct untuk menyimpan data riwayat kunjungan dokter
struct Kunjungan
{
    int id;
    string namaPasien;
    string namaDokter;
    string tanggalKunjungan;
    Kunjungan *berikutnya;
};

// Fungsi untuk menambahkan data kunjungan baru
void tambahKunjungan(Kunjungan **kepala)
{
    Kunjungan *kunjunganBaru = new Kunjungan();

    cout << "=== Tambah Kunjungan ===" << endl;
    cout << "ID: ";
    cin >> kunjunganBaru->id;
    cin.ignore();
    cout << "Nama Pasien: ";
    getline(cin, kunjunganBaru->namaPasien);
    cout << "Nama Dokter: ";
    getline(cin, kunjunganBaru->namaDokter);
    cout << "Tanggal Kunjungan (DD-MM-YYYY): ";
    getline(cin, kunjunganBaru->tanggalKunjungan);

   kunjunganBaru->berikutnya = nullptr; // Node baru belum memiliki node berikutnya

    // Jika linked list kosong
    if (*kepala == nullptr) {
        *kepala = kunjunganBaru;
    } else {
        // Traverse ke akhir linked list dan tambahkan node baru di akhir
        Kunjungan* sementara = *kepala;
        while (sementara->berikutnya != nullptr) {
            sementara = sementara->berikutnya;
        }
        sementara->berikutnya = kunjunganBaru;
    }
}

// Fungsi untuk menampilkan semua riwayat kunjungan
void tampilkanKunjungan(Kunjungan *kepala){
    cout << "=== Riwayat Kunjungan Dokter ===" << endl;
    if (kepala == nullptr){
        cout << "Tidak ada kunjungan yang tercatat" << endl;
    }
    else {
        Kunjungan* sementara = kepala;
        while (sementara != nullptr) {
            cout << "ID: " << sementara->id << endl;
            cout << "Nama Pasien: " << sementara->namaPasien << endl;
            cout << "Nama Dokter: " << sementara->namaDokter << endl;
            cout << "Tanggal Kunjungan: " << sementara->tanggalKunjungan << endl;
            cout << "---------------------------------------" << endl;
            sementara = sementara->berikutnya;
        }
    }
    sleep(3);
}

// Fungsi untuk mengupdate data kunjungan
void updateKunjungan(Kunjungan *kepala)
{
    int idCari;
    cout << "Masukkan ID kunjungan yang ingin di-update: ";
    cin >> idCari;
    cin.ignore();

    Kunjungan *sementara = kepala;
    while (sementara != nullptr)
    {
        if (sementara->id == idCari){
            cout << "Nama Pasien baru: ";
            cin.ignore();
            getline(cin, sementara->namaPasien);
            cout << "Nama Dokter baru: ";
            getline(cin, sementara->namaDokter);
            cout << "Tanggal Kunjungan baru (DD-MM-YYYY): ";
            getline(cin, sementara->tanggalKunjungan);
            cout << "Data berhasil di-update!" << endl;
            return;
        }
        sementara = sementara->berikutnya;
    }

    cout << "Kunjungan dengan ID " << idCari << " tidak ditemukan" << endl;
}

// Fungsi untuk menghapus data kunjungan
void hapusKunjungan(Kunjungan **kepala)
{
    int idCari;
    cout << "Masukkan ID kunjungan yang ingin dihapus: ";
    cin >> idCari;

    Kunjungan *sementara = *kepala;
    Kunjungan *sebelumnya = nullptr;

    if (sementara != nullptr && sementara->id == idCari){
        *kepala = sementara->berikutnya; // Node pertama dihapus
        delete sementara;
        cout << "Data berhasil dihapus!" << endl;
        return;
    }

    // Mencari node yang ingin dihapus
    while (sementara != nullptr && sementara->id != idCari){
        sebelumnya = sementara;
        sementara = sementara->berikutnya;
    }

    // Jika ID tidak ditemukan
    if (sementara == nullptr){
        cout << "Kunjungan dengan ID " << idCari << " tidak ditemukan." << endl;
        return;
    }

    // Menghapus node
    sebelumnya->berikutnya = sementara->berikutnya;
    delete sementara;
    cout << "Data berhasil dihapus!" << endl;
}

int main()
{
    const int MAX_KUNJUNGAN = 100;
    Kunjungan kunjunganList[MAX_KUNJUNGAN];
    Kunjungan* kepala = nullptr; // Awalnya linked list kosong
    int pilihan;
    do
    {
        cout << "+-------------------------------------+" << endl;
        cout << "| Pencatatan Riwayat Kunjungan Dokter |" << endl;
        cout << "+-------------------------------------+" << endl;
        cout << "|1. Tambah Kunjungan                  |" << endl;
        cout << "|2. Tampilkan Kunjungan               |" << endl;
        cout << "|3. Update Kunjungan                  |" << endl;
        cout << "|4. Hapus Kunjungan                   |" << endl;
        cout << "|5. Keluar                            |" << endl;
        cout << "+-------------------------------------+" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambahKunjungan(&kepala);
            break;
        case 2:
            tampilkanKunjungan(kepala);
            break;
        case 3:
            updateKunjungan(kepala);
            break;
        case 4:
            hapusKunjungan(&kepala);
            break;
        case 5:
            cout << "Keluar dari program" << endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
