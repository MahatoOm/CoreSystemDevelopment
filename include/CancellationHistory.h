#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"

struct CancellationNode
{
    Reservation reservation;
    CancellationNode* next;

    CancellationNode(const Reservation& reservation)
    {
        this->reservation = reservation;
        next = nullptr;
    }
};

class CancellationHistory
{
private:
    CancellationNode* top;

public:
    CancellationHistory();

    ~CancellationHistory();

    void push(const Reservation& reservation);

    bool pop(Reservation& reservation);

    bool isEmpty() const;

    void display() const;
};

#endif