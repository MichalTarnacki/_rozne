package Symulacja.Zwierzeta;
import Symulacja.*;

import java.awt.*;

public class Lis extends Zwierze{
    protected void SetInicjatywa(){
        this.inicjatywa=7;
    };
    protected void SetSila(){
        this.sila=3;
    };
    public Lis(Swiat swiat){
        super(swiat);
        SetInicjatywa();
        SetSila();
    };
    public char Rysowanie(){
        return 'L';
    };
    public Organizm Urodz() {
        return new Lis(this.swiat);
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Lis)
        return true;
    else
        return false;
    };
    public void Akcja(){
        super.Akcja();
        for (Organizm organizm: swiat.GetOrganizmy()){
            if(organizm.GetSila()>this.GetSila()&&organizm.GetPolozenie().equals(this.GetPolozenie())){
                this.SetPolozenie(this.GetPoprzedniePolozenie());
                swiat.zdarzenia.DodajString( "Lis chcial isc na pozycje: " + organizm.GetPolozenie() + " ale wytropil: " + organizm.Rysowanie() + " i nie idzie dalej ");
            }
        }

    }
    @Override
    public Color GetColor(){
        return new Color(0,100,0);
    };
}
