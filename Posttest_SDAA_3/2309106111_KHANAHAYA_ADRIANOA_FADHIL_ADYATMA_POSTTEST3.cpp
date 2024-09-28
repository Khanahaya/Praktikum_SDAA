#include <iostream>
#include <string>
using namespace std;

// Struct untuk node tiket
struct TicketNode {
    string passengerName;
    string destination;
    int ticketAmount;
    TicketNode* next; // Pointer to the next node
};

// Fungsi untuk menambah tiket
void createTicket(TicketNode** head) {
    TicketNode* newTicket = new TicketNode; // Alokasi memori untuk node baru
    cout << "Masukkan nama penumpang: ";
    cin >> newTicket->passengerName;
    cout << "Masukkan tujuan: ";
    cin >> newTicket->destination;
    cout << "Masukkan jumlah tiket: ";
    cin >> newTicket->ticketAmount;
    newTicket->next = nullptr;

    if (*head == nullptr) {
        // Jika list kosong, set head ke node baru
        *head = newTicket;
    } else {
        // Jika tidak kosong, tambahkan ke akhir list
        TicketNode* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTicket;
    }
    cout << "Tiket berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan tiket
void readTickets(TicketNode* head) {
    if (head == nullptr) {
        cout << "Tidak ada tiket yang tersedia.\n";
    } else {
        TicketNode* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << "Tiket ke-" << index++ << ":\n";
            cout << "Nama Penumpang: " << current->passengerName << "\n";
            cout << "Tujuan: " << current->destination << "\n";
            cout << "Jumlah Tiket: " << current->ticketAmount << "\n";
            cout << "--------------------------\n";
            current = current->next;
        }
    }
}

// Fungsi untuk memperbarui tiket
void updateTicket(TicketNode* head) {
    int index;
    cout << "Masukkan nomor tiket yang ingin diupdate: ";
    cin >> index;

    TicketNode* current = head;
    for (int i = 1; current != nullptr && i < index; i++) {
        current = current->next;
    }

    if (current != nullptr) {
        cout << "Masukkan nama penumpang baru: ";
        cin >> current->passengerName;
        cout << "Masukkan tujuan baru: ";
        cin >> current->destination;
        cout << "Masukkan jumlah tiket baru: ";
        cin >> current->ticketAmount;
        cout << "Tiket berhasil diupdate!\n";
    } else {
        cout << "Nomor tiket tidak valid.\n";
    }
}

// Fungsi untuk menghapus tiket
void deleteTicket(TicketNode** head) {
    int index;
    cout << "Masukkan nomor tiket yang ingin dihapus: ";
    cin >> index;

    if (*head == nullptr) {
        cout << "Tidak ada tiket yang tersedia untuk dihapus.\n";
        return;
    }

    TicketNode* current = *head;
    TicketNode* previous = nullptr;

    for (int i = 1; current != nullptr && i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Nomor tiket tidak valid.\n";
        return;
    }

    if (previous == nullptr) {
        // Hapus head
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    
    delete current; // Hapus node yang dipilih
    cout << "Tiket berhasil dihapus!\n";
}

int main() {
    TicketNode* tickets = nullptr;  // Pointer ke head linked list
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
                createTicket(&tickets);
                break;
            case 2:
                readTickets(tickets);
                break;
            case 3:
                updateTicket(tickets);
                break;
            case 4:
                deleteTicket(&tickets);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 5);

    // Hapus semua tiket sebelum keluar
    while (tickets != nullptr) {
        TicketNode* temp = tickets;
        tickets = tickets->next;
        delete temp;
    }

    return 0;
}
