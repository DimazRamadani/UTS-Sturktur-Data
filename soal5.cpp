#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

// Struct untuk menyimpan data buku
struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

// Stack untuk menyimpan riwayat peminjaman buku
stack<string> riwayatPeminjaman;

// Queue untuk mengelola antrian peminjaman buku
queue<string> antrianPeminjaman;

// Array of pointers untuk menyimpan data buku
Buku* perpustakaan[10] = {nullptr};  // Maksimal 10 buku
int jumlahBuku = 0;

// Fungsi untuk menambah buku
void tambahBuku() {
    if (jumlahBuku < 10) {
        perpustakaan[jumlahBuku] = new Buku;
        cout << "Masukkan ISBN: ";
        cin >> perpustakaan[jumlahBuku]->ISBN;
        cout << "Masukkan Judul: ";
        cin.ignore();
        getline(cin, perpustakaan[jumlahBuku]->judul);
        cout << "Masukkan Pengarang: ";
        getline(cin, perpustakaan[jumlahBuku]->pengarang);
        cout << "Masukkan Tahun Terbit: ";
        cin >> perpustakaan[jumlahBuku]->tahunTerbit;
        jumlahBuku++;
        cout << "Buku berhasil ditambahkan.\n";
    } else {
        cout << "Perpustakaan penuh!\n";
    }
}

// Fungsi untuk mencari buku berdasarkan ISBN
void cariBuku(const string& ISBN) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (perpustakaan[i]->ISBN == ISBN) {
            cout << "Buku ditemukan: " << perpustakaan[i]->judul 
                 << " oleh " << perpustakaan[i]->pengarang 
                 << ", Tahun: " << perpustakaan[i]->tahunTerbit << endl;
            return;
        }
    }
    cout << "Buku dengan ISBN tersebut tidak ditemukan.\n";
}

// Fungsi untuk menampilkan semua buku
void tampilkanBuku() {
    cout << "\nDaftar Buku:\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << "ISBN: " << perpustakaan[i]->ISBN
             << ", Judul: " << perpustakaan[i]->judul
             << ", Pengarang: " << perpustakaan[i]->pengarang
             << ", Tahun Terbit: " << perpustakaan[i]->tahunTerbit << endl;
    }
}

// Fungsi untuk meminjam buku
void pinjamBuku(const string& ISBN) {
    antrianPeminjaman.push(ISBN);
    cout << "Buku dengan ISBN " << ISBN << " masuk ke antrian peminjaman.\n";
}

// Fungsi untuk memproses peminjaman buku
void prosesPeminjaman() {
    if (!antrianPeminjaman.empty()) {
        string ISBN = antrianPeminjaman.front();
        antrianPeminjaman.pop();
        riwayatPeminjaman.push(ISBN);
        cout << "Buku dengan ISBN " << ISBN << " telah dipinjam.\n";
    } else {
        cout << "Tidak ada buku dalam antrian peminjaman.\n";
    }
}

// Fungsi untuk menampilkan riwayat peminjaman
void tampilkanRiwayat() {
    cout << "\nRiwayat Peminjaman Buku:\n";
    stack<string> temp = riwayatPeminjaman;  // Salin stack untuk ditampilkan
    while (!temp.empty()) {
        cout << "ISBN: " << temp.top() << endl;
        temp.pop();
    }
}

int main() {
    int pilihan;
    string ISBN;

    do {
        cout << "\nMenu Perpustakaan:\n";
        cout << "1. Tambah Buku\n2. Cari Buku\n3. Tampilkan Buku\n";
        cout << "4. Pinjam Buku\n5. Proses Peminjaman\n6. Tampilkan Riwayat\n0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                cout << "Masukkan ISBN buku yang dicari: ";
                cin >> ISBN;
                cariBuku(ISBN);
                break;
            case 3:
                tampilkanBuku();
                break;
            case 4:
                cout << "Masukkan ISBN buku yang ingin dipinjam: ";
                cin >> ISBN;
                pinjamBuku(ISBN);
                break;
            case 5:
                prosesPeminjaman();
                break;
            case 6:
                tampilkanRiwayat();
                break;
        }
    } while (pilihan != 0);

    // Membersihkan memori heap
    for (int i = 0; i < jumlahBuku; i++) {
        delete perpustakaan[i];
    }

    return 0;
}
