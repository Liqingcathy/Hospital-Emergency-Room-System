/*
 *  Author: Liqing Li
 *  File:   PatientPriorityQueue.h
 *  Purpose:Specification and implementation files for defining and implementing priorityQueue members and
 *          functions like creating priority queue using patient object to add, remove, peek, and list elements of this heap.
 *  Note:   This PatientPriorityQueue is a min heap order defined by Patient.h
 *          Patient priority is 1. immediate 2. emergency, 3.urgent, 4.minimal
 *          If patient's priority code ties, the arrival order determines the heap order.
 */


#ifndef PATIENTPRIORITYQUEUE_H
#define PATIENTPRIORITYQUEUE_H
#include "Patient.h"
#include <vector>
#include <sstream>
#include <iomanip>

class PatientPriorityQueue{
public:
    //Creates an empty PatientPriorityQueue(triage system) with no patients, zero parameter.
    //Pre-condition: None
    //Post-condition: Creates an empty heap priority queue
    PatientPriorityQueue();

    //Adds the patient to the priority queue so that the heap is min heap.
    //The heap order is defined by priority code and then arrival code
    //After each patient is added, the heap order remains min heap order, priority is in min order.
    //Pre-condition: Strings of Patient's priority code and full name
    //Post-condition: Returns true if patient is added.
    void add(std::string priority, std::string name);

    //Glance at the first object in the heap which is the min value node.
    //Pre-condition: None
    //Post-condition: Returns the highest priority patient without removing it.
    std::string peek();

    //Removes the highest priority patient from the queue which is the first node.
    //Pre-condition: None. This function needs to maintain heap order.
    //Post-condition: Returns patient's full name when min value is removed.
    std::string remove();

    //Counts the number of patients in the priority queue.
    //Pre-condition: None
    //Post-condition: Return an integer number of the size
    int size();

    //Lists the string representation of the object in min heap order.
    //Pre-condition: None
    //Post-condition: Prints out each object's arrive code, priority code, full name in heap order.
    std::string to_String();
private:
    std::vector<Patient> allPatient; //Stores patient in a vector in heap order
    int nextPatientNumber;
    //Keeps track of the last patient inserted into the heap, so that as patients arrive,
    //they will get assigned proper arrivalOrder from 1 to number has been counting.

    //Private function to re-heapify and bubble down after removing nodes
    //Pre-condition: A rootIndex which is 0
    //Post-condition: Return a re-ordered min heap to public function remove
    void removeHelper(int rootIndex);
};


PatientPriorityQueue::PatientPriorityQueue(){
    nextPatientNumber = 1; //patient counts from 1
}

void PatientPriorityQueue::add(std::string priority, std::string name) {
    Patient p(name, priority, nextPatientNumber);//constructs patient node
    allPatient.push_back(p);
    int newDataIndex = size()-1;
    bool inPlace = false;
    while((newDataIndex > 0) && !inPlace) {
        int parentIndex = (newDataIndex - 1) / 2;
        if(allPatient[parentIndex] < allPatient[newDataIndex]){
            Patient temp = allPatient[newDataIndex];
            allPatient[newDataIndex] = allPatient[parentIndex];
            allPatient[parentIndex] = temp;
            newDataIndex = parentIndex;
        }
        else
            inPlace = true;
    }
    nextPatientNumber++;
    }

std::string PatientPriorityQueue::peek() {
    return allPatient.at(0).getFullName(); //peek higher priority one, without removing
}

//Private function, calling from remove function
//re-heapify the heap by bubbling down the top node by smaller value in the child node
void PatientPriorityQueue::removeHelper(int rootIndex) {
    if (2 * rootIndex + 1 < size()) { // the root is not a leaf (that is, it has a left child)
        int leftChildIndex = 2 * rootIndex + 1; // left child index
        if (leftChildIndex + 1 < size()) { // the root has a right child
            int rightChildIndex = leftChildIndex + 1;

            // If right child is higher priority than left, assign higher to left.
            if (allPatient[leftChildIndex] < allPatient[rightChildIndex]) {
                leftChildIndex = rightChildIndex;
            }
            //If root patient isn't the highest priority, swap with child
            if (allPatient[rootIndex] < allPatient[leftChildIndex]) {
                Patient temp = allPatient[rootIndex];
                allPatient[rootIndex] = allPatient[leftChildIndex];
                allPatient[leftChildIndex] = temp;
                removeHelper(leftChildIndex);
            }
        }
    }
}
//public function
std::string PatientPriorityQueue::remove() {
    Patient p = allPatient[0];
    int lastIndex = size()-1;
    allPatient[0] = allPatient[lastIndex]; //moves to right most node
    allPatient.erase(allPatient.begin() + lastIndex); //?????
    removeHelper(0); //re-heapify the min index value
    return p.getFullName();
}


int PatientPriorityQueue::size() {
    return allPatient.size();
}

//You may want to #include <sstream> and use a stringstream object to capture the string traversal.
std::string PatientPriorityQueue::to_String() {
    std::stringstream allElement;
    for (int i = 0; i < size(); i++) {
        //Arrival #   Priority Code   Patient Name
        allElement << std::setw(8) << std::right  << allPatient[i].getArrivalOrder() << "\t\t"
        << std::setw(14)  << std::left << allPatient[i].getPriorityCode()
        << std::setw(14) << std::left << allPatient[i].getFullName() << '\n';
    }
    return allElement.str();
}

#endif //PATIENTPRIORITYQUEUE_H
