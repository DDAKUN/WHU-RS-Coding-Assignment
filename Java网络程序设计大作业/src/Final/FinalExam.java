package Final;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;




public class FinalExam {
	int[] a =new int[100000]; 
	static int find,num;//����ȫ�ֱ���
	public void run() {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
	}

	public void sort1(int a[]) {//ð����������
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
                    a[j+1]=temp;//ð�ݽ���
                }
            }
        }
	}
	
	public void sort2(int a[]) {//�������򣨽���
		  int i,j,temp;
		  progressbar.setValue(0);
    	    for (i=0;i<a.length;i++)//����ѭ��
    	    {
    	    	progressbar.setValue((i+1)/1000);
    	        for (j=i+1;j<a.length;j++)
    	        {
    	            if(a[j]>a[i])//�����ұߴ�������򽻻�
    	            {
    	                temp=a[j];
    	                a[j]=a[i];
    	                a[i]=temp;
    	            }
    	        }        
    	    }
	}
	
	
	public void sort3(int[] a){//ѡ����������
	    for(int i = 0; i < a.length - 1 ; i++){
	        int min = i; // ������������С��ֵ
	        for (int j = i + 1; j < a.length ;j++){
	             if(a[j] < a[min]){
	                 // �ҵ���ǰ����������С��ֵ������
	                 min = j;
	             }
	        }
	        if(min != i){
	            // �����˵���
	            int temp =  a[min];
	            a[min] = a[i];
	            a[i] = temp;
	        }
	    }
	}

	
	/**
	* �鲢����
	*/
	public static void sort4(int[] a) {
	    sort(a,0,a.length-1);
	}
	 
	public static void sort(int[] data,int left,int right) {
	    if(left >= right) return;
	    //�ҳ��м�����
	    int center = (left + right)/2;
	    //�����������еݹ�
	    sort(data, left, center);
	    //���ұ�������еݹ�
	    sort(data, center+1, right);
	    //�ϲ�
	    merge(data,left,center,right);
	}
		
	public static void merge(int[] data,int left, int center,int right) {
	    //��ʱ����
	    int[] tmpArr = new int[data.length];
	    //�������һ��Ԫ������
	    int mid = center + 1;
	    //third ��¼��ʱ���������
	    int third = left;
	    //�����������һ��Ԫ�ص�����
	    int tmp = left;
	    while (left <= center && mid <=right) {
	        //������������ȡ����С�ķ�����ʱ����
	        if (data[left] <= data[mid]) {
	            tmpArr[third++] = data[left++];
	        } else {
	            tmpArr[third++] = data[mid++];
	        }
	    }
	    //ʣ�ಿ�����η�����ʱ���飨ʵ��������whileֻ��ִ������һ����
	    while(mid <= right) {
	        tmpArr[third++] = data[mid++];
	    }
	    while(left <= center) {
	        tmpArr[third++] = data[left++];
	    }
	    //����ʱ�����е����ݿ�����ԭ������
	    while (tmp <= right) {
	        data[tmp] = tmpArr[tmp++];
	    }
	}
	
	
	public void search1(int arr[],int a) {
        int i;//˳�����
        int temp=20000;//����һ���޴�ֵ
        for (i = 0; i < arr.length; i++) {
        	if(Math.abs(arr[i]-a)==0) {
        		 find=arr[i];
                 num=i+1;//���бȽϣ��ҳ�˭���ӽ�
                 break;
        	}
        	if(Math.abs(arr[i]-a)<temp) {
               temp=Math.abs(arr[i]-a);
               find=arr[i];
               num=i+1;//���бȽϣ��ҳ�˭���ӽ�
        	}
        	progressbar.setValue((i+1)/1000);
        }
	}
	
	public void search2(int arr[],int a) {
	        int min = 0;//�۰����
			int max = arr.length-1;
			int mid=0;
			int temp=20000;
			while (min <= max) {
				mid = (min + max) / 2;
				if(Math.abs(arr[mid]-a)==temp) {
		               temp=Math.abs(arr[mid]-a);
		               find=arr[mid];
		               num=mid+1;
		        	}//���бȽ�
				if(Math.abs(arr[mid]-a)<temp) {
		               temp=Math.abs(arr[mid]-a);
		               find=arr[mid];
		               num=mid+1;
		        	}//���бȽ�
				else if (arr[mid] > a) {
					max = mid - 1;//���ڱ���λ
				} else {
					min = mid + 1;//ǰ�ڱ���λ
				}
			}
	}
	
	static final int WIDTH=640;
	static final int HEIGHT=498;
	private JFileChooser jfc=new  JFileChooser(new File("."));//�Ի���
	JFrame f;
	JPanel p;
	JToolBar bar;
	JProgressBar progressbar;
	public FinalExam(){
		//���ô��ڲ���
		 f = new JFrame("�������");
		 f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//�����˵������󲢼��봰��
		JMenuBar menubar1 = new JMenuBar();
		f.setJMenuBar(menubar1);

 		//������岢���봰��
		p = new JPanel();
 		f.setContentPane(p);
 		
	       
		//�����˵���
 		JMenu menu1=new JMenu("�ļ�");
		JMenu menu2=new JMenu("��������");
     	JMenu menu3=new JMenu("���ݲ�ѯ");
     	JMenu menu4=new JMenu("�˳�");	
		//���˵������μ���˵���
     		menubar1.add(menu1);
     		menubar1.add(menu2);
     		menubar1.add(menu3);
     		menubar1.add(menu4);
 		//�����Ӳ˵���
		JMenuItem item1=new JMenuItem("ѡ���ļ�");
		JMenuItem item2=new JMenuItem("ð����������)");
     	JMenuItem item3=new JMenuItem("�������򣨽���");
     	JMenuItem item4=new JMenuItem("˳�����");
     	JMenuItem item5=new JMenuItem("�۰����");
     	JMenuItem item6=new JMenuItem("�˳�");
     	JMenuItem item7 =new JMenuItem("�����ļ����ļ�����ʽΪxxx.txt��");
     	JMenuItem item8=new JMenuItem("ѡ����������)");
     	JMenuItem item9=new JMenuItem("�鲢��������");
     	
     	//�����Ӳ˵�ͼƬ
     	ImageIcon logo1 = new ImageIcon(getClass().getResource("fasong.png"));
        //ͼƬѹ����ֻ��Ķ�20��15��������
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
        
      
       
    	
 
    	

 		//�Ӳ˵������μ���˵���
     		menu1.add(item1);
     		menu1.addSeparator();//���Ƿָ��
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
     		menu4.addSeparator();//���Ƿָ��

     		//��������������
		
     		//�������������󣬲����������μ���
		     bar = new JToolBar();
		     progressbar =new JProgressBar();
		     progressbar.setStringPainted(true);
		//������аڷŹ�������������
     		BorderLayout bord = new BorderLayout();//�����ò���
     		p.setLayout(bord);
     		p.add("North",bar);    //�����ݲ��֣�ָ��������λ��
     		f.setVisible(true);
     		f.setSize(WIDTH,HEIGHT);
            p.add("South",progressbar);
            
		// ����һ���ı�����������������Ϣ
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
		        p.add("Center",new JScrollPane(textArea));    //���ݲ��֣�ָ���ı�����λ������ӹ�����
		       
		//�˵��еĲ˵���͹������еĹ�������ǰ��������յ�������ķ������ü���
       		// ��� ��ť �ĵ�����������������������Ϣ���뵽 �ı�����
		ActionListener listen = new ActionListener(){
    			public void actionPerformed(ActionEvent e){
    				
      				if(e.getSource()==item2) {
      					progressbar.setValue(0);
      					 long startTime=System.currentTimeMillis();//���忪ʼʱ��
                         sort1(a);
                         long endTime=System.currentTimeMillis();//�������ʱ��
                         long time=endTime-startTime; //���㻨��ʱ��
     
     				     textArea.append("����ɹ��������б��棡\n");
                    
                         JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
                         textArea.append("\n\n");
                         
      					 
      				}
      				if(e.getSource()==item3) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort2(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("����ɹ��������б��棡\n");
                        JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item8) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort3(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("����ɹ��������б��棡\n");
                        JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item9) {
      					progressbar.setValue(0);
      					long startTime=System.currentTimeMillis();
      					sort4(a);
      					long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
      					
      					 textArea.append("����ɹ��������б��棡\n");
                        JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
      					textArea.append("\n\n");
      				}
      				if(e.getSource()==item4) {
      				
      				     String m = JOptionPane.showInputDialog("����Ҫ��ѯ����");
      			         int b = Integer.parseInt(m);
      			         long startTime=System.currentTimeMillis();
      			         search1(a,b);
      			         textArea.append("��ӽ�����Ϊ"+find+"\n");
      			         textArea.append("λ��Ϊ��"+num+"��\n");
      			       long endTime=System.currentTimeMillis();
                       long time=endTime-startTime; 
                       JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
      				}
      				if(e.getSource()==item5) {
      					
      					String n = JOptionPane.showInputDialog("����Ҫ��ѯ����");
     			         int c = Integer.parseInt(n);
     			        long startTime=System.currentTimeMillis();
     			         search2(a,c);
     			         textArea.append("��ӽ�����Ϊ"+find+"\n");
     			         textArea.append("λ��Ϊ��"+num+"��\n");
     			        long endTime=System.currentTimeMillis();
                        long time=endTime-startTime; 
                        JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
      				}
      				if(e.getSource()==item6) {
      					System.exit(0);
      				}
      				if(e.getSource()==item1){
              			//���ļ�ѡ�����Ի���
              			int status=jfc.showOpenDialog(f);
              			//û��ѡ�򿪰�ť�����ʾ
                 			if(status!=JFileChooser.APPROVE_OPTION){
                     			textArea.append("û��ѡ���ļ�");
                 			}
                 			else{

                     			try {
                         				//��ѡ�е��ļ�����Ϊ�ļ�����
                         				File file=jfc.getSelectedFile();
                         				Scanner scanner=new Scanner(file);
                         			    int j=0;
                         			   //���ж�ȡ
                         				while(scanner.hasNextLine()){
                         					
                         					String str=scanner.nextLine();
                         					a[j] = Integer.parseInt(str);
                             				j++;
                             				progressbar.setValue((j+1)/1000);//��ʾ����
                         				}
                         				//�Ѷ�ȡ�����ݴ浽�ı�����
                         				for(int i=0;i<a.length;i++) {
                         					String s= String.valueOf(a[i]);
                         					textArea.append(s+"\n");
                         					progressbar.setValue((i+1)/1000);//��ʾ����
                         				}
                         				textArea.append("ȫ����ȡ��ɣ�\n\n");

                    			} catch (FileNotFoundException e1) {
                        				System.out.println("ϵͳû���ҵ����ļ�");
                        				e1.printStackTrace();
                    			}


                 			}

            		} 
      				if(e.getSource()==item7) {
      				int re=jfc.showOpenDialog(f);
             		if(re==JFileChooser.APPROVE_OPTION){
                 		File f=jfc.getSelectedFile();
                 		try {      //�����ļ�����
                    			BufferedWriter writer =new BufferedWriter(new FileWriter(f));
                    			
                                //������a�е�ȫ������д��writer����Ӧ���ļ���
                    			for(int i=0;i<a.length;i++) {
                    			   String s= String.valueOf(a[i]);//ת������Ϊ��ֵ��
         						   writer.write(s);
         						   writer.write("\n");
         						   writer.flush();//ˢ���ļ�������ֹ���ݶ�ʧ
                    			}
                    			writer.close();
                		} catch (FileNotFoundException e1) {
                    			System.out.println("ϵͳû���ҵ����ļ�"); 
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
