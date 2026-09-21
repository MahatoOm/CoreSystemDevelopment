#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>

struct WaitingNode
{
    std::string studentID;
    std::string studentName;
    WaitingNode* next;

    WaitingNode(const std::string& id,
                const std::string& name)
    {
        studentID = id;
        studentName = name;
        next = nullptr;
    }
};

class WaitingList
{
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    WaitingList();

    ~WaitingList();

    void enqueue(const std::string& studentID,
                 const std::string& studentName);

    bool dequeue(std::string& studentID,
                 std::string& studentName);

    bool isEmpty() const;

    void display() const;
};

#endif