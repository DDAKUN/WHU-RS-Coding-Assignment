package shixi;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Work3{
	int[] a =new int[100]; 
	static int find,num;//定义全局变量
	public void generate(int a[]){
	    Random ran = new Random();
	    for (int i = 0; i < 100; i++) {
	        a[i] = ran.nextInt(100);//随机产生数组
	    }
	}
	
	
	public void sort1(int a[]) {//冒泡排序（升序）
        int temp=0,i,j;
        for(i=0;i<a.length;i++)
        {
            for(j=0;j<a.length-i-1;j++)
            {
                if(a[j]>a[j+1])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;//冒泡交换
                }
            }
        }
	}
	
	public void sort2(int a[]) {//交换排序（降序）
		  int i,j,temp;
    	    for (i=0;i<a.length;i++)//两次循环
    	    {
    	        for (j=i+1;j<a.length;j++)
    	        {
    	            if(a[j]>a[i])//碰到右边大于左边则交换
    	            {
    	                temp=a[j];
    	                a[j]=a[i];
    	                a[i]=temp;
    	            }
    	        }        
    	    }
	}
	
	
	public void search1(int arr[],int a) {
        int i;//顺序查找
        int temp=20000;//定义一个巨大值
        for (i = 0; i < 99; i++) {
        	if(Math.abs(arr[i]-a)<temp) {
               temp=Math.abs(arr[i]-a);
               find=arr[i];
               num=i+1;//进行比较，找出谁更接近
        	}
        }
	}
	
	public void search2(int arr[],int a) {
	        int min = 0;//折半查找
			int max = arr.length-1;
			int mid=0;
			int temp=20000;
			while (min <= max) {
				mid = (min + max) / 2;
				if(Math.abs(arr[mid]-a)<temp) {
		               temp=Math.abs(arr[mid]-a);
		               find=arr[mid];
		               num=mid+1;
		        	}//进行比较
				else if (arr[mid] > a) {
					max = mid - 1;//后哨兵移位
				} else {
					min = mid + 1;//前哨兵移位
				}
			}
	}
	static final int WIDTH=600;
	static final int HEIGHT=400;
	
	JFrame f;
	JPanel p;
	JToolBar bar;
	public Work3(){
		//设置窗口参数
		 f = new JFrame("数组测试");
		 f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 		
		//建立菜单棒对象并加入窗口
		JMenuBar menubar1 = new JMenuBar();
		f.setJMenuBar(menubar1);

 		//建立面板并加入窗口
		p = new JPanel();
 		f.setContentPane(p);
 		 JOptionPane.showMessageDialog(null, "周家豪制作"); 
		//建立菜单项
 		JMenu menu1=new JMenu("生成数据");
		JMenu menu2=new JMenu("数据排序");
     	JMenu menu3=new JMenu("数据查询");
     	JMenu menu4=new JMenu("退出");	
		//将菜单项依次加入菜单棒
     		menubar1.add(menu1);
     		menubar1.add(menu2);
     		menubar1.add(menu3);
     		menubar1.add(menu4);
 		//建立子菜单项
		JMenuItem item1=new JMenuItem("生成随机数组");
		JMenuItem item2=new JMenuItem("冒泡排序");
     		JMenuItem item3=new JMenuItem("交换排序");
     		JMenuItem item4=new JMenuItem("顺序查找");
     		JMenuItem item5=new JMenuItem("折半查找");
     		JMenuItem item6=new JMenuItem("退出");
     	
 
 
 		//子菜单项依次加入菜单项
     		menu1.add(item1);
     		menu1.addSeparator();//这是分割符
     		
 
 
     		menu2.add(item2);
     		menu2.addSeparator();
     		menu2.add(item3);
 
     		menu3.add(item4);
     		menu3.addSeparator();
     		menu3.add(item5);
            
     		menu4.add(item6);
     		menu4.addSeparator();//这是分割符

     		//建立工具条按键
		
     		//建立工具条对象，并将按键依次加入
		bar = new JToolBar();
     		
 
		//在面板中摆放工具条
     		BorderLayout bord = new BorderLayout();//先设置布局
     		p.setLayout(bord);
     		p.add("North",bar);    //再依据布局，指定工具条位置
     		f.setVisible(true);
     		f.setSize(WIDTH,HEIGHT);
          
		// 创建一个文本区域，用于输出相关信息
        		final JTextArea textArea = new JTextArea();
        		textArea.setLineWrap(true);
		        p.add("Center",textArea);    //依据布局，指定文本区域位置
		      
		//菜单中的菜单项和工具条中的工具项就是按键，按照点击按键的方法设置监听
       		// 添加 按钮 的点击动作监听器，并把相关信息输入到 文本区域
		ActionListener listen = new ActionListener(){
    			public void actionPerformed(ActionEvent e){
    				if(e.getSource()==item1)  {
    					generate(a);
    					for(int i=0;i<100;i++) {
    						String s= String.valueOf(a[i]);
    						textArea.append(s+" ");
    					}
    					textArea.append("\n\n");
    				}
      				if(e.getSource()==item2) {
      					 long startTime=System.currentTimeMillis();
                         sort1(a);
                         for(int i=0;i<100;i++) {
     						String s= String.valueOf(a[i]);
     						textArea.append(s+" ");
     					 }
                         long endTime=System.currentTimeMillis();
                         long time=endTime-startTime; 
                         JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
                         textArea.append("\n\n");
      				}
      				if(e.getSource()==item3) {
      					long startTime=System.currentTimeMillis();
      					sort2(a);
      					for(int i=0;i<100;i++) {
     						String s= String.valueOf(a[i]);
     						textArea.append(s+" ");
     					}
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
                        JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item4) {
      				
      				 String m = JOptionPane.showInputDialog("输入要查询的数");
      			         int b = Integer.parseInt(m);
      			       long startTime=System.currentTimeMillis();
      			         search1(a,b);
      			         textArea.append("最接近的数为"+find+"\n");
      			         textArea.append("位置为第"+num+"个\n");
      			       long endTime=System.currentTimeMillis();
                       long time=endTime-startTime; 
                       JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
      				}
      				if(e.getSource()==item5) {
      					
      					String n = JOptionPane.showInputDialog("输入要查询的数");
     			         int c = Integer.parseInt(n);
     			        long startTime=System.currentTimeMillis();
     			         search2(a,c);
     			         textArea.append("最接近的数为"+find+"\n");
     			         textArea.append("位置为第"+num+"个\n");
     			        long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
                        JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
      				}
      				if(e.getSource()==item6) {
      					System.exit(0);
      				}
      				
      			}
		};
		item1.addActionListener(listen);
   		item2.addActionListener(listen);
   		item3.addActionListener(listen);
   		item4.addActionListener(listen);
   		item5.addActionListener(listen);
   		item6.addActionListener(listen);
   		
 
	}
 
	public static void main(String[] args)
	{
		new Work3();
	}
}
