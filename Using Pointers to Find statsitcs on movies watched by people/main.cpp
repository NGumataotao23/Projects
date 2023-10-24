// The program written allows a user to find the median of movies watched by an inputted amount of students
// Writer: Nathan Gumataotao
// Date: 3/12/2023
// Completed
#include <iostream>

using namespace std;
    //initialize all functions
double median(int*, int);
int mode(int*, int);
int *makeArray(int);
void getMovieData(int*, int );
void selectionSort(int[], int);
double average(int*, int);
int main()
{
    //pointer used to track specific data point in array
    int *movieData;
    int num;
    int mov;
    //asks how many students to input
    cout << "How many Students were surveyed? ";
    cin >> num;
    movieData = makeArray(num);
    getMovieData(movieData, num);
    selectionSort(movieData, num);

    //asks questions to send to each individual function
    //also assigns a pointer to each array elements
    cout << "The average number of movies seen is ";
    cout << average(movieData, num)<<endl;
    cout << "The median of the number of movies seen is: ";
    cout << median(movieData, num)<<endl;
    cout << "The mode of the number of movies seen is: ";

    //checks to see if the mode is present or not
    mov = mode(movieData,num );
    if (mov == -1)
        cout << "The set has no Mode" << endl;
    else
        cout << "The mode is " << mov <<endl;

    delete[] movieData;
    movieData = 0;

    return 0;

}
//creates the array
int *makeArray(int siZe){
    int *ptr;
    ptr = new int[siZe];

    return ptr;
}
//tracks the number of movies each student saw
void getMovieData(int arr[], int num){

    cout << "Enter the number of movies each student saw" << endl;
    for(int counT = 0; counT < num; counT++){
        cout << "Student " <<(counT + 1) << ": ";
        cin >> arr[counT];
    }
}
//sorts the students in order to more easily find the median
void selectionSort(int value[], int sizE){
    int startScan, minIndex, minValue;

    for(startScan = 0; startScan < (sizE - 1); startScan++){
        minIndex = startScan;
        minValue = value[startScan];
        for(int index = startScan + 1; index < sizE; index++){
            if(value[index] < minValue){
                minValue = value[index];
                minIndex = index;
            }
        }
        value[minIndex] = value[startScan];
        value[startScan] = minValue;
    }
}
//finds the median of all the numbers inputted to the array
double median(int* arr, int num){
    double med;

    if(num % 2 == 0){
        int mid1 = num /2;
        int mid2 = (num/2) - 1;
        med = ((*(arr+mid1)+*(arr + mid2)) / 2.0);

    }
    else
        med = *(arr + (num/2));
    return med;

}
//calculates the mode of the array
int mode(int *arr, int num){
    int *freq, highest, elem, counT;

    freq = makeArray(num);

    for(counT = 0; counT < num; counT++){
        freq[counT] =0;
    }
    for(int count1 = 0; count1 < num; count1++){
        for(int count2 = 0; count2 < num; count2++){
            if(*(arr +count2) == *(arr +count1))
                (*(freq +count1))++;
        }
    }
    highest = *freq;
    elem = 0;

    for(counT = 1; counT < num; counT++){
        if(*(freq + counT) > highest){
            highest + *(freq +counT);
            elem = counT;
        }
    }
    if(highest ==1)
        return -1;
    else
        return *(arr+elem);
}
//uses the array to calculate the average of movies watched
double average(int arr[], int num){

    int total = 0;
    double ave;

    for (int counT = 0; counT < num; counT++){
        total += arr[counT];
    }
    ave = total / static_cast<double>(num);

    return ave;
}
