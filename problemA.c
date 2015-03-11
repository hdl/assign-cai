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
    return 0;

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

void print_all(entry all_data[], int counter){
    entry *one_entry;

    while(counter--){
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
