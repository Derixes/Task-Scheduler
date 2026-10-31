#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

class Resource {
private:
    int id;
    std::string description;
    bool active;
    int* data;          // Simulated memory buffer (models real resource payload)
    size_t dataSize;    // Number of ints in data buffer

    static int nextId;

public:
    // Constructs a new active resource with auto-assigned ID.
    // bufferSize > 0 allocates a simulated data payload of that many ints.
    Resource(const std::string& description, size_t bufferSize = 0);

    // Copy: creates a NEW resource with a new ID (models dup()/clone)
    Resource(const Resource& other);

    // Move: transfers ownership, invalidates source
    Resource(Resource&& other);

    ~Resource();

    // Assignment is not allowed
    Resource& operator=(const Resource&) = delete;
    Resource& operator=(Resource&&) = delete;

    int getId() const;
    std::string getDescription() const;
    bool isActive() const;
    size_t getDataSize() const;

    // Reset the ID counter (for testing)
    static void resetIdCounter();

    friend std::ostream& operator<<(std::ostream& os, const Resource& r);
};

#endif // RESOURCE_H
