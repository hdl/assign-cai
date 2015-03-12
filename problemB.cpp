#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

#define MAX 100
using namespace std;

typedef struct{
    string first_name;
    string last_name;
    double scores[5];
    double average;
}entry;

int read_line(fstream &input, entry * one_entry);
int computeAverages(entry all_data[], int counter, entry *all_average);
void print_all(entry all_data[], int counter);
void write_file(ofstream &output, entry all_data[], int total);

void sort_by_grade(entry all_data[], entry new_data[], int counter);
void mergesort_grade(entry all_data[], int iBegin, int iEnd, entry new_data[]);
void merge_grade(entry all_data[], int iBegin, int iMiddle, int iEnd, entry new_data[]);

void sort_by_name(entry all_data[], entry new_data[], int counter);
void mergesort_name(entry all_data[], int iBegin, int iEnd, entry new_data[]);
void merge_name(entry all_data[], int iBegin, int iMiddle, int iEnd, entry new_data[]);



int main(){

    fstream input("Grades.dat");
    ofstream output("FinalGrades.dat");

    entry all_data[MAX];
    entry all_average;
    int counter=0;

    while(!input.eof()){
        if(read_line(input, &all_data[counter]))
            counter++;
    }

    computeAverages(all_data, counter, &all_average);

    //print_all(all_data, counter);
    //print_all(&all_average, 1);

    write_file(output, all_data, counter);
    for(int i=0; i<5; i++)
        output << all_average.scores[i]<<" ";
    output << all_average.average<<endl;
    input.close();
    output.close();


    // begin cout sort data
    string choice;

    entry *new_data = new entry[counter];
    while(1){
        cout << "Would you like to sort the results by last name or final grade (enter n or g)?:"<<endl;
        cin >> choice;

        if(choice == "g"){
            sort_by_grade(all_data, new_data, counter);
            print_all(new_data, counter);
        }
        else if(choice =="n"){
            sort_by_name(all_data, new_data, counter);
            print_all(new_data, counter);
        }
        else
            return 0;
    }

    return 0;

}


void sort_by_grade(entry all_data[], entry new_data[], int counter)
{
    mergesort_grade(all_data, 0, counter, new_data);
}

void mergesort_grade(entry all_data[], int iBegin, int iEnd, entry new_data[])
{
    if(iEnd - iBegin < 2){
        //cout << "base, finish " << iBegin << " to " << iEnd-1<<endl;
        return;
    }
    int iMiddle = (iEnd + iBegin)/2;
    mergesort_grade(all_data, iBegin, iMiddle, new_data);
    mergesort_grade(all_data, iMiddle, iEnd, new_data);
    merge_grade(all_data, iBegin, iMiddle, iEnd, new_data);

    //cout << "merge " << iBegin << " to " << iEnd-1<<endl;
}

void merge_grade(entry all_data[], int iBegin, int iMiddle, int iEnd, entry new_data[])
{
    int i0= iBegin, i1=iMiddle;

    //while thre are elements in the left or right
    for(int j = iBegin; j<iEnd; j++){
        if (i0 < iMiddle && (i1 >= iEnd || all_data[i0].average >= all_data[i1].average)){
            new_data[j] = all_data[i0];
            i0 = i0 + 1;
        }
        else{
            new_data[j] = all_data[i1];
            i1 = i1 + 1;
        }
    }

    for(int k=iBegin; k<iEnd; k++)
        all_data[k]=new_data[k];
}

//-----------------------------
void sort_by_name(entry all_data[], entry new_data[], int counter)
{
    mergesort_name(all_data, 0, counter, new_data);
}

void mergesort_name(entry all_data[], int iBegin, int iEnd, entry new_data[])
{
    if(iEnd - iBegin < 2){
        //cout << "base, finish " << iBegin << " to " << iEnd-1<<endl;
        return;
    }
    int iMiddle = (iEnd + iBegin)/2;
    mergesort_name(all_data, iBegin, iMiddle, new_data);
    mergesort_name(all_data, iMiddle, iEnd, new_data);
    merge_name(all_data, iBegin, iMiddle, iEnd, new_data);

    //cout << "merge " << iBegin << " to " << iEnd-1<<endl;
}

void merge_name(entry all_data[], int iBegin, int iMiddle, int iEnd, entry new_data[])
{
    int i0= iBegin, i1=iMiddle;

    //while thre are elements in the left or right
    for(int j = iBegin; j<iEnd; j++){
        if (i0 < iMiddle && (i1 >= iEnd || all_data[i0].last_name <= all_data[i1].last_name)){
            new_data[j] = all_data[i0];
            i0 = i0 + 1;
        }
        else{
            new_data[j] = all_data[i1];
            i1 = i1 + 1;
        }
    }

    for(int k=iBegin; k<iEnd; k++)
        all_data[k]=new_data[k];
}

// get the data from the input file that has a file stream as at least one of its arguments
int read_line(fstream &input, entry * one_entry){

    input >> one_entry->last_name;
    if(input.eof()) return 0;
    input >> one_entry->first_name;
    if(input.eof()) return 0;
    for(int i=0; i<5; i++){
        input >> one_entry->scores[i];
        if(input.eof()) return 0;

    }

    return 1;
}


int computeAverages(entry all_data[], int counter, entry *all_average){
    for(int i=0; i<counter; i++){
        all_data[i].average=0;
        for(int j=0; j<5; j++)
            all_data[i].average += all_data[i].scores[j];
        all_data[i].average /= 5;
    }


    for(int i=0; i<6; i++){
        for(int j=0; j<counter; j++){
            all_average->scores[i]+=all_data[j].scores[i];
        }
        all_average->scores[i]/=counter;
    }

    return 1;
}

void print_all(entry all_data[], int total){
    entry *one_entry;
    int counter;
    for(counter=0; counter<total; counter++){
        one_entry = &all_data[counter];
        cout << one_entry->last_name << " " << one_entry->first_name<< " ";
        for(int i=0; i<5;i++)
            cout << one_entry->scores[i] << " ";

        cout << one_entry->average<<endl;
    }


}
void write_file(ofstream &output, entry all_data[], int total){
    entry *one_entry;
    for(int counter=0; counter<total; counter++){
        one_entry = &all_data[counter];
        output << one_entry->last_name << " " << one_entry->first_name<< " ";
        for(int i=0; i<4;i++)
            output << one_entry->scores[i] << " ";
        output << one_entry->average<<endl;
    }


}
