package shixi;

interface Speaker{
	public void speak();
	public void announce(String str);
}

class Philosopher implements Speaker{
	private String philosophy;
	public Philosopher(String philosophy) {
		this.philosophy = philosophy;
	}
	public void speak() {
		System.out.println(philosophy);
	}
	
	public void announce(String announcement) {
		
		System.out.println(announcement);
	}
	public void pontificate() {
		for(int count =1;count<=10;count++) {
			System.out.println(philosophy);
		}
		
	}
	
}

class Dog implements Speaker{

	
	public void speak() {
		System.out.println("woof");
		
	}

	
	public void announce(String announcement) {
		System.out.println("woof:"+announcement);
		
	}
	
}

public class Talking {

	public static void main(String args[]) {
		Speaker current;
		current =new Dog();
		current.speak();
		current =new Philosopher("Who am I?");
		current.speak();
		((Philosopher) current).pontificate();
	}
	
}
