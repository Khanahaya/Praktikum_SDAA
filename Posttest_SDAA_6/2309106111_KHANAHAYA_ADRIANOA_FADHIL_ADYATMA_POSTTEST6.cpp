#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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

// Fungsi untuk mencari menggunakan Fibonacci Search (integer)
int fibonacciSearch(TicketNode* head, int x) {
    int fib2 = 0; // (m-2)'th Fibonacci No.
    int fib1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fib2 + fib1; // m'th Fibonacci No.
    
    while (fibM < countNodes(head)) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    TicketNode* current = head;
    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fib2, countNodes(head) - 1);
        current = head;

        for (int j = 0; j < i; j++)
            current = current->next;

        if (current->ticketAmount < x) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (current->ticketAmount > x) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i; // Return index
        }
    }

    if (fib1 && current->ticketAmount == x) {
        return offset + 1; // Return index
    }

    return -1; // Not found
}

// Fungsi untuk mencari menggunakan Jump Search (integer)
int jumpSearch(TicketNode* head, int x) {
    int n = countNodes(head);
    int jump = sqrt(n);
    int prev = 0;
    TicketNode* current = head;

    for (int i = 0; i < prev + jump && current != nullptr; i++, current = current->next) {
        prev++;
    }

    while (current != nullptr && current->ticketAmount < x) {
        prev = prev + jump;
        for (int i = 0; i < jump && current != nullptr; i++, current = current->next) {
            prev++;
        }
    }

    if (current != nullptr && current->ticketAmount == x) {
        return prev; // Return index
    }

    return -1; // Not found
}

// Fungsi untuk mengimplementasikan Boyer-Moore pada string
void badCharacterHeuristic(const string& pattern, vector<int>& badChar) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < pattern.length(); i++) {
        badChar[(int)pattern[i]] = i;
    }
}

int boyerMooreSearch(TicketNode* head, const string& pattern) {
    vector<int> badChar(256);
    badCharacterHeuristic(pattern, badChar);

    int m = pattern.length();
    int n = countNodes(head);

    TicketNode* current = head;
    vector<TicketNode*> nodes;

    while (current != nullptr) {
        nodes.push_back(current);
        current = current->next;
    }

    for (int i = 0; i <= n - m; ) {
        int j = m - 1;
        while (j >= 0 && nodes[i + j]->passengerName == pattern[j]) {
            j--;
        }

        if (j < 0) {
            return i; // Found at index i
        } else {
            i += max(1, j - badChar[(int)nodes[i + j]->passengerName[0]]);
        }
    }

    return -1; // Not found
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
        cout << "9. Cari Tiket di Stack (Fibonacci Search)\n";
        cout << "10. Cari Tiket di Queue (Jump Search)\n";
        cout << "11. Cari Tiket berdasarkan Nama di Stack (Boyer-Moore)\n";
        cout << "12. Keluar\n";
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
            case 9: {
                int ticketAmount;
                cout << "Masukkan jumlah tiket yang dicari: ";
                cin >> ticketAmount;
                int index = fibonacciSearch(stackTickets, ticketAmount);
                if (index != -1) {
                    cout << "Tiket ditemukan di index: " << index << "\n";
                } else {
                    cout << "Tiket tidak ditemukan.\n";
                }
                break;
            }
            case 10: {
                int ticketAmount;
                cout << "Masukkan jumlah tiket yang dicari: ";
                cin >> ticketAmount;
                int index = jumpSearch(queueTickets, ticketAmount);
                if (index != -1) {
                    cout << "Tiket ditemukan di index: " << index << "\n";
                } else {
                    cout << "Tiket tidak ditemukan.\n";
                }
                break;
            }
            case 11: {
                string name;
                cout << "Masukkan nama penumpang yang dicari: ";
                cin >> name;
                int index = boyerMooreSearch(stackTickets, name);
                if (index != -1) {
                    cout << "Tiket dengan nama '" << name << "' ditemukan di index: " << index << "\n";
                } else {
                    cout << "Tiket dengan nama '" << name << "' tidak ditemukan.\n";
                }
                break;
            }
            case 12:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 12);

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
