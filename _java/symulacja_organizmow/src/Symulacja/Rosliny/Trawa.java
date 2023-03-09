package Symulacja.Rosliny;
import Symulacja.*;

import java.awt.*;

public class Trawa extends Roslina {
    public Trawa(Swiat swiat){
        super(swiat);
    };
    public char Rysowanie(){
        return 't';
    };
    public Organizm Urodz(){
        return new Trawa(this.swiat);
    };
    public int GetPrawdopodobienstwo(){
        return 30;
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Trawa)
           return true;
        else
          return false;
    };
    @Override
    public Color GetColor(){
        return new Color(255,255,0);
    };
}
