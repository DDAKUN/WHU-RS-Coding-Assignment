package shixi;
public class FunnyNumbers { 
	public static void main(String args[]) { 
		double largeNum = Math.exp(4000.0);
        int posDivZero = 10/0; 
        double negDivZero = -10.0 / 0.0; 
        double zeroDivZero = 0.0/0.0;
        System.out.println(largeNum); 
        System.out.println(posDivZero); 
        System.out.println(negDivZero); 
        System.out.println(zeroDivZero);
        double x=largeNum+posDivZero; 
        double y=largeNum+negDivZero; 
        double z=largeNum+zeroDivZero; 
        System.out.println("x="+x); 
        System.out.println("y="+y); 
        System.out.println("z="+z);
        } 
	}
