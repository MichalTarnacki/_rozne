package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class Zolw extends Zwierze {
    protected void SetInicjatywa(){
        this.inicjatywa=1;
    }
    protected void SetSila(){
        this.sila=2;
    }
    public Zolw(Swiat swiat){
        super(swiat);
    }
    public char Rysowanie(){
        return 'Z';
    }
    public Organizm Urodz() {
        return new Zolw(this.swiat);
    }
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Zolw)
            return true;
        else
            return false;
    }
    public void Akcja(){
        int x=(int)(Math.random()*100);
        if(x>=75)
            super.Akcja();
    }
    public void Kolizja(Organizm organizm){
        if(organizm.GetSila()<5&&!(organizm instanceof Zolw)){
            organizm.SetPolozenie(organizm.GetPoprzedniePolozenie());
            swiat.zdarzenia.DodajString( "Organizm: " + organizm.GetPolozenie() + " jest za slaby zeby walczyc z zolwiem, wraca na poprzenia pozycje: " + organizm.GetPolozenie());
        }
    else
        super.Kolizja(organizm);

    }
    @Override
    public Color GetColor(){
        return new Color(0,100,100);
    };
}
