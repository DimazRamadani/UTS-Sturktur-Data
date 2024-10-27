#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan data mahasiswa
struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa(Mahasiswa* mahasiswa[], int& jumlah) {
    if (jumlah < 10) {
        mahasiswa[jumlah] = new Mahasiswa;
        cout << "Masukkan NIM: ";
        cin >> mahasiswa[jumlah]->NIM;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, mahasiswa[jumlah]->nama);
        cout << "Masukkan IPK: ";
        cin >> mahasiswa[jumlah]->IPK;
        jumlah++;
    } else {
        cout << "Array penuh!\n";
    }
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void hapusMahasiswa(Mahasiswa* mahasiswa[], int& jumlah, const string& NIM) {
    for (int i = 0; i < jumlah; i++) {
        if (mahasiswa[i]->NIM == NIM) {
            delete mahasiswa[i];
            for (int j = i; j < jumlah - 1; j++) {
                mahasiswa[j] = mahasiswa[j + 1];
            }
            mahasiswa[jumlah - 1] = nullptr;
            jumlah--;
            cout << "Data mahasiswa dengan NIM " << NIM << " telah dihapus.\n";
            return;
        }
    }
    cout << "Mahasiswa dengan NIM tersebut tidak ditemukan.\n";
}

// Fungsi untuk menampilkan data mahasiswa
void tampilkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "NIM: " << mahasiswa[i]->NIM
             << ", Nama: " << mahasiswa[i]->nama
             << ", IPK: " << mahasiswa[i]->IPK << endl;
    }
}

// Fungsi untuk mengurutkan mahasiswa berdasarkan IPK
void urutkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (mahasiswa[j]->IPK > mahasiswa[j + 1]->IPK) {
                swap(mahasiswa[j], mahasiswa[j + 1]);
            }
        }
    }
}

int main() {
    Mahasiswa* mahasiswa[10] = {nullptr};
    int jumlah = 0;
    int pilihan;
    string NIM;

    do {
        cout << "1. Tambah Mahasiswa\n2. Hapus Mahasiswa\n3. Tampilkan Mahasiswa\n4. Urutkan Mahasiswa\n0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMahasiswa(mahasiswa, jumlah);
                break;
            case 2:
                cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
                cin >> NIM;
                hapusMahasiswa(mahasiswa, jumlah, NIM);
                break;
            case 3:
                tampilkanMahasiswa(mahasiswa, jumlah);
                break;
            case 4:
                urutkanMahasiswa(mahasiswa, jumlah);
                break;
        }
    } while (pilihan != 0);

    // Membersihkan memori heap
    for (int i = 0; i < jumlah; i++) {
        delete mahasiswa[i];
    }

    return 0;
}
