#include <iostream>
#include <cstring>
#include <cstdlib>

#define max 100

using namespace std;

class Accommodation {
public:
    virtual void displayRoom() = 0;
};

class Facility {
public:
    virtual void displayFacility() = 0;
};

class Customer {
private:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;

public:
    const char* getName() const {
        return name;
    }

    void setName(const char* newName) {
        strncpy(name, newName, sizeof(name));
        name[sizeof(name) - 1] = '\0';
    }

    const char* getAddress() const {
        return address;
    }

    void setAddress(const char* newAddress) {
        strncpy(address, newAddress, sizeof(address));
        address[sizeof(address) - 1] = '\0';
    }

    const char* getPhone() const {
        return phone;
    }

    void setPhone(const char* newPhone) {
        strncpy(phone, newPhone, sizeof(phone));
        phone[sizeof(phone) - 1] = '\0';
    }

    const char* getFromDate() const {
        return from_date;
    }

    void setFromDate(const char* newFromDate) {
        strncpy(from_date, newFromDate, sizeof(from_date));
        from_date[sizeof(from_date) - 1] = '\0';
    }

    const char* getToDate() const {
        return to_date;
    }

    void setToDate(const char* newToDate) {
        strncpy(to_date, newToDate, sizeof(to_date));
        to_date[sizeof(to_date) - 1] = '\0';
    }

    float getPaymentAdvance() const {
        return payment_advance;
    }

    void setPaymentAdvance(float newPaymentAdvance) {
        payment_advance = newPaymentAdvance;
    }

    int getBookingId() const {
        return booking_id;
    }

    void setBookingId(int newBookingId) {
        booking_id = newBookingId;
    }

    Customer() {
        setName("");
        setAddress("");
        setPhone("");
        setFromDate("");
        setToDate("");
        setPaymentAdvance(0.0);
        setBookingId(0);
    }
};

class Room : public Accommodation, public Facility {
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
        roomNumber = rno;
        status = 0;
    }

    static int getRoomCount() {
        return roomCount;
    }

    virtual void displayRoom() {
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nType AC/Non-AC (A/N): " << ac;
        cout << "\nType Comfort (S/N): " << type;
        cout << "\nType Size (B/S): " << stype;
        cout << "\nRent: " << rent;
    }

    virtual void displayFacility() {
        cout << "\nAdditional Facilities: ";
        cout << "\n1. Free Wi-Fi";
        cout << "\n2. Mini Bar";
        cout << "\n3. Room Service";
        cout << "\n4. Spa";
        cout << "\n5. Gym";
        cout << "\n6. Back";
    }

    void viewAdditionalFacilities() {
        char choice;
        do {
            system("cls");
            displayFacility();
            cout << "\nEnter your choice (1-6): ";
            cin >> choice;

            switch (choice) {
                case '1':
                    cout << "\nFree Wi-Fi is available.";
                    break;
                case '2':
                    cout << "\nMini Bar is available.";
                    break;
                case '3':
                    cout << "\nRoom Service is available.";
                    break;
                case '4':
                    cout << "\nSpa is available.";
                    break;
                case '5':
                    cout << "\nGym is available.";
                    break;
                case '6':
                    // Back to the main menu
                    return;
                default:
                    cout << "\nInvalid choice. Please try again.";
            }

            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        } while (true);
    }

    static Room* addRoom(int rno);
    void searchRoom(int);
    bool isValidDate(const char*);
    bool isChronologicalDate(const char*, const char*);
    void registerCustomer(int);
    static void displayAllRooms();
};

Room rooms[max];
int Room::roomCount = 0;

Room* Room::addRoom(int rno) {
    Room* room = new Room(rno);

    cout << "\nType AC/Non-AC (A/N): ";
    cin >> room->ac;
    cout << "\nType Comfort (S/N): ";
    cin >> room->type;
    cout << "\nType Size (B/S): ";
    cin >> room->stype;
    cout << "\nDaily Rent: ";
    cin >> room->rent;

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
            cout << "\nRoom is Reserved for " << rooms[i].cust.getName() << " from " << rooms[i].cust.getFromDate() << " to " << rooms[i].cust.getToDate();
        } else {
            cout << "\nRoom is available";
        }
        rooms[i].displayRoom();
        cin.get();
    } else {
        cout << "\nRoom not found";
        cin.get();
    }
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
        char tempName[100];
        cin.getline(tempName, sizeof(tempName));
        rooms[i].cust.setName(tempName);

        cout << "\nEnter Customer Address: ";
        char tempAddress[100];
        cin.getline(tempAddress, sizeof(tempAddress));
        rooms[i].cust.setAddress(tempAddress);

        cout << "\nEnter Customer Phone: ";
        char tempPhone[12];
        cin.getline(tempPhone, sizeof(tempPhone));
        rooms[i].cust.setPhone(tempPhone);

        do {
            cout << "\nEnter From Date (dd/mm/yyyy): ";
            char tempFromDate[20];
            cin >> tempFromDate;
            rooms[i].cust.setFromDate(tempFromDate);
        } while (!isValidDate(rooms[i].cust.getFromDate()));

        do {
            cout << "\nEnter To Date (dd/mm/yyyy): ";
            char tempToDate[20];
            cin >> tempToDate;
            rooms[i].cust.setToDate(tempToDate);
        } while (!isValidDate(rooms[i].cust.getToDate()) || !isChronologicalDate(rooms[i].cust.getFromDate(), rooms[i].cust.getToDate()));

        cout << "\nEnter Advance Payment: ";
        float paymentAdvance;
        cin >> paymentAdvance;
        rooms[i].cust.setPaymentAdvance(paymentAdvance);

        if (rooms[i].cust.getPaymentAdvance() >= rooms[i].rent) {
            cout << "\nAdvance payment is equal to or greater than the room rent.";
        } else {
            rooms[i].status = 1;
            rooms[i].cust.setBookingId(i + 1);
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
                cout << "Reserved for " << rooms[i].cust.getName() << " from " << rooms[i].cust.getFromDate() << " to " << rooms[i].cust.getToDate();
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
        cout << "\n6. View Additional Facilities";
        cout << "\nEnter your choice (1-6): ";
        cin >> ch;

        switch (ch) {
            case '1':
                cout << "Enter Room Number: ";
                cin >> rno;
                rooms[Room::roomCount++] = *Room::addRoom(rno);
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
                // Release dynamically allocated memory for each room
                for (int i = 0; i < Room::roomCount; i++) {
                    delete &rooms[i];
                }
                exit(0);
            case '6':
                rooms[Room::roomCount].viewAdditionalFacilities();
                break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }
    } while (ch != '5');
    return 0;
}
