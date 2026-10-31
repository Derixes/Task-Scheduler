#include "Resource.h"
#include <cstring>

int Resource::nextId = 1;

Resource::Resource(const std::string& description, size_t bufferSize)
    : id(nextId++), description(description), active(true),
      data(nullptr), dataSize(bufferSize) {
    if (dataSize > 0) {
        data = new int[dataSize];
        std::memset(data, 0xAB, dataSize * sizeof(int));
    }
    std::cout << "[Resource] Created #" << id << " (" << description << ")" << std::endl;
}

Resource::Resource(const Resource& other)
    : id(nextId++), description(other.description), active(true),
      data(nullptr), dataSize(other.dataSize) {
    if (dataSize > 0) {
        data = new int[dataSize];
        std::memcpy(data, other.data, dataSize * sizeof(int));
    }
    std::cout << "[Resource] Copied #" << other.id << " -> #" << id << std::endl;
}

Resource::Resource(Resource&& other)
    : id(other.id), description(std::move(other.description)), active(true),
      data(other.data), dataSize(other.dataSize) {
    other.data = nullptr;
    other.dataSize = 0;
    other.active = false;
    other.id = -1;
    std::cout << "[Resource] Moved #" << id << std::endl;
}

Resource::~Resource() {
    delete[] data;
    if (active) {
        std::cout << "[Resource] Destroyed #" << id << std::endl;
    }
}

int Resource::getId() const { return id; }
std::string Resource::getDescription() const { return description; }
bool Resource::isActive() const { return active; }
size_t Resource::getDataSize() const { return dataSize; }

void Resource::resetIdCounter() { nextId = 1; }

std::ostream& operator<<(std::ostream& os, const Resource& r) {
    if (r.active) {
        os << "Resource #" << r.id << " (" << r.description << ")";
    } else {
        os << "Resource [INACTIVE]";
    }
    return os;
}
