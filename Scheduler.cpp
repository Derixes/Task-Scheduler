#include "Scheduler.h"
#include <algorithm>

Scheduler::Scheduler() {
    std::cout << "[Scheduler] Initialized" << std::endl;
}

Scheduler::~Scheduler() {
    std::cout << "[Scheduler] Shutting down (" << tasks.size() << " tasks)" << std::endl;
    for (std::vector<Task*>::size_type i = 0; i < tasks.size(); i++) {
        delete tasks[i];
    }
}

void Scheduler::addTask(Task* task) {
    tasks.push_back(task);
    std::cout << "[Scheduler] Added: " << *task << std::endl;
}

std::string Scheduler::runNext() {
    Task* best = nullptr;
    for (std::vector<Task*>::size_type i = 0; i < tasks.size(); i++) {
        if (!tasks[i]->isCompleted()) {
            if (best == nullptr || tasks[i]->getPriority() > best->getPriority()) {
                best = tasks[i];
            }
        }
    }
    if (best == nullptr) {
        std::string msg = "[Scheduler] No tasks to run";
        std::cout << msg << std::endl;
        return msg;
    }
    std::string result = best->execute();
    best->setCompleted(true);
    std::cout << result << std::endl;
    return result;
}

void Scheduler::runAll() {
    // Collect incomplete task indices, sort by priority descending (stable)
    std::vector<int> indices;
    for (int i = 0; i < (int)tasks.size(); i++) {
        if (!tasks[i]->isCompleted()) {
            indices.push_back(i);
        }
    }
    std::stable_sort(indices.begin(), indices.end(),
        [this](int a, int b) {
            return tasks[a]->getPriority() > tasks[b]->getPriority();
        });

    for (std::vector<int>::size_type i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        std::string result = tasks[idx]->execute();
        tasks[idx]->setCompleted(true);
        std::cout << result << std::endl;
    }
}

int Scheduler::fork(int index) {
    if (index < 0 || index >= (int)tasks.size()) {
        std::cout << "[Scheduler] Fork failed: invalid index " << index << std::endl;
        return -1;
    }
    Task* cloned = tasks[index]->clone();
    tasks.push_back(cloned);
    int newIndex = (int)tasks.size() - 1;
    std::cout << "[Scheduler] Forked: " << *cloned << " (from index " << index << ")" << std::endl;
    return newIndex;
}

void Scheduler::printQueue() const {
    std::cout << "[Scheduler] Queue (" << tasks.size() << " tasks):" << std::endl;
    for (std::vector<Task*>::size_type i = 0; i < tasks.size(); i++) {
        std::cout << "  " << i << ": " << *tasks[i];
        if (tasks[i]->isCompleted()) {
            std::cout << " [DONE]";
        }
        std::cout << std::endl;
    }
}

int Scheduler::size() const {
    return (int)tasks.size();
}

const Task& Scheduler::getTask(int index) const {
    return *tasks[index];
}
