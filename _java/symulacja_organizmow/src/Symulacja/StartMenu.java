package Symulacja;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StartMenu extends JFrame {
    int buttonNum=0;
    public boolean exit=false;

    private JButton nowaGra = new JButton();
    private JButton wyjdz = new JButton();
    private JButton wczytaj = new JButton();
    public StartMenu(){
        super();
        Layout();
        Options();
        this.setVisible(true);
    }
    private void Options(){
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Symulacja organizmow, s188627");
        this.setResizable(false);
        this.setUndecorated(true);
        this.setLocationRelativeTo(null);
        this.setBackground(new Color(1.0f,1.0f,1.0f,0.0f));
        this.setLayout(new GridBagLayout());
    }
    private void Layout(){
        final ImageIcon tlo = new ImageIcon("background.png");
        JLabel label = new JLabel();
        label.setText("Symulacja organizmow");

        label.setIcon(tlo);
        label.setVerticalAlignment(JLabel.CENTER);
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setLayout(null);
        JLabel label2 = new JLabel("Symulacja organizmow");
        label2.setFont(new Font("Rockwell", Font.PLAIN, 20));
        label2.setHorizontalAlignment(JLabel.CENTER);
        label2.setBounds((tlo.getIconWidth()-300)/2,60,300,30);
        JLabel label3 = new JLabel("s188627");
        label3.setFont(new Font("Rockwell", Font.PLAIN, 20));
        label3.setHorizontalAlignment(JLabel.CENTER);
        label3.setBounds((tlo.getIconWidth()-200)/2,30,200,30);


        nowaGra.setBounds((tlo.getIconWidth()-200)/2,390,200,35);
        nowaGra.setFont(new Font("Rockwell", Font.PLAIN, 15));
        nowaGra.setText("Nowagra");
        wczytaj.setBounds((tlo.getIconWidth()-200)/2,425,200,35);
        wczytaj.setFont(new Font("Rockwell", Font.PLAIN, 15));
        wczytaj.setText("Wczytaj");

        wyjdz.setBounds((tlo.getIconWidth()-200)/2,460,200,35);
        wyjdz.setFont(new Font("Rockwell", Font.PLAIN, 15));
        wyjdz.setText("Wyjdz");

        label.add(label2);
        label.add(label3);
        label.add(nowaGra);
        label.add(wczytaj);
        label.add(wyjdz);

        wyjdz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=3;
            }
        });
        wczytaj.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=2;
            }
        });
        nowaGra.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=1;
            }
        });
        this.add(label);
////        JLabel background = new JLabel("", tlo, JLabel.CENTER);
//        JLabel title = new JLabel();
//        title.setText("addad");
//        background.add(title, JLabel.CENTER);
//        background.setBounds(0,0,background.getWidth(), background.getHeight());
//        title.setBackground(new Color(1.0f,1.0f,1.0f,1.0f));
//        title.setHorizontalAlignment(JLabel.CENTER);
//        title.setVerticalAlignment(JLabel.CENTER);
//        this.add(background);
//        this.add(title);
        this.setSize(tlo.getIconWidth(),tlo.getIconHeight());

    }

}
