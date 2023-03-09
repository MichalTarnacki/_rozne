package Symulacja.Rosliny;
import Symulacja.*;

import java.awt.*;
import java.util.Set;

public class WilczeJagody extends Roslina {
   public WilczeJagody(Swiat swiat){
        super(swiat);
       SetSila();
    };
    public char Rysowanie(){
     return 'w';
    };
    public Organizm Urodz(){
     return new WilczeJagody(this.swiat);
    };
    public int GetPrawdopodobienstwo(){
     return 5;
    };
    public boolean MozeBycPartnerem(Organizm organizm){
      if(organizm instanceof WilczeJagody)
       return true;
      else
       return false;
    };
    public void Kolizja(Organizm organizm){
      swiat.zdarzenia.DodajString("Organizm: " + organizm.Rysowanie() + " na pozycji " + organizm.GetPolozenie() + " <br/>zjada Wilcze Jagody i umiera");
      swiat.ZabijOrganizm(organizm);
    }
    protected void SetSila(){
      this.sila=99;
    }
    @Override
    public Color GetColor(){
        return new Color(255,0,255);
    };
}
