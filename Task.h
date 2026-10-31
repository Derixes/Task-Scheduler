#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include "Resource.h"

// ============================================================
//  Abstract base class for all tasks.
// ============================================================
class Task {
protected:
    std::string name;
    int priority;
    Resource resource;
    bool completed;

public:
    Task(const std::string& name, int priority, Resource resource);
    Task(const Task& other);
    Task(Task&& other);
    virtual ~Task();

    // Pure virtual: perform the task, return a description of what was done
    virtual std::string execute() = 0;

    // Pure virtual: prototype pattern -- return a deep copy of this task
    virtual Task* clone() const = 0;

    // Pure virtual: return the task type as a string (e.g. "ComputeTask")
    virtual std::string getType() const = 0;

    std::string getName() const;
    int getPriority() const;
    const Resource& getResource() const;
    bool isCompleted() const;
    void setCompleted(bool completed);

    friend std::ostream& operator<<(std::ostream& os, const Task& t);
};

// ============================================================
//  CPU-bound computation task.
// ============================================================
class ComputeTask : public Task {
private:
    int iterations;

public:
    ComputeTask(const std::string& name, int priority, Resource resource, int iterations);
    ComputeTask(const ComputeTask& other);
    ComputeTask(ComputeTask&& other);
    ~ComputeTask() override;

    std::string execute() override;
    Task* clone() const override;
    std::string getType() const override;

    int getIterations() const;
};

// ============================================================
//  I/O-bound task (file read/write).
// ============================================================
class IOTask : public Task {
private:
    std::string filename;

public:
    IOTask(const std::string& name, int priority, Resource resource, const std::string& filename);
    IOTask(const IOTask& other);
    IOTask(IOTask&& other);
    ~IOTask() override;

    std::string execute() override;
    Task* clone() const override;
    std::string getType() const override;

    std::string getFilename() const;
};

// ============================================================
//  Network-bound task.
// ============================================================
class NetworkTask : public Task {
private:
    std::string address;
    int port;

public:
    NetworkTask(const std::string& name, int priority, Resource resource,
                const std::string& address, int port);
    NetworkTask(const NetworkTask& other);
    NetworkTask(NetworkTask&& other);
    ~NetworkTask() override;

    std::string execute() override;
    Task* clone() const override;
    std::string getType() const override;

    std::string getAddress() const;
    int getPort() const;
};

#endif // TASK_H
