package Symulacja;

import javax.swing.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Date;

public class main {
    public static void main(String[] args) throws IOException, InterruptedException {
        StartMenu start = new StartMenu();
        while (start.buttonNum==0) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(start.buttonNum==2){
                File plik = new File(Swiat.miejsceZapisu);
                if(!plik.exists()) {
                    JOptionPane.showMessageDialog(start, "Plik zapisu nie istnieje!",
                            "Błąd", JOptionPane.ERROR_MESSAGE);
                    start.buttonNum = 0;
                }
            }
        }
        start.dispose();
        if(start.buttonNum==3){
            return;
        }
        else if(start.buttonNum==2){
            SwiatHex swiat = new SwiatHex();
            swiat.Wczytaj();
            swiat.ZainicjujOkno();
            swiat.Symuluj();
        }
        else{
            Plansza plansza = new Plansza(10,5);
            KonfiguracjaOrganizmow konfiguracja = new KonfiguracjaOrganizmow(1,0,0,0
                    ,0,0,0,0,0,0,0
                    ,0);
            SwiatHex swiat = new SwiatHex(plansza, konfiguracja);
            swiat.ZainicjujOkno();
            swiat.Symuluj();
        }
    }
}
