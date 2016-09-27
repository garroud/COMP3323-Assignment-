#include <iostream>

using namespace std;

double estimate_eqWidth(int LEFT, int RIGHT, char * histogram_path)
{
	// to get the estimated result using the equi-width histogram
	
	return 0.0;
}

double estimate_eqDepth(int LEFT, int RIGHT, char * histogram_path)
{
	// to get the estimated result using the equi-depth histogram
	
	return 0.0;
}

int get_result(int LEFT, int RIGHT, char * dat_path)
{
	// to get the real result, using the actual data
	
	return 0;
}

int main(int argc, char** argv)
{
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
	return 0;
}

