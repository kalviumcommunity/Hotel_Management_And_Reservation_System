#include <iostream>
#include <cstring>

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

    Customer() {
        strcpy(name, "");
        strcpy(address, "");
        strcpy(phone, "");
        strcpy(from_date, "");
        strcpy(to_date, "");
        payment_advance = 0.0;
        booking_id = 0;
    }
};

class Room {
public:
    static int roomCount; 
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

    Room() {
        type = '\0';
        stype = '\0';
        ac = '\0';
        roomNumber = 0;
        rent = 0;
        status = 0;
    }

    Room(int rno) {
        this->roomNumber = rno;
        this->status = 0;
    }

    Room addRoom(int);
    void searchRoom(int);
    void displayRoom(Room);
    bool isValidDate(const char*);
    bool isChronologicalDate(const char*, const char*);
    void registerCustomer(int);
    static void displayAllRooms();
};

Room rooms[max];
int Room::roomCount = 0; 

Room Room::addRoom(int rno) {
    Room room(rno);
    cout << "\nType AC/Non-AC (A/N): ";
    cin >> room.ac;
    cout << "\nType Comfort (S/N): ";
    cin >> room.type;
    cout << "\nType Size (B/S): ";
    cin >> room.stype;
    cout << "\nDaily Rent: ";
    cin >> room.rent;

    cout << "\nRoom Added Successfully!\n\n\n";
    cin.ignore();
    return room;
}

void Room::searchRoom(int rno) {
    int i, found = 0;
    for (i = 0; i < Room::roomCount; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "Room Details\n";
        if (rooms[i].status == 1) {
            cout << "\nRoom is Reserved for " << rooms[i].cust.name << " from " << rooms[i].cust.from_date << " to " << rooms[i].cust.to_date;
        } else {
            cout << "\nRoom is available";
        }
        displayRoom(rooms[i]);
        cin.get();
    } else {
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

bool Room::isValidDate(const char* date) {
    int dd, mm, yy;
    if (sscanf(date, "%d/%d/%d", &dd, &mm, &yy) == 3) {
        if (yy >= 0 && mm >= 1 && mm <= 12 && dd >= 1) {
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (yy % 4 == 0 && (yy % 100 != 0 || yy % 400 == 0)) {
                daysInMonth[2] = 29;
            }
            return dd <= daysInMonth[mm];
        }
    }
    return false;
}

bool Room::isChronologicalDate(const char* fromDate, const char* toDate) {
    int dd1, mm1, yy1;
    int dd2, mm2, yy2;

    sscanf(fromDate, "%d/%d/%d", &dd1, &mm1, &yy1);
    sscanf(toDate, "%d/%d/%d", &dd2, &mm2, &yy2);

    if (yy1 < yy2)
        return true;
    if (yy1 > yy2)
        return false;
    if (mm1 < mm2)
        return true;
    if (mm1 > mm2)
        return false;
    return dd1 <= dd2;
}

void Room::registerCustomer(int rno) {
    int i, found = 0;
    for (i = 0; i < Room::roomCount; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1 && rooms[i].status == 0) {
        cout << "\nEnter Customer Name: ";
        cin.ignore();
        cin.getline(rooms[i].cust.name, sizeof(rooms[i].cust.name));

        cout << "\nEnter Customer Address: ";
        cin.getline(rooms[i].cust.address, sizeof(rooms[i].cust.address));

        cout << "\nEnter Customer Phone: ";
        cin.getline(rooms[i].cust.phone, sizeof(rooms[i].cust.phone));

        do {
            cout << "\nEnter From Date (dd/mm/yyyy): ";
            cin >> rooms[i].cust.from_date;
        } while (!isValidDate(rooms[i].cust.from_date));

        do {
            cout << "\nEnter To Date (dd/mm/yyyy): ";
            cin >> rooms[i].cust.to_date;
        } while (!isValidDate(rooms[i].cust.to_date) || !isChronologicalDate(rooms[i].cust.from_date, rooms[i].cust.to_date));

        cout << "\nEnter Advance Payment: ";
        cin >> rooms[i].cust.payment_advance;

        if (rooms[i].cust.payment_advance >= rooms[i].rent) {
            cout << "\nAdvance payment is equal to or greater than the room rent.";
        } else {
            rooms[i].status = 1;
            rooms[i].cust.booking_id = i + 1;
            cout << "\nCustomer Registered Successfully!";
        }
        cin.ignore();
    } else if (found == 1 && rooms[i].status == 1) {
        cout << "\nRoom is already booked!";
    } else {
        cout << "\nRoom not found";
    }
    cin.get();
}

void Room::displayAllRooms() {
    if (Room::roomCount > 0) {
        cout << "List of All Rooms:\n";
        for (int i = 0; i < Room::roomCount; i++) {
            cout << "Room Number: " << rooms[i].roomNumber << " Status: ";
            if (rooms[i].status == 1) {
                cout << "Reserved for " << rooms[i].cust.name << " from " << rooms[i].cust.from_date << " to " << rooms[i].cust.to_date;
            } else {
                cout << "Available";
            }
            cout << "\n";
        }
    } else {
        cout << "No rooms added yet.\n";
    }
}

int main() {
    char ch;
    int rno;

    do {
        system("cls");
        cout << "HOTEL MANAGEMENT SYSTEM";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Register Customer";
        cout << "\n4. Display All Rooms";
        cout << "\n5. Exit";
        cout << "\nEnter your choice (1-5): ";
        cin >> ch;

        switch (ch) {
            case '1':
                cout << "Enter Room Number: ";
                cin >> rno;
                rooms[Room::roomCount++] = rooms[Room::roomCount].addRoom(rno);
                break;
            case '2':
                cout << "Enter Room Number: ";
                cin >> rno;
                rooms[Room::roomCount].searchRoom(rno);
                break;
            case '3':
                cout << "Enter Room Number: ";
                cin >> rno;
                rooms[Room::roomCount].registerCustomer(rno);
                break;
            case '4':
                Room::displayAllRooms();
                cin.get();
                break;
            case '5':
                exit(0);
        }
    } while (ch != '5');
    return 0;
}
