/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 *  
 * Algorithms for insertion,merge and quick sort are referred from cormen
 * implemented by kshitija karkar.
 * Implementation of default random engine referred from 
 * http://www.codeproject.com
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<random>
#include<chrono>
#include "CensusData.h"

using namespace std;
// formal parameter name commented out to avoid unused variable warning
/**************************************************************************
Insertion Sort: Sorts the data according to insertion sort algorithm by 
value of key. 
IN: type to check whether to sort by population or name
OUT:N.A
**************************************************************************/
void CensusData::insertionSort(int type) {
   Record *key;
   int j,i;
   if(type==POPULATION) //to sort by population
   {
     for(j=1;j<(signed)data.size();j++) 
     {
	key=data[j];
	i=j-1;
	while(i>=0 && data[i]->population>=key->population)
	{
	  data[i+1]=data[i];  //swap data if element is greater than key.
	  i=i-1;
	}
	data[i+1]=key;
     }
   }
   else //to sort by name
   {
     for(j=1;j<(signed)data.size();j++)
     {
	key=data[j];
	i=j-1;
	while(i>=0 && (*(data[i]->city)>=*(key->city))) //compare city names
	{
	   data[i+1]=data[i];
	   i=i-1;
	}
	data[i+1]=key;
     }
   }
}

// formal parameter name commented out to avoid unused variable warning
/**************************************************************************
Merge Sort: Sorts data according to merge sort algorithm by comparing 2
vectors (or data sets).
IN: type to check whether to sort by population or name
OUT:N.A
**************************************************************************/
void CensusData::mergeSort(int type) {

   int p=0;
   int r=(signed)data.size()-1;	
   if(type==POPULATION)
   {		
     Merge_Sort_Population(p,r); //call to sort by population function
   }
   else
   {
     Merge_Sort_Name(p,r); //call to sort by name function
   }
}

/****************************************************************************
Recursive calls of Merge Sort
IN:p and r that is start and end of vector
OUT:N.A
****************************************************************************/
void CensusData::Merge_Sort_Population(int p,int r)
{
   int q;
   if(p<r)
   {
     q=(p+r)/2;
     Merge_Sort_Population(p,q);
     Merge_Sort_Population(q+1,r);//after every 2 calls to merge sort
     Merge(p,q,r); //there is one call to merge
   }
}
/***************************************************************************
Recursive calls to merge sort by name
IN:p and r that is start and end of vector
OUT:N.A
****************************************************************************/
void CensusData::Merge_Sort_Name(int p,int r)
{
   int q;
   if(p<r)
   {
     q=(p+r)/2;
     Merge_Sort_Name(p,q);
     Merge_Sort_Name(q+1,r);
     Merge_Name(p,q,r);
   }
}

/**************************************************************************
Merge by Population to combine data
IN:p and r that is start and end of vector, q to divide the vector
OUT:N.A
**************************************************************************/
void CensusData::Merge(int p,int q,int r)
{
   int n1=q-p+1;
   int n2=r-q;
   int i,j,k;
   vector <Record*>left;
   vector <Record *>right;
   for(i=0;i<n1;i++)
   {
     left.push_back(data[p+i]); //enter data in left vector
   }	
   for(j=0;j<n2;j++)
   {
     right.push_back(data[q+j+1]);  //enter data in right vector
   }
   i=0;
   j=0;
   for(k=p;k<=r;k++)
   {
     if(left[i]->population<=right[j]->population)  
     {
       data[k]=left[i];
       i=i+1;
     }
     else //whichever element has less value will be inserted in data 
     {
       data[k]=right[j];
       j=j+1;
     }
     if(i==(signed)left.size()&&j!=(signed)right.size())
     {
       while(j!=(signed)right.size()) //right vector is still there
       {			
	  k=k+1;			
	  data[k]=right[j]; //insert all elements from right in data vector
	  j=j+1;
	}
      }	
      if(j==(signed)right.size()&&i!=(signed)left.size()) //check for left 
      {
	 while(i!=(signed)left.size())			
	 {
	   k=k+1;			
	   data[k]=left[i]; //insert all elements from left
	   i=i+1;
	 }		
      }
   }
}

/*******************************************************************************
Merge_Name() to combine data depending on name
IN:p and r that is start and end of vector
OUT:N.A
*******************************************************************************/
void CensusData::Merge_Name(int p,int q,int r)
{
   int n1=q-p+1;
   int n2=r-q;
   int i,j,k;
   vector <Record*>left;
   vector <Record *>right;
   for(i=0;i<n1;i++)
   {
     left.push_back(data[p+i]);
   }	
   for(j=0;j<n2;j++)
   {
     right.push_back(data[q+j+1]);
   }
   i=0; //initialise i,j
   j=0;
   for(k=p;k<=r;k++)
   {
     if((*(left[i]->city)<=*(right[j]->city)))
     {
	data[k]=left[i]; //data in left is less
	i=i+1;
     }
     else
     {
	data[k]=right[j];
	j=j+1;
     }		
     if(i==(signed)left.size()&&j!=(signed)right.size())
     {
	while(j!=(signed)right.size())
	{			
	  k=k+1;			
	  data[k]=right[j];
	  j=j+1;
	}
     }	
     if(j==(signed)right.size()&&i!=(signed)left.size())
     {
	while(i!=(signed)left.size())			
	{
	  k=k+1;			
	  data[k]=left[i];
	  i=i+1;
	}		
     }
  }
}


// formal parameter name commented out to avoid unused variable warning
/*****************************************************************************
Quick sort: sorts according to quick sort algorithm by dividing the vector 
according to pivot
IN: type to check whether sort by population or name
OUT:N.A
******************************************************************************/
void CensusData::quickSort(int type) {
	int p=0;
	int r=data.size()-1;
	random_device rnd;    //generates random number
	rand.seed(rnd());     //for unique number every time
	if(type==POPULATION)
		Randomized_Quicksort_Population(p,r);
	else
		Randomized_Quicksort_Name(p,r);

}

/*****************************************************************
Recursive calls to Quicksort
IN: p and r that is start and end of vector
OUT: N.A
*****************************************************************/
void CensusData::Randomized_Quicksort_Population(int p,int r)
{
   int q;
   if(p<r)
   {
     q=Randomized_Partition_population(p,r);
     Randomized_Quicksort_Population(p,q-1);
     Randomized_Quicksort_Population(q+1,r);
   }
}

/*******************************************************************
select any element and swap with last element
IN:p and r that is start and end of vector
OUT : call to partition passing p and r
*******************************************************************/
int CensusData::Randomized_Partition_population(int p,int r)
{
   Record *y;
   int i;
   uniform_int_distribution<int> uni(p,r); //range to generate index	
   i=uni(rand);   //generates index from the data vectore
   y=data[i];     //exchange that element with last element and make it pivot 
   data[i]=data[r];
   data[r]=y;
   return Partition_population(p,r);
}

/*********************************************************************
Partition() to carry out swapping
IN:p and r that is start and end of vector
OUT: value for q
**********************************************************************/
int CensusData::Partition_population(int p,int r)
{
   Record *x,*y;
   x=data[r]; //set pivot
   int i=p-1;
   int j;
   for(j=p;j<=r-1;j++)
   {
     if(data[j]->population<=x->population) //compare for swapping
     {
	i=i+1;
	y=data[i];
	data[i]=data[j];
	data[j]=y;
     }
   }
   y=data[i+1];
   data[i+1]=data[r];
   data[r]=y;
   return i+1;
}
/*************************************************************************
Quicksort to sort by name
IN:p and r that is start and end of vector
OUT:N.A.
*************************************************************************/
void CensusData::Randomized_Quicksort_Name(int p,int r)
{
   int q;
   if(p<r)
   {
     q=Randomized_Partition_name(p,r);
     Randomized_Quicksort_Name(p,q-1);
     Randomized_Quicksort_Name(q+1,r);
   }
}

/*************************************************************************
To select any element as pivot 
IN:p and r that is start and end of vector
OUT : call to partition passing p and r
*************************************************************************/
int CensusData::Randomized_Partition_name(int p,int r)
{
   Record *y;
   int i;
   uniform_int_distribution<int> uni(p,r);	
   i=uni(rand);
   y=data[i];
   data[i]=data[r];
   data[r]=y;
   return Partition_name(p,r);
}

/**************************************************************
Partition() to sort according to name
IN:p and r that is start and end of vector
OUT : value to q
***************************************************************/
int CensusData::Partition_name(int p,int r)
{
   Record *x,*y;
   x=data[r];
   int i=p-1;
   int j;
   for(j=p;j<=r-1;j++)
   {
     if(*data[j]->city<=*x->city)
     {
	i=i+1;
	y=data[i];
	data[i]=data[j];
	data[j]=y;
      }
   }
   y=data[i+1];
   data[i+1]=data[r];
   data[r]=y;
   return i+1;
}

