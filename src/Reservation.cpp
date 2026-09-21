#include "Reservation.h"
#include <iostream>

Reservation::Reservation()
{
    reservationID = "";
    studentID = "";
    studentName = "";
    resourceID = "";
    reservationDate = "";
}

Reservation::Reservation(const std::string& reservationID,
                         const std::string& studentID,
                         const std::string& studentName,
                         const std::string& resourceID,
                         const std::string& reservationDate)
{
    this->reservationID = reservationID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->reservationDate = reservationDate;
}

std::string Reservation::getReservationID() const
{
    return reservationID;
}

std::string Reservation::getStudentID() const
{
    return studentID;
}

std::string Reservation::getStudentName() const
{
    return studentName;
}

std::string Reservation::getResourceID() const
{
    return resourceID;
}

std::string Reservation::getReservationDate() const
{
    return reservationDate;
}

void Reservation::display() const
{
    std::cout << "Reservation ID: " << reservationID
              << " | Student ID: " << studentID
              << " | Student: " << studentName
              << " | Resource: " << resourceID
              << " | Date: " << reservationDate
              << '\n';
}