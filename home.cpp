#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>


using namespace std;

int displayHelp(){
	cout<<"\n\t\t======================================================\n"<<endl;
	cout<<"\t\t*				HELP MENU					*\n"<<endl;
	cout<<"\t\t======================================================\n\n"<<endl;
	cout<<"\t\tadd <Location>						:Add new location"<<endl;
	cout<<"\t\tdelete <Location>					:Delete an existing location"<<endl;
	cout<<"\t\trecord <Location> <Disease> <cases>			:Record a disease and it's cases"<<endl;
	cout<<"\t\tlist locations						:List all existing locations"<<endl;
	cout<<"\t\tlist diseases						:List existing Diseases in Locations"<<endl;
	cout<<"\t\twhere <disease>						:Find where disease exists"<<endl;
	cout<<"\t\tcases <location><disease>				:Find the cases of a disease in locations"<<endl;
	cout<<"\t\tcases <disease>						:Find total cases of a given disease"<<endl;
	cout<<"\t\thelp							:Prints user manual"<<endl;
	cout<<"\t\tExit							:Exit the whole program\n\n"<<endl;
}

int addLocation(string userInput){
		istringstream iss(userInput);
		string command, place;
		iss >> command >> place;
		transform(place.begin(), place.end(), place.begin(), ::toupper);
			
		ofstream outputFile("Locations.txt", ::ios::app); //open locations file in append mode
		if(outputFile.is_open()){
			outputFile << place << endl;
			outputFile.close();
			cout<< "\t\tLocation "+ place +" was added successfully!"<<endl;
		}else {
			cerr<<"\t\tFailed to save location" <<endl;
		}
}

int listLocations(string input){
	istringstream iss(input);
	string command, item;
	iss>> command >> item;
	transform(input.begin(), input.end(), input.begin(), ::toupper);
			
	ifstream inputFile("Locations.txt");
	if(inputFile.is_open()){
		string location;
		while(getline(inputFile, location)){
			cout<< "\t\t" + location <<endl;
		}
		inputFile.close();
	}
	else{
		cerr<< "\t\tError reading from locations file" <<endl;
	}
}

int listDiseases(){
	ifstream inputFile("records.csv");
	if(inputFile.is_open()){
		string location, disease, line;
		while(getline(inputFile, line)){
			istringstream iss(line);
			iss >> location >> disease; //disease is the disease already stored in the records file
			transform(disease.begin(), disease.end(), disease.begin(), ::toupper);
					
			cout<<"\t\t" + disease<<endl;
		}
	}else {
		cerr<< "\t\tFailed to open records file."<<endl;
	}
}

bool isLocation(string input){
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	
	ifstream inputFile("Locations.txt");
	string location;
	if(inputFile.is_open()){
		while(getline(inputFile, location)){
			if(input == location){
				return true;
			}
		}
							
		return false;
	}else{
		cerr<<"\t\tFailed to open the locations file."<<endl;
	}
}

bool isDisease(string input){
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	
	ifstream inputFile("records.csv");
	string line, location, disease;
	if(inputFile.is_open()){
		while(getline(inputFile, line)){
			istringstream iss(line);
			iss >> location >> disease;
			if(input == disease){
				return true;
			}
		}
	}else{
		cerr<<"\t\tFailed to open the records file."<<endl;
	}
}


int main(){
	string userInput; 
	transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
	
	cout<<"\t\t======================================================"<<endl;
	cout<<"\t\t*	Welcome to Disease Cases Reporting System!		*"<<endl;
	cout<<"\t\t*	*********************************************	*"<<endl;
	cout<<"\t\t*									*"<<endl;
	cout<<"\t\t*  It is developed by Nshuti Jabes as practical  *"<<endl;
	cout<<"\t\t*evaluation for the end of yr3						*"<<endl;
	cout<<"\t\t====================================================== \n\n"<<endl;
	cout<<"\t\tStarting Time: Thu Apr 05 23:59:08 CAT 2022"<<endl;
	cout<<"\t\tNeed help? Type 'help' then press Enter key.\n\n"<<endl;
	
	while(true){
		cout<<"\t\tConsole>\t";
		getline(cin, userInput);
		istringstream iss(userInput);
		string req;
		iss>>req;
		transform(req.begin(), req.end(), req.begin(), ::toupper);
		
		
		if(req == "HELP"){
			displayHelp();
		}
		else if(req == "ADD"){
			addLocation(userInput);	
		}
		else if(req == "LIST"){
			istringstream iss(userInput);
			string command, request;
			iss>> command >> request;
			
			if(request == "locations"){
				listLocations(userInput);
			}
			else if(request == "diseases"){
				listDiseases();
			}else{
				cerr<< "\t\tUnknown command!" <<endl;
			}
			
		}
		
		else if(req == "RECORD"){
			bool locationExists = false;
			istringstream iss(userInput);
			string command, location, disease, num_of_cases, line;
			iss >> command >> location >> disease >> num_of_cases;
			transform(location.begin(), location.end(), location.begin(), ::toupper);
			transform(disease.begin(), disease.end(), disease.begin(), ::toupper);
			
			//checking whether the entered location exists
			ifstream inputFile("Locations.txt");
			
			//check whether the location exists
			if(inputFile.is_open()){
				while(getline(inputFile, line)){
					
					if(line == location){
						locationExists = true;
						goto Found;
					}
					
				}
				cerr<< "\t\tThe Entered location doesn't exist" << endl;
			} else {
				cerr<< "\t\tFailed to open file" << endl;
			}
			
			//we will be brought to this step only if the location exists
			Found:
			
			//adding the disease and it's details to csv file
			ofstream outputFile("records.csv", ::ios::app); //open the records file in append mode
			if(locationExists){
				if(outputFile.is_open()){ //loop through all the lines in the records file
					outputFile << location << " " << disease << " " << num_of_cases <<endl;
				}else{
					cerr<<"\t\tFailed to open records file" << endl;
				}
			}
			
		}
		
		else if(req == "WHERE"){
			istringstream reqIss(userInput);
			string command, reqDisease;
			reqIss >> command >> reqDisease; //reqDisease is the disease the user is looking for
			transform(reqDisease.begin(), reqDisease.end(), reqDisease.begin(), ::toupper);
			
			ifstream inputFile("records.csv");
			if(inputFile.is_open()){
				string location, disease, line;
				while(getline(inputFile, line)){
					istringstream iss(line);
					iss >> location >> disease; //disease is the disease already stored in the records file
					transform(location.begin(), location.end(), location.begin(), ::tolower);
					
					if(reqDisease == disease){
						cout<< "\t\t[" + location + "]" <<endl;
						return 0;
					}
				}
				cerr<<"\t\tNo location with this disease"<<endl;
			}else {
				cerr<< "\t\tFailed to open records file."<<endl;
			}
		}
	
		else if(req == "CASES"){
			istringstream iss(userInput);
			string location, command, second, third;
			iss>> command >> second >> third;
			transform(second.begin(), second.end(), second.begin(), ::toupper);
			
			//check whether the second variable is either a location or disease
			if(isLocation(second)){
				ifstream inputFile("records.csv");
				string line, location, disease, count;
				while (getline(inputFile, line)){
					istringstream iss(line);
					iss >> location >> disease >> count;
							
					if(location == second){
						transform(third.begin(), third.end(), third.begin(), ::toupper);
						
						if(isDisease(third)){
							if(third == disease){
								cout<<"\t\tCases of "+disease+" at "+ location + " are: " + count <<endl;
							}
						}
						else{
							cout<<"Unkown disease"<<endl;
						}
					}
				}
			}
					
			else if(isDisease(second)){
				ifstream inputFile("records.csv");
				string line, location, disease, count;
				while (getline(inputFile, line)){
					istringstream iss(line);
					iss >> location >> disease >> count;
							
					if(second == disease){
						cout<<"\t\tTotal cases of '"+ disease + "' = "+ count<<endl;
					}
				}
			}
					
			else{
				cerr<<"\t\tThe command after 'cases' command is neither a location nor a disease. Please specify!!!"<<endl;	
			}
		}
		
		
	}
	
	
	
}
