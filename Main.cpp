/*
 * Author:  Liqing Li
 * File:    Main.cpp
 * Purpose: Tests a hospital emergency room system defined and implemented in PatientPriorityQueue and Patient class.
 *          This program adds patients to the system, sees next patient, removes patient from waiting room and lists patients for operators.
 * Process: Prompt user to enter a command by instruction. Each commands complete an action to either see options of the system,
 *          or add patients or peek next patient to seen next or remove patient from waiting room or list all patients in the waiting room.
 *          Load command reads all patients list in the txt file and executes by the commands in the file. The result executed based on
 *          the file should return a correct order of patients in the emergency room system rule i.e put patients by order:
 *          1. immediate 2. emergency, 3.urgent, 4.minimal, if priority is the same, put earlier arrived patient to next order.
 * Output:  Prints out executed command and corresponding result of patients added, removed, peeked, listed by priority system.
 *          Returns message if there's no patient in the waiting room or there's no patient to remove from the list.
 * Test     /usr/local/bin/g++-10 p3.cpp Patient.h PatientPriorityQueue.h -o -pedantic -Wall -Werror -std=c++11

 *
 * */


#include "PatientPriorityQueue.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

void removeSpaces(string& str);
// Removes lead or tail space for command, priority code and name input

//TEST prompt and result based on each command executed
int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

    // process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));


	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {

    // get command
    string cmd = delimitBySpace(line);

    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add") {
        addPatientCmd(line, priQueue);
    } else if (cmd == "peek"){
        peekNextCmd(priQueue);
    }else if (cmd == "next"){
		removePatientCmd(priQueue);
    }else if (cmd == "list"){
		showPatientListCmd(priQueue);
    }else if (cmd == "load"){
        execCommandsFromFileCmd(line, priQueue);
    }else if (cmd == "quit"){
		return false;
    }else{
		cout << "Error: unrecognized command: " << cmd << endl;
    }
	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;
    // get priority and name
    priority = delimitBySpace(line);

    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;

    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    // TODO: add logic to remove leading/trailing spaces
        removeSpaces(name);

    // TODO: validate priority is between 1 and 4 , add patient
    if (priority == "immediate" || priority == "emergency" || priority == "urgent" || priority == "minimal") {
        priQueue.add(priority, name);
        cout << "\nAdded patient \"" << name <<"\""<< " to the priority system" << std::endl;
    } else {
            cerr << "invalid priority code, please re-enter from required options." ;
        }
    }

//Trim additionally lead and end space from input
void removeSpaces(string& str){
    while(!str.empty() && isspace(str.front())){
        str.erase(str.begin());
    }
    while(!str.empty() && isspace(str.back())){
        str.pop_back();
    }
}
void peekNextCmd(PatientPriorityQueue &priQueue) {
	// TODO: shows next patient to be seen
    if(priQueue.size() == 0){
        cout << "There are no patients in the waiting area.\n";
    }else{
        cout << "Highest priority patient to be called next: " ;
        cout << priQueue.peek();
        cout << endl;
    }
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
	// TODO: removes and shows next patient to be seen
    if(priQueue.size() == 0) {
        cout << "There are no patients in the waiting area\n" ;

    }else {
        cout << "This patient will now be seen: ";
        cout << priQueue.remove() << std::endl;
    }
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    // TODO: shows patient detail in heap order
    cout << priQueue.to_String();
    if (priQueue.size() == 0) {
        cout << "There are no patients in the waiting area\n";
    }
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0; //unsigned: non-negative integer
    char delimiter = ' ';
    string result = "";
    removeSpaces(s);
    pos = s.find(delimiter);
    //int pos updates from 0 to an index where find ' '
    //ex: add' 'minimal' 'Sam >>> pos: 3 >>> add
    if (pos != string::npos) { //string::npos-> usually used to indicate failure.
        result = s.substr(0, pos);
        //each call result="add" -> result="minimal" -> result="Sam Hamilton"
        s.erase(0, pos + 1);
        //each call s="add minimal Sam Hamilton" -> s="minimal Sam Hamilton" -> s="Sam Hamilton"
    }
    return result;
}

void welcome() {
	// TODO
	cout << "+-------------------------------------------------+\n"
	<< "Welcome to CPSC-5910 hospital emergency room system.\n"
	<< "This program helps prioritize patient's order.\n"
	<< "You might start entering \"help\" to see the menu.\n"
	<< "+-------------------------------------------------+\n";

}

void goodbye() {
	// TODO
	std::cout << "\nThank you for using the hospital emergency room service.\n"
              << "See you next time\n";
}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
