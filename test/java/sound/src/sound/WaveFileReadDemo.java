package sound;
// WaveFileReadDemo.jave
// RobinTang
// 2012-08-23

import javax.swing.JFrame;


public class WaveFileReadDemo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String filename = "C:\\Users\\Cooly\\Desktop\\青橙视界2-谢柯.wav";
		JFrame frame = new JFrame();
		WaveFileReader reader = new WaveFileReader(filename);
		if(reader.isSuccess()){
			int[] data = reader.getData()[0]; //获取第一声道
			DrawPanel drawPanel = new DrawPanel(data); // 创建一个绘制波形的面板
			frame.add(drawPanel);
			frame.setTitle(filename);
//			frame.setSize(800, 400);
			frame.setSize(400, 200);
			frame.setLocationRelativeTo(null);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		}
		else{
			System.err.println(filename + "不是一个正常的wav文件");
		}	
	}
}
