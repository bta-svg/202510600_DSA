#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class User {
protected:
    string name;
    string email;
    string phone;

public:
    User() {}
    User(string n, string e, string p) : name(n), email(e), phone(p) {}

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    void setName(string n) { name = n; }
    void setEmail(string e) { email = e; }
    void setPhone(string p) { phone = p; }
};

class VehicleOwner : public User {
public:
    VehicleOwner() : User() {}
    VehicleOwner(string n, string e, string p) : User(n, e, p) {}
};

class Vehicle {
private:
    string plateNumber;
    string vehicleType;
    int year;
    VehicleOwner owner;

public:
    Vehicle() {}
    Vehicle(string plate, string type, int yr, VehicleOwner own)
        : plateNumber(plate), vehicleType(type), year(yr), owner(own) {}

    string getPlateNumber() const { return plateNumber; }
    string getVehicleType() const { return vehicleType; }
    int getYear() const { return year; }
    VehicleOwner getOwner() const { return owner; }
};

bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.rfind('.');
    if (atPos == string::npos || dotPos == string::npos) return false;
    if (atPos == 0 || dotPos < atPos || dotPos == email.size() - 1) return false;
    return true;
}

bool isValidPhone(const string& phone) {
    if (phone.size() != 13) return false;
    if (phone.substr(0, 4) != "+250") return false;
    for (size_t i = 4; i < phone.size(); i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}

bool isValidPlate(const string& plate) {
    if (plate.size() != 7) return false;
    if (!isupper(plate[0]) || !isupper(plate[1]) || !isupper(plate[2])) return false;
    if (!isdigit(plate[3]) || !isdigit(plate[4]) || !isdigit(plate[5])) return false;
    if (!isupper(plate[6])) return false;
    return true;
}

void addRecord() {
    string plate, type, ownerName, email, phone;
    int year;

    do {
        cout << "Plate Number (e.g. RAA123A): ";
        cin >> plate;
        transform(plate.begin(), plate.end(), plate.begin(), ::toupper);
        if (!isValidPlate(plate)) cout << "Invalid plate format. Try again.\n";
    } while (!isValidPlate(plate));

    cout << "Vehicle Type: ";
    cin >> type;

    do {
        cout << "Year: ";
        cin >> year;
        if (year < 1900 || year > 2025) cout << "Invalid year. Enter between 1900 and 2025.\n";
    } while (year < 1900 || year > 2025);

    cin.ignore();
    cout << "Owner Name: ";
    getline(cin, ownerName);

    do {
        cout << "Email: ";
        cin >> email;
        if (!isValidEmail(email)) cout << "Invalid email. Try again.\n";
    } while (!isValidEmail(email));

    do {
        cout << "Phone (+250XXXXXXXXX): ";
        cin >> phone;
        if (!isValidPhone(phone)) cout << "Invalid phone. Must start with +250 and be 13 characters.\n";
    } while (!isValidPhone(phone));

    ofstream file("records.txt", ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    file << plate << "," << type << "," << year << "," << ownerName << "," << email << "," << phone << "\n";
    file.close();
    cout << "Record saved successfully.\n";
}

void displayAll() {
    ifstream file("records.txt");
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    string line;
    vector<Vehicle> vehicles;

    while (getline(file, line)) {
        stringstream ss(line);
        string plate, type, yearStr, ownerName, email, phone;
        getline(ss, plate, ',');
        getline(ss, type, ',');
        getline(ss, yearStr, ',');
        getline(ss, ownerName, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        int year = stoi(yearStr);
        VehicleOwner owner(ownerName, email, phone);
        vehicles.push_back(Vehicle(plate, type, year, owner));
    }
    file.close();

    if (vehicles.empty()) {
        cout << "No records to display.\n";
        return;
    }

    cout << "\n" << string(90, '-') << "\n";
    cout << left << setw(10) << "Plate"
         << setw(12) << "Type"
         << setw(6)  << "Year"
         << setw(20) << "Owner"
         << setw(25) << "Email"
         << setw(15) << "Phone" << "\n";
    cout << string(90, '-') << "\n";

    for (const auto& v : vehicles) {
        cout << left << setw(10) << v.getPlateNumber()
             << setw(12) << v.getVehicleType()
             << setw(6)  << v.getYear()
             << setw(20) << v.getOwner().getName()
             << setw(25) << v.getOwner().getEmail()
             << setw(15) << v.getOwner().getPhone() << "\n";
    }
    cout << string(90, '-') << "\n";
}

void searchRecord() {
    string query;
    cout << "Enter plate number to search: ";
    cin >> query;
    transform(query.begin(), query.end(), query.begin(), ::toupper);

    ifstream file("records.txt");
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string plate, type, yearStr, ownerName, email, phone;
        getline(ss, plate, ',');
        getline(ss, type, ',');
        getline(ss, yearStr, ',');
        getline(ss, ownerName, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (plate == query) {
            cout << "\n--- Vehicle Found ---\n";
            cout << "Plate     : " << plate << "\n";
            cout << "Type      : " << type << "\n";
            cout << "Year      : " << yearStr << "\n";
            cout << "Owner     : " << ownerName << "\n";
            cout << "Email     : " << email << "\n";
            cout << "Phone     : " << phone << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << "No vehicle found with plate number: " << query << "\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Vehicle Registration System ===\n";
        cout << "1. Add Vehicle Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search by Plate Number\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayAll(); break;
            case 3: searchRecord(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
