/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H
#include<random>
#include <vector>
using std::ifstream;
using std::string;
using std::vector;
using std::default_random_engine;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!
//
   bool isSmaller(int, Record*, Record*); // this is one I used - you may delete
   void Merge_Sort_Population(int,int);  //Merge sort for name and population to divide the data
   void Merge_Sort_Name(int,int);
   void Merge(int,int,int); //Merge to sort and combine
   void Merge_Name(int,int,int);
   void Randomized_Quicksort_Population(int,int); //Randomized to use any element for sorting
   void Randomized_Quicksort_Name(int,int);
   int Randomized_Partition_population(int,int);
   int Randomized_Partition_name(int,int);
   int Partition_population(int,int);
   int Partition_name(int,int);
   default_random_engine rand; // choose any element from data randomly
 
};

#endif // CSCI_311_CENSUSDATA_H
