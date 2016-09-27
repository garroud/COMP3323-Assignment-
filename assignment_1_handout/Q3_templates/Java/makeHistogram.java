public class makeHistogram{
	public static void create_histogram(String data_path, String eq_width_path, String eq_depth_path){
		// To create an equi-width histogram and an equi-depth histogram, and save them to files.
		// Each output file should contain exactly eight lines, and each line should contain a single integer.
		
		
	}

	public static void main(String args[]){
  		if(args.length != 3){
  			System.out.println("Usage: java makeHistogram DATA_PATH EQ_WIDTH_PATH EQ_DEPTH_PATH");
  			/*
			DATA_PATH(String): the file path of final_general.dat
			EQ_WIDTH_PATH(String): the output file path of the equal-width histogram
  			EQ_DEPTH_PATH(String): the output file path of the equal-depth histogram
  			*/
  			return;
  		}
  		create_histogram(args[0], args[1], args[2]);
  	}
}