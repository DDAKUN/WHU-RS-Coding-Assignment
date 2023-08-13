package shixi;

abstract class Shape{
	abstract double computeArea();//计算面积
	abstract double computeCircumference();//计算周长
}
class Rectangle extends Shape{
	double x,y;
	Rectangle(double a,double b){
		x=a;y=b;
	}
	double computeCircumference() {
		return 2*x+2*y;
	}
	double computeArea() {
		return x*y;
	}
}

class Circle extends Shape{
	double r;
	Circle(double a){
		r=a;
	}
    double computeArea() {
		return Math.PI*r*r;
	}
    double computeCircumference() {
		return 2*Math.PI*r;
	}
}


public class ShapeTestWithPolymorphism {
	public static void main(String args[]) {
		Rectangle a=new Rectangle(2,3);
		Circle b=new Circle(3);
		System.out.println("边长为2，3的长方形面积为"+a.computeArea());
		System.out.println("边长为2，3的长方形周长为"+a.computeCircumference());
		System.out.println("半径为3的圆面积为"+b.computeArea());
		System.out.println("半径为3的圆周长为"+b.computeCircumference());
	}
}
