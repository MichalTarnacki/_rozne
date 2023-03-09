package Symulacja.Rosliny;
import Symulacja.*;

import java.awt.*;

public class Guarana extends Roslina {
    public Guarana(Swiat swiat){
        super(swiat);
    };
    public char Rysowanie(){
        return 'g';
    };
    public Organizm Urodz(){
        return new Guarana(this.swiat);
    };
    public int GetPrawdopodobienstwo(){
        return 20;
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Guarana)
        return true;
    else
        return false;
    };
    public void Kolizja(Organizm organizm){
        swiat.zdarzenia.DodajString("Organizm: " + organizm.Rysowanie() + " na pozycji " + organizm.GetPolozenie() + "<br/>zjada Guarane, jego sila rosnie");
        organizm.ZwiekszSile(3);
        super.Kolizja(organizm);
    }
    @Override
    public Color GetColor(){
        return new Color(0,255,0);
    };
}
