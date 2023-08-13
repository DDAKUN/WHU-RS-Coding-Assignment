package shixi;

class Car{
	int Speed;
	public void push_break(){
		System.out.println("Car break!");
	}
	
}

class TrashCar extends Car{
	double amount;
	public void push_break() {
		System.out.println("TrashCar break!");
	}
}
public class CarDemo {
	public static void main(String args[]) {
		Car car=new TrashCar();
		car.push_break();
		
	}
}
