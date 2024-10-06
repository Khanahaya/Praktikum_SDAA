#include <iostream>
#include <string>
using namespace std;

// STRUCT untuk node tiket
struct TicketNode {
    string passengerName;
    string destination;
    int ticketAmount;
    TicketNode* next; 
};

// Fungsi untuk menambah tiket ke stack (push)
void pushTicket(TicketNode** head) {
    TicketNode* newTicket = new TicketNode; // alokasi memori untuk node baru
    cout << "Masukkan nama penumpang: ";
    cin >> newTicket->passengerName;
    cout << "Masukkan tujuan: ";
    cin >> newTicket->destination;
    cout << "Masukkan jumlah tiket: ";
    cin >> newTicket->ticketAmount;
    newTicket->next = *head;
    *head = newTicket;
    cout << "Tiket berhasil ditambahkan ke stack!\n";
}

// Fungsi untuk menghapus tiket dari stack (pop)
void popTicket(TicketNode** head) {
    if (*head == nullptr) {
        cout << "Stack kosong, tidak ada tiket untuk dihapus.\n";
        return;
    }

    TicketNode* temp = *head;
    *head = (*head)->next;
    delete temp;

    cout << "Tiket berhasil dihapus dari stack!\n";
}

// Fungsi untuk menambahkan tiket ke queue (enqueue)
void enqueueTicket(TicketNode** head) {
    TicketNode* newTicket = new TicketNode;
    cout << "Masukkan nama penumpang: ";
    cin >> newTicket->passengerName;
    cout << "Masukkan tujuan: ";
    cin >> newTicket->destination;
    cout << "Masukkan jumlah tiket: ";
    cin >> newTicket->ticketAmount;
    newTicket->next = nullptr;

    if (*head == nullptr) {
        *head = newTicket;
    } else {
        TicketNode* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTicket;
    }
    cout << "Tiket berhasil ditambahkan ke queue!\n";
}

// Fungsi untuk menghapus tiket dari queue (dequeue)
void dequeueTicket(TicketNode** head) {
    if (*head == nullptr) {
        cout << "Queue kosong, tidak ada tiket untuk dihapus. \n";
        return;
    }

    TicketNode* temp = *head;
    *head = (*head)->next;
    delete temp;

    cout << "Tiket berhasil dihapus dari queue!\n";
}

// Fungsi untuk menampilkan tiket (stack/queue)
void readTickets(TicketNode* head) {
    if (head == nullptr) {
        cout << "Tidak ada tiket yang tersedia.\n";
    } else {
        TicketNode* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << "Tiket ke-" << index++ << ":\n";
            cout << "Nama penumpang: " << current->passengerName << "\n";
            cout << "Tujuan: " << current->destination << "\n";
            cout << "Jumlah Tiket: " << current->ticketAmount << "\n";
            cout << "--------------------------\n";
            current = current->next;
        }
    }
}

int main() {
    TicketNode* stackTickets = nullptr; // stack 
    TicketNode* queueTickets = nullptr; // queue
    int choice;

    do {
        cout << "\nSistem Manajemen Pembelian Tiket:\n";
        cout << "1. Tambah Tiket ke Stack (Push)\n";
        cout << "2. Hapus Tiket dari Stack (Pop)\n";
        cout << "3. Lihat Semua Tiket di Stack\n";
        cout << "4. Tambah Tiket ke Queue (Enqueue)\n";
        cout << "5. Hapus Tiket dari Queue (Dequeue)\n";
        cout << "6. Lihat Semua Tiket di Queue\n";
        cout << "7. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1:
                pushTicket(&stackTickets);
                break;
            case 2:
                popTicket(&stackTickets);
                break;
            case 3:
                readTickets(stackTickets);
                break;
            case 4:
                enqueueTicket(&queueTickets);
                break;
            case 5:
                dequeueTicket(&queueTickets);
                break;
            case 6:
                readTickets(queueTickets);
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 7);

    //Hapus semua tiket sebelum keluar (stack)
    while (stackTickets != nullptr) {
        TicketNode* temp = stackTickets;
        stackTickets = stackTickets->next;
        delete temp;
    }

    // Hapus semua tiket sebelum keluar (queue)
    while (queueTickets != nullptr) {
        TicketNode* temp = queueTickets;
        queueTickets = queueTickets->next;
        delete temp;
    }

    return 0;
}