#include <iostream>
#include <string>
using namespace std;

// ==================== DATE CLASS (Member 1 - Mohamed) ====================
class Date {
private:
    int day;
    int month;
    int year;
 
public:
    // Constructor
    Date(int d = 1, int m = 1, int y = 2000) {
        day = d;
        month = m;
        year = y;
    }
 
    // Check if year is leap
    bool isLeapYear() {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return true;
        return false;
    }
 
    // Get number of days in month
    int daysInMonth() {
        if (month == 2) {
            if (isLeapYear())
                return 29;
            else
                return 28;
        }
 
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
 
        return 31;
    }
 
    // Validation for date
    bool isValidDate() {
        if (month < 1 || month > 12)
            return false;
 
        if (day < 1 || day > daysInMonth())
            return false;
 
        return true;
    }
 
    // Convert date to total days (utility function)
    int toDays() {
        int totalDays = day;
 
        for (int m = 1; m < month; m++) {
            if (m == 2) {
                if (isLeapYear())
                    totalDays += 29;
                else
                    totalDays += 28;
            }
            else if (m == 4 || m == 6 || m == 9 || m == 11) {
                totalDays += 30;
            }
            else {
                totalDays += 31;
            }
        }
 
        totalDays += year * 365;
        totalDays += year / 4;   // leap years approx
 
        return totalDays;
    }
 
    // Calculate days between two dates
    int daysBetween(Date other) {
        int d1 = toDays();
        int d2 = other.toDays();
 
        if (d1 > d2)
            return d1 - d2;
        else
            return d2 - d1;
    }
 
    // Print date
    void printDate() {
        cout << day << "/" << month << "/" << year << endl;
    }
};

// ==================== ROOM CLASS (Member 2 - Jana) ====================
class Room {
private:
    int roomnumber;
    string type;
    string status;
    double baserate;

public:
    Room(int number, string t, double rate) {
        roomnumber = number;
        type = t;
        baserate = rate;
        status = "Available";  
    }
    
    double calculateRate(int season) {
        if (season == 1) {
            return baserate + 200;   
        }
        else if (season == 2) {
            return baserate - 100;
        }
        else {
            return baserate;
        }
    }
    
    int getRoomnumber() {
        return roomnumber;
    }

    string getType() {
        return type;
    }

    string getStatus() {
        return status;
    }

    void setStatus(string s) {
        status = s;
    }

    string bookRoom() {
        if (status == "Available") {
            status = "Booked";
            return "Room booked successfully.";
        }
        else {
            return "Room is not available.";
        }
    }

    void displayInfo() {
        cout << "Room Number: " << roomnumber << endl;
        cout << "Type: " << type << endl;

        if (status == "Available") {
            cout << "Status: Available " << endl;
        }
        else if (status == "Booked") {
            cout << "Status: Booked " << endl;
        }
        else if (status == "Maintenance") {
            cout << "Status: Maintenance " << endl;
        }
        else {
            cout << "Status: Unknown" << endl;
        }

        cout << "Base Rate: " << baserate << endl;
        cout << "-----------------------" << endl;
    }
};

// ==================== GUEST STRUCT & FUNCTIONS (Member 3 - Marim) ====================
struct Guest {
    string name;
    int stayCount;
    int loyaltyPoints;
    int penalties;
    string guestClass;
    string benefits;
};

string assignGuestClass(int stayCount) {
    if (stayCount >= 10)
        return "VIP";
    else if (stayCount >= 5)
        return "Regular";
    else
        return "New";
}

string applyLoyaltyProgram(int loyaltyPoints) {
    int threshold = 100;
    if (loyaltyPoints >= 100)
        return"Upgraded Benefits";
    else
        return "Standard Benefits";
}

struct PenaltyResult {
    int loyaltyPoints;
    int penalties;
};

PenaltyResult applyPenaltySystem(int loyaltyPoints, int penalties) {
    while (penalties > 0) {
        cout << "Applying penalty. Penalties left: " << penalties << endl;
        loyaltyPoints = (loyaltyPoints - 10 >= 0) ? loyaltyPoints - 10 : 0;
        penalties--;
    }
    return {loyaltyPoints, penalties};
}

// ==================== MAIN PROGRAM (Integration) ====================
int main() {
    cout << "========================================" << endl;
    cout << "   HOTEL MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;

    // Create rooms (Member 2 code)
    Room r1(101, "Single", 500);
    Room r2(202, "Double", 700);
    Room r3(303, "Suite", 1200);

    // Set initial statuses
    r1.setStatus("Available");
    r2.setStatus("Available");
    r3.setStatus("Available");

    // Create guests array (Member 3 code)
    const int SIZE = 3;
    Guest guests[SIZE] = {
        {"jana", 10, 120, 1, "", ""},
        {"sara", 3, 50, 0, "", ""},
        {"mariska", 7, 80, 2, "", ""}
    };

    // Process guests (Member 3 code)
    cout << "\n========== Processing Existing Guests ==========" << endl;
    for (int i = 0; i < SIZE; i++) {
        guests[i].guestClass = assignGuestClass(guests[i].stayCount);
        cout << guests[i].name << " is assigned to class " << guests[i].guestClass << endl;

        guests[i].benefits = applyLoyaltyProgram(guests[i].loyaltyPoints);
        cout << guests[i].name << " has " << guests[i].benefits << endl;

        PenaltyResult result = applyPenaltySystem(guests[i].loyaltyPoints, guests[i].penalties);
        guests[i].loyaltyPoints = result.loyaltyPoints;
        guests[i].penalties = result.penalties;

        cout << guests[i].name << "'s penalties cleared. Remaining loyalty points: " 
             << guests[i].loyaltyPoints << endl;
        cout << "----------------------------------------" << endl;
    }

    // Get new guest info (Member 4 code style)
    string guestName;
    cout << "\nEnter your full name: ";
    getline(cin, guestName);

    // Get season
    int season;
    cout << "Enter season (High=1, Low=2, Normal=3): ";
    cin >> season;
    cin.ignore();

    // Display available rooms
    cout << "\n========== Available Rooms ==========" << endl;
    r1.displayInfo();
    cout << "Rate: " << r1.calculateRate(season) << endl << endl;

    r2.displayInfo();
    cout << "Rate: " << r2.calculateRate(season) << endl << endl;

    r3.displayInfo();
    cout << "Rate: " << r3.calculateRate(season) << endl << endl;

    // Book a room
    int rn;
    cout << "Enter room number to book: ";
    cin >> rn;

    if (rn == r1.getRoomnumber())
        cout << r1.bookRoom() << endl;
    else if (rn == r2.getRoomnumber())
        cout << r2.bookRoom() << endl;
    else if (rn == r3.getRoomnumber())
        cout << r3.bookRoom() << endl;
    else
        cout << "Room not found." << endl;

    // Test Date class (Member 1)
    cout << "\n========== Testing Date Functionality ==========" << endl;
    int d1, m1, y1, d2, m2, y2;
    cout << "Enter check-in date (day month year): ";
    cin >> d1 >> m1 >> y1;
    cout << "Enter check-out date (day month year): ";
    cin >> d2 >> m2 >> y2;

    Date checkIn(d1, m1, y1);
    Date checkOut(d2, m2, y2);

    if (checkIn.isValidDate() && checkOut.isValidDate()) {
        cout << "Check-in date: ";
        checkIn.printDate();
        cout << "Check-out date: ";
        checkOut.printDate();
        cout << "Number of nights: " << checkIn.daysBetween(checkOut) << endl;
    } else {
        cout << "Invalid date(s) entered!" << endl;
    }

    cout << "\n========================================" << endl;
    cout << "Thank you for using Hotel Management System!" << endl;
    cout << "========================================" << endl;

    return 0;
}