package shixi;

abstract class Shape{
	abstract double computeArea();//�������
	abstract double computeCircumference();//�����ܳ�
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
		System.out.println("�߳�Ϊ2��3�ĳ��������Ϊ"+a.computeArea());
		System.out.println("�߳�Ϊ2��3�ĳ������ܳ�Ϊ"+a.computeCircumference());
		System.out.println("�뾶Ϊ3��Բ���Ϊ"+b.computeArea());
		System.out.println("�뾶Ϊ3��Բ�ܳ�Ϊ"+b.computeCircumference());
	}
}
