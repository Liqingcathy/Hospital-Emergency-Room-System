/*
 *  Author: Liqing Li
 *  File:   Patient.h
 *  Purpose:Specification and implementation files for defining and implementing
 *          private members of patient, constructors, operator assignment, getter functions & toString function.
 *  Note:   Operator assignment function determines the PatientPriorityQueue is a min heap and defines order rule
 *          of patient priority queue is 1. immediate 2. emergency, 3.urgent, 4.minimal
 *          If patient's priority code ties, the arrival order determines their order to be seen.
 *
 */

#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <vector>


class Patient{
public:
    //A default constructor create an empty patient.
    //Pre-condition: None
    //Post-condition: An empty patient object.
    Patient();

    //A parameterized patient constructor creates a patient object
    //Pre-condition: String of fullname, priority code and int arrive code
    //Post-condition: Creates a patient object holds specific values
    Patient(std::string fullName, std::string code, int arrive);

    //Operator assignment function compares values of the patient by priority code and arrive code.
    //Patient1<Patient2 means patient1's priority is higher than patient 2, arrive code 1 is earlier than patient2
    //Pre-condition: A reference of a patient to compare with
    //Post-condition: Returns true if this patient's priority higher than referenced patient's priority code
    //Returns true if their priority code is same but this patient's arrive number is earlier than the reference patient
    bool operator<(const Patient& patient1);

    //A getter function to get patient's full name
    std::basic_string<char> getFullName() const;
    //A getter function to get patient's priority code
    std::basic_string<char> getPriorityCode() const;
    //A getter function to get patient's arrival order
    int getArrivalOrder() const;

    //A destructor to clear the patient object
    //Pre-condition: None
    //Post-condition: Destroy the object
    ~Patient();

    //Prints out the patient object as a string representation as required
    //Pre-condition: None
    //Post-condition: Example of result- Jane Smith { pri=urgent, arrive=3 }
    std::string toString();

private:
    std::string fullName;
    std::string priorityCode;
    int arrivalOrder;
};

Patient::Patient():fullName(""),priorityCode(""),arrivalOrder(0){}


Patient::Patient(std::string fullName, std::string priority, int arrive){
    this->fullName = fullName;
    //Converts to a string number to easily compares the priority as defined
    if(priority == "immediate") {
        priorityCode = "1";
    }else if(priority == "emergency"){
        priorityCode = "2";
    }else if(priority == "urgent"){
        priorityCode = "3";
    }else if(priority == "minimal"){
        priorityCode = "4";
    }
    this->arrivalOrder = arrive;

}
/*
 * Overloaded operators in order to properly add, peek, and remove patients from the priority queue
 * if priority is different, return by priority code, if priority code is tied, return earlier arrival order
 * Priority: 1. immediate 2. emergency, 3.urgent, 4.minimal
 * If priority code ties, return by earlier arrival order: 1, 2 , 3 ,4 ...
 *
 * By default a max heap --- return this->arrivalOrder < patient1.arrivalOrder;
 * Changes to a min heap --- return this->arrivalOrder > patient1.arrivalOrder;
 * */
bool Patient::operator < (const Patient &patient1) {
    if(priorityCode == patient1.priorityCode ) {
        return this->arrivalOrder > patient1.arrivalOrder;
    }else {
        return this->priorityCode > patient1.priorityCode;
    }
}


Patient::~Patient(){ }

std::basic_string<char> Patient::getFullName() const {
    return fullName;
}

//Converts back to string word version of priority code to match type in the main class
std::basic_string<char> Patient::getPriorityCode() const {
    std::stringstream ss;
    if(priorityCode == "1") {
        ss <<  "immediate";
    }else if(priorityCode == "2"){
        ss << "emergency";
    }else if(priorityCode == "3"){
        ss << "urgent";
    }else if(priorityCode == "4"){
        ss << "minimal";
    }
    return ss.str();
}

int Patient::getArrivalOrder() const {
   return arrivalOrder;
}

//Jane Smith { pri=urgent, arrive=3 }
std::string Patient::toString(){
    std::stringstream ss ;
    ss << fullName << "{ pri=" << priorityCode << ", arrive=" << arrivalOrder  << " }";

    return ss.str();
}


#endif //PATIENT_H
