package Symulacja.Rosliny;

import Symulacja.Zwierzeta.CyberOwca;
import Symulacja.*;

import java.awt.*;

public class BarszczSosnowskiego extends Roslina {
    public BarszczSosnowskiego(Swiat swiat){
        super(swiat);
    };
    public char Rysowanie(){
        return 'b';
    };
    public Organizm Urodz(){
        return new BarszczSosnowskiego(this.swiat);
    };
    public int GetPrawdopodobienstwo(){
        return 5;
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof BarszczSosnowskiego)
        return true;
    else
        return false;
    };
    public void Akcja(){
        ZabijWokolo();
        super.Akcja();
    };
    public void Kolizja(Organizm organizm){
        if(!(organizm instanceof CyberOwca))
            swiat.ZabijOrganizm(organizm);
    };
    void ZabijWokolo(){
        boolean juzZabil = false;
        Polozenie nowePolozenie = new Polozenie();
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1; j++){
                nowePolozenie.Set(this.GetPolozenie().GetX()+j, this.GetPolozenie().GetY()+i);
                if(this.swiat instanceof Swiat) {
                    if (nowePolozenie.GetY() < 0 || nowePolozenie.GetX() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM())
                        ;
                    else {
                        for (Organizm organizm : swiat.GetOrganizmy()) {
                            if (organizm.SprawdzCzyZyje() && organizm.GetPolozenie().equals(nowePolozenie) && organizm != this && !(organizm instanceof BarszczSosnowskiego) && !(organizm instanceof CyberOwca)) {
                                if (juzZabil == false) {
                                    swiat.zdarzenia.DodajString("Barszcz " + this.polozenie + " zabija wszystkich<br/> wokoło");
                                    juzZabil = true;
                                }
                                swiat.ZabijOrganizm(organizm);
                                swiat.zdarzenia.DodajString("  Ginie: " + organizm.Rysowanie() + " " + organizm.GetPolozenie());
                            }
                        }
                    }
                }
                else{
                    if (nowePolozenie.GetY() < 0 || nowePolozenie.GetX() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM() || (i==1&&j==1) || (i==-1&&j==-1)) ;
                    else {
                        for (Organizm organizm : swiat.GetOrganizmy()) {
                            if (organizm.SprawdzCzyZyje() && organizm.GetPolozenie().equals(nowePolozenie) && organizm != this && !(organizm instanceof BarszczSosnowskiego) && !(organizm instanceof CyberOwca)) {
                                if (juzZabil == false) {
                                    swiat.zdarzenia.DodajString("Barszcz " + this.polozenie + " zabija wszystkich<br/> wokoło");
                                    juzZabil = true;
                                }
                                swiat.ZabijOrganizm(organizm);
                                swiat.zdarzenia.DodajString("  Ginie: " + organizm.Rysowanie() + " " + organizm.GetPolozenie());
                            }
                        }
                    }
                }
            }
        }
    };
    protected void SetSila(){
        this.sila=9;
    };

    @Override
    public Color GetColor(){
        return new Color(255,0,0);
    };
}
