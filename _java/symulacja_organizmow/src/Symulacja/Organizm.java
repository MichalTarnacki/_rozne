package Symulacja;

import java.awt.*;
import java.util.Date;
public abstract class Organizm implements Comparable <Organizm> {

    protected double sila=0;
    protected double inicjatywa=0;
    protected Polozenie polozenie = new Polozenie(-1,-1), poprzedniePolozenie = new Polozenie(-1,-1);
    private Date czasUrodzenia = new Date();
    public Swiat swiat;
    boolean czyZywy=true;
    boolean zdolnyDoRozrodu=false;
    protected abstract void SetInicjatywa();
    protected abstract void SetSila();

    public Organizm(Swiat swiat) {
        this.swiat=swiat;
    };
    public abstract void Akcja();
    public void Kolizja(Organizm organizm) {
        swiat.zdarzenia.DodajString("Organizm: " + organizm.Rysowanie() + " atakuje <br/> organizm: " + this.Rysowanie() + " na polu:" + this.GetPolozenie());
        if(this.GetSila()>organizm.GetSila()){
            swiat.ZabijOrganizm(organizm);
            swiat.zdarzenia.DodajString("  Zwycieza: " + this.Rysowanie());
        }
    else{
            swiat.ZabijOrganizm(this);
            swiat.zdarzenia.DodajString("  Zwycieza: " + organizm.Rysowanie());
        }
    };
    public abstract char Rysowanie();
    public final double GetInicjatywa() {
        return this.inicjatywa;
    };
    public final double GetDlugoscZycia() {
        Date aktualny = new Date();
        return aktualny.compareTo(czasUrodzenia); //posible error
    };
    public final double GetSila() {
        return this.sila;
    }
    public final Polozenie GetPolozenie() {
        return new Polozenie(polozenie);
    };
    public final void SetPolozenie(Polozenie polozenie) {
        this.polozenie.Set(polozenie);
    };
    public final Polozenie GetPoprzedniePolozenie() {
        return new Polozenie(poprzedniePolozenie);
    };
    public final void SetPoprzedniePolozenie(Polozenie polozenie) {
        this.poprzedniePolozenie.Set(polozenie);
    };
    public final boolean SprawdzCzyMoznaBezpiecznieRuszyc(int zasiegRuchu) {
        Polozenie nowePolozenie = new Polozenie();
        boolean pustePole;
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1; j++) {
                nowePolozenie.Set(this.GetPolozenie().GetX() + j * zasiegRuchu, this.GetPolozenie().GetY() + i * zasiegRuchu);
                pustePole = true;
                if (!(this.swiat instanceof SwiatHex)) {
                    if (nowePolozenie.GetY() < 0 || nowePolozenie.GetX() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM())
                        pustePole = false;
                    else {
                        for (Organizm organizm : swiat.GetOrganizmy()) {
                            if (organizm.GetPolozenie().equals(nowePolozenie))
                                pustePole = false;
                        }
                    }
                    if (pustePole)
                        return true;
                }
                else {
                    if(j==1&&i==0)
                        nowePolozenie.Set(nowePolozenie.GetX()-2*zasiegRuchu, nowePolozenie.GetY()+2*zasiegRuchu);
                    else if(j==-1&&i==0)
                        nowePolozenie.Set(nowePolozenie.GetX()+2*zasiegRuchu, nowePolozenie.GetY()-2*zasiegRuchu);

                    if (nowePolozenie.GetY() < 0 || nowePolozenie.GetX() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM() || (j==1&&i==1) || (j==-1&&i==-1))
                        pustePole = false;
                    else {
                        for (Organizm organizm : swiat.GetOrganizmy()) {
                            if (organizm.GetPolozenie().equals(nowePolozenie))
                                pustePole = false;
                        }
                    }
                    if (pustePole)
                        return true;

                }
            }
        }
        return false;
    };
    public final boolean SprawdzCzyZyje() {
        return this.czyZywy;
    };
    public final void Zabij() {
        this.czyZywy=false;
    };
    public abstract Organizm Urodz();
    public final void ZwiekszSile(double oIle) {
        this.sila+=oIle;
    };
    public final boolean CzyMozeSieRozmnazac() {
        return this.zdolnyDoRozrodu;
    };
    public final void SetZdolnoscRozrodu(boolean status) {
        this.zdolnyDoRozrodu=status;
    };
    public abstract boolean MozeBycPartnerem(Organizm organizm);
    public void WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, Date czasUrodzenia, boolean czyZywy, boolean zdolnyDoRozrodu){
        WczytajWlasciwosci(sila, inicjatywa, polozenie, poprzedniePolozenie, czasUrodzenia, czyZywy, zdolnyDoRozrodu, false, 0);
    }
    public void WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, Date czasUrodzenia, boolean czyZywy, boolean zdolnyDoRozrodu, boolean parametr1, int parametr2){
        this.sila=sila;
        this.inicjatywa=inicjatywa;
        this.polozenie=new Polozenie(polozenie);
        this.poprzedniePolozenie=new Polozenie(poprzedniePolozenie);
        this.czasUrodzenia= (Date) czasUrodzenia.clone();
        this.czyZywy=czyZywy;
        this.zdolnyDoRozrodu=zdolnyDoRozrodu;
        ;
    };
    @Override
    public String toString(){
        return toString(TrybToString.Ladnie);
    }
    public String toString(TrybToString tryb){
        if(tryb==TrybToString.Ladnie)
            return "[" + this.Rysowanie() + "] " + "Sila: " + this.sila + " Inicjatywa: " + this.inicjatywa + " Symulacja.Polozenie: " + this.polozenie + " Czy zywy: " + this.czyZywy + " Zdolny do rozrodu: " + this.zdolnyDoRozrodu;
        else{
            int czyZ = czyZywy? 1: 0;
            int zdolnyD = zdolnyDoRozrodu? 1: 0;
            return this.Rysowanie() + " " + this.czasUrodzenia.getTime() + " " + (int)this.sila + " " + (int)this.inicjatywa + " " + this.polozenie.toString(TrybToString.Krotko) + " " + this.poprzedniePolozenie.toString(TrybToString.Krotko) + " " + czyZ + " " + zdolnyD;
        }

    }
    @Override
    public int compareTo(Organizm organizm){
        if(this.inicjatywa<organizm.inicjatywa)
            return 1;
        else if(this.inicjatywa> organizm.inicjatywa)
            return -1;
        else{
            return this.czasUrodzenia.compareTo(organizm.czasUrodzenia);
        }
    }
    public abstract Color GetColor();
}

