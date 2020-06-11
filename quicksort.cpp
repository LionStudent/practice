#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

/*
void printArray(int arr[]){
    
    int size = sizeof(arr) ;// sizeof(arr[0]);
    for (int i=0; i<size; i+=1){
        arr[i] = rand() % 100+1;
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;   
}
*/

void randomArray(int arr[], int size){
    for (int i=0; i<size; i+=1){
        arr[i] = rand() % 100 + 1;
    }
}

void printArray(int arr[], int size)  
{  
    for (int i = 0; i < size; i++){
        cout << arr[i] << " "; 
    }
    cout << endl;  
} 

void swap( int arr[], int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int n = 10;

int get_pivot(int arr[], int start, int end){
    cout << start << " " << end << endl;
    int pick = arr[end];
    int pivot = start-1;
    for (int i=start; i<end; i++){
        if (arr[i] < pick){
            pivot++;
            swap(arr, i, pivot);
            printArray(arr, n);
        }
    }
    swap(arr, pivot+1, end);
    return pivot+1;
}

void quicksort(int arr[], int start, int end){
    
    if (start < end){
        int pivot = get_pivot(arr, start, end);
        quicksort(arr, start, pivot-1);
        quicksort(arr, pivot+1, end);
    }
}
int main(){
    //int n = 10;
    //int nums[n];
    
    
    int nums[n];
    randomArray(nums, n);
    printArray(nums, n);
    quicksort(nums, 0, n-1);
    cout << "Sorted:" << endl;
    printArray(nums, n);
    
    
    map<string, int> h;
    h["one"] = 1;
    h["two"] = 2;
    h["three"] = 3;
    for (auto x : h){ 
        cout << x.first << ", " << x.second << endl;
    }
    cout << h["three"] << endl;

    list<int> v;
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    
    auto itr = find(v.begin(), v.end(), 5 );
    v.insert(itr, 7);
    
    for (int x : v){ 
        cout << x << endl;
    }
    //cout << v[2] << endl;
    
    return 0;
}




