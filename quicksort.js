console.log("hello wolrd");

let n = 10;

function getRandom(l){
    for (let i=0; i<n; i++){
        let rand = Math.floor(Math.random() * 100 + 1);
        l.push(rand);
    }
}

function swap(arr, a,b){
    //console.log("swap(): "+arr + " "+ a + " " + b );

    let tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

function getPivot(arr, begin, end){
    
    let pivot = arr[end];
    let lastIndexOfSmallerNum = begin-1; // out of range at start
    for (let i=begin; i<end; i++){
        if (arr[i] < pivot){
            lastIndexOfSmallerNum++;
            swap(arr, i, lastIndexOfSmallerNum);
        }
    }
    // handle the pivot value; which out of range of hte for-loop
    swap(arr, lastIndexOfSmallerNum+1, end);
    return lastIndexOfSmallerNum+1;
}

function quicksort(arr, begin, end, level){
    //console.log(arr + " "+ begin + " " + end + " " + level );
    //if (level > 2) throw "quit!";

    if (begin < end){
        level++;
        let pivot = getPivot(arr, begin, end);
        quicksort(arr, begin, pivot-1, level);
        quicksort(arr, pivot+1, end, level);
    }
}

let l = [];

getRandom(l);
console.log(l);

quicksort(l, 0, n-1, 1);
console.log(l);