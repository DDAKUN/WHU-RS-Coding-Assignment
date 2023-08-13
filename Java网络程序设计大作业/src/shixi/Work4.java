package shixi;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.Scanner;

public class Work4 extends JFrame implements ActionListener{
	//���ڱ������������з������ܷ���
	private JTextArea ta;  //���������
 	private JFileChooser jfc=new  JFileChooser(new File("."));//�Ի���
    	private JButton bOpen,bSave;//����
    	private JScrollPane ps;//������

    	public Work4(){	//����һ����������

        		ta=new JTextArea(10,20);   //������һ���ַ���ʾ��
        		ps=new JScrollPane(ta);     //����ˮƽ����ֱ����
        		bOpen=new JButton("ѡ���ļ�");  //������һ����ѡ���ļ�������
        		bSave=new JButton("�����ļ�");   //������һ���������ļ�������

        		bOpen.addActionListener(this);    //����������ӵ���¼�������
        		bSave.addActionListener(this);

        		this.add(ps);  //�������봰��
        		this.add(bOpen);  //�������봰��
        		this.add(bSave);
       		this.setTitle("�ļ�ѡ������ʹ��");  //���ô�������
        		this.setLayout(new FlowLayout(FlowLayout.CENTER,15,10));
        		this.setSize(300,300);
        		this.setLocationRelativeTo(null);
        		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        		this.setVisible(true);  //��ʾ����


    	}

    	@Override
    	public void actionPerformed(ActionEvent e) {

          		JButton jbt= (JButton) e.getSource();
          		//1.���bOpenҪ������Ϊ
          		if(jbt==bOpen){
              			//���ļ�ѡ�����Ի���
              			int status=jfc.showOpenDialog(this);
              			//û��ѡ�򿪰�ť�����ʾ
                 			if(status!=JFileChooser.APPROVE_OPTION){
                     			ta.setText("û��ѡ���ļ�");
                 			}
                 			else{

                     			try {
                         				//��ѡ�е��ļ�����Ϊ�ļ�����
                         				File file=jfc.getSelectedFile();
                         				Scanner scanner=new Scanner(file);
                         				String info="";
                         				while(scanner.hasNextLine()){
                             					String str=scanner.nextLine();
                             					info+=str+"\r\n";
                         				}
                         				//�Ѷ�ȡ�����ݴ浽�ı�����
                         				ta.setText(info);

                    			} catch (FileNotFoundException e1) {
                        				System.out.println("ϵͳû���ҵ����ļ�");
                        				e1.printStackTrace();
                    			}


                 			}

            		} 
          		//2.���bSaveҪ������
          		else{
                 		int re=jfc.showOpenDialog(this);
                 		if(re==JFileChooser.APPROVE_OPTION){
                     		File f=jfc.getSelectedFile();
                     		try {      //�����ļ�����
                        			FileOutputStream fsp=new FileOutputStream(f);
                        			BufferedOutputStream out=new BufferedOutputStream(fsp);
                        			//���ı�����ת��Ϊ�ֽڴ浽�ֽ�����
                        			byte[] b=(ta.getText()).getBytes();
                        			//������b�е�ȫ������д��out����Ӧ���ļ���
                        			out.write(b, 0, b.length);
                        			out.close();
                    		} catch (FileNotFoundException e1) {
                        			System.out.println("ϵͳû���ҵ����ļ�"); 
	                    	} catch (IOException e1) {
	                        		System.out.println("IOException");
                    		}
                 	      }
            		}
    	}
    	public static void main(String[] args) {
        		Work4 fc=new Work4();
    	}
}
