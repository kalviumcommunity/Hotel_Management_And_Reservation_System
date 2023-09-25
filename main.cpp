#include <iostream>
#include <string.h>

#define max 100

using namespace std;

class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

class Room {
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

    Room addRoom(int);
    void searchRoom(int);
    void displayRoom(Room);
};


Room rooms[max];
int count = 0;

Room Room::addRoom(int rno) {
    Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N): ";
    cin >> room.ac;
    cout << "\nType Comfort (S/N): ";
    cin >> room.type;
    cout << "\nType Size (B/S): ";
    cin >> room.stype;
    cout << "\nDaily Rent: ";
    cin >> room.rent;
    room.status = 0;
    cout << "\nRoom Added Successfully!\n\n\n";
    cin.get();
    return room;
}

void Room::searchRoom(int rno) {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "Room Details\n";
        if (rooms[i].status == 1) {
            cout << "\nRoom is Reserved";
        }
        else {
            cout << "\nRoom is available";
        }
        displayRoom(rooms[i]);
        cin.get();
    }
    else {
        cout << "\nRoom not found";
        cin.get(); 
    }
}

void Room::displayRoom(Room tempRoom) {
    cout << "\nRoom Number: " << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N): " << tempRoom.ac;
    cout << "\nType Comfort (S/N): " << tempRoom.type;
    cout << "\nType Size (B/S): " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
}

int main() {
    char ch;
    int rno;

    do {
        system("cls");
        cout << "HOTEL MANAGEMENT SYSTEM";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Exit";
        cout << "\nEnter your choice (1-3): ";
        cin >> ch;

        switch (ch) {
        case '1':
            cout << "Enter Room Number: ";
            cin >> rno;
            rooms[count++] = rooms[count].addRoom(rno);
            break;
        case '2':
            cout << "Enter Room Number: ";
            cin >> rno;
            rooms[count].searchRoom(rno);
            break;
        case '3':
            exit(0);
        }
    } while (ch != '3');
    return 0;
}