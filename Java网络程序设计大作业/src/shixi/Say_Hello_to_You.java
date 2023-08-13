package shixi;
import java.io.*; 
public class Say_Hello_to_You{ 
	public static void main (String[] args) 
			throws IOException{ InputStreamReader reader=new InputStreamReader(System.in); 
			BufferedReader input=new BufferedReader(reader); 
			System.out.print("Enter your name:"); 
			String name=input.readLine(); 
			System.out.println("Hello,"+ name + "!");

	}
	}