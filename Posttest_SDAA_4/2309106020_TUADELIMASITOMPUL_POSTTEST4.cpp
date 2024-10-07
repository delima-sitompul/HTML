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

// Stack untuk menyimpan riwayat kunjungan
struct Stack
{
    Kunjungan *top;
};

// Queue untuk antrian pasien
struct Queue
{
    Kunjungan *depan;
    Kunjungan *belakang;
};

// Fungsi untuk menambahkan data kunjungan baru ke stack (push)
void pushKunjungan(Stack *stack)
{
    Kunjungan *kunjunganBaru = new Kunjungan();

    cout << "=== Push Kunjungan ke Stack ===" << endl;
    cout << "ID: ";
    cin >> kunjunganBaru->id;
    cin.ignore();
    cout << "Nama Pasien: ";
    getline(cin, kunjunganBaru->namaPasien);
    cout << "Nama Dokter: ";
    getline(cin, kunjunganBaru->namaDokter);
    cout << "Tanggal Kunjungan (DD-MM-YYYY): ";
    getline(cin, kunjunganBaru->tanggalKunjungan);

    kunjunganBaru->berikutnya = stack->top;
    stack->top = kunjunganBaru;
    cout << "Data berhasil ditambahkan ke Stack!" << endl;
    sleep(2);
}

// Fungsi untuk menghapus kunjungan dari stack (pop)
void popKunjungan(Stack *stack)
{
    if (stack->top == nullptr)
    {
        cout << "Stack kosong. Tidak ada kunjungan yang bisa di-pop." << endl;
        sleep(2);
        return;
    }
    Kunjungan *kunjunganHapus = stack->top;
    stack->top = stack->top->berikutnya;
    cout << "Kunjungan dengan ID " << kunjunganHapus->id << " berhasil di-pop dari stack." << endl;
    delete kunjunganHapus;
    sleep(2);
}

// Fungsi untuk melihat data teratas di stack (peek)
void peekKunjungan(Stack *stack)
{
    if (stack->top == nullptr)
    {
        cout << "Stack kosong." << endl;
    }
    else
    {
        cout << "=== Data Teratas di Stack ===" << endl;
        cout << "ID: " << stack->top->id << endl;
        cout << "Nama Pasien: " << stack->top->namaPasien << endl;
        cout << "Nama Dokter: " << stack->top->namaDokter << endl;
        cout << "Tanggal Kunjungan: " << stack->top->tanggalKunjungan << endl;
    }
    sleep(3);
}

// Fungsi untuk menampilkan semua kunjungan di stack
void showStack(Stack *stack)
{
    cout << "=== Isi Stack ===" << endl;
    if (stack->top == nullptr)
    {
        cout << "Stack kosong." << endl;
    }
    else
    {
        Kunjungan *sementara = stack->top;
        while (sementara != nullptr)
        {
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

// Fungsi untuk menambahkan pasien ke dalam queue (enqueue)
void enqueueKunjungan(Queue *queue)
{
    Kunjungan *kunjunganBaru = new Kunjungan();

    cout << "=== Enqueue Kunjungan ke Queue ===" << endl;
    cout << "ID: ";
    cin >> kunjunganBaru->id;
    cin.ignore();
    cout << "Nama Pasien: ";
    getline(cin, kunjunganBaru->namaPasien);
    cout << "Nama Dokter: ";
    getline(cin, kunjunganBaru->namaDokter);
    cout << "Tanggal Kunjungan (DD-MM-YYYY): ";
    getline(cin, kunjunganBaru->tanggalKunjungan);
    kunjunganBaru->berikutnya = nullptr;

    if (queue->belakang == nullptr) 
    {
        queue->depan = queue->belakang = kunjunganBaru;
    }
    else
    {
        queue->belakang->berikutnya = kunjunganBaru;
        queue->belakang = kunjunganBaru;
    }
    cout << "Data berhasil ditambahkan ke Queue!" << endl;
    sleep(2);
}

// Fungsi untuk menghapus pasien dari queue (dequeue)
void dequeueKunjungan(Queue *queue)
{
    if (queue->depan == nullptr)
    {
        cout << "Queue kosong. Tidak ada kunjungan yang bisa di-dequeue." << endl;
        sleep(2);
        return;
    }

    Kunjungan *kunjunganHapus = queue->depan;
    queue->depan = queue->depan->berikutnya;

    if (queue->depan == nullptr)
    {
        queue->belakang = nullptr; 
    }

    cout << "Kunjungan dengan ID " << kunjunganHapus->id << " berhasil di-dequeue dari queue." << endl;
    delete kunjunganHapus;
    sleep(2);
}

// Fungsi untuk melihat data terdepan di queue (peek)
void peekQueue(Queue *queue)
{
    if (queue->depan == nullptr)
    {
        cout << "Queue kosong." << endl;
    }
    else
    {
        cout << "=== Data Terdepan di Queue ===" << endl;
        cout << "ID: " << queue->depan->id << endl;
        cout << "Nama Pasien: " << queue->depan->namaPasien << endl;
        cout << "Nama Dokter: " << queue->depan->namaDokter << endl;
        cout << "Tanggal Kunjungan: " << queue->depan->tanggalKunjungan << endl;
    }
    sleep(3);
}

// Fungsi untuk menampilkan semua antrian pasien
void showQueue(Queue *queue)
{
    cout << "=== Isi Queue ===" << endl;
    if (queue->depan == nullptr)
    {
        cout << "Queue kosong." << endl;
    }
    else
    {
        Kunjungan *sementara = queue->depan;
        while (sementara != nullptr)
        {
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

int main()
{
    Stack stack;
    stack.top = nullptr; 
    Queue queue;
    queue.depan = queue.belakang = nullptr; 

    int pilihan;
    do
    {
        cout << "+------------------------------+" << endl;
        cout << "|  Menu Stack/Queue Kunjungan  |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "|1. Operasi Stack              |" << endl;
        cout << "|2. Operasi Queue              |" << endl;
        cout << "|3. Keluar                     |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1)
        {
            int pilihanStack;
            do
            {
                cout << "+------------------------------+" << endl;
                cout << "|    Menu Stack Kunjungan      |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "|1. Push                       |" << endl;
                cout << "|2. Pop                        |" << endl;
                cout << "|3. Peek                       |" << endl;
                cout << "|4. Show                       |" << endl;
                cout << "|5. Kembali                    |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "Masukkan pilihan: ";
                cin >> pilihanStack;
                cin.ignore();

                switch (pilihanStack)
                {
                case 1:
                    pushKunjungan(&stack);
                    break;
                case 2:
                    popKunjungan(&stack);
                    break;
                case 3:
                    peekKunjungan(&stack);
                    break;
                case 4:
                    showStack(&stack);
                    break;
                }
            } while (pilihanStack != 5);
        }
        else if (pilihan == 2)
        {
            int pilihanQueue;
            do
            {
                cout << "+------------------------------+" << endl;
                cout << "|     Menu Queue Kunjungan     |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "|1. Enqueue                    |" << endl;
                cout << "|2. Dequeue                    |" << endl;
                cout << "|3. Peek                       |" << endl;
                cout << "|4. Show                       |" << endl;
                cout << "|5. Kembali                    |" << endl;
                cout << "+------------------------------+" << endl;
                cout << "Masukkan pilihan: ";
                cin >> pilihanQueue;
                cin.ignore();

                switch (pilihanQueue)
                {
                case 1:
                    enqueueKunjungan(&queue);
                    break;
                case 2:
                    dequeueKunjungan(&queue);
                    break;
                case 3:
                    peekQueue(&queue);
                    break;
                case 4:
                    showQueue(&queue);
                    break;
                }
            } while (pilihanQueue != 5);
        }

    } while (pilihan != 3);

    cout << "Terima kasih telah menggunakan program ini." << endl;
    return 0;
}
