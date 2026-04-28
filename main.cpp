#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int max_cars = 10;

struct Car {
    string plateNumber;
    string model;
    string make;
    int year;
    string rentalStatus;
    string rentDate;
    string expectedReturnDate;
    string returnDate;

    Car() : year(0), rentalStatus("Available"), rentDate(""), expectedReturnDate(""), returnDate("") {}
};

class CarRentalSystem {
private:
    Car cars[max_cars];
    int carCount;

public:
    CarRentalSystem() {
        carCount = 0;
    }

    void writeLog(const string& action, const Car& car) {
        ofstream logFile("log.txt", ios::app);
        if (logFile.is_open()) {
            logFile << action << ": " << car.plateNumber << " | "
                    << car.model << " | " << car.make << " | "
                    << car.year << " | " << car.rentalStatus << "\n";
            logFile.close();
        }
    }

    void saveCarsToFile() {
        ofstream outFile("CarList.txt", ios::out);
        if (outFile.is_open()) {
            for (int i = 0; i < carCount; ++i) {
                outFile << cars[i].plateNumber << " "
                        << cars[i].model << " "
                        << cars[i].make << " "
                        << cars[i].year << " "
                        << cars[i].rentalStatus << " "
                        << (cars[i].rentDate.empty() ? "-" : cars[i].rentDate) << " "
                        << (cars[i].expectedReturnDate.empty() ? "-" : cars[i].expectedReturnDate) << " "
                        << (cars[i].returnDate.empty() ? "-" : cars[i].returnDate) << "\n";
            }
            outFile.close();
        }
    }

    void loadCarsFromFile() {
        ifstream inFile("CarList.txt");
        if (!inFile) {
            cout << "No saved cars found.\n";
            return;
        }

        carCount = 0;
        while (carCount < max_cars) {
            Car car;
            if (!(inFile >> car.plateNumber >> car.model >> car.make >> car.year >> car.rentalStatus
                  >> car.rentDate >> car.expectedReturnDate >> car.returnDate)) {
                break;
            }

            if (car.rentDate == "-") car.rentDate = "";
            if (car.expectedReturnDate == "-") car.expectedReturnDate = "";
            if (car.returnDate == "-") car.returnDate = "";

            cars[carCount++] = car;
        }

        inFile.close();
        cout << carCount << " cars loaded from file.\n";
    }

    void addCar() {
        if (carCount >= max_cars) {
            cout << "No more space to add cars.\n";
            return;
        }

        Car newCar;
        cout << "Enter plate number: ";
        cin >> newCar.plateNumber;
        cout << "Enter model: ";
        cin >> newCar.model;
        cout << "Enter make: ";
        cin >> newCar.make;
        cout << "Enter year: ";
        cin >> newCar.year;

        cars[carCount++] = newCar;
        cout << "Car added.\n";

        saveCarsToFile();
        writeLog("Added", newCar);
    }

    void displayAllCars() {
        cout << "\n--- All Cars ---\n";
        for (int i = 0; i < carCount; i++) {
            cout << "\n==============================\n";
            cout << "Car #" << (i + 1) << "\n";
            cout << "Plate Number       : " << cars[i].plateNumber << "\n";
            cout << "Model              : " << cars[i].model << "\n";
            cout << "Make               : " << cars[i].make << "\n";
            cout << "Year               : " << cars[i].year << "\n";
            cout << "Status             : " << cars[i].rentalStatus << "\n";
            cout << "Rent Date          : " << (cars[i].rentDate.empty() ? "-" : cars[i].rentDate) << "\n";
            cout << "Expected Return    : " << (cars[i].expectedReturnDate.empty() ? "-" : cars[i].expectedReturnDate) << "\n";
            cout << "Return Date        : " << (cars[i].returnDate.empty() ? "-" : cars[i].returnDate) << "\n";
            cout << "==============================\n";
        }
    }

    void menu() {
        loadCarsFromFile();
        int choice;
        do {
            cout << "\n--- Car Rental Menu ---\n";
            cout << "1. Add Car\n";
            cout << "2. View All Cars\n";
            cout << "3. Exit\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1: addCar(); break;
                case 2: displayAllCars(); break;
                case 3: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    CarRentalSystem app;
    app.menu();
    return 0;
}