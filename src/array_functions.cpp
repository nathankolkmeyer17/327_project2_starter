/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "constants.h"
#include "utilities.h"

using namespace std;
enum sortOrder {
	NONE,ASCENDING, DESCENDING, NUMBER_OCCURRENCES
};
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry {
	string word;
	int number_occurances;
};
//TODO add a global array of entry structs (global to this file)
entry myEntryArray[50];
//TODO add variable to keep track of next available slot in array
int nextSlot;
//TODO define all functions in header file
void clearArray(){
	for(int a = 0; a < nextSlot; a++){
		myEntryArray[a].word = " ";
		myEntryArray[a].number_occurances = 0;
	}
	nextSlot = 0;
}

int getArraySize(){
	return nextSlot;
}

std::string getArrayWordAt(int i){
	return myEntryArray[i].word;

}
int getArrayWord_NumbOccur_At(int i){
	return myEntryArray[i].number_occurances;
}

void processToken(std::string &token){
	std::string copyToken = token;
	strip_unwanted_chars(copyToken);
	toUpper(copyToken);
	bool isInArray=false;
	int y;
	for( y = 0; y < nextSlot;y++){
		std::string entryCopy = myEntryArray[y].word;
		toUpper(entryCopy);
		if(entryCopy == copyToken){
			myEntryArray[y].number_occurances += 1;
			isInArray = true;
			break;
		}
	}
	if(isInArray!= true && strip_unwanted_chars(token)){
		myEntryArray[nextSlot].word= token;
		myEntryArray[nextSlot].number_occurances +=1;
		nextSlot+=1;
	}

}


void processLine(std::string &myString){
	stringstream ss(myString);
	string tempToken;
	while(getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)){
		processToken(tempToken);
	}
}

bool processFile(std::fstream &myfstream){
	if(myfstream.is_open()){
		std::string line;
		while(!myfstream.eof()){
			getline(myfstream, line);
			processLine(line);
		}
		return true;
	}
	else{
		return false;
	}

}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in){

	myfile.open(myFileName.c_str(), mode);
	if (myfile.is_open()){
		return true;
	}
	else{
		return false;
	}


}

void closeFile(std::fstream& myfile){
	myfile.close();
}

int writeArraytoFile(const std::string &outputfilename){
	std::ofstream thisStream;
	thisStream.open(outputfilename.c_str());

	if(!thisStream.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}

	if(getArraySize()==0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	else{
		for(int i = 0; i < nextSlot;i++){
			thisStream << myEntryArray[i].word << " " << myEntryArray[i].number_occurances << endl;
		}
		thisStream.close();
		return constants::SUCCESS;
	}

}

void sortArray(constants::sortOrder so){
	switch(so){
	case constants::NONE:
		break;
	case constants::NUMBER_OCCURRENCES:
		break;
	case constants::ASCENDING:
		break;
	case constants::DESCENDING:
		break;

	}


}
