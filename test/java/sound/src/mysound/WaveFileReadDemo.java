package mysound;


import javax.swing.JFrame;


public class WaveFileReadDemo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String filename = "C:\\Users\\Cooly\\Desktop\\����ӽ�1-л��.wav";
		JFrame frame = new JFrame();
		WaveFileReader reader = new WaveFileReader(filename);
		System.out.println(reader.getDataLen());
		if(reader.isSuccess()){
			int[] data = reader.getData()[0]; //��ȡ��һ����
			DrawPanel drawPanel = new DrawPanel(data); // ����һ�����Ʋ��ε����
			frame.add(drawPanel);
			frame.setTitle(filename);
			frame.setSize(800, 400);
			frame.setLocationRelativeTo(null);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		}
		else{
			System.err.println(filename + "����һ��������wav�ļ�");
		}	
	}
}