#include <iostream>
#include <stack>
#include <cmath>   // untuk fungsi pow()
#include <sstream> // untuk parsing input
using namespace std;

// Fungsi untuk mengevaluasi ekspresi postfix
double evaluasiPostfix(const string& ekspresi) {
    stack<double> st;  // Stack untuk menyimpan operan
    stringstream ss(ekspresi);  // Stringstream untuk memisahkan token
    string token;

    // Parsing setiap token dalam ekspresi postfix
    while (ss >> token) {
        if (isdigit(token[0])) {  // Jika token adalah angka
            st.push(stod(token)); // Konversi string ke double dan push ke stack
        } else {  // Jika token adalah operator
            double operan2 = st.top(); st.pop();  // Ambil operan kedua
            double operan1 = st.top(); st.pop();  // Ambil operan pertama

            double hasil = 0;
            switch (token[0]) {
                case '+': hasil = operan1 + operan2; break;
                case '-': hasil = operan1 - operan2; break;
                case '*': hasil = operan1 * operan2; break;
                case '/': hasil = operan1 / operan2; break;
                case '^': hasil = pow(operan1, operan2); break;
                default:
                    cout << "Operator tidak valid.\n";
                    return 0;
            }
            st.push(hasil);  // Push hasil ke stack
            cout << "Langkah: " << operan1 << " " << token << " " << operan2 
                 << " = " << hasil << endl;
        }
    }

    // Hasil akhir adalah elemen terakhir di stack
    return st.top();
}

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix: ";
    getline(cin, ekspresi);  // Membaca seluruh ekspresi

    double hasil = evaluasiPostfix(ekspresi);
    cout << "Hasil akhir: " << hasil << endl;

    return 0;
}
