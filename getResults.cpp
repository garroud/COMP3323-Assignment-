#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
// base(int n): check the size of bin, 11 if the last bin, 10 otherwise;
double base(int n){
	if (n == 7) return 11.0;
	return 10.0;
}
double estimate_eqWidth(int LEFT, int RIGHT, char * histogram_path)
{
	// to get the estimated result using the equi-width histogram
	if (LEFT > RIGHT){
		cerr << "LEFT > RIGHT ! Invalid input!" << endl;
		return 0;
	}
	ifstream input;
	input.open(histogram_path);
	if (!input.is_open()){
		cerr << histogram_path  << "is invalid!" << endl;
		exit(1);
	}
	vector<int> histogram;
	string line;
	while(getline(input, line)){
		histogram.push_back(atoi(line.c_str()));
	}
	input.close();
	double total = 0;
  //Consider a boundary case:age 80
	if(LEFT == 80) return (histogram.back() * 1/11.0);
	if(RIGHT == 80){
			total += histogram.back() * 1/11.0;
			RIGHT -= 1;
	}
	int left_index = LEFT / 10;
	int right_index = RIGHT / 10;
	//if LEFT and RIGHT fall into the same bin
	if (left_index == right_index){
		return (RIGHT - LEFT+1)/base(left_index) * histogram[left_index];
	}
	//Deal with the bin in which LEFT falls
	total += ((left_index+1)*10 - LEFT)/base(left_index) * histogram[left_index];
	//Deal with the internal bins
	for (int i = left_index + 1; i < right_index ; ++i){
		total += histogram[i];
	}
	// Deal with the bin in which RIGHT falls
	total += (RIGHT - right_index * 10 + 1)/base(right_index) * histogram[right_index];
	return total;
}

double estimate_eqDepth(int LEFT, int RIGHT, char * histogram_path)
{
	// to get the estimated result using the equi-depth histogram
	if (LEFT > RIGHT){
		cerr << "LEFT > RIGHT ! Invalid input!" << endl;
		return 0;
	}
	ifstream input;
	input.open(histogram_path);
	if (!input.is_open()){
		cerr << histogram_path  << "is invalid!" << endl;
		exit(1);
	}
	vector<double> histogram;
	string line;
	getline(input,line);
	int size = atoi(line.c_str());
	//add age 0 to the histogram
	histogram.push_back(0);
	while(getline(input, line)){
		histogram.push_back(atoi(line.c_str()));
	}
	//add age 80 to the histogram, and count it into the bin
	histogram.push_back(80.5);
	int index = 1;
	int bin = size / 8;
	double total_bin = 0;
	//Determine the position of LEFT and RIGHT
	for (; index < histogram.size(); ++index){
		if(LEFT <= histogram[index]){
			if(RIGHT < histogram[index]){
				return (bin * (RIGHT - LEFT + 1)/double(floor(histogram[index]) - ceil(histogram[index-1])+1));
			}
			total_bin += bin * (floor(histogram[index])-LEFT + 1 )/double(floor(histogram[index])-ceil(histogram[index-1])+1);
			break;
		}
	}
	for(index += 1;index < histogram.size(); ++index){
		if (RIGHT < histogram[index]){
			total_bin += bin * (RIGHT - ceil(histogram[index-1]) + 1)/double(floor(histogram[index]) - ceil(histogram[index-1]) + 1);
			break;
		}
		total_bin += bin;
	}
	input.close();
	return total_bin;
}

int get_result(int LEFT, int RIGHT, char * dat_path)
{
	// to get the real result, using the actual data
	if (LEFT > RIGHT){
		cerr << "LEFT > RIGHT ! Invalid input!" << endl;
		return 0;
	}
	ifstream data_input;
	data_input.open(dat_path);
	if(!data_input.is_open()){
		cerr << dat_path << "is invalid!" << endl;
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
	int count = 0;
	for (int i= 0 ; i <= ages.size()-1; i++){
		if(ages[i] <= RIGHT && LEFT <= ages[i]){
			count += 1;
		}
	}
	return count;
}

void report_test(char * path1, char * path2, char* path3){
	ofstream test;
	test.open("test.txt");
	int left , right;
	srand (time(NULL));
	for(int i = 0 ; i<= 99 ; ++i){
	left = rand() % 81;
	right = rand() % 81;
	if(left > right){
		int temp = left;
		left = right;
		right = temp;
	}
	double wid = estimate_eqWidth(left,right, path1);
	double dep = estimate_eqDepth(left,right, path2);
	double real = get_result(left,right, path3);
	double error_wid = (wid - real)/real;
	double error_dep = (dep - real)/real;
	int size = right - left + 1;
	test << left << " " << right << " " << size << " " << wid <<
					   " " << dep << " " << real << " " << error_wid << " "
						 << error_dep << endl;
}
	test.close();
	return;
}

void report_test_all(char * path1, char * path2, char* path3){
	ofstream test;
	int left , right;
	srand (time(NULL));
	for(left = 0 ; left< 80 ; left+=10){
		test.open("test_all_" + to_string(left) + ".txt");
		for(right= left ; right <= 80; ++right){
			double wid = estimate_eqWidth(left,right, path1);
			double dep = estimate_eqDepth(left,right, path2);
			double real = get_result(left,right, path3);
			double error_wid = (wid - real)/real;
			double error_dep = (dep - real)/real;
			int size = right - left + 1;
			test << left << " " << right << " " << size << " " << wid <<
					   " " << dep << " " << real << " " << error_wid << " "
						 << error_dep << endl;
					 }
			test.close();
}
	test.close();
	return;
}
int main(int argc, char** argv)
{
		srand (time(NULL));
	if (argc != 6){
		cerr << "Usage: " << argv[0] << " LEFT RIGHT WIDTH_HISTOGRAM_PATH DEPTH_HISTOGRAM_PATH DATA_PATH" << endl;
		/*
			LEFT(int): the lower bound of the interval
			RIGHT(int): the upper bound of the interval
			WIDTH_HISTOGRAM_PATH(char *): the file path of the equal-width histogram
			DEPTH_HISTOGRAM_PATH(char *): the file path of the equal-depth histogram
			DATA_PATH(char *): the file path of final_general.dat
  		*/
		return -1;
	}
	cout << estimate_eqWidth(atoi(argv[1]), atoi(argv[2]), argv[3]) << endl;
	cout << estimate_eqDepth(atoi(argv[1]), atoi(argv[2]), argv[4]) << endl;
	cout << get_result(atoi(argv[1]), atoi(argv[2]), argv[5]) << endl;
	report_test_all(argv[3],argv[4],argv[5]);
	return 0;
}
