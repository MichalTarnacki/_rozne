package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class Owca extends Zwierze {
    protected void SetInicjatywa(){
        this.inicjatywa=4;
    };
    protected void SetSila(){
        this.sila=4;
    };
    public Owca(Swiat swiat){
        super(swiat);
        SetInicjatywa();
        SetSila();
    };
    public char Rysowanie(){
        return 'O';
    };
    public Organizm Urodz() {
        return new Owca(this.swiat);
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Owca)
        return true;
    else
        return false;
    };
    @Override
    public Color GetColor(){
        return new Color(0,0,100);
    };
}
