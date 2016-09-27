public class getResults{
	public static double estimate_eqWidth(int LEFT, int RIGHT, String histogram_path){
		// to get the estimated result using the equi-width histogram
	
		return 0.0;
	}


	public static double estimate_eqDepth(int LEFT, int RIGHT, String histogram_path){
		// to get the estimated result using the equi-depth histogram

		return 0.0;
	}
		
	public static int get_result(int LEFT, int RIGHT, String dat_path){
		// to get the real result, using the actual data

		
		return 0;
	}

	public static void main(String args[]){
  		if(args.length != 5){
  			System.out.println("Usage: java getResults LEFT RIGHT EQ_WIDTH_PATH EQ_DEPTH_PATH DATA_PATH");
  			/*
			LEFT(int): the lower bound of the interval
			RIGHT(int): the upper bound of the interval
			EQ_WIDTH_PATH(String): the file path of the equal-width histogram
			EQ_DEPTH_PATH(String): the file path of the equal-depth histogram
			DATA_PATH(String): the file path of final_general.dat
  			*/
  			return;
  		}
  		System.out.println(estimate_eqWidth(Integer.parseInt(args[0]), Integer.parseInt(args[1]), args[2]));
  		System.out.println(estimate_eqDepth(Integer.parseInt(args[0]), Integer.parseInt(args[1]), args[3]));
  		System.out.println(get_result(Integer.parseInt(args[0]), Integer.parseInt(args[1]), args[4]));
  	}
}