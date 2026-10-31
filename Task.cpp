#include "Task.h"
#include <sstream>

// Constructor: initialize name, priority, completed (to false),
// and MOVE the resource parameter into the member variable.
Task::Task(const std::string& name, int priority, Resource resource)
    : name(name), priority(priority), resource(std::move(resource)), completed(false) {
 
    std::cout << "[Task] Created " << name << '\n';
}

// Copy constructor: copy name, priority from other,
// copy the resource (this triggers Resource copy ctor -> new ID),
// and set completed to false.
Task::Task(const Task& other)
    : name(other.name), priority(other.priority), resource(other.resource), completed(false) {

    std::cout << "[Task] Copying " << name << "\n";
}

// Move constructor: move name, resource from other,
// copy priority and completed, then reset other's state.
Task::Task(Task&& other)
    : name(std::move(other.name)), priority(other.priority),
      resource(std::move(other.resource)), completed(other.completed) {

    other.completed = false;
    std::cout << "[Task] Moving " << name << '\n';
}

Task::~Task() {

    std::cout << "[Task] Destroying " << name << '\n';
}

std::string     Task::getName() const          { return name; }
int             Task::getPriority() const      { return priority; }
const Resource& Task::getResource() const      { return resource; }
bool            Task::isCompleted() const      { return completed; }
void            Task::setCompleted(bool c)     { completed = c; }

std::ostream& operator<<(std::ostream& os, const Task& t) {
    os << "[" << t.getType() << "] " << t.name << " (priority " << t.priority << ", " << t.resource << ")";
    return os;
}

// ============================================================
//  ComputeTask
// ============================================================

// Constructor: delegate to Task base, initialize iterations.
ComputeTask::ComputeTask(const std::string& name, int priority, Resource resource, int iterations)
    : Task(name, priority, std::move(resource)), iterations(iterations) {}

// Copy constructor: delegate to Task copy ctor, copy iterations.
ComputeTask::ComputeTask(const ComputeTask& other)
    : Task(other), iterations(other.iterations) {}

// Move constructor: delegate to Task move ctor, copy iterations.
ComputeTask::ComputeTask(ComputeTask&& other)
    : Task(std::move(other)), iterations(other.iterations) {}

ComputeTask::~ComputeTask() {}

// execute(): build and return a string describing the computation.
std::string ComputeTask::execute() {
    std::ostringstream oss;

    oss << "[" << getType() << "] " << name << ": Computing " << iterations << " iterations using " << resource;
    return oss.str();
}

// clone(): return a new deep copy of this object.
Task* ComputeTask::clone() const {
    return new ComputeTask(*this);
}

std::string ComputeTask::getType() const { return "ComputeTask"; }

int ComputeTask::getIterations() const { return iterations; }

// ============================================================
//  IOTask
// ============================================================

IOTask::IOTask(const std::string& name, int priority, Resource resource, const std::string& filename)
    : Task(name, priority, std::move(resource)), filename(filename) {}

IOTask::IOTask(const IOTask& other)
    : Task(other), filename(other.filename) {}

IOTask::IOTask(IOTask&& other)
    : Task(std::move(other)), filename(std::move(other.filename)) {}

IOTask::~IOTask() {}

std::string IOTask::execute(){
    std::ostringstream oss;

    oss << "[IOTask] " << name << ": Processing " << filename << " using " << resource;
    return oss.str(); 
}
Task*       IOTask::clone() const       { return new IOTask(*this); }
std::string IOTask::getType() const     { return "IOTask"; }
std::string IOTask::getFilename() const { return filename; }

// ============================================================
//  NetworkTask
// ============================================================

NetworkTask::NetworkTask(const std::string& name, int priority, Resource resource,
                         const std::string& address, int port)
    : Task(name, priority, std::move(resource)), address(address), port(port) {}

NetworkTask::NetworkTask(const NetworkTask& other)
    : Task(other), address(other.address), port(other.port) {}

NetworkTask::NetworkTask(NetworkTask&& other)
    : Task(std::move(other)), address(std::move(other.address)), port(other.port) {}

NetworkTask::~NetworkTask() {}
std::string NetworkTask::execute() {
    std::ostringstream oss;

    oss << "[NetworkTask] " << name << ": Connecting to " << address << ":" << port << " using " << resource;
    return oss.str(); 
}
Task*       NetworkTask::clone() const   { return new NetworkTask(*this); }
std::string NetworkTask::getType() const { return "NetworkTask"; }
std::string NetworkTask::getAddress() const { return address; }
int         NetworkTask::getPort() const { return port; }
