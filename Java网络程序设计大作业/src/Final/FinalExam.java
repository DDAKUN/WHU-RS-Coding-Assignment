package Final;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;




public class FinalExam {
	int[] a =new int[100000]; 
	static int find,num;//定义全局变量
	public void run() {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
	}

	public void sort1(int a[]) {//冒泡排序（升序）
        int temp=0,i,j;
        progressbar.setValue(0);
        for(i=0;i<a.length;i++)
        { 
        	progressbar.setValue((i+1)/1000);
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
		  progressbar.setValue(0);
    	    for (i=0;i<a.length;i++)//两次循环
    	    {
    	    	progressbar.setValue((i+1)/1000);
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
	
	
	public void sort3(int[] a){//选择排序（升序）
	    for(int i = 0; i < a.length - 1 ; i++){
	        int min = i; // 遍历的区间最小的值
	        for (int j = i + 1; j < a.length ;j++){
	             if(a[j] < a[min]){
	                 // 找到当前遍历区间最小的值的索引
	                 min = j;
	             }
	        }
	        if(min != i){
	            // 发生了调换
	            int temp =  a[min];
	            a[min] = a[i];
	            a[i] = temp;
	        }
	    }
	}

	
	/**
	* 归并排序
	*/
	public static void sort4(int[] a) {
	    sort(a,0,a.length-1);
	}
	 
	public static void sort(int[] data,int left,int right) {
	    if(left >= right) return;
	    //找出中间索引
	    int center = (left + right)/2;
	    //对左边数组进行递归
	    sort(data, left, center);
	    //对右边数组进行递归
	    sort(data, center+1, right);
	    //合并
	    merge(data,left,center,right);
	}
		
	public static void merge(int[] data,int left, int center,int right) {
	    //临时数组
	    int[] tmpArr = new int[data.length];
	    //右数组第一个元素索引
	    int mid = center + 1;
	    //third 记录临时数组的索引
	    int third = left;
	    //缓存左数组第一个元素的索引
	    int tmp = left;
	    while (left <= center && mid <=right) {
	        //从两个数组中取出最小的放入临时数组
	        if (data[left] <= data[mid]) {
	            tmpArr[third++] = data[left++];
	        } else {
	            tmpArr[third++] = data[mid++];
	        }
	    }
	    //剩余部分依次放入临时数组（实际上两个while只会执行其中一个）
	    while(mid <= right) {
	        tmpArr[third++] = data[mid++];
	    }
	    while(left <= center) {
	        tmpArr[third++] = data[left++];
	    }
	    //将临时数组中的内容拷贝回原数组中
	    while (tmp <= right) {
	        data[tmp] = tmpArr[tmp++];
	    }
	}
	
	
	public void search1(int arr[],int a) {
        int i;//顺序查找
        int temp=20000;//定义一个巨大值
        for (i = 0; i < arr.length; i++) {
        	if(Math.abs(arr[i]-a)==0) {
        		 find=arr[i];
                 num=i+1;//进行比较，找出谁更接近
                 break;
        	}
        	if(Math.abs(arr[i]-a)<temp) {
               temp=Math.abs(arr[i]-a);
               find=arr[i];
               num=i+1;//进行比较，找出谁更接近
        	}
        	progressbar.setValue((i+1)/1000);
        }
	}
	
	public void search2(int arr[],int a) {
	        int min = 0;//折半查找
			int max = arr.length-1;
			int mid=0;
			int temp=20000;
			while (min <= max) {
				mid = (min + max) / 2;
				if(Math.abs(arr[mid]-a)==temp) {
		               temp=Math.abs(arr[mid]-a);
		               find=arr[mid];
		               num=mid+1;
		        	}//进行比较
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
	
	static final int WIDTH=640;
	static final int HEIGHT=498;
	private JFileChooser jfc=new  JFileChooser(new File("."));//对话框
	JFrame f;
	JPanel p;
	JToolBar bar;
	JProgressBar progressbar;
	public FinalExam(){
		//设置窗口参数
		 f = new JFrame("数组测试");
		 f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//建立菜单棒对象并加入窗口
		JMenuBar menubar1 = new JMenuBar();
		f.setJMenuBar(menubar1);

 		//建立面板并加入窗口
		p = new JPanel();
 		f.setContentPane(p);
 		
	       
		//建立菜单项
 		JMenu menu1=new JMenu("文件");
		JMenu menu2=new JMenu("数据排序");
     	JMenu menu3=new JMenu("数据查询");
     	JMenu menu4=new JMenu("退出");	
		//将菜单项依次加入菜单棒
     		menubar1.add(menu1);
     		menubar1.add(menu2);
     		menubar1.add(menu3);
     		menubar1.add(menu4);
 		//建立子菜单项
		JMenuItem item1=new JMenuItem("选择文件");
		JMenuItem item2=new JMenuItem("冒泡排序（升序)");
     	JMenuItem item3=new JMenuItem("交换排序（降序）");
     	JMenuItem item4=new JMenuItem("顺序查找");
     	JMenuItem item5=new JMenuItem("折半查找");
     	JMenuItem item6=new JMenuItem("退出");
     	JMenuItem item7 =new JMenuItem("保存文件（文件名格式为xxx.txt）");
     	JMenuItem item8=new JMenuItem("选择排序（升序)");
     	JMenuItem item9=new JMenuItem("归并排序（升序）");
     	
     	//加载子菜单图片
     	ImageIcon logo1 = new ImageIcon(getClass().getResource("fasong.png"));
        //图片压缩，只需改动20与15自行设置
        Image oldLogo1 = logo1.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        ImageIcon newLogo1 = new ImageIcon(oldLogo1);
        item1.setIcon(newLogo1);
        menu1.setIcon(newLogo1);
        
        ImageIcon logo2 = new ImageIcon(getClass().getResource("baocun.png"));
        Image oldLogo2 = logo2.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        ImageIcon newLogo2 = new ImageIcon(oldLogo2);
        item7.setIcon(newLogo2);
        
        
        ImageIcon logo3 = new ImageIcon(getClass().getResource("bianji.png"));
        Image oldLogo3 = logo3.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        ImageIcon newLogo3 = new ImageIcon(oldLogo3);
        item2.setIcon(newLogo3);
        item3.setIcon(newLogo3);
        item8.setIcon(newLogo3);
        item9.setIcon(newLogo3);
        menu2.setIcon(newLogo3);
        
        ImageIcon logo4 = new ImageIcon(getClass().getResource("sousuo.png"));
        Image oldLogo4 = logo4.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        ImageIcon newLogo4 = new ImageIcon(oldLogo4);
        item4.setIcon(newLogo4);
        item5.setIcon(newLogo4);
        menu3.setIcon(newLogo4);
        
        ImageIcon logo5 = new ImageIcon(getClass().getResource("dianzan.png"));
        Image oldLogo5 = logo5.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        ImageIcon newLogo5 = new ImageIcon(oldLogo5);
        item6.setIcon(newLogo5);
        menu4.setIcon(newLogo5);
        
        ImageIcon logo6 = new ImageIcon(getClass().getResource("shoucang.png"));
        Image oldLogo6 = logo6.getImage().getScaledInstance(20,15,Image.SCALE_SMOOTH);
        f.setIconImage(oldLogo6);
        
      
       
    	
 
    	

 		//子菜单项依次加入菜单项
     		menu1.add(item1);
     		menu1.addSeparator();//这是分割符
     		menu1.add(item7);
 
 
     		menu2.add(item2);
     		menu2.addSeparator();
     		menu2.add(item3);
     		menu2.addSeparator();
     		menu2.add(item8);
     		menu2.addSeparator();
     		menu2.add(item9);
 
     		menu3.add(item4);
     		menu3.addSeparator();
     		menu3.add(item5);
            
     		menu4.add(item6);
     		menu4.addSeparator();//这是分割符

     		//建立工具条按键
		
     		//建立工具条对象，并将按键依次加入
		     bar = new JToolBar();
		     progressbar =new JProgressBar();
		     progressbar.setStringPainted(true);
		//在面板中摆放工具条，进度条
     		BorderLayout bord = new BorderLayout();//先设置布局
     		p.setLayout(bord);
     		p.add("North",bar);    //再依据布局，指定工具条位置
     		f.setVisible(true);
     		f.setSize(WIDTH,HEIGHT);
            p.add("South",progressbar);
            
		// 创建一个文本区域，用于输出相关信息
            final ImageIcon imageIcon = new ImageIcon(getClass().getResource("beijing.jpeg"));
        		JTextArea textArea = new JTextArea(){
        		      Image image = imageIcon.getImage();

        		      Image grayImage = GrayFilter.createDisabledImage(image);
        		      {
        		        setOpaque(false);
        		      }

        		      public void paint(Graphics g) {
        		        g.drawImage(grayImage, 0, 0, this);
        		        super.paint(g);
        		      }
        		};
        		textArea.setLineWrap(true);
		        p.add("Center",new JScrollPane(textArea));    //依据布局，指定文本区域位，并添加滚动条
		       
		//菜单中的菜单项和工具条中的工具项就是按键，按照点击按键的方法设置监听
       		// 添加 按钮 的点击动作监听器，并把相关信息输入到 文本区域
		ActionListener listen = new ActionListener(){
    			public void actionPerformed(ActionEvent e){
    				
      				if(e.getSource()==item2) {
      					progressbar.setValue(0);
      					 long startTime=System.currentTimeMillis();//定义开始时间
                         sort1(a);
                         long endTime=System.currentTimeMillis();//定义结束时间
                         long time=endTime-startTime; //计算花费时间
     
     				     textArea.append("排序成功，请自行保存！\n");
                    
                         JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
                         textArea.append("\n\n");
                         
      					 
      				}
      				if(e.getSource()==item3) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort2(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("排序成功，请自行保存！\n");
                        JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item8) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort3(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("排序成功，请自行保存！\n");
                        JOptionPane.showMessageDialog(null, "花费时间为："+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item9) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort4(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("排序成功，请自行保存！\n");
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
      				if(e.getSource()==item1){
              			//打开文件选择器对话框
              			int status=jfc.showOpenDialog(f);
              			//没有选打开按钮结果提示
                 			if(status!=JFileChooser.APPROVE_OPTION){
                     			textArea.append("没有选中文件");
                 			}
                 			else{

                     			try {
                         				//被选中的文件保存为文件对象
                         				File file=jfc.getSelectedFile();
                         				Scanner scanner=new Scanner(file);
                         			    int j=0;
                         			   //逐行读取
                         				while(scanner.hasNextLine()){
                         					
                         					String str=scanner.nextLine();
                         					a[j] = Integer.parseInt(str);
                             				j++;
                             				progressbar.setValue((j+1)/1000);//显示进度
                         				}
                         				//把读取的数据存到文本框中
                         				for(int i=0;i<a.length;i++) {
                         					String s= String.valueOf(a[i]);
                         					textArea.append(s+"\n");
                         					progressbar.setValue((i+1)/1000);//显示进度
                         				}
                         				textArea.append("全部读取完成！\n\n");

                    			} catch (FileNotFoundException e1) {
                        				System.out.println("系统没有找到此文件");
                        				e1.printStackTrace();
                    			}


                 			}

            		} 
      				if(e.getSource()==item7) {
      				int re=jfc.showOpenDialog(f);
             		if(re==JFileChooser.APPROVE_OPTION){
                 		File f=jfc.getSelectedFile();
                 		try {      //保存文件操作
                    			BufferedWriter writer =new BufferedWriter(new FileWriter(f));
                    			
                                //将数组a中的全部内容写到writer流对应的文件中
                    			for(int i=0;i<a.length;i++) {
                    			   String s= String.valueOf(a[i]);//转换整形为数值型
         						   writer.write(s);
         						   writer.write("\n");
         						   writer.flush();//刷新文件流，防止数据丢失
                    			}
                    			writer.close();
                		} catch (FileNotFoundException e1) {
                    			System.out.println("系统没有找到此文件"); 
                    	} catch (IOException e1) {
                        		System.out.println("IOException");
                		}
             	      }
      				}
      			}
		};
		item1.addActionListener(listen);
   		item2.addActionListener(listen);
   		item3.addActionListener(listen);
   		item4.addActionListener(listen);
   		item5.addActionListener(listen);
   		item6.addActionListener(listen);
   		item7.addActionListener(listen);
   		item8.addActionListener(listen);
   		item9.addActionListener(listen);
 
	}
 
	public static void main(String[] args)
	{
		FinalExam demo1=new FinalExam();
		
	}
}
