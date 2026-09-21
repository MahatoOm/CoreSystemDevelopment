#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <vector>
#include <string>

#include "Resource.h"
#include "Reservation.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

class ReservationManager
{
private:
    // Required vector for resource inventory
    std::vector<Resource> resources;

    // Required linked list for active reservations
    ReservationNode* reservationHead;

    // Waiting list queue
    WaitingList waitingList;

    // Cancellation history stack
    CancellationHistory cancellationHistory;

public:
    ReservationManager();

    ~ReservationManager();

    // File operations
    void loadResources();
    void loadReservations();

    // Resource operations
    void displayResources();
    int findResourceIndex(const std::string& resourceID) const;

    // Reservation operations
    void createReservation();
    void cancelReservation();
    void displayReservations();

    // Search
    void searchReservation();

    // Waiting list
    void addToWaitingList();

    void displayWaitingList();

    // Cancellation
    void undoCancellation();
    void displayCancellationHistory();

private:
    // Linked list helper functions
    bool reservationExists(const std::string& reservationID) const;

    ReservationNode* findReservation(
        const std::string& reservationID) const;

    bool insertReservation(const Reservation& reservation);

    bool removeReservation(
        const std::string& reservationID,
        Reservation& removedReservation);
};

#endif