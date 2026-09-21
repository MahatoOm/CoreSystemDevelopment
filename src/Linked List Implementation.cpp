#include <iostream>
#include <string>
using namespace std;
//a linked list that stores actibe reservations
struct Node {
	Reservation reservation;
	Node* next;
	Node(Reservation r) {
		reservation = r;
		next = nullptr;
	}
};

class ReservationList {
private: 
	Node* head;

public: 
	ReservationList() {
		head = nullptr;
	}
	void insertReservation(Reservation r);
	void displayReservations();
	bool removeReservation(string studentID, string resourceID);
};

//insert reservation
void ReservationList::insertReservation(ReservationList r) {
	Node* newNode = new Node(r);
	//if list is empty
	if (head == nullptr) {
		head = newNode;
		return;
	}
	//Add to the front
	newNode->next = head;
	head = newNode;
}

//remove reservation
bool ReservationList::removeReservation(string studentID, string resourceID) {
	Node* current = head;
	Node* previous = nullptr;
	//traverse the list to find the reservation
	while (current != nullptr) {
		if (current->reservation.studentID == studentID &&
			current->reservation.resourceID == resourceID) {
			//removing the first node
			if (previous == nullptr) {
				head = current->next;
			}
			else {
				previous->next = current->next;
			}
			delete current;
			cout << "Reservation canceled successfully!" << endl;
			return true;
		}
		previous = current;
		current = current->next;
	}
	cout << "Reservation not found!" << endl;
	return false;
}

//Display reservations
void ReservationList::displayReservations() {
	
	if (current == nullptr) {
		cout << "No active reservations." << endl;
		return;
	}
	Node* current = head;
	cout << "===== Active Reservations =====" << endl;
	while (current != nullptr) {
		cout << "Student ID: " << current->reservation.studentID << endl;
		cout << "Student Name: " << current->reservation.studentName << endl;
		cout << "Resource ID: " << current->reservation.resourceID << endl;
		cout << "-------------------------" << endl;

		current = current->next;
	}
}