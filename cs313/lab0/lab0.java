import java.util.Scanner;  //import Scanner packagepublic 

class lab0 {
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		int numProblems = scanner.nextInt();  //retrieve the number of lines
		for(int i = 0; i < numProblems; ++i){
			int a = scanner.nextInt();  //retrieve the first integer
			int b = scanner.nextInt();  //retrieve the second integer
			int g = gcd(a,b);
			int l = lcm(a,b);
			System.out.println(g + " " + l);
		}

		scanner.close();
	}
	
	public static int gcd(int a, int b){
		// Find the greatest common divisor of a and b
		int gcd = 1;
		int dividend;
		int divisor;

		//check if a or b is 0 and return gcd appropriately
		if(a == 0){
			if(b == 0){
				return 1;
			}else{
				return b;
			}
		}else if(b == 0){
			return a;
		}
		
		//set dividend and divisor based on which is larger:
		if(a >= b){
			dividend = a;
			divisor = b;
		}else{
                        dividend = b;
                        divisor = a;
                }

		//find actual gcd:
		while(divisor != 0){
			int remainder = dividend % divisor;
			if (remainder == 0){
                                gcd = divisor; //if the remainder is 0 then the divisor is the gcd
                        }
			dividend = divisor;
			divisor = remainder;
		}
		
		return gcd;
	}
	
	public static int lcm(int a, int b){
		// Find the least common multiple of a and b
		int lcm = (a * b) / (gcd(a, b)); //definition of a*b = gcd(a,b) * lcm(a,b)
		return lcm;		
	}
}

