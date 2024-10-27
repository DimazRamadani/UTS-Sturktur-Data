#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Struct untuk menyimpan data peralatan
struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

// Fungsi untuk menambah data peralatan
void tambahPeralatan(vector<Peralatan>& inventaris) {
    Peralatan p;
    cout << "Masukkan kode peralatan: ";
    cin >> p.kode;
    cout << "Masukkan nama peralatan: ";
    cin.ignore();
    getline(cin, p.nama);
    cout << "Masukkan jumlah: ";
    cin >> p.jumlah;
    cout << "Masukkan kondisi: ";
    cin.ignore();
    getline(cin, p.kondisi);
    inventaris.push_back(p);
}

// Fungsi untuk mengubah data peralatan berdasarkan kode
void ubahPeralatan(vector<Peralatan>& inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin diubah: ";
    cin >> kode;

    for (auto& p : inventaris) {
        if (p.kode == kode) {
            cout << "Masukkan nama baru: ";
            cin.ignore();
            getline(cin, p.nama);
            cout << "Masukkan jumlah baru: ";
            cin >> p.jumlah;
            cout << "Masukkan kondisi baru: ";
            cin.ignore();
            getline(cin, p.kondisi);
            cout << "Data berhasil diubah.\n";
            return;
        }
    }
    cout << "Peralatan dengan kode tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus data peralatan berdasarkan kode
void hapusPeralatan(vector<Peralatan>& inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin dihapus: ";
    cin >> kode;

    auto it = remove_if(inventaris.begin(), inventaris.end(), 
                        [&kode](const Peralatan& p) { return p.kode == kode; });

    if (it != inventaris.end()) {
        inventaris.erase(it, inventaris.end());
        cout << "Data berhasil dihapus.\n";
    } else {
        cout << "Peralatan dengan kode tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk menyimpan data ke file
void simpanKeFile(const vector<Peralatan>& inventaris) {
    ofstream file("inventaris.txt");
    for (const auto& p : inventaris) {
        file << p.kode << ',' << p.nama << ',' << p.jumlah << ',' << p.kondisi << '\n';
    }
    file.close();
}

// Fungsi untuk membaca data dari file
void bacaDariFile(vector<Peralatan>& inventaris) {
    ifstream file("inventaris.txt");
    if (!file) {
        cout << "File tidak ditemukan.\n";
        return;
    }

    Peralatan p;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        pos = line.find(',');
        p.kode = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        p.nama = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        p.jumlah = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        p.kondisi = line;
        inventaris.push_back(p);
    }
    file.close();
}

// Fungsi untuk menampilkan laporan inventaris
void tampilkanInventaris(const vector<Peralatan>& inventaris) {
    for (const auto& p : inventaris) {
        cout << "Kode: " << p.kode
             << ", Nama: " << p.nama
             << ", Jumlah: " << p.jumlah
             << ", Kondisi: " << p.kondisi << '\n';
    }
}

// Fungsi untuk mengurutkan inventaris berdasarkan kode
void urutkanInventaris(vector<Peralatan>& inventaris) {
    sort(inventaris.begin(), inventaris.end(), 
         [](const Peralatan& a, const Peralatan& b) { return a.kode < b.kode; });
}

int main() {
    vector<Peralatan> inventaris;
    bacaDariFile(inventaris);

    int pilihan;
    do {
        cout << "\n1. Tambah Peralatan\n2. Ubah Peralatan\n3. Hapus Peralatan\n";
        cout << "4. Tampilkan Inventaris\n5. Simpan ke File\n6. Urutkan Inventaris\n0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPeralatan(inventaris);
                break;
            case 2:
                ubahPeralatan(inventaris);
                break;
            case 3:
                hapusPeralatan(inventaris);
                break;
            case 4:
                tampilkanInventaris(inventaris);
                break;
            case 5:
                simpanKeFile(inventaris);
                break;
            case 6:
                urutkanInventaris(inventaris);
                cout << "Inventaris berhasil diurutkan.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
