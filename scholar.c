//
//  scholar.c
//  P4
//
//  Created by Andrea Donoso on 10/28/21.
//

#include <stdio.h>
#include <stdlib.h>

int solution(long long array[], int numBooks, long long numPages);
void merge(long long array[], int low, int high, int mid);
void mergeSort(long long array[], int low, int high);


int main(void)
{
    int c;
    int n;
    long long L;
    long long *books=NULL;
    int maxNumBooks=0;
    
    // Number of test cases
    scanf("%d", &c);
    
    for(int j=0; j<c; j++)
    {
        // Number of books, max number of pages willing to read
        scanf("%d %lld", &n, &L);
        
        // Dynamically allocating an array for the pages each book holds
        books=(long long*)malloc(n*sizeof(long long));
        
        // Gets the number of pages each book holds
        for(int i=0; i<n; i++)
        {
            scanf("%lld", &books[i]);
            //books[i]=1+rand()%L;
            //printf("%lld\n", books[i]);
        }
        
        // Sorts the number of pages of each book in increasing order
        mergeSort(books, 0, n-1);
        
        // Gets the maximum number of books that can be read without exceeding the page limit
        maxNumBooks=solution(books,n,L);
        
        // Prints the maximum number of different books one can read without going over the maximum page limit.
        printf("%d\n", maxNumBooks);
    }
    
    // Freeing dynamically allocated memory
    free(books);
    
    return 0;
}

// Counts the max number of books one can read without exceeding the page limit
int solution(long long bookPages[], int numBooks, long long numPages)
{
    long long temp=0;
    int totBooks=0;
    
    // Adds up the number of pages of each book from the sorted book page array to temp and increments totBooks everytime a book can be read fully without exceeding the maximum number of pages to be read
    for(int i=0; i<numBooks; i++)
    {
        temp+=bookPages[i];
        totBooks++;
        //printf("%lld ", bookPages[i]);
        
        // If a book being added makes temp exceed the maximum number of pages, we decrement totBooks once and exit the loop
        if(temp>numPages)
        {
            totBooks--;
            break;
        }
    }
    
    // Returns the total number of books capable of being read fully without exceeding the maximum page number
    return totBooks;
    }


void merge(long long array[], int low, int high, int middle)
{
    long long *temp, length;
    
    // Auxiliary array
    length=high-low+1;
    temp=(long long*)calloc(length, sizeof(long long));
    
    int counter1=low;
    int counter2=middle;
    
    int mc=0;
    
    // While we still have items left to copy
    while( counter1<middle || counter2<=high)
    {
        if( counter2>high || (counter1<middle && array[counter1]<array[counter2]))
        {
            temp[mc]=array[counter1];
            counter1++;
            mc++;
        }
        else
        {
            temp[mc]=array[counter2];
            counter2++;
            mc++;
        }
    }
    
    // Copies back the sorted temp array to the original array (from index low to high)
    for(int i=low; i<=high; i++)
        array[i]=temp[i-low];
    
    free(temp);
}

// Recursively splits the array and calls the merge function to sort and merge the array
void mergeSort(long long array[], int low, int high)
{
    int mid;
    
    // While our array is more than 1 element long:
    if(low<high)
    {
        // Splits our array in half
        mid=(high+low)/2;
        
        //Calls to sort the left and right sides of the array
        mergeSort(array, low, mid);
        mergeSort(array, mid+1, high);
        
        // Sorts and merges the array
        merge(array,low,high,mid+1);
    }
}


