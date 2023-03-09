package Symulacja;

import Symulacja.Zwierzeta.Owca;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Okno extends JFrame {
    Swiat swiat;
    protected int margin = 5;
    protected JPanel panel;
    protected int pasek=25;
    public int buttonNum=0;
    public char humanKey='\0';
    public boolean updateWindow=false;

    protected KeyListener key = new KeyListener(){
        @Override
        public void keyTyped(KeyEvent e) {
        }

        @Override
        public void keyPressed(KeyEvent e) {

            char keyk=e.getKeyChar();
            if ((keyk == 'w'))
                buttonNum=4;
            else if (keyk == 'a')
                buttonNum=5;
            else if (keyk == 's')
                buttonNum=6;
            else if (keyk == 'd')
                buttonNum=7;
            else if (keyk == 'r')
                buttonNum=8;
        }

        @Override
        public void keyReleased(KeyEvent e) {
        }
    };

    public Okno(String title, Swiat swiat){
        super("Symulacja");
        this.swiat=swiat;
        this.setFocusable(true);
        addKeyListener(key);
        Options();
        Update();
        this.setVisible(true);
        this.setLayout(null);
}

    public Okno() {

    }

    protected void Options(){
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Symulacja organizmow, s188627");
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setLayout(null);
        this.setSize(800,600);
    }

    private void Layout() {

    }
    public void Update(){
        this.getContentPane().removeAll();
        this.revalidate();
        this.repaint();
        Dimension board = new Dimension(this.getHeight()-2*margin-pasek, this.getHeight()-2*margin-pasek);
        Dimension pole = new Dimension((int)board.getWidth()/swiat.GetPlansza().GetN(),(int)board.getHeight()/swiat.GetPlansza().GetM());

        JButton nastepnaTura = new JButton("Nastepna tura");
        nastepnaTura.setBounds(board.width+2, margin+52, (this.getWidth()-(int)board.getWidth()),50 );
        JButton zapisz = new JButton("Zapisz");
        zapisz.setBounds(board.width+(this.getWidth()-(int)board.getWidth())/2+2, margin, (this.getWidth()-(int)board.getWidth())/2,50 );
        JButton wczytaj = new JButton("Wczytaj");
        wczytaj.setBounds(board.width+2, margin, (this.getWidth()-(int)board.getWidth())/2,50 );

        nastepnaTura.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=1;
            }
        });
        wczytaj.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=2;
            }
        });
        zapisz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buttonNum=3;
            }
        });


        JLabel log = new JLabel("Log:");
        log.setBounds(board.width+2, margin+104, (this.getWidth()-(int)board.getWidth()),50 );
        log.setVerticalAlignment(JLabel.CENTER);
        log.setHorizontalAlignment(JLabel.CENTER);
        JLabel label2;
        if(swiat.IstniejeCzlowiek())
         label2 = new JLabel("<html>" + "<br/> Aktualnie wybrany kierunek: <br/>" + swiat.KierunekCzlowiekaToString() + "<br/>" + swiat.zdarzenia.Wypisz() +  "</html>");
        else
            label2 = new JLabel("<html>" + swiat.zdarzenia.Wypisz() + "</html>");
        JScrollPane j = new JScrollPane(label2);
        j.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        j.setBounds(board.width+2, margin+154, (this.getWidth()-(int)board.getWidth()),400 );
        this.add(j);
        this.add(nastepnaTura);
        this.add(zapisz);
        this.add(wczytaj);
        this.add(log);


        panel = new JPanel(){
            @Override
            public void paint(Graphics g){
                this.setLayout(null);
                Graphics2D g2d = (Graphics2D) g;
                g2d.setStroke(new BasicStroke(3));
                g2d.setPaint(Color.BLACK);
                g2d.drawLine(margin, margin, (int)board.getWidth(), margin);
                g2d.drawLine(margin, margin, margin, (int)board.getHeight());
                g2d.drawLine((int)board.getWidth(), margin, (int)board.getWidth(), (int)board.getHeight());
                g2d.drawLine(margin, (int)board.getWidth(), (int)board.getWidth(), (int)board.getHeight());
                Organizm organizm;
//                for(int i=1; i<=swiat.GetPlansza().GetN(); i++)
//                    g2d.drawLine(margin+i*(int)pole.getWidth(), margin, margin+i*(int)pole.getWidth(), (int)board.getHeight());
//                for(int i=1; i<=swiat.GetPlansza().GetM(); i++)
//                    g2d.drawLine(margin, margin+i*(int)pole.getHeight(), (int)board.getWidth(), margin+i*(int)pole.getHeight());
                for (int y = 0; y < swiat.GetPlansza().GetM(); y++) {
                    for (int x = 0; x < swiat.GetPlansza().GetN(); x++) {
                            for (int i=0; i<swiat.GetOrganizmy().size(); i++){
                                organizm=swiat.GetOrganizmy().get(i);
                                if(organizm.SprawdzCzyZyje()&&organizm.GetPolozenie().equals(new Polozenie(x,y))){
                                    g2d.setColor(organizm.GetColor());
                                    g2d.fillRect(margin+x*(int)pole.getWidth(), margin+y*(int)pole.getHeight(), (int)pole.getWidth(), (int)pole.getHeight());
                                }

                            }
                        }
                }
            }
        };

        panel.setSize(this.getWidth()-pasek, this.getHeight()-pasek);
        this.add(panel);
        boolean found=false;
        Polozenie p = new Polozenie();
        for (int y = 0; y < swiat.GetPlansza().GetM(); y++) {
            for (int x = 0; x < swiat.GetPlansza().GetN(); x++) {
                found=false;
                p.Set(x,y);
                for (Symulacja.Organizm organizm: swiat.GetOrganizmy()){
                    if(organizm.SprawdzCzyZyje()&&organizm.GetPolozenie().equals(p)){
                        found=true;

                    }
                }
                if(!found){
                    JButton but = new PrzyciskDodaj(new Polozenie(p), swiat);
                        but.setBounds(margin+x*(int)pole.getWidth()+4, margin+y*(int)pole.getHeight()+4,(int)pole.getWidth()-8,(int)pole.getHeight()-8);
                        this.add(but);
                }
            }
        }
        this.revalidate();
        this.repaint();
    }
    public void Wait(){

    }

    public void keyPressed(KeyEvent e) {
        System.out.println(e.getKeyChar());
    }
}
