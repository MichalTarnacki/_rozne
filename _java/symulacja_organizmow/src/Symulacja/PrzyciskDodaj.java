package Symulacja;

import Symulacja.Zwierzeta.Owca;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class PrzyciskDodaj extends JButton {
    public final Polozenie polozenie = new Polozenie();
    public PrzyciskDodaj(Polozenie polozenie, Swiat swiat){
        this.polozenie.Set(new Polozenie(polozenie));
        addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                WybierzZwierzeMenu menu = new WybierzZwierzeMenu(swiat, polozenie);
                }
        });
    }
}
