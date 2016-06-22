package mysound;


import javax.swing.JFrame;


public class WaveFileReadDemo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String filename = "C:\\Users\\Cooly\\Desktop\\青橙视界1-谢柯.wav";
		JFrame frame = new JFrame();
		WaveFileReader reader = new WaveFileReader(filename);
		System.out.println(reader.getDataLen());
		if(reader.isSuccess()){
			int[] data = reader.getData()[0]; //获取第一声道
			DrawPanel drawPanel = new DrawPanel(data); // 创建一个绘制波形的面板
			frame.add(drawPanel);
			frame.setTitle(filename);
			frame.setSize(800, 400);
			frame.setLocationRelativeTo(null);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		}
		else{
			System.err.println(filename + "不是一个正常的wav文件");
		}	
	}
}
