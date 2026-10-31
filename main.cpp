#include <iostream>
#include "Scheduler.h"

int main() {
    std::cout << "=== Creating Tasks ===" << std::endl;

    ComputeTask t1("Matrix Multiply", 5, Resource("CPU Core"), 1000);
    IOTask t2("Log Write", 3, Resource("Disk"), "output.log");
    NetworkTask t3("API Call", 7, Resource("NIC"), "192.168.1.1", 8080);

    std::cout << "\n=== Moving Tasks into Scheduler ===" << std::endl;
    Scheduler scheduler;
    scheduler.addTask(new ComputeTask(std::move(t1)));
    scheduler.addTask(new IOTask(std::move(t2)));
    scheduler.addTask(new NetworkTask(std::move(t3)));

    std::cout << "\n=== Scheduler Queue ===" << std::endl;
    scheduler.printQueue();

    std::cout << "\n=== Forking Task 0 ===" << std::endl;
    scheduler.fork(0);

    std::cout << "\n=== Queue After Fork ===" << std::endl;
    scheduler.printQueue();

    std::cout << "\n=== Running All Tasks ===" << std::endl;
    scheduler.runAll();

    std::cout << "\n=== Final Queue ===" << std::endl;
    scheduler.printQueue();

    std::cout << "\n=== Cleanup ===" << std::endl;
    // Moved-from local tasks are destroyed here (inactive resources)
    // Scheduler destructor cleans up owned tasks
    return 0;
}
