#include "ReservationManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

ReservationManager::ReservationManager()
{
    reservationHead = nullptr;
}

ReservationManager::~ReservationManager()
{
    ReservationNode* current = reservationHead;

    while (current != nullptr)
    {
        ReservationNode* temp = current;
        current = current->next;

        delete temp;
    }

    reservationHead = nullptr;
}

// ============================================================
// RESOURCE FILE LOADING
// ============================================================

void ReservationManager::loadResources()
{
    std::ifstream file("data/resources.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open resources.txt\n";
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string id;
        std::string name;
        std::string type;
        std::string status;

        // Your file uses | as the delimiter
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, status, '|');

        Resource resource(id, name, type, status);

        resources.push_back(resource);
    }

    file.close();

    std::cout << resources.size()
              << " resources loaded successfully.\n";
}

// ============================================================
// RESERVATION FILE LOADING
// ============================================================

void ReservationManager::loadReservations()
{
    std::ifstream file("data/reservations.txt");

    if (!file.is_open())
    {
        std::cerr << "Warning: Could not open reservations.txt\n";
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string reservationID;
        std::string studentID;
        std::string studentName;
        std::string resourceID;
        std::string reservationDate;

        // Your file uses | as the delimiter
        std::getline(ss, reservationID, '|');
        std::getline(ss, studentID, '|');
        std::getline(ss, studentName, '|');
        std::getline(ss, resourceID, '|');
        std::getline(ss, reservationDate, '|');

        Reservation reservation(
            reservationID,
            studentID,
            studentName,
            resourceID,
            reservationDate
        );

        if (!insertReservation(reservation))
        {
            std::cerr << "Warning: Could not load reservation "
                      << reservationID << '\n';
        }
    }

    file.close();
}

// ============================================================
// RESOURCE FUNCTIONS
// ============================================================

void ReservationManager::displayResources()
{
    if (resources.empty())
    {
        std::cout << "No resources available.\n";
        return;
    }

    std::cout << "\n========== RESOURCES ==========\n";

    for (const Resource& resource : resources)
    {
        resource.display();
    }

    std::cout << "===============================\n";
}

int ReservationManager::findResourceIndex(
    const std::string& resourceID) const
{
    for (int i = 0; i < static_cast<int>(resources.size()); i++)
    {
        if (resources[i].getResourceID() == resourceID)
        {
            return i;
        }
    }

    return -1;
}

// ============================================================
// LINKED LIST FUNCTIONS
// ============================================================

bool ReservationManager::reservationExists(
    const std::string& reservationID) const
{
    return findReservation(reservationID) != nullptr;
}

ReservationNode* ReservationManager::findReservation(
    const std::string& reservationID) const
{
    ReservationNode* current = reservationHead;

    while (current != nullptr)
    {
        if (current->data.getReservationID() == reservationID)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool ReservationManager::insertReservation(
    const Reservation& reservation)
{
    // Prevent duplicate reservation IDs
    if (reservationExists(reservation.getReservationID()))
    {
        return false;
    }

    ReservationNode* newNode =
        new ReservationNode(reservation);

    // Insert at beginning of linked list
    newNode->next = reservationHead;
    reservationHead = newNode;

    return true;
}

bool ReservationManager::removeReservation(
    const std::string& reservationID,
    Reservation& removedReservation)
{
    if (reservationHead == nullptr)
    {
        return false;
    }

    ReservationNode* current = reservationHead;
    ReservationNode* previous = nullptr;

    while (current != nullptr)
    {
        if (current->data.getReservationID() == reservationID)
        {
            removedReservation = current->data;

            if (previous == nullptr)
            {
                // Removing first node
                reservationHead = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            delete current;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

// ============================================================
// DISPLAY RESERVATIONS
// ============================================================

void ReservationManager::displayReservations()
{
    if (reservationHead == nullptr)
    {
        std::cout << "No active reservations.\n";
        return;
    }

    std::cout << "\n======= ACTIVE RESERVATIONS =======\n";

    ReservationNode* current = reservationHead;

    while (current != nullptr)
    {
        current->data.display();
        current = current->next;
    }

    std::cout << "===================================\n";
}

// ============================================================
// CREATE RESERVATION
// ============================================================

void ReservationManager::createReservation()
{
    std::string reservationID;
    std::string studentID;
    std::string studentName;
    std::string resourceID;
    std::string reservationDate;

    std::cout << "\nEnter Reservation ID: ";
    std::cin >> reservationID;

    if (reservationExists(reservationID))
    {
        std::cout << "Error: Reservation ID already exists.\n";
        return;
    }

    std::cout << "Enter Student ID: ";
    std::cin >> studentID;

    std::cin.ignore();

    std::cout << "Enter Student Name: ";
    std::getline(std::cin, studentName);

    std::cout << "Enter Resource ID: ";
    std::cin >> resourceID;

    int resourceIndex = findResourceIndex(resourceID);

    if (resourceIndex == -1)
    {
        std::cout << "Error: Invalid Resource ID.\n";
        return;
    }

    if (resources[resourceIndex].getAvailabilityStatus()
        != "Available")
    {
        std::cout << "Resource is currently unavailable.\n";

        std::cout << "Would you like to join the waiting list? (y/n): ";

        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            waitingList.enqueue(studentID, studentName);

            std::cout << "Added to waiting list.\n";
        }

        return;
    }

    std::cout << "Enter Reservation Date: ";
    std::cin >> reservationDate;

    Reservation reservation(
        reservationID,
        studentID,
        studentName,
        resourceID,
        reservationDate
    );

    if (insertReservation(reservation))
    {
        resources[resourceIndex].setAvailabilityStatus(
            "Reserved"
        );

        std::cout << "Reservation Created Successfully.\n";
    }
    else
    {
        std::cout << "Could not create reservation.\n";
    }
}

// ============================================================
// CANCEL RESERVATION
// ============================================================

void ReservationManager::cancelReservation()
{
    std::string reservationID;

    std::cout << "\nEnter Reservation ID to cancel: ";
    std::cin >> reservationID;

    Reservation removedReservation;

    if (!removeReservation(reservationID, removedReservation))
    {
        std::cout << "Reservation not found.\n";
        return;
    }

    // Add cancelled reservation to stack
    cancellationHistory.push(removedReservation);

    // Make resource available again
    int resourceIndex =
        findResourceIndex(
            removedReservation.getResourceID()
        );

    if (resourceIndex != -1)
    {
        resources[resourceIndex].setAvailabilityStatus(
            "Available"
        );
    }

    std::cout << "Reservation Cancelled.\n";
    std::cout << "Added to cancellation history.\n";
}

// ============================================================
// UNDO CANCELLATION
// ============================================================

void ReservationManager::undoCancellation()
{
    Reservation reservation;

    if (!cancellationHistory.pop(reservation))
    {
        std::cout << "Cancellation history is empty.\n";
        return;
    }

    int resourceIndex =
        findResourceIndex(
            reservation.getResourceID()
        );

    if (resourceIndex == -1)
    {
        std::cout << "Error: Resource no longer exists.\n";
        return;
    }

    if (resources[resourceIndex].getAvailabilityStatus()
        != "Available")
    {
        std::cout
            << "Cannot restore reservation because resource "
            << "is currently unavailable.\n";

        // Put it back on the stack
        cancellationHistory.push(reservation);

        return;
    }

    if (insertReservation(reservation))
    {
        resources[resourceIndex].setAvailabilityStatus(
            "Reserved"
        );

        std::cout << "Reservation Restored Successfully.\n";
    }
    else
    {
        std::cout << "Could not restore reservation.\n";
    }
}

// ============================================================
// WAITING LIST
// ============================================================

void ReservationManager::addToWaitingList()
{
    std::string studentID;
    std::string studentName;

    std::cout << "Enter Student ID: ";
    std::cin >> studentID;

    std::cin.ignore();

    std::cout << "Enter Student Name: ";
    std::getline(std::cin, studentName);

    waitingList.enqueue(studentID, studentName);

    std::cout << "Student added to waiting list.\n";
}

void ReservationManager::displayWaitingList()
{
    waitingList.display();
}

// ============================================================
// CANCELLATION HISTORY
// ============================================================

void ReservationManager::displayCancellationHistory()
{
    cancellationHistory.display();
}

// ============================================================
// SEARCH RESERVATIONS
// ============================================================

void ReservationManager::searchReservation()
{
    int choice;

    std::cout << "\nSearch By:\n";
    std::cout << "1. Reservation ID\n";
    std::cout << "2. Student ID\n";
    std::cout << "Enter choice: ";

    std::cin >> choice;

    if (choice == 1)
    {
        std::string reservationID;

        std::cout << "Enter Reservation ID: ";
        std::cin >> reservationID;

        ReservationNode* result =
            findReservation(reservationID);

        if (result == nullptr)
        {
            std::cout << "Reservation not found.\n";
        }
        else
        {
            result->data.display();
        }
    }
    else if (choice == 2)
    {
        std::string studentID;

        std::cout << "Enter Student ID: ";
        std::cin >> studentID;

        ReservationNode* current = reservationHead;

        bool found = false;

        while (current != nullptr)
        {
            if (current->data.getStudentID() == studentID)
            {
                current->data.display();
                found = true;
            }

            current = current->next;
        }

        if (!found)
        {
            std::cout << "No reservations found for student.\n";
        }
    }
    else
    {
        std::cout << "Invalid search option.\n";
    }
}


// #include <iostream>
// #include  <string>

// using namespace std;

// struct Reservation {
// 	int reservationID;
// 	string studentName;
// 	string resourceID;
// 	string reservationDate;
// 	int studentID;
// };

// class ReservationManager {
// public:
// 	ReservationList activeReservations;

// public:
// 	void createReservation();
// 	void cancelReservation();
// 	void displayActiveReservations();
// };

// //Create a new reservation
// void ReservationManager ::createReservation() {
// 	Reservation newReservation;
// 	cout << "Enter Reservation ID: ";
// 	cin >> newReservation.reservationID;
// 	cout << "Enter Student ID: ";
// 	cin >> newReservation.studentID;
// 	cout << "Enter Student Name: ";
// 	cin.ignore();
// 	getline(cin, newReservation.studentName);
// 	cout << "Enter Resource ID: ";
// 	getline(cin, newReservation.resourceID);
// 	cout << "Enter Reservation Date (YYYY-MM-DD): ";
// 	getline(cin, newReservation.reservationDate);
// 	activeReservations.addReservation(newReservation);
// 	cout << "Reservation created successfully!" << endl;
// }

// //Cancel an existing reservation
// void ReservationManager ::cancelReservation() {
// 	int reservationID;
// 	cout << "Enter Reservation ID to cancel: ";
// 	cin >> reservationID;
// 	if (activeReservations.removeReservation(reservationID)) {
// 		cout << "Reservation canceled successfully!" << endl;
// 	}
// 	else {
// 		cout << "Reservation ID not found!" << endl;
// 	}
// }

// //Display all active reservations
// void ReservationManager ::displayActiveReservations() {
// 	activeReservations.displayReservations();
// }