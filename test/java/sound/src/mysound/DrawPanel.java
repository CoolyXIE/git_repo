package mysound;
// filename: DrawPanel.java
// RobinTang
// 2012-08-23

import java.awt.Color;
import java.awt.Graphics;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;

import javax.swing.JPanel;


@SuppressWarnings("serial")
public class DrawPanel extends JPanel {
	private int[] data = null;
	
	public DrawPanel(int[] data) {
		this.data = data;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		int ww = getWidth();
		int hh = getHeight();
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, ww, hh);
		
		int len = data.length;
		int step = len/ww;
		if(step==0)
			step = 1;
		
		int prex = 0, prey = 0;	//��һ������
		int x = 0, y = 0;
		
		g.setColor(Color.RED);
		double k = hh/2.0/32768.0;
		BufferedWriter bw = FileHelper.writeFile("C:\\Users\\Cooly\\Desktop\\1.txt", false);
		for(int i=0; i<ww; ++i){
			x = i;
			
			// �����Ǹ�����ȡ��������
			// ʵ����Ӧ�ð��ղ����������ü��
			y = hh-(int)(data[i*3]*k+hh/2);
			
			try {
				bw.write(y + " ");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if(i!=0){
				g.drawLine(x, y, prex, prey);
			}
			prex = x;
			prey = y;
		}
		try {
			bw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}