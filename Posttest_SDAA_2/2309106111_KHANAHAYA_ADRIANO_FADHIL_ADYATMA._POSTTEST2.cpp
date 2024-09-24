#include <iostream>
#include <string>
using namespace std;

// Struct untuk data tiket
struct Ticket {
    string passengerName;
    string destination;
    int ticketAmount;
};

// Fungsi untuk menambah tiket
void createTicket(Ticket* tickets, int* ticketCount) {
    if (*ticketCount < 100) {  // Maksimal 100 tiket
        cout << "Masukkan nama penumpang: ";
        cin >> tickets[*ticketCount].passengerName;
        cout << "Masukkan tujuan: ";
        cin >> tickets[*ticketCount].destination;
        cout << "Masukkan jumlah tiket: ";
        cin >> tickets[*ticketCount].ticketAmount;
        (*ticketCount)++;
        cout << "Tiket berhasil ditambahkan!\n";
    } else {
        cout << "Tidak bisa menambahkan lebih banyak tiket, memori penuh.\n";
    }
}

// Fungsi untuk menampilkan tiket
void readTickets(Ticket* tickets, int ticketCount) {
    if (ticketCount == 0) {
        cout << "Tidak ada tiket yang tersedia.\n";
    } else {
        for (int i = 0; i < ticketCount; i++) {
            cout << "Tiket ke-" << i + 1 << ":\n";
            cout << "Nama Penumpang: " << tickets[i].passengerName << "\n";
            cout << "Tujuan: " << tickets[i].destination << "\n";
            cout << "Jumlah Tiket: " << tickets[i].ticketAmount << "\n";
            cout << "--------------------------\n";
        }
    }
}

// Fungsi untuk memperbarui tiket
void updateTicket(Ticket* tickets, int ticketCount) {
    int index;
    cout << "Masukkan nomor tiket yang ingin diupdate: ";
    cin >> index;
    if (index > 0 && index <= ticketCount) {
        index--;  // Adjust index
        cout << "Masukkan nama penumpang baru: ";
        cin >> tickets[index].passengerName;
        cout << "Masukkan tujuan baru: ";
        cin >> tickets[index].destination;
        cout << "Masukkan jumlah tiket baru: ";
        cin >> tickets[index].ticketAmount;
        cout << "Tiket berhasil diupdate!\n";
    } else {
        cout << "Nomor tiket tidak valid.\n";
    }
}

// Fungsi untuk menghapus tiket
void deleteTicket(Ticket* tickets, int* ticketCount) {
    int index;
    cout << "Masukkan nomor tiket yang ingin dihapus: ";
    cin >> index;
    if (index > 0 && index <= *ticketCount) {
        index--;  // Adjust index
        for (int i = index; i < *ticketCount - 1; i++) {
            tickets[i] = tickets[i + 1];
        }
        (*ticketCount)--;
        cout << "Tiket berhasil dihapus!\n";
    } else {
        cout << "Nomor tiket tidak valid.\n";
    }
}

int main() {
    Ticket tickets[100];  // Array untuk menyimpan tiket
    int ticketCount = 0;  // Jumlah tiket yang ada
    int choice;

    do {
        cout << "\nSistem Manajemen Pembelian Tiket Kereta:\n";
        cout << "1. Tambah Tiket\n";
        cout << "2. Lihat Semua Tiket\n";
        cout << "3. Update Tiket\n";
        cout << "4. Hapus Tiket\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createTicket(tickets, &ticketCount);
                break;
            case 2:
                readTickets(tickets, ticketCount);
                break;
            case 3:
                updateTicket(tickets, ticketCount);
                break;
            case 4:
                deleteTicket(tickets, &ticketCount);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 5);

    return 0;
}
