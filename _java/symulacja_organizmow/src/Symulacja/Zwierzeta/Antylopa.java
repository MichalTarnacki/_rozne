package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class Antylopa extends Zwierze {
    protected void SetInicjatywa(){
        this.inicjatywa=4;
    };
    protected void SetSila(){
        this.sila=4;
    };
    public Antylopa(Swiat swiat){
        super(swiat);
        SetInicjatywa();
        SetSila();
    };
    public char Rysowanie(){
        return 'A';
    };
    public Organizm Urodz() {
        return new Antylopa(this.swiat);
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Antylopa)
            return true;
        else
            return false;
    };
    public void Akcja(){
        Ruch(2);
    };
    public void Kolizja(Organizm organizm){
        boolean czySieRuszyl;
        int x=(int)(Math.random()*100);
        if(x>=50&&!(organizm instanceof Antylopa)){
            czySieRuszyl=RuchBezKolizji(2);
            if(!czySieRuszyl)
                super.Kolizja(organizm);
        else{
                swiat.zdarzenia.DodajString( "Antylopa: " + this.GetPolozenie() + " ucieka bez kolizji");
            }
        }
    else
        super.Kolizja(organizm);
    };
    @Override
    public Color GetColor(){
        return new Color(0,255,255);
    };
}
