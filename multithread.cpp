#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <chrono>
#include <mutex>

int exitFlag = 0;
std::mutex queueMutex;
std::mutex consoleMutex;

void doWork(std::string name, std::vector<std::string> &tasks){
    while (!exitFlag){
        // get a task off the "queue"
        std::vector<std::string> myTasks;
        {
            std::lock_guard<std::mutex> lk(queueMutex);
            if (!tasks.empty()){
                std::string task = tasks.front();
                tasks.erase(tasks.begin());
                myTasks.push_back(task);
            }
        }
        // process my long running task
        for (std::string& task : myTasks){
            {
                std::lock_guard<std::mutex> lk(consoleMutex);
                std::cout << name << " is working on task: " << task << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main(){
    int numThreads = 3;
    std::string threadList[numThreads] = {"Thread-1", "Thread-2", "Thread-3"};
    
    int numNames = 5;
    std::string nameList[numNames] = {"One", "Two", "Three", "Four", "Five"};
    
    std::vector<std::thread> threads;
    std::vector<std::string> tasks;
    
    // Create new threads
    for (int i=0; i<numThreads; i++){
        std::string currName = threadList[i];
        threads.emplace_back(doWork, currName, std::ref(tasks));
    }

    // Fill the queue
    {
        std::lock_guard<std::mutex> queueLock(queueMutex); //lock queue
        for (int i=0; i<numNames; i++){
            std::string currString = nameList[i];
            tasks.push_back(currString);
        }
    } // release queue
    
     
    // Wait for queue to empty
    while (!tasks.empty()){}
    
    // Notify threads it's time to exit
    exitFlag = 1;
 
    // Wait for all threads to complete
    for (std::thread& thread : threads){
        thread.join();
    }
    std::cout <<  "Exiting Main Thread" << std::endl;
}