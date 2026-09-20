#include <iostream>
#include  <string>

using namespace std;

struct Reservation {
	int reservationID;
	string studentName;
	string resourceID;
	string reservationDate;
	int studentID;
};

class ReservationManager {
public:
	ReservationList activeReservations;

public:
	void createReservation();
	void cancelReservation();
	void displayActiveReservations();
};

//Create a new reservation
void ReservationManager ::createReservation() {
	Reservation newReservation;
	cout << "Enter Reservation ID: ";
	cin >> newReservation.reservationID;
	cout << "Enter Student ID: ";
	cin >> newReservation.studentID;
	cout << "Enter Student Name: ";
	cin.ignore();
	getline(cin, newReservation.studentName);
	cout << "Enter Resource ID: ";
	getline(cin, newReservation.resourceID);
	cout << "Enter Reservation Date (YYYY-MM-DD): ";
	getline(cin, newReservation.reservationDate);
	activeReservations.addReservation(newReservation);
	cout << "Reservation created successfully!" << endl;
}

//Cancel an existing reservation
void ReservationManager ::cancelReservation() {
	int reservationID;
	cout << "Enter Reservation ID to cancel: ";
	cin >> reservationID;
	if (activeReservations.removeReservation(reservationID)) {
		cout << "Reservation canceled successfully!" << endl;
	}
	else {
		cout << "Reservation ID not found!" << endl;
	}
}

//Display all active reservations
void ReservationManager ::displayActiveReservations() {
	activeReservations.displayReservations();
}