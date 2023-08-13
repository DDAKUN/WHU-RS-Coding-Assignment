package shixi;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.Scanner;

public class Work4 extends JFrame implements ActionListener{
	//类内变量，类中所有方法都能访问
	private JTextArea ta;  //文字域组件
 	private JFileChooser jfc=new  JFileChooser(new File("."));//对话框
    	private JButton bOpen,bSave;//按键
    	private JScrollPane ps;//滚动条

    	public Work4(){	//建立一个操作窗口

        		ta=new JTextArea(10,20);   //窗口中一个字符显示区
        		ps=new JScrollPane(ta);     //窗口水平、垂直卷动条
        		bOpen=new JButton("选择文件");  //窗口中一个“选择文件”按键
        		bSave=new JButton("保存文件");   //窗口中一个“保存文件”按键

        		bOpen.addActionListener(this);    //两个按键添加点击事件监听器
        		bSave.addActionListener(this);

        		this.add(ps);  //卷动跳加入窗口
        		this.add(bOpen);  //按键加入窗口
        		this.add(bSave);
       		this.setTitle("文件选择器的使用");  //设置窗口属性
        		this.setLayout(new FlowLayout(FlowLayout.CENTER,15,10));
        		this.setSize(300,300);
        		this.setLocationRelativeTo(null);
        		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        		this.setVisible(true);  //显示窗口


    	}

    	@Override
    	public void actionPerformed(ActionEvent e) {

          		JButton jbt= (JButton) e.getSource();
          		//1.点击bOpen要做的事为
          		if(jbt==bOpen){
              			//打开文件选择器对话框
              			int status=jfc.showOpenDialog(this);
              			//没有选打开按钮结果提示
                 			if(status!=JFileChooser.APPROVE_OPTION){
                     			ta.setText("没有选中文件");
                 			}
                 			else{

                     			try {
                         				//被选中的文件保存为文件对象
                         				File file=jfc.getSelectedFile();
                         				Scanner scanner=new Scanner(file);
                         				String info="";
                         				while(scanner.hasNextLine()){
                             					String str=scanner.nextLine();
                             					info+=str+"\r\n";
                         				}
                         				//把读取的数据存到文本框中
                         				ta.setText(info);

                    			} catch (FileNotFoundException e1) {
                        				System.out.println("系统没有找到此文件");
                        				e1.printStackTrace();
                    			}


                 			}

            		} 
          		//2.点击bSave要做的事
          		else{
                 		int re=jfc.showOpenDialog(this);
                 		if(re==JFileChooser.APPROVE_OPTION){
                     		File f=jfc.getSelectedFile();
                     		try {      //保存文件操作
                        			FileOutputStream fsp=new FileOutputStream(f);
                        			BufferedOutputStream out=new BufferedOutputStream(fsp);
                        			//将文本内容转换为字节存到字节数组
                        			byte[] b=(ta.getText()).getBytes();
                        			//将数组b中的全部内容写到out流对应的文件中
                        			out.write(b, 0, b.length);
                        			out.close();
                    		} catch (FileNotFoundException e1) {
                        			System.out.println("系统没有找到此文件"); 
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
