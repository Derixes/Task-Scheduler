#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <iostream>
#include "Task.h"

// ============================================================
//  Scheduler: manages a queue of tasks, executes them
//  polymorphically in priority order.
// ============================================================
class Scheduler {
private:
    std::vector<Task*> tasks;

public:
    Scheduler();
    ~Scheduler();

    // No copying schedulers
    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;

    // Takes ownership of a dynamically-allocated task
    void addTask(Task* task);

    // Executes the highest-priority incomplete task
    std::string runNext();

    // Executes all incomplete tasks in priority order (stable, descending)
    void runAll();

    // Clones task at index, adds clone to queue. Returns new index, or -1 on failure.
    int fork(int index);

    // Prints the current queue
    void printQueue() const;

    // Returns number of tasks in queue
    int size() const;

    // Access a task by index (const)
    const Task& getTask(int index) const;
};

#endif // SCHEDULER_H
