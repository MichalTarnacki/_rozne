package Symulacja;

import Symulacja.Rosliny.*;;
import Symulacja.Zwierzeta.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class WybierzZwierzeMenu extends JFrame {
    private Polozenie polozenie;
    public int buttonNum=0;
    Swiat swiat;

    public WybierzZwierzeMenu(Swiat swiat, Polozenie polozenie){
        this.swiat=swiat;
        this.polozenie=new Polozenie(polozenie);
        Options();
        Update();
        this.setVisible(true);
    }
    private void Options(){
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setTitle("Symulacja organizmow, s188627");
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setLayout(null);
        this.setSize(300,300);
    }

    private void Layout() {

    }
    public void Update(){
        Dimension buttonSize = new Dimension(this.getWidth()/4, (this.getHeight()-25)/3);
        PrzyciskZwierze but;
        String numer;
        for(int i=0; i<3; i++){
            for(int j=0; j<4; j++){
                numer=new String("" + i+j);
                but= new PrzyciskZwierze();
                but.setBounds(j*((int)buttonSize.getWidth()), i*((int)buttonSize.getHeight()), (int)buttonSize.getWidth(),(int)buttonSize.getHeight());
                if(numer.equals("00")){
                    but.setText("Barszcz");
                    but.UstawOrganizm(new BarszczSosnowskiego(swiat));
                }
                else if(numer.equals("01")){
                    but.setText("Guarana");
                    but.UstawOrganizm(new Guarana(swiat));
                }
                else if(numer.equals("02")){
                    but.setText("Mlecz");
                    but.UstawOrganizm(new Mlecz(swiat));
                }
                else if(numer.equals("03")){
                    but.setText("Trawa");
                    but.UstawOrganizm(new Trawa(swiat));
                }
                else if(numer.equals("10")){
                    but.setText("WilczeJagody");
                    but.UstawOrganizm(new WilczeJagody(swiat));
                }
                else if(numer.equals("11")){
                    but.setText("Antylopa");
                    but.UstawOrganizm(new Antylopa(swiat));
                }
                else if(numer.equals("12")){
                    but.setText("CyberOwca");
                    but.UstawOrganizm(new CyberOwca(swiat));
                }
                else if(numer.equals("13")){
                    but.setText("Lis");
                    but.UstawOrganizm(new Lis(swiat));
                }
                else if(numer.equals("20")){
                    but.setText("Owca");
                    but.UstawOrganizm(new Owca(swiat));
                }
                else if(numer.equals("21")){
                    but.setText("Wilk");
                    but.UstawOrganizm(new Wilk(swiat));
                }
                else if(numer.equals("22")){
                    but.setText("Zółw");
                    but.UstawOrganizm(new Zolw(swiat));
                }
                else if(numer.equals("23")){
                    but.setText("Czlowiek");
                    but.UstawOrganizm(new Czlowiek(swiat));
                }
                PrzyciskZwierze finalBut = but;
                but.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        swiat.NarodzOrganizm(finalBut.organizm.Urodz(), new Polozenie(polozenie), TrybNarodz.Dodaj);
                        dispose();
                    }
                });
                this.add(but);
            }

        }
        this.repaint();



    }
    public void Wait(){

    }

    public void keyPressed(KeyEvent e) {
        System.out.println(e.getKeyChar());
    }
}
