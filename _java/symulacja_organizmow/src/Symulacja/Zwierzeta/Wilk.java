package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class Wilk extends Zwierze {
        protected void SetInicjatywa(){
            this.inicjatywa=5;
        };
        protected void SetSila(){
            this.sila=9;
        };
        public Wilk(Swiat swiat){
            super(swiat);
            SetInicjatywa();
            SetSila();
        };
        public char Rysowanie(){
            return 'W';
        };
        public Organizm Urodz() {
            return new Wilk(this.swiat);
        };
        public boolean MozeBycPartnerem(Organizm organizm){
            if(organizm instanceof Zwierze)
                return true;
            else
                return false;
        };
    @Override
    public Color GetColor(){
        return new Color(100,100,0);
    };
}
