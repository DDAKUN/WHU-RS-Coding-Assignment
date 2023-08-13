package shixi;

class A{
	public A() {
		System.out.println("String a");
	}
}

class B extends A{
	
	public B() {
		System.out.println("String b");
	}
	
}

class C extends B{
	public C() {
		System.out.println("String c");
	}
	
}
public class ConstructorTest {

	public static void main(String args[]){
		C c= new C();
	}
}
