#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <chrono>
#include <mutex>

int exitFlag = 0;
std::mutex queueMutex;
std::mutex consoleMutex;

void doWork(int threadID, std::string name, std::queue<std::string> &q){
    while (!exitFlag){
        std::string data = "";
        {
            std::lock_guard<std::mutex> lockMutex(queueMutex);
            if (!q.empty()){
                data = q.front();
                q.pop();
            }
        }
        if (data.compare("") != 0){
            {                   
                std::lock_guard<std::mutex> consoleLock(consoleMutex); // lock the console
                std::cout << "name: " << name << " data: " << data << std::endl;
            } // relesse the console
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
    std::queue<std::string> workQueue;
    
    for (int i=0; i<numThreads; i++){
        std::string currName = threadList[i];
        int threadID = i+1;
        threads.emplace_back(doWork, threadID, currName, std::ref(workQueue));
    }

    {
        std::lock_guard<std::mutex> queueLock(queueMutex); //lock queue
        for (int i=0; i<numNames; i++){
            std::string currString = nameList[i];
            workQueue.push(currString);
        }
    } // release queue
       
    while (!workQueue.empty()){}
    exitFlag = 1;
 
    //for (auto& thread : threads){
    for (std::thread& thread : threads){
        thread.join();
    }
    
    std::cout <<  "Exiting Main Thread" << std::endl;
}