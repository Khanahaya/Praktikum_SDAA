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

// Fungsi untuk menghitung jumlah node
int countNodes(TicketNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Fungsi untuk merge dua linked list
TicketNode* merge(TicketNode* left, TicketNode* right) {
    if (!left) return right;
    if (!right) return left;

    TicketNode* result = nullptr;

    if (left->ticketAmount <= right->ticketAmount) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Fungsi untuk melakukan merge sort
TicketNode* mergeSort(TicketNode* head) {
    if (!head || !head->next) return head;

    TicketNode* middle = head;
    TicketNode* fast = head->next;

    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }

    TicketNode* left = head;
    TicketNode* right = middle->next;
    middle->next = nullptr;

    return merge(mergeSort(left), mergeSort(right));
}

// Fungsi untuk partition dan melakukan quick sort
TicketNode* partition(TicketNode* head, TicketNode* end, TicketNode** newHead, TicketNode** newEnd) {
    TicketNode* pivot = end;
    TicketNode* prev = nullptr;
    TicketNode* current = head;
    TicketNode* tail = pivot;

    while (current != pivot) {
        if (current->ticketAmount > pivot->ticketAmount) {
            if (!(*newHead)) *newHead = current;
            prev = current;
            current = current->next;
        } else {
            if (prev) prev->next = current->next;
            TicketNode* temp = current->next;
            current->next = nullptr;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }

    if (!(*newHead)) *newHead = pivot;
    *newEnd = tail;

    return pivot;
}

// Fungsi untuk melakukan quick sort
TicketNode* quickSort(TicketNode* head) {
    if (!head || !head->next) return head;

    TicketNode* newHead = nullptr;
    TicketNode* newEnd = nullptr;

    TicketNode* pivot = partition(head, head, &newHead, &newEnd);

    if (newHead != pivot) {
        TicketNode* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quickSort(newHead);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSort(pivot->next);

    return newHead;
}

// Fungsi untuk mendapatkan tail dari linked list
TicketNode* getTail(TicketNode* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
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
        cout << "7. Urutkan Tiket di Stack (Ascending)\n";
        cout << "8. Urutkan Tiket di Queue (Descending)\n";
        cout << "9. Keluar\n";
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
                stackTickets = mergeSort(stackTickets);
                cout << "Tiket di stack berhasil diurutkan secara ascending!\n";
                break;
            case 8:
                queueTickets = quickSort(queueTickets);
                cout << "Tiket di queue berhasil diurutkan secara descending!\n";
                break;
            case 9:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 9);

    // Hapus semua tiket sebelum keluar (stack)
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
