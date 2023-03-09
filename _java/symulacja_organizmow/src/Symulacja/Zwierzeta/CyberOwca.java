package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class CyberOwca extends Zwierze {
    protected void SetInicjatywa(){
        this.inicjatywa=4;
    };
    protected void SetSila(){
        this.sila=11;
    };
    public CyberOwca(Swiat swiat){
        super(swiat);
        SetInicjatywa();
        SetSila();
    };
    public char Rysowanie(){
        return 'C';
    };
    public Organizm Urodz() {
        return new CyberOwca(this.swiat);
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof CyberOwca)
        return true;
    else
        return false;
    };
    @Override
    public Color GetColor(){
        return new Color(100,0,0);
    };
}
