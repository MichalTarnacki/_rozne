package Symulacja;

import java.io.*;
import java.util.*;

public class SwiatHex extends Swiat{
    public SwiatHex(Plansza plansza, KonfiguracjaOrganizmow konfiguracjaOrganizmow) throws IOException {
        this.plansza.Set(plansza);
//        if (konfiguracjaOrganizmow.getLacznaLiczbaOrganizmow() > plansza.GetLiczbaPol()) //throw "Za duzo zwierzat!!";
        WczytajOrganizmy(konfiguracjaOrganizmow);
        LosujPozycje();
    }
    public SwiatHex() throws IOException {
//        if (konfiguracjaOrganizmow.getLacznaLiczbaOrganizmow() > plansza.GetLiczbaPol()) //throw "Za duzo zwierzat!!";
//        Wczytaj();
    }
    @Override
    public void ZainicjujOkno(){
        okno = new OknoHex("Symulacja", this);
    }
}
