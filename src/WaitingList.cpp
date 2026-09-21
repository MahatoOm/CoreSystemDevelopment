
#include <iostream>
#include <string>

using namespace std;

// Stores information about a student waiting for a resource
struct WaitingStudent
{
    int studentID;
    string studentName;
    string resourceID;
};

// Node for the queue
struct WaitingNode
{
    WaitingStudent student;
    WaitingNode* next;
};

// Waiting list implemented using a queue
class WaitingList
{
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    // Constructor
    WaitingList()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Add a student to the waiting list
    void addStudent(int studentID, string studentName, string resourceID)
    {
        WaitingStudent newStudent;

        newStudent.studentID = studentID;
        newStudent.studentName = studentName;
        newStudent.resourceID = resourceID;

        WaitingNode* newNode = new WaitingNode;

        newNode->student = newStudent;
        newNode->next = nullptr;

        // If the queue is empty
        if (rear == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            // Add the student at the end
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Student added to waiting list." << endl;
    }

    // Remove the first student from the waiting list
    void removeStudent()
    {
        if (front == nullptr)
        {
            cout << "Waiting list is empty." << endl;
            return;
        }

        WaitingNode* temporary = front;

        cout << "Removed student: "
             << temporary->student.studentName << endl;

        front = front->next;

        // If the queue becomes empty
        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temporary;
    }

    // Display all students in the waiting list
    void displayWaitingList()
    {
        if (front == nullptr)
        {
            cout << "Waiting list is empty." << endl;
            return;
        }

        WaitingNode* current = front;

        cout << "\nWaiting List:" << endl;

        while (current != nullptr)
        {
            cout << "Student ID: "
                 << current->student.studentID << endl;

            cout << "Student Name: "
                 << current->student.studentName << endl;

            cout << "Resource ID: "
                 << current->student.resourceID << endl;

            cout << "------------------------" << endl;

            current = current->next;
        }
    }

    // Destructor
    ~WaitingList()
    {
        while (front != nullptr)
        {
            WaitingNode* temporary = front;
            front = front->next;
            delete temporary;
        }

        rear = nullptr;
    }
};