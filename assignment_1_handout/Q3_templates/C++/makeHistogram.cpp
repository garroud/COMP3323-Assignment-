#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int bin(int data){
	for(int i = 0 ; i <= 7 ; ++i){
		if (data >= i*10 && data < (i+1)*10) return i;
		if (data == 80) return i;
	}
	cerr << "There is an age not inside [0,80]" << endl;
	return -1;
}
void create_histogram(char * data_path, char * eq_width_path, char * eq_depth_path)
{
	// To create an equi-width histogram and an equi-depth histogram, and save them to files.
	ifstream data_input;
	data_input.open(data_path);
	if (!data_input.is_open()){
		cerr << "The" << data_path << "is invalid!" << endl;
		exit(1);
	}
	vector<int> ages; //the vector which stores all the ages
	string line;
	while(getline(data_input,line)){
		//parse the input line by line
		for (int i = 0 ; i <= line.length(); ++i){
			if (line[i] == ' '){
  		// record down the age in this line
				 string age;
				 int j = i + 1;
				 do{
					 age += line[j];
					 j++;
				 }while(line[j] != ' ');
				 ages.push_back(atoi(age.c_str()));
				 break;
			}
		}
	}
	data_input.close();
	sort(ages.begin(), ages.end());
	// Each output file should contain exactly eight lines, and each line should contain a single integer.
	ofstream eqWidth , eqDepth;
	eqWidth.open(eq_width_path);
	eqDepth.open(eq_depth_path);
	//check whether the two files are opened;
	if(!eqWidth.is_open()){
		cerr << eq_width_path << "is invalid!" << endl;
		exit(1);
	}
	if(!eqDepth.is_open()){
		cerr << eq_depth_path << "is invalid!" << endl;
		exit(1);
	}
	// eqWdith: Determine the frequency in each bin
	int His_eqWid[8] = {0,0,0,0,0,0,0,0};
	vector<int> His_eqDep;
	int avr_frq = ages.size() / 8;
	int check = 0; // check whether a bin of His_eqDep is full
	for(int i = 0 ; i < ages.size(); ++i){
		His_eqWid[bin(ages[i])] += 1;
		if (!(check == avr_frq)) check += 1 ;
		else {
			His_eqDep.push_back(ages[i]);
			check = 1;
		}
	}
	for(int i = 0 ; i <= 7 ; ++i){
		eqWidth << His_eqWid[i] << endl;
	}
	for(int i = 0 ; i < His_eqDep.size() ; ++i){
		eqDepth << His_eqDep[i] << endl;
	}
	eqWidth.close();
	eqDepth.close();
}

int main(int argc, char ** argv)
{
	if (argc != 4){
		cerr << "Ussage: " << argv[0] << " DATA_PATH EQ_WIDTH_PATH EQ_DEPTH_PATH" << endl;
		/*
			DATA_PATH(char *): the file path of final_general.dat
			EQ_WIDTH_PATH(char *): the output file path of the equal-width histogram
  			EQ_DEPTH_PATH(char *): the output file path of the equal-depth histogram
  		*/
		return -1;
	}
	create_histogram(argv[1], argv[2], argv[3]);
	return 0;
}
