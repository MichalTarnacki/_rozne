package Symulacja;

import javax.swing.*;

public class PrzyciskZwierze extends JButton {
    public Organizm organizm;
    public PrzyciskZwierze(){
    }
    public void UstawOrganizm(Organizm organizm){
        this.organizm=organizm;
    }
}
