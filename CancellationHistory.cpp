
#include <iostream>
#include <string>

using namespace std;

// Stores information about a cancelled reservation
struct Reservation
{
    int reservationID;
    int studentID;
    string studentName;
    string resourceID;
    string date;
};

// Node for the stack
struct CancellationNode
{
    Reservation reservation;
    CancellationNode* next;
};

// Cancellation history implemented using a stack
class CancellationHistory
{
private:
    CancellationNode* top;

public:
    // Constructor
    CancellationHistory()
    {
        top = nullptr;
    }

    // Add a cancelled reservation to the stack
    void pushCancellation(
        int reservationID,
        int studentID,
        string studentName,
        string resourceID,
        string date)
    {
        Reservation newReservation;

        newReservation.reservationID = reservationID;
        newReservation.studentID = studentID;
        newReservation.studentName = studentName;
        newReservation.resourceID = resourceID;
        newReservation.date = date;

        CancellationNode* newNode = new CancellationNode;

        newNode->reservation = newReservation;
        newNode->next = top;

        top = newNode;

        cout << "Reservation added to cancellation history."
             << endl;
    }

    // Restore the most recently cancelled reservation
    bool restoreLastCancellation(Reservation& restoredReservation)
    {
        if (top == nullptr)
        {
            cout << "No cancelled reservations to restore."
                 << endl;

            return false;
        }

        CancellationNode* temporary = top;

        restoredReservation = temporary->reservation;

        top = top->next;

        delete temporary;

        cout << "Last cancelled reservation restored."
             << endl;

        return true;
    }

    // Display cancellation history
    void displayHistory()
    {
        if (top == nullptr)
        {
            cout << "Cancellation history is empty." << endl;
            return;
        }

        CancellationNode* current = top;

        cout << "\nCancellation History:" << endl;

        while (current != nullptr)
        {
            cout << "Reservation ID: "
                 << current->reservation.reservationID << endl;

            cout << "Student ID: "
                 << current->reservation.studentID << endl;

            cout << "Student Name: "
                 << current->reservation.studentName << endl;

            cout << "Resource ID: "
                 << current->reservation.resourceID << endl;

            cout << "Date: "
                 << current->reservation.date << endl;

            cout << "------------------------" << endl;

            current = current->next;
        }
    }

    // Destructor
    ~CancellationHistory()
    {
        while (top != nullptr)
        {
            CancellationNode* temporary = top;
            top = top->next;
            delete temporary;
        }
    }
};