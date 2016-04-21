#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>

using namespace std;

void read_files (vector <int> &v); //reads files, numbers added to 4 vectors (according to filenames)

//all 5 sorting methods, will have access to vectors containing ints from txt files and ints to cout total
//number of comparisons and exchanges, return 1 when complete w sorting
int BubbleSort (vector <int> &v);
int InsertionSort (vector <int> &v);
int QuickSort (vector <int> &v, int left, int right, int c, int e);
void swapp (int x, int y); //for use in quicksort
int part (vector <int> &v, int left, int right, int pIndex, int c, int e);//quicksort
int ShellSort (vector <int> &v);
int MergeSort (vector <int> &v, int low, int high, int c, int e);
void merg (vector <int> &v, int low, int high, int mid, int c, int e); //mergesort purposes

void vectoroutput(vector <int> &test); //debugging purposes, outputs contents of vectors (after sorting)

int main()
{
    //4 int vectors will contain numbers in all 4 diff txt files, vectors named appropriately (according to filename)
    vector <int> few_unique_vector;
    vector <int> nearly_sorted_vector;
    vector <int> random_vector;
    vector <int> reversed_vector;
    int answer; //will allow user to choose which sorting method to use to sort data within 4 vectors (further below in main)
    int left, right; //quicksort purposes, mark where you are in pivot
    int low, high; //mergesort purposes, mark pos in array (vector)
    int c, e; //comparisons and exchanges, use in quicksort and mergesort
    cout << "Begin entering names of files in this order (along w/ txt extensions): FewUnique; NearlySorted; Random; Reversed. \n";
    //let user know to enter filenames in specific order  (so appropriate vectors are filled in)

    //begin reading txt files w ints and insert them into appropriate vectors
    read_files(few_unique_vector); read_files(nearly_sorted_vector); read_files(random_vector); read_files(reversed_vector);

    //debugging purposes
    cout << "Size of vectors: \n";
    cout << "few unique: " << few_unique_vector.size() << endl;
    cout << "nearly_sorted: " << nearly_sorted_vector.size() << endl;
    cout << "random: " << random_vector.size() << endl;
    cout << "reversed: " << reversed_vector.size() << endl;

    cout << "Which sorting method would you like to choose? \n";
    cout << "Type 1 for Bubble; Type 2 for Insertion; Type 3 for Quick; Type 4 for Shell; Type 5 for Merge. \n";
    cin >> answer;

    if (answer==1)
    {
        cout << "Results for few unique: \n";
        BubbleSort(few_unique_vector);
        cout << "Results for nearly sorted \n";
        BubbleSort(nearly_sorted_vector);
        cout << "Results for random: \n";
        BubbleSort(random_vector);
        cout << "Results for reversed: \n";
        BubbleSort(reversed_vector);
    }
    else if (answer==2)
    {
        cout << "Results for few unique \n";
        InsertionSort(few_unique_vector);
        cout << "Results for nearly sorted: \n";
        InsertionSort(nearly_sorted_vector);
        cout << "Results for random: \n";
        InsertionSort(random_vector);
        cout << "Results for reversed: \n";
        InsertionSort(reversed_vector);
    }
    else if (answer==3) //init all c and e to 0 to allow another iteration of function for each vector
    {
        cout << "Results for few unique: \n";
        QuickSort(few_unique_vector, left, right, c, e); c=e=0;
        cout << "Results for nearly sorted: \n";
        QuickSort(nearly_sorted_vector, left, right, c, e); c=e=0;
        cout << "Results for random: \n";
        QuickSort(random_vector, left, right, c, e); c=e=0;
        cout << "Results for reversed: \n";
        QuickSort(reversed_vector, left, right, c, e); c=e=0;
    }
    else if (answer==4)
    {
        cout << "Results for few unique: \n";
        ShellSort(few_unique_vector);
        cout << "Results for nearly sorted: \n";
        ShellSort(nearly_sorted_vector);
        cout << "Results for random: \n";
        ShellSort(random_vector);
        cout << "Results for reversed: \n";
        ShellSort(reversed_vector);

    }
    else if (answer==5) //c=e=0 similar to quicksort (reset values for new iteration for each vector), after cout-ing the results
    {
        cout << "Results for few unique: \n";
        MergeSort(few_unique_vector, low, high, c, e); c=e=0;
        cout << "Results for nearly sorted: \n";
        MergeSort(nearly_sorted_vector, low, high, c, e); c=e=0;
        cout << "Results for random: \n";
        MergeSort(random_vector, low, high, c, e); c=e=0;
        cout << "Results for reversed: \n";
        MergeSort(reversed_vector, low, high, c, e); c=e=0;
    }
    else {
        cout << "Error, please enter a valid answer \n";
        cin >> answer;
    }

    /*cout << endl << endl << "Done with sorting! Outputting the vectors! \n";
    cout << "few unique: \n"; vectoroutput(few_unique_vector); cout << endl << endl;
    cout << "nearly sorted: \n"; vectoroutput(nearly_sorted_vector); cout << endl << endl;
    cout << "random: \n"; vectoroutput(random_vector); cout << endl << endl;
    cout << "reversed \n"; vectoroutput(reversed_vector); cout << endl << endl;
    */

    return 0;
}

void read_files(vector <int> &v)
{
    ifstream in; //input filestream to read file
    char * filename = new char [10]; //user input to type name of file with .txt extension
    cout << "Please enter the name of the file: ";
    cin >> filename;
    in.open(filename); //read from file name as provided by user
    if (!in.is_open()){ //when the file cannot be opened, show error msg and give user another chance until the right filename is typed
        cout << "Error, please type another file. \n";
        cin >> filename;
    }

    char * num = new char [100]; //char array to store the integers as they are read
    while (in.peek()!=EOF){
        in.getline(num,100,' '); //ints will be put in char array with the delineator being a space
        v.push_back(atoi(num));
    }
    in.clear();
    in.close();
    cout << "Vector has been filled out according to contents in " << filename << endl << endl;
}

int BubbleSort (vector <int> &v)
{
    int i, j, temp, comparisons, exchanges;
    for (i=1;i<v.size();i++){
        for (j=0;j<v.size()-i;j++) {
            if (v[j]>v[j+1]) { //begin comparisons
                temp = v[j];
                v[j] = v[j+1];
                v[j+1]=temp;
                exchanges++;
                comparisons++;//both exch and comp increase by 1
            }
            else
                comparisons+=1; //when no change is made, comparison will only increase
        }
    }
    cout << "Total number of comparisons: " << comparisons << endl; //total # of comparisons
    cout << "Total number of exchanges: " << exchanges << endl << endl; //total # of exchanges
    return 1;
}

int InsertionSort (vector <int> &v)
{
    int i, j, element, comparisons, exchanges;
    for (i=1;i<v.size();i++) {
        element = v[i];
        j=i; //begin parallel comparisons
        while ((j<0) && (v[j-1]>element))
        {
            v[j] = v[j-1];
            j = j-1;
            comparisons++;
        }
        v[j] = element;
        comparisons++;
        exchanges++;
    }
    cout << "Total number of comparisons: " << comparisons << endl; //total # of comparisons
    cout << "Total number of exchanges: " << exchanges << endl << endl; //total # of exchanges
    return 1;
}

int QuickSort (vector <int> &v, int left, int right, int c, int e)
{
    right = v.size();
    if (left < right)
    {
        int pivot = (left+right)/2; //begin pivot @ middle of vector
        int pivotNew = part(v, left, right, pivot, c, e); //new pivot created according to partition made
        QuickSort(v, left, pivotNew - 1, c, e); //recursive property, right changes, c and e are updated
        QuickSort(v, pivotNew + 1, right, c, e); //left changes, right stays the same, c and e are updated
    }
    cout << "Total number of comparisons: " << c << endl; //total # comparisons done in sorting
    cout << "Total number of exchanges: " << e << endl << endl;//total # of exchanges done in sorting
    return 1;
}

void swapp (int x, int y) //for use in quicksort to swap numbers, use pointers to signal where values are located
{
    int temp; //used as a placeholder for value in first index to be put in second index
    temp = x;
    x = y;
    y = temp;
}

int part (vector <int> &v, int left, int right, int pIndex, int c, int e)//quicksort
{
    int p = v[pIndex]; //pIndex = index of pivot
    do
    {
        while (v[left] < p) {
            left++;
            c++; //comparisons increases
        }
        while (v[right] > p) {
            right--;
            c++; //comparisons increases
        }
        if (left < right && v[left] != v[right])
        {
            swapp(v[left], v[right]);
            e++; //exchanges increases after a swap
        }
        else
        {
            return right;
        }
    }
    while (left < right);

    return right;
}

int ShellSort (vector <int> &v)
{
    int comparisons, exchanges, temp, gap, i, swapped, n;
    n = v.size();
    gap = n/2;
    do
    {
        do
        {
            swapped = 0;
            for (i=0;i<n-gap;i++)
            {
                if (v[i] > v[i+gap]) //exchanges made
                {
                    temp = v[i];
                    v[i] = v[i+gap];
                    v[i+gap] = temp;
                    swapped = 1;
                    exchanges++; //exchanges and comparisons increment
                    comparisons++;
                }
                else
                    comparisons++; //if no swap is made, only a comparison is made, increment by 1
            }
        } while (swapped==1);
    } while ((gap=gap/2)>=1);
    cout << "Total number of comparisons: " << comparisons << endl; //total # of comparisons
    cout << "Total number of exchanges: " << exchanges << endl << endl; //total # of exchanges
    return 1;

}

int MergeSort (vector <int> &v, int low, int high, int c, int e)
{
    int mid;
    high = v.size();
    if (low<high)
    {
        mid = (low+high)/2; //index of mid will be in middle of vector
        MergeSort(v, low, mid, c, e);//recursive function
        MergeSort(v, mid+1, high, c, e); //repeated twice to allow BOTH halves to be sorted
        merg(v, low, high, mid, c, e); //merge halves, v now sorted
    }
    cout << "Total number of comparisons: " << c << endl; //total # of comparisons
    cout << "Total number of exchanges: " << e << endl << endl; //total # of exchanges
    return 1;
}

void merg (vector <int> &v, int low, int high, int mid, int c, int e)
{

    int i, j, k; //position of index for diff arrays used (3 total - 2 theoretical, 1 temporary C)
    int C [10000]; //third array (to replace contents of v at the end)
    i = low;
    j = mid+1;
    k=0;
    while ((i<=mid) && (j<=high))
    { //allow 2 arrays v(i) and v(j) (differ in index according to values of i and j) to be merged with temp array C
        //two arrays are really just v but starting at diff indexes according to mid established
        if (v[i] < v[j]){
            C[k] = v[i++];
            e++;
        }
        else {
            C[k] = v[j++];
            e++;
        }
        k++; c++;
    }

    while (i<=mid)
        C[k++] = v[i++];
    while (j<=high)
        C[k++]=v[j++];
    for (i=low, j=0; i<=high; i++, j++) //begin copying C into v, replacing values and allowing the sorted values to be correctly entered
    {
        v[i]=C[j];
    }
}

void vectoroutput (vector <int> &test) //debugging purposes, output contests of SORTED vectors (depending on sorting algorithm chosen)
{
    int i;
    for (i=0;i<test.size()-1;i++)
        cout << test[i] << " "; //ints are separated by spaces
    cout << test[i] << endl; //final int is cout-ed
    cout << "Done with output for this vector \n";
}
