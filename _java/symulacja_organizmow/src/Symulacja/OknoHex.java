package Symulacja;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class OknoHex extends Okno{

    public OknoHex(String title, Swiat swiat) {
        super(title, swiat);
        this.swiat=swiat;
        this.setFocusable(true);
        addKeyListener(key);
        Options();
        Update();
        this.setVisible(true);
        this.setLayout(null);
    }

    public OknoHex() {

    }
    @Override
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

        double o = (board.getWidth()-margin)/(((4.0/3)*swiat.GetPlansza().GetN())+((2.0/3)*swiat.GetPlansza().GetM())-1);
        double p = 2.0*(board.getHeight()-2*pasek)/(swiat.GetPlansza().GetM()+1);
        Dimension wymiaryHex = new Dimension((int)o,(int)p);


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
                int przesuniecieX;
                int przesuniecieX2;
                int przesuniecieY;
                for (int y = 0; y < swiat.GetPlansza().GetM(); y++) {
                    for (int x = 0; x < swiat.GetPlansza().GetN(); x++) {
                        for (int i=0; i<swiat.GetOrganizmy().size(); i++){
                            organizm=swiat.GetOrganizmy().get(i);
                            if(organizm.SprawdzCzyZyje()&&organizm.GetPolozenie().equals(new Polozenie(x,y))){
                                przesuniecieX = y*((int)wymiaryHex.getWidth())*2/3;
                                przesuniecieX2 = ((int) wymiaryHex.getWidth())*4/3;
                                przesuniecieY = ((int)wymiaryHex.getHeight())/2;
                                int[] xPoints = {2*margin+x*przesuniecieX2+((int)wymiaryHex.getWidth())/3+przesuniecieX,2*margin+x*przesuniecieX2+(int)wymiaryHex.getWidth()/3*2+przesuniecieX,2*margin+x*przesuniecieX2+(int)wymiaryHex.getWidth()+przesuniecieX,2*margin+x*przesuniecieX2+(int)wymiaryHex.getWidth()*2/3+przesuniecieX,2*margin+x*przesuniecieX2+(int)wymiaryHex.getWidth()/3+przesuniecieX,2*margin+x*przesuniecieX2+przesuniecieX};
                                int[] yPoints = {pasek+y*przesuniecieY,pasek+y*przesuniecieY,pasek+y*przesuniecieY+(int) wymiaryHex.getHeight()/2,pasek+y*przesuniecieY+(int) wymiaryHex.getHeight(),pasek+y*przesuniecieY+(int) wymiaryHex.getHeight(),pasek+y*przesuniecieY+(int) wymiaryHex.getHeight()/2};
                                  g2d.setColor(Color.BLACK);
                                g2d.setStroke(new BasicStroke(5));
                                  g2d.drawPolygon(xPoints, yPoints, xPoints.length);
                                g2d.setColor(organizm.GetColor());
                                g2d.fillPolygon(xPoints, yPoints, xPoints.length);

                            }

                        }
                    }
                }
            }
        };

        panel.setSize(this.getWidth()-pasek, this.getHeight()-pasek);
        this.add(panel);
        int przesuniecieX;
        int przesuniecieX2;
        int przesuniecieY;
        boolean found=false;
        Polozenie po = new Polozenie();
        for (int y = 0; y < swiat.GetPlansza().GetM(); y++) {
            for (int x = 0; x < swiat.GetPlansza().GetN(); x++) {
                found=false;
                po.Set(x,y);
                przesuniecieX = y*((int)wymiaryHex.getWidth())*2/3;
                przesuniecieX2 = ((int) wymiaryHex.getWidth())*4/3;
                przesuniecieY = ((int)wymiaryHex.getHeight())/2;
                for (Symulacja.Organizm organizm1: swiat.GetOrganizmy()){
                    if(organizm1.SprawdzCzyZyje()&&organizm1.GetPolozenie().equals(po)){
                        found=true;

                    }
                }
                if(!found){
                    JButton but = new PrzyciskDodaj(new Polozenie(po), swiat);
                    but.setBounds(x*przesuniecieX2+((int)wymiaryHex.getWidth())*2/3+przesuniecieX, pasek+y*przesuniecieY+(int) wymiaryHex.getHeight()/4,(int)wymiaryHex.getWidth()/3,(int)wymiaryHex.getHeight()/2);
                    this.add(but);
                }
            }
        }

        this.revalidate();
        this.repaint();
    }
}
