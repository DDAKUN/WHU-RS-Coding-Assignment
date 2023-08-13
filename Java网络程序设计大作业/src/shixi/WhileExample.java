package shixi;

public class WhileExample { 
	public static void main(String[] args) { 
		String copyFromMe = "Copy this string until you encounter the letter 'u'."; 
		StringBuffer copyToMe = new StringBuffer();
		int i = 0; 
		char c = copyFromMe.charAt(i); 
		while (c != 'u') {
	copyToMe.append(c); 
	c = copyFromMe.charAt(++i);
	}
		System.out.println(copyToMe);
	}
}