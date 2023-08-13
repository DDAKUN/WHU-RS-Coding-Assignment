
public class GeneralFunction {

		
public static int addUp(int x,int y) { 
			 return x+y;
    }
		 
public static int method() {
	 int a=9;
	 int b=10;
	 int c=GeneralFunction.addUp(a,b);
	 return c;
 }
 public static void main(String[] args) {
    int c=method();
	 System.out.println("c="+c);
 }
}

