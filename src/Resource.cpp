#include "Resource.h"
#include <iostream>

Resource::Resource()
{
    resourceID = "";
    resourceName = "";
    resourceType = "";
    availabilityStatus = "";
}

Resource::Resource(const std::string& id,
                   const std::string& name,
                   const std::string& type,
                   const std::string& status)
{
    resourceID = id;
    resourceName = name;
    resourceType = type;
    availabilityStatus = status;
}

std::string Resource::getResourceID() const
{
    return resourceID;
}

std::string Resource::getResourceName() const
{
    return resourceName;
}

std::string Resource::getResourceType() const
{
    return resourceType;
}

std::string Resource::getAvailabilityStatus() const
{
    return availabilityStatus;
}

void Resource::setAvailabilityStatus(const std::string& status)
{
    availabilityStatus = status;
}

void Resource::display() const
{
    std::cout << "ID: " << resourceID
              << " | Name: " << resourceName
              << " | Type: " << resourceType
              << " | Status: " << availabilityStatus
              << '\n';
}