package Symulacja.Rosliny;
import Symulacja.*;

import java.awt.*;

public class Mlecz extends Roslina {
    public Mlecz(Swiat swiat){
        super(swiat);
    };
    public char Rysowanie(){
        return 'm';
    };
    public Organizm Urodz(){
        return new Mlecz(this.swiat);
    };
    public int GetPrawdopodobienstwo(){
        return 10;
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Mlecz)
        return true;
    else
        return false;
    };
    public void Akcja(){
        for(int i=0; i<3;i++)
            super.Akcja();
    };
    @Override
    public Color GetColor(){
        return new Color(0,0,255);
    };
}
