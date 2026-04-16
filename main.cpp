//NIKHIL BONDE
//VEHICLE RENTAL SYSTEM USING OOPS C++

#include <iostream>
#include <vector>
using namespace std;

// Base Class
class Vehicle {
protected:
    int id;
    string brand;
    double rentPerDay;
    bool available;

public:
    Vehicle(int i, string b, double r) {
        id = i;
        brand = b;
        rentPerDay = r;
        available = true;
    }

    virtual void display() {
        cout << "ID: " << id << ", Brand: " << brand
             << ", Rent/Day: " << rentPerDay
             << (available ? " [Available]" : " [Rented]") << endl;
    }

    virtual double calculateRent(int days) = 0;

    bool isAvailable() { return available; }
    void rentOut() { available = false; }
    void returnBack() { available = true; }

    int getId() { return id; }
};

// Car Class
class Car : public Vehicle {
public:
    Car(int i, string b, double r) : Vehicle(i, b, r) {}

    double calculateRent(int days) override {
        return rentPerDay * days + 100;
    }
};

// Bike Class
class Bike : public Vehicle {
public:
    Bike(int i, string b, double r) : Vehicle(i, b, r) {}

    double calculateRent(int days) override {
        return rentPerDay * days;
    }
};

// Customer Class
class Customer {
private:
    int customerId;
    string name;

public:
    Customer(int id, string n) {
        customerId = id;
        name = n;
    }

    void display() {
        cout << "Customer ID: " << customerId
             << ", Name: " << name << endl;
    }
};

// Rental Class
class Rental {
private:
    Vehicle* vehicle;
    Customer customer;
    int days;

public:
    Rental(Vehicle* v, Customer c, int d)
        : vehicle(v), customer(c), days(d) {}

    void processRental() {
        if (vehicle->isAvailable()) {
            vehicle->rentOut();
            double cost = vehicle->calculateRent(days);

            cout << "\nRental Successful!\n";
            customer.display();
            cout << "Total Cost: " << cost << endl;
        } else {
            cout << "Vehicle not available.\n";
        }
    }

    void returnVehicle() {
        vehicle->returnBack();
        cout << "Vehicle returned successfully.\n";
    }
};

// Rental System
class RentalSystem {
private:
    vector<Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* v) {
        vehicles.push_back(v);
    }

    void showVehicles() {
        for (auto v : vehicles) {
            v->display();
        }
    }

    Vehicle* findVehicle(int id) {
        for (auto v : vehicles) {
            if (v->getId() == id)
                return v;
        }
        return nullptr;
    }
};

// Main Function
int main() {
    RentalSystem system;

    system.addVehicle(new Car(1, "Toyota", 1000));
    system.addVehicle(new Bike(2, "Yamaha", 300));
    system.addVehicle(new Car(1, "BMW", 30000));

    Customer c1(101, "Nikhil");

    cout << "Available Vehicles:\n";
    system.showVehicles();

    Vehicle* v = system.findVehicle(1);

    if (v != nullptr) {
        Rental r(v, c1, 3);
        r.processRental();

        cout << "\nAfter Rental:\n";
        system.showVehicles();

        r.returnVehicle();
    }

    cout << "\nAfter Return:\n";
    system.showVehicles();

    return 0;
}
