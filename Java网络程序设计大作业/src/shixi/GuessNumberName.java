package shixi;
import java.util.*;
public class GuessNumberName {
   
	public static void main(String args[]) {
		double m=0;
		int i=1;
		double n=Math.random()*99+1;
		System.out.println("Please enter a number");
		Scanner reader = new Scanner(System.in);
		m=reader.nextDouble();
		
		while(m!=n) {
			if(m>n) {
				System.out.println("Your answer is HIGH,try again");
				System.out.println("Please enter a number again");
				m=reader.nextDouble();
				i++;
			}
			if(m<n) {
				System.out.println("Your answer is LOW,try again");
				System.out.println("Please enter a number again");
				m=reader.nextDouble();
				i++;
			}
		}
		System.out.println("You win! You have guessed "+i+" times!");
		
	}
}
