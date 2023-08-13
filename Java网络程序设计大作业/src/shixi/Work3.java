package shixi;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Work3{
	int[] a =new int[100]; 
	static int find,num;//����ȫ�ֱ���
	public void generate(int a[]){
	    Random ran = new Random();
	    for (int i = 0; i < 100; i++) {
	        a[i] = ran.nextInt(100);//�����������
	    }
	}
	
	
	public void sort1(int a[]) {//ð����������
        int temp=0,i,j;
        for(i=0;i<a.length;i++)
        {
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
    	    for (i=0;i<a.length;i++)//����ѭ��
    	    {
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
	
	
	public void search1(int arr[],int a) {
        int i;//˳�����
        int temp=20000;//����һ���޴�ֵ
        for (i = 0; i < 99; i++) {
        	if(Math.abs(arr[i]-a)<temp) {
               temp=Math.abs(arr[i]-a);
               find=arr[i];
               num=i+1;//���бȽϣ��ҳ�˭���ӽ�
        	}
        }
	}
	
	public void search2(int arr[],int a) {
	        int min = 0;//�۰����
			int max = arr.length-1;
			int mid=0;
			int temp=20000;
			while (min <= max) {
				mid = (min + max) / 2;
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
	static final int WIDTH=600;
	static final int HEIGHT=400;
	
	JFrame f;
	JPanel p;
	JToolBar bar;
	public Work3(){
		//���ô��ڲ���
		 f = new JFrame("�������");
		 f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 		
		//�����˵������󲢼��봰��
		JMenuBar menubar1 = new JMenuBar();
		f.setJMenuBar(menubar1);

 		//������岢���봰��
		p = new JPanel();
 		f.setContentPane(p);
 		 JOptionPane.showMessageDialog(null, "�ܼҺ�����"); 
		//�����˵���
 		JMenu menu1=new JMenu("��������");
		JMenu menu2=new JMenu("��������");
     	JMenu menu3=new JMenu("���ݲ�ѯ");
     	JMenu menu4=new JMenu("�˳�");	
		//���˵������μ���˵���
     		menubar1.add(menu1);
     		menubar1.add(menu2);
     		menubar1.add(menu3);
     		menubar1.add(menu4);
 		//�����Ӳ˵���
		JMenuItem item1=new JMenuItem("�����������");
		JMenuItem item2=new JMenuItem("ð������");
     		JMenuItem item3=new JMenuItem("��������");
     		JMenuItem item4=new JMenuItem("˳�����");
     		JMenuItem item5=new JMenuItem("�۰����");
     		JMenuItem item6=new JMenuItem("�˳�");
     	
 
 
 		//�Ӳ˵������μ���˵���
     		menu1.add(item1);
     		menu1.addSeparator();//���Ƿָ��
     		
 
 
     		menu2.add(item2);
     		menu2.addSeparator();
     		menu2.add(item3);
 
     		menu3.add(item4);
     		menu3.addSeparator();
     		menu3.add(item5);
            
     		menu4.add(item6);
     		menu4.addSeparator();//���Ƿָ��

     		//��������������
		
     		//�������������󣬲����������μ���
		bar = new JToolBar();
     		
 
		//������аڷŹ�����
     		BorderLayout bord = new BorderLayout();//�����ò���
     		p.setLayout(bord);
     		p.add("North",bar);    //�����ݲ��֣�ָ��������λ��
     		f.setVisible(true);
     		f.setSize(WIDTH,HEIGHT);
          
		// ����һ���ı�����������������Ϣ
        		final JTextArea textArea = new JTextArea();
        		textArea.setLineWrap(true);
		        p.add("Center",textArea);    //���ݲ��֣�ָ���ı�����λ��
		      
		//�˵��еĲ˵���͹������еĹ�������ǰ��������յ�������ķ������ü���
       		// ��� ��ť �ĵ�����������������������Ϣ���뵽 �ı�����
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
                         JOptionPane.showMessageDialog(null, "����ʱ��Ϊ��"+time+"ms"); 
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
