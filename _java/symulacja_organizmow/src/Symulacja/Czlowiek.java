package Symulacja;

import java.awt.*;
import java.util.Date;

public class Czlowiek extends Zwierze{
    private boolean czyRuchAntylopyAktywny=false;
    private int czasAktywacji = - 1;
    private KierunekRuchu kierunek;
    protected void SetInicjatywa(){
        this.inicjatywa=5;
    };
    protected void SetSila(){
        this.sila=9;
    };
    public Czlowiek(Swiat swiat){
        super(swiat);
        SetInicjatywa();
        SetSila();
    };
    public void Akcja(){
        if(czyRuchAntylopyAktywny){
            if(swiat.GetNumerRundy()-czasAktywacji<3)
                Ruch(2);
            else if (swiat.GetNumerRundy()-czasAktywacji<5){
                int x=(int)(Math.random()*100);
                if(x>=50)
                    Ruch(2);
                else
                    Ruch(1);
            }
            else{
                czyRuchAntylopyAktywny=false;
                Akcja();
            }
        }
        else
            super.Akcja();
    };
    public char Rysowanie(){
        return '+';
    };
    public void Ruch(int zasiegRuchu){

        Polozenie nowePolozenie = new Polozenie();
            nowePolozenie.Set(polozenie);
            if(!(this.swiat instanceof SwiatHex)) {
                if (kierunek == KierunekRuchu.Zachod)
                    nowePolozenie.Set(polozenie.GetX() - zasiegRuchu, polozenie.GetY());
                else if (kierunek == KierunekRuchu.Wschod)
                    nowePolozenie.Set(polozenie.GetX() + zasiegRuchu, polozenie.GetY());
                else if (kierunek == KierunekRuchu.Polnoc)
                    nowePolozenie.Set(polozenie.GetX(), polozenie.GetY() - zasiegRuchu);
                else if (kierunek == KierunekRuchu.Polodnie)
                    nowePolozenie.Set(polozenie.GetX(), polozenie.GetY() + zasiegRuchu);
                if (nowePolozenie.GetX() < 0 || nowePolozenie.GetY() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM())
                    nowePolozenie = polozenie;
            }
            else{
                if (kierunek == KierunekRuchu.Zachod)
                    nowePolozenie.Set(polozenie.GetX() - zasiegRuchu, polozenie.GetY() + zasiegRuchu);
                else if (kierunek == KierunekRuchu.Wschod)
                    nowePolozenie.Set(polozenie.GetX() + zasiegRuchu, polozenie.GetY() - zasiegRuchu);
                else if (kierunek == KierunekRuchu.Polnoc)
                    nowePolozenie.Set(polozenie.GetX(), polozenie.GetY() - zasiegRuchu);
                else if (kierunek == KierunekRuchu.Polodnie)
                    nowePolozenie.Set(polozenie.GetX(), polozenie.GetY() + zasiegRuchu);
                if (nowePolozenie.GetX() < 0 || nowePolozenie.GetY() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM())
                    nowePolozenie = polozenie;
            }
        polozenie=nowePolozenie;
    };
    public Organizm Urodz(){
        return new Czlowiek(this.swiat);
    };
    public boolean MozeBycPartnerem(Organizm organizm){
        if(organizm instanceof Czlowiek)
            return true;
        else
            return false;
    };
    public void SpecjalnaUmiejetnosc(){
        if(!czyRuchAntylopyAktywny){
            if(czasAktywacji==-1||swiat.GetNumerRundy()-czasAktywacji>9){
                czyRuchAntylopyAktywny=true;
                czasAktywacji=swiat.GetNumerRundy();
                swiat.zdarzenia.DodajString( "Symulacja.Czlowiek aktywowal specjalna umiejetnosc");
            }
            else
                swiat.zdarzenia.DodajString( "Nie można aktywować umiejetności");
        }
        else
            swiat.zdarzenia.DodajString( "Nie można aktywować umiejetności");
    };
    public void WczytajWlasciwosci(double sila, double inicjatywa, Polozenie polozenie, Polozenie poprzedniePolozenie, Date czasUrodzenia, boolean czyZywy, boolean zdolnyDoRozrodu, boolean parametr1, int parametr2){
        this.czyRuchAntylopyAktywny=(boolean)parametr1;
        this.czasAktywacji=(int)parametr2;
        super.WczytajWlasciwosci(sila, inicjatywa, polozenie, poprzedniePolozenie, czasUrodzenia, czyZywy, zdolnyDoRozrodu,parametr1, parametr2);
    };
    public void UstawKierunekRuchu(KierunekRuchu kierunek){
        this.kierunek=kierunek;
    };

    @Override
    public String toString(){
        return toString(TrybToString.Ladnie);
    }
    public String toString(TrybToString tryb){
        if(tryb==TrybToString.Ladnie)
            return super.toString() + " Ruch antylopy aktywny: " + czyRuchAntylopyAktywny + " Czas aktywacji:" + czasAktywacji;
        else{
            int czyR = czyRuchAntylopyAktywny? 1: 0;
            return super.toString(TrybToString.Krotko) + " " + czyR + " " + czasAktywacji;
        }

    }
    @Override
    public Color GetColor(){
        return new Color(100,100,100);
    };
}
