#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource
{
private:
    std::string resourceID;
    std::string resourceName;
    std::string resourceType;
    std::string availabilityStatus;

public:
    Resource();
    Resource(const std::string& id,
             const std::string& name,
             const std::string& type,
             const std::string& status);

    std::string getResourceID() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    std::string getAvailabilityStatus() const;

    void setAvailabilityStatus(const std::string& status);

    void display() const;
};

#endif