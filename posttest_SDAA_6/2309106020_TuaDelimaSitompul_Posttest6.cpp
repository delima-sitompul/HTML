#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Struct untuk menyimpan data riwayat kunjungan dokter
struct Kunjungan {
    int id;
    string namaPasien;
    string namaDokter;
    string tanggalKunjungan; 
    Kunjungan* berikutnya;
};

// Stack untuk menyimpan riwayat kunjungan
struct Stack {
    Kunjungan* top;
};

// Queue untuk antrian pasien
struct Queue {
    Kunjungan* depan;
    Kunjungan* belakang;
};

// Fungsi untuk mengubah format tanggal ke bentuk YYYY-MM-DD
string formatTanggal(const string& tanggal) {
    return tanggal.substr(6, 4) + "-" + tanggal.substr(3, 2) + "-" + tanggal.substr(0, 2);
}

// Fungsi untuk mencari ID menggunakan Fibonacci Search
int fibonacciSearch(vector<Kunjungan*>& list, int id) {
    int n = list.size();
    int fib2 = 0, fib1 = 1, fibM = fib2 + fib1;

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fib2, n - 1);

        if (list[i]->id < id) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (list[i]->id > id) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && list[offset + 1]->id == id) {
        return offset + 1;
    }

    return -1;
}

// Fungsi untuk mencari ID menggunakan Jump Search
int jumpSearch(vector<Kunjungan*>& list, int id) {
    int n = list.size();
    int step = sqrt(n);
    int prev = 0;

    while (list[min(step, n) - 1]->id < id) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (list[prev]->id < id) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (list[prev]->id == id)
        return prev;

    return -1;
}

// Fungsi Boyer-Moore untuk pencarian string
int boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0)
        return -1;

    vector<int> last(256, -1);
    for (int i = 0; i < m; i++)
        last[pattern[i]] = i;

    int skip = 0;
    while (n - skip >= m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[skip + j])
            j--;

        if (j < 0) {
            return skip;
        } else {
            skip += max(1, j - last[text[skip + j]]);
        }
    }
    return -1;
}

// Fungsi untuk menampilkan semua kunjungan di stack
void showStack(Stack* stack) {
    vector<Kunjungan*> kunjunganList;
    Kunjungan* sementara = stack->top;
    while (sementara != nullptr) {
        kunjunganList.push_back(sementara);
        sementara = sementara->berikutnya;
    }

    cout << "+------------------------------+" << endl;
    cout << "|========= Isi Stack ==========|" << endl;
    cout << "+------------------------------+" << endl;
    if (kunjunganList.empty()) {
        cout << "Stack kosong." << endl;
    } else {
        for (size_t i = 0; i < kunjunganList.size(); i++) {
            cout << "ID: " << kunjunganList[i]->id << endl;
            cout << "Nama Pasien: " << kunjunganList[i]->namaPasien << endl;
            cout << "Nama Dokter: " << kunjunganList[i]->namaDokter << endl;
            cout << "Tanggal Kunjungan: " << kunjunganList[i]->tanggalKunjungan << endl;
            cout << "+------------------------------+" << endl;
        }
    }
}

// Fungsi untuk menampilkan semua kunjungan di queue
void showQueue(Queue* queue) {
    vector<Kunjungan*> kunjunganList;
    Kunjungan* sementara = queue->depan;
    while (sementara != nullptr) {
        kunjunganList.push_back(sementara);
        sementara = sementara->berikutnya;
    }

    cout << "+------------------------------+" << endl;
    cout << "|========= Isi Queue ==========|" << endl;
    cout << "+------------------------------+" << endl;
    if (kunjunganList.empty()) {
        cout << "Queue kosong." << endl;
    } else {
        for (size_t i = 0; i < kunjunganList.size(); i++) {
            cout << "ID: " << kunjunganList[i]->id << endl;
            cout << "Nama Pasien: " << kunjunganList[i]->namaPasien << endl;
            cout << "Nama Dokter: " << kunjunganList[i]->namaDokter << endl;
            cout << "Tanggal Kunjungan: " << kunjunganList[i]->tanggalKunjungan << endl;
            cout << "+------------------------------+" << endl;
        }
    }
}

// Fungsi untuk mencari di Stack
void searchStack(Stack* stack) {
    vector<Kunjungan*> kunjunganList;
    Kunjungan* sementara = stack->top;
    while (sementara != nullptr) {
        kunjunganList.push_back(sementara);
        sementara = sementara->berikutnya;
    }

    int pilihan;
    cout << "+------------------------------+" << endl;
    cout << "|======== Search Stack ========|" << endl;
    cout << "+------------------------------+" << endl;
    cout << "1. Cari berdasarkan ID (Fibonacci Search)" << endl;
    cout << "2. Cari berdasarkan ID (Jump Search)" << endl;
    cout << "3. Cari berdasarkan Nama Pasien (Boyer-Moore)" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1 || pilihan == 2) {
        int id;
        cout << "Masukkan ID yang dicari: ";
        cin >> id;

        int hasil;
        if (pilihan == 1)
            hasil = fibonacciSearch(kunjunganList, id);
        else
            hasil = jumpSearch(kunjunganList, id);

        if (hasil != -1) {
            cout << "Data ditemukan: " << endl;
            cout << "ID: " << kunjunganList[hasil]->id << endl;
            cout << "Nama Pasien: " << kunjunganList[hasil]->namaPasien << endl;
            cout << "Nama Dokter: " << kunjunganList[hasil]->namaDokter << endl;
            cout << "Tanggal Kunjungan: " << kunjunganList[hasil]->tanggalKunjungan << endl;
            cout << "+------------------------------+" << endl;
        } else {
            cout << "Data tidak ditemukan." << endl;
        }
    } else if (pilihan == 3) {
        string namaPasien;
        cout << "Masukkan Nama Pasien yang dicari: ";
        getline(cin, namaPasien);

        bool ditemukan = false;
        for (auto& kunjungan : kunjunganList) {
            if (boyerMooreSearch(kunjungan->namaPasien, namaPasien) != -1) {
                cout << "Data ditemukan: " << endl;
                cout << "ID: " << kunjungan->id << endl;
                cout << "Nama Pasien: " << kunjungan->namaPasien << endl;
                cout << "Nama Dokter: " << kunjungan->namaDokter << endl;
                cout << "Tanggal Kunjungan: " << kunjungan->tanggalKunjungan << endl;
                cout << "+------------------------------+" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan." << endl;
        }
    }
}

// Fungsi untuk mencari di Queue
void searchQueue(Queue* queue) {
    vector<Kunjungan*> kunjunganList;
    Kunjungan* sementara = queue->depan;
    while (sementara != nullptr) {
        kunjunganList.push_back(sementara);
        sementara = sementara->berikutnya;
    }

    int pilihan;
    cout << "+------------------------------+" << endl;
    cout << "=== Search Queue ===" << endl;
    cout << "+------------------------------+" << endl;
    cout << "1. Cari berdasarkan ID (Fibonacci Search)" << endl;
    cout << "2. Cari berdasarkan ID (Jump Search)" << endl;
    cout << "3. Cari berdasarkan Nama Pasien (Boyer-Moore)" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1 || pilihan == 2) {
        int id;
        cout << "Masukkan ID yang dicari: ";
        cin >> id;

        int hasil;
        if (pilihan == 1)
            hasil = fibonacciSearch(kunjunganList, id);
        else
            hasil = jumpSearch(kunjunganList, id);

        if (hasil != -1) {
            cout << "Data ditemukan: " << endl;
            cout << "ID: " << kunjunganList[hasil]->id << endl;
            cout << "Nama Pasien: " << kunjunganList[hasil]->namaPasien << endl;
            cout << "Nama Dokter: " << kunjunganList[hasil]->namaDokter << endl;
            cout << "Tanggal Kunjungan: " << kunjunganList[hasil]->tanggalKunjungan << endl;
            cout << "+------------------------------+" << endl;
        } else {
            cout << "Data tidak ditemukan." << endl;
        }
    } else if (pilihan == 3) {
        string namaPasien;
        cout << "Masukkan Nama Pasien yang dicari: ";
        getline(cin, namaPasien);

        bool ditemukan = false;
        for (auto& kunjungan : kunjunganList) {
            if (boyerMooreSearch(kunjungan->namaPasien, namaPasien) != -1) {
                cout << "Data ditemukan: " << endl;
                cout << "ID: " << kunjungan->id << endl;
                cout << "Nama Pasien: " << kunjungan->namaPasien << endl;
                cout << "Nama Dokter: " << kunjungan->namaDokter << endl;
                cout << "Tanggal Kunjungan: " << kunjungan->tanggalKunjungan << endl;
                cout << "+------------------------------+" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan." << endl;
        }
    }
}

// Fungsi untuk push data ke stack
void pushStack(Stack* stack, Kunjungan* kunjungan) {
    kunjungan->berikutnya = stack->top;
    stack->top = kunjungan;
    cout << "Data berhasil ditambahkan ke Stack." << endl;
}

// Fungsi untuk pop data dari stack
Kunjungan* popStack(Stack* stack) {
    if (stack->top == nullptr) {
        cout << "Stack kosong, tidak ada yang bisa di-pop." << endl;
        return nullptr;
    }

    Kunjungan* temp = stack->top;
    stack->top = stack->top->berikutnya;
    cout << "Data berhasil di-pop dari Stack." << endl;
    return temp;
}

// Fungsi untuk enqueu data ke queue
void enqueue(Queue* queue, Kunjungan* kunjungan) {
    kunjungan->berikutnya = nullptr;
    if (queue->belakang != nullptr) {
        queue->belakang->berikutnya = kunjungan;
    } else {
        queue->depan = kunjungan;
    }
    queue->belakang = kunjungan;
    cout << "Data berhasil ditambahkan ke Queue." << endl;
}

// Fungsi untuk dequeue data dari queue
Kunjungan* dequeue(Queue* queue) {
    if (queue->depan == nullptr) {
        cout << "Queue kosong, tidak ada yang bisa di-dequeue." << endl;
        return nullptr;
    }

    Kunjungan* temp = queue->depan;
    queue->depan = queue->depan->berikutnya;
    if (queue->depan == nullptr) {
        queue->belakang = nullptr;
    }
    cout << "Data berhasil di-dequeue dari Queue." << endl;
    return temp;
}

// Fungsi utama
int main() {
    Stack stack = {nullptr};
    Queue queue = {nullptr};

    int pilihan;
    do {
        cout << "+------------------------------+" << endl;
        cout << "|  Menu Stack/Queue Kunjungan  |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "|1. Operasi Stack              |" << endl;
        cout << "|2. Operasi Queue              |" << endl;
        cout << "|3. Keluar                     |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            int pilihanStack;
            do {
                cout << "+------------------------------+" << endl;
                cout << "|        Menu Stack            |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "|1. Push Kunjungan             |" << endl;
                cout << "|2. Pop Kunjungan              |" << endl;
                cout << "|3. Tampilkan Semua Kunjungan  |" << endl;
                cout << "|4. Search Stack               |" << endl;
                cout << "|5. Kembali ke Menu Utama      |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "Masukkan pilihan: ";
                cin >> pilihanStack;

                switch (pilihanStack) {
                case 1: {
                    Kunjungan* kunjungan = new Kunjungan();
                    cout << "Masukkan ID: ";
                    cin >> kunjungan->id;
                    cin.ignore();
                    cout << "Masukkan Nama Pasien: ";
                    getline(cin, kunjungan->namaPasien);
                    cout << "Masukkan Nama Dokter: ";
                    getline(cin, kunjungan->namaDokter);
                    cout << "Masukkan Tanggal Kunjungan (DD-MM-YYYY): ";
                    getline(cin, kunjungan->tanggalKunjungan);
                    pushStack(&stack, kunjungan);
                    break;
                }
                case 2: {
                    Kunjungan* kunjungan = popStack(&stack);
                    if (kunjungan != nullptr) {
                        cout << "Data di-pop dari Stack: " << endl;
                        cout << "ID: " << kunjungan->id << endl;
                        cout << "Nama Pasien: " << kunjungan->namaPasien << endl;
                        cout << "Nama Dokter: " << kunjungan->namaDokter << endl;
                        cout << "Tanggal Kunjungan: " << kunjungan->tanggalKunjungan << endl;
                        cout << "+------------------------------+" << endl;
                        delete kunjungan;
                    }
                    break;
                }
                case 3:
                    showStack(&stack);
                    break;
                case 4:
                    searchStack(&stack);
                    break;
                }
            } while (pilihanStack != 5);
        } else if (pilihan == 2) {
            int pilihanQueue;
            do {
                cout << "+------------------------------+" << endl;
                cout << "=== Menu Queue ===" << endl;
                cout << "+------------------------------+" << endl;
                cout << "1. Enqueue Queue" << endl;
                cout << "2. Dequeue Queue" << endl;
                cout << "3. Show Queue" << endl;
                cout << "4. Search Queue" << endl;
                cout << "5. Keluar dari Menu Queue" << endl;
                cout << "Masukkan pilihan: ";
                cin >> pilihanQueue;

                switch (pilihanQueue) {
                case 1: {
                    Kunjungan* kunjungan = new Kunjungan();
                    cout << "Masukkan ID: ";
                    cin >> kunjungan->id;
                    cin.ignore();
                    cout << "Masukkan Nama Pasien: ";
                    getline(cin, kunjungan->namaPasien);
                    cout << "Masukkan Nama Dokter: ";
                    getline(cin, kunjungan->namaDokter);
                    cout << "Masukkan Tanggal Kunjungan (DD-MM-YYYY): ";
                    getline(cin, kunjungan->tanggalKunjungan);
                    enqueue(&queue, kunjungan);
                    break;
                }
                case 2: {
                    Kunjungan* kunjungan = dequeue(&queue);
                    if (kunjungan != nullptr) {
                        cout << "Data di-dequeue dari Queue: " << endl;
                        cout << "ID: " << kunjungan->id << endl;
                        cout << "Nama Pasien: " << kunjungan->namaPasien << endl;
                        cout << "Nama Dokter: " << kunjungan->namaDokter << endl;
                        cout << "Tanggal Kunjungan: " << kunjungan->tanggalKunjungan << endl;
                        cout << "+------------------------------+" << endl;
                        delete kunjungan;
                    }
                    break;
                }
                case 3:
                    showQueue(&queue);
                    break;
                case 4:
                    searchQueue(&queue);
                    break;
                }
            } while (pilihanQueue != 5);
        }
    } while (pilihan != 3);

    return 0;
}
