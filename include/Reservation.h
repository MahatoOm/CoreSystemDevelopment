#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation
{
private:
    std::string reservationID;
    std::string studentID;
    std::string studentName;
    std::string resourceID;
    std::string reservationDate;

public:
    Reservation();

    Reservation(const std::string& reservationID,
                const std::string& studentID,
                const std::string& studentName,
                const std::string& resourceID,
                const std::string& reservationDate);

    std::string getReservationID() const;
    std::string getStudentID() const;
    std::string getStudentName() const;
    std::string getResourceID() const;
    std::string getReservationDate() const;

    void display() const;
};

// Node used by the active reservation linked list
struct ReservationNode
{
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& reservation)
    {
        data = reservation;
        next = nullptr;
    }
};

#endif