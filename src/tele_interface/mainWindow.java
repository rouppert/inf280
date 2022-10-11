package tele_interface;

import tele_interface.Client;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;


public class mainWindow extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JTextArea textZone;
	JScrollPane scrollPane;
	JMenuBar menuBar;
	JToolBar toolBar;
	Client client;
	int height = 800;
	int length = 200;
	
	public static void main (String argv[]) {
		new mainWindow();
	}
	
	public mainWindow() {
		createTextArea();
		createMenuBar();
		createToolBar();
		launchClient();
		drawComponents();
	}
	
	public void launchClient() {
		try {
			client = new Client("localhost", 3331);	
		}
		catch(Exception e) {}
	}
	
	public void createTextArea() {
		textZone = new JTextArea(4, 4);
		scrollPane = new JScrollPane(textZone);
	}
	
	public void createMenuBar() {
		menuBar = new JMenuBar();
		JMenu menu1 = new JMenu("Menu");
		JMenu submenu1 = new JMenu("Write");
		JMenu submenu2 = new JMenu("Options");
		JMenuItem Item1 = new JMenuItem(new WriteLine1());
		JMenuItem Item2 = new JMenuItem(new WriteLine2());
		//JMenuItem exitItem = new JMenuItem(new Exit());
		submenu1.add(Item1);
		submenu1.add(Item2);
		//submenu2.add(exitItem);
		menu1.add(submenu1);
		menu1.add(submenu2);
		menuBar.add(menu1);
		//setSize(new Dimension(200, 200));
	}
	
	public void createToolBar() {
		GridLayout toolBarLayout = new GridLayout(3, 1);
		ImageIcon findIcon = resizeIcon(new ImageIcon(mainWindow.class.getResource("/ressources/searching-magnifying-glass.png")), length, length);
		ImageIcon playIcon = resizeIcon(new ImageIcon(mainWindow.class.getResource("/ressources/play-button-arrowhead.png")), length, length);
		ImageIcon exitIcon = resizeIcon(new ImageIcon(mainWindow.class.getResource("/ressources/power.png")), length, length);
		toolBar = new JToolBar();
		//JButton Button1 = new JButton(new WriteLine1());
		//JButton Button2 = new JButton(new WriteLine2());
		JButton exitButton = new JButton(new Exit(exitIcon));
		JButton findButton = new JButton(new mediaButton("find", findIcon));
		JButton playButton = new JButton(new mediaButton("play", playIcon));
		//toolBar.add(Button1);
		//toolBar.add(Button2);
		exitButton.setSize(new Dimension(length, length));
		findButton.setSize(new Dimension(length, length));
		playButton.setSize(new Dimension(length, length));
		toolBar.setLayout(toolBarLayout);
		toolBar.add(exitButton);
		toolBar.add(findButton);
		toolBar.add(playButton);
		toolBar.setFloatable( false);
	}
	
	public void drawComponents() {
		//setLayout(mainLayout);
		add(menuBar, BorderLayout.NORTH);
		add(toolBar, BorderLayout.CENTER);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Main");
		pack();
		//setSize(length, height);
		//setResizable(false);
		setVisible(true);
	}
	
	private static ImageIcon resizeIcon(ImageIcon icon, int resizedWidth, int resizedHeight) {
	    Image img = icon.getImage();  
	    Image resizedImage = img.getScaledInstance(resizedWidth, resizedHeight,  java.awt.Image.SCALE_SMOOTH);  
	    return new ImageIcon(resizedImage);
	}
	
	class WriteLine1 extends AbstractAction {
		public WriteLine1() {
			super("Write Line 1");
		}
		public void actionPerformed(ActionEvent e) {
			textZone.append("Telecom devant Centrale au classement l'Etudiant \n");
		}
	}
	
	class WriteLine2 extends AbstractAction {
		public WriteLine2() {
			super("Write Line 2");
		}
		public void actionPerformed(ActionEvent e) {
			textZone.append("Allez les Verts \n");
		}
	}
	
	class Exit extends AbstractAction {
		public Exit(ImageIcon icon) {
			super("", icon);
		}
		public void actionPerformed(ActionEvent e) {
			System.exit(0);
		}
	}
	
	class mediaButton extends AbstractAction {
		String searchedMedia;
		String request = "find";
		public mediaButton(String request_, ImageIcon icon) {
			super("", icon);
			this.request = request_;
		}
		
		public void actionPerformed(ActionEvent e) {
			searchedMedia = JOptionPane.showInputDialog("Which media do you want to " + this.request + "?");
			client.send(this.request + " " + searchedMedia);
			System.out.println(this.request + "find");
		}
	}
}
