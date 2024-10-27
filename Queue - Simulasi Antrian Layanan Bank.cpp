#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Struct untuk menyimpan data pelanggan
struct Pelanggan {
    int nomorAntrian;
    int waktuLayanan;  // Waktu layanan dalam menit
};

// Class Queue untuk mengelola antrian pelanggan
class Queue {
private:
    queue<Pelanggan> q;  // Queue dari STL
public:
    // Menambah pelanggan ke dalam antrian
    void enqueue(int nomor, int waktu) {
        q.push({nomor, waktu});
    }

    // Mengeluarkan pelanggan dari antrian
    Pelanggan dequeue() {
        if (!q.empty()) {
            Pelanggan p = q.front();
            q.pop();
            return p;
        } else {
            return {-1, 0};  // Return pelanggan dummy jika queue kosong
        }
    }

    // Mengecek apakah antrian kosong
    bool isEmpty() const {
        return q.empty();
    }

    // Mendapatkan ukuran antrian
    int size() const {
        return q.size();
    }
};

// Fungsi untuk menjalankan simulasi antrian dengan 3 loket layanan
void simulasiAntrian(Queue& antrian) {
    int totalWaktuTunggu = 0;
    int totalPelanggan = 0;
    int waktuLoket[3] = {0, 0, 0};  // Waktu layanan untuk 3 loket

    while (!antrian.isEmpty()) {
        for (int i = 0; i < 3; i++) {  // Setiap loket melayani 1 pelanggan
            if (!antrian.isEmpty()) {
                Pelanggan p = antrian.dequeue();
                totalWaktuTunggu += waktuLoket[i];  // Hitung waktu tunggu
                waktuLoket[i] += p.waktuLayanan;    // Tambah waktu layanan ke loket
                totalPelanggan++;
                cout << "Pelanggan " << p.nomorAntrian 
                     << " dilayani di loket " << i + 1 
                     << " selama " << p.waktuLayanan << " menit.\n";
            }
        }
    }

    // Hitung statistik akhir
    cout << "\nStatistik:\n";
    cout << "Total pelanggan terlayani: " << totalPelanggan << endl;
    cout << "Rata-rata waktu tunggu: " 
         << (totalWaktuTunggu / (double)totalPelanggan) << " menit\n";
    cout << "Sisa antrian: " << antrian.size() << endl;
}

int main() {
    Queue antrian;
    int jumlahPelanggan, waktu;

    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlahPelanggan;

    // Menambahkan pelanggan ke dalam antrian
    for (int i = 1; i <= jumlahPelanggan; i++) {
        cout << "Masukkan waktu layanan untuk pelanggan " << i << ": ";
        cin >> waktu;
        antrian.enqueue(i, waktu);
    }

    // Menjalankan simulasi antrian
    simulasiAntrian(antrian);

    return 0;
}
