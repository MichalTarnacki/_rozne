package Symulacja;

import java.io.*;
import java.util.*;
import javax.swing.*;
import Symulacja.Sluchacz;

public class Swiat {
    protected Plansza plansza = new Plansza();
    protected int liczbaOrganizmow;
    protected List<Organizm> organizmy = new ArrayList<>();
    protected List<Organizm> noweOrganizmy = new ArrayList<>();
    public Sluchacz zdarzenia = new Sluchacz();
    protected int numerRundy = 0;
    static final String miejsceZapisu = "plik.txt";
    protected Okno okno;
    protected KierunekRuchu kierunekCzlowieka = KierunekRuchu.BRAK;

    public Swiat(Plansza plansza, KonfiguracjaOrganizmow konfiguracjaOrganizmow) {
        this.plansza.Set(plansza);
//        if (konfiguracjaOrganizmow.getLacznaLiczbaOrganizmow() > plansza.GetLiczbaPol()) //throw "Za duzo zwierzat!!";
        WczytajOrganizmy(konfiguracjaOrganizmow);
        LosujPozycje();
    }
    public Swiat() throws IOException {
//        if (konfiguracjaOrganizmow.getLacznaLiczbaOrganizmow() > plansza.GetLiczbaPol()) //throw "Za duzo zwierzat!!";
//        Wczytaj();
    }
    public void ZainicjujOkno(){
        okno = new Okno("Symulacja", this);
    }

    protected void WykonajTure() throws FileNotFoundException, UnsupportedEncodingException, InterruptedException {
        SortujOrganizmy();
        PrzywrocMozliwosciRozrodu();
        okno.Update();
        Iterator<Organizm> iterator=organizmy.iterator();
        int size=organizmy.size();
        Organizm organizm;
        Organizm organizm2;
        for (int i=0; i<size; i++){
            organizm=organizmy.get(i);
            if(organizm.SprawdzCzyZyje()){
                organizm.Akcja();
                int size2=organizmy.size();
                for (int j=0; j<size2; j++){
                    organizm2=organizmy.get(j);
                    if(organizm2.SprawdzCzyZyje()&&organizm.GetPolozenie().equals(organizm2.GetPolozenie())&&organizm!=organizm2){
                        organizm2.Kolizja(organizm);
                    }
                }
                organizm.SetPoprzedniePolozenie(organizm.GetPolozenie());
            }
        }
        UsunMartweOrganizmy();
        AktualizujNumerRundy();
    }

    public void Symuluj() throws IOException, InterruptedException {
        boolean quit = false;
        boolean wczytaj = false;
        okno.setSize(800, 600);
        okno.setVisible(true);
        while(!SprawdzCzyZostalTylkoJedenGatunek()){
//            okno.Update();
            while (okno.buttonNum==0) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if(okno.buttonNum==2){
                    Wczytaj();
                    zdarzenia.Wyczysc();
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==3){
                    ZapiszAktualnyStan();
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==4){
                    SterujCzlowiekiem(KierunekRuchu.Polnoc);
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==5){
                    SterujCzlowiekiem(KierunekRuchu.Zachod);
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==6){
                    SterujCzlowiekiem(KierunekRuchu.Polodnie);
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==7){
                    SterujCzlowiekiem(KierunekRuchu.Wschod);
                    okno.Update();
                    okno.buttonNum=0;
                }
                else if(okno.buttonNum==8){
                    WlaczSpecjalnaUmiejetnosc();
                    okno.Update();
                    okno.buttonNum=0;
                }
                else {
                    continue;
                }
            }
            zdarzenia.Wyczysc();
            okno.buttonNum=0;
            quit=true;
            WykonajTure();
            okno.Update();
            System.gc();
        }
    }

    private void RysujSwiat() {
        boolean found;
        Polozenie polozenie = new Polozenie(0, 0);
        System.out.println("+-----------------------------------------+");
        System.out.println("|Wirtualny Symulacja.Swiat - Michal Tarnacki s188627|");
        System.out.println("+-----------------------------------------+");
        for (int y = 0; y < plansza.GetM() + 2; y++) {
            for (int x = 0; x < plansza.GetN() + 2; x++) {
                if ((x == 0 && y == 0) || (x == 0 && y == plansza.GetM() + 1) || (x == plansza.GetN() + 1 && y == 0) || (x == plansza.GetN() + 1 && y == plansza.GetM() + 1))
                    System.out.print('+');
                else if (x == 0 || x == plansza.GetN() + 1)
                    System.out.print('|');
                else if (y == 0 || y == plansza.GetM() + 1)
                    System.out.print('-');
                else {
                    polozenie.Set(x-1, y-1);
                    found=false;
                    for (Symulacja.Organizm organizm: organizmy){
                        if(organizm.SprawdzCzyZyje()&&organizm.GetPolozenie().equals(polozenie)){
                            System.out.print(organizm.Rysowanie());
                            found = true;
                        }
                    }
                    if(!found)
                    System.out.print(' ');
                }
            }
            System.out.print("\n");
        }
        System.out.println("Aktualna liczba organizmow:" + liczbaOrganizmow);
    }

    protected void SortujOrganizmy() {
        organizmy.sort(Organizm::compareTo);
    }

    protected void WczytajOrganizmy(KonfiguracjaOrganizmow konfiguracja) {
        Symulacja.Organizm nowyOrganizm;
        for (int i = 0; i < konfiguracja.liczbaLudzi; i++) {
            nowyOrganizm = new Symulacja.Czlowiek(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaAntylop; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.Antylopa(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaWilkow; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.Wilk(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaOwiec; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.Owca(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaLisow; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.Lis(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaZolwi; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.Zolw(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaCyberOwiec; i++) {
            nowyOrganizm = new Symulacja.Zwierzeta.CyberOwca(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaTraw; i++) {
            nowyOrganizm = new Symulacja.Rosliny.Trawa(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaMleczy; i++) {
            nowyOrganizm = new Symulacja.Rosliny.Mlecz(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaGuarany; i++) {
            nowyOrganizm = new Symulacja.Rosliny.Guarana(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaWilczychJagod; i++) {
            nowyOrganizm = new Symulacja.Rosliny.WilczeJagody(this);
            organizmy.add(nowyOrganizm);
        }
        for (int i = 0; i < konfiguracja.liczbaBarszuSosnowskiego; i++) {
            nowyOrganizm = new Symulacja.Rosliny.BarszczSosnowskiego(this);
            organizmy.add(nowyOrganizm);
        }
        liczbaOrganizmow = konfiguracja.getLacznaLiczbaOrganizmow();
    }

    protected void LosujPozycje() {
        Polozenie polozenie = new Polozenie();
        boolean uniq;
        for (Organizm organizm : organizmy) {
            do {
                polozenie.Set((int) (Math.random()*plansza.GetN()), (int) (Math.random()*plansza.GetM()));
                uniq = true;
                for (Organizm organizm2 : organizmy) {
                    if (polozenie.equals(organizm2.GetPolozenie()))
                        uniq = false;
                }
            } while (!uniq);
            organizm.SetPolozenie(polozenie);
            organizm.SetPoprzedniePolozenie(polozenie);
        }
    };

    public Plansza GetPlansza() {
        return new Plansza(this.plansza);
    }

    private void KolejnoscRuchu() {
    }

    public void ZabijOrganizm(Organizm organizm) {
        organizm.Zabij();
        liczbaOrganizmow--;
    }

    ;

    public void NarodzOrganizm(Organizm organizm, Polozenie polozenie, TrybNarodz tryb) {
        Organizm nowyOrganizm = organizm.Urodz();
        nowyOrganizm.SetPolozenie(polozenie); //2 3 // 3 1 +1 -2
        nowyOrganizm.SetPoprzedniePolozenie(polozenie);
        nowyOrganizm.SetZdolnoscRozrodu(false);
        organizmy.add(nowyOrganizm);
        liczbaOrganizmow++;
        System.out.println("Rodzi sie na " + polozenie);
        if(tryb == TrybNarodz.Dodaj)
          okno.Update();
    }

    protected void UsunMartweOrganizmy() {
        Organizm organizm=null;
        noweOrganizmy.clear();
        for (Organizm organizm2: organizmy){
            if(organizm2.SprawdzCzyZyje())
                noweOrganizmy.add(organizm2);
        }
        organizmy.clear();
        organizmy.addAll(noweOrganizmy);
    }
    ;

    public List<Organizm> GetOrganizmy() {
        return organizmy;
    };

    protected void PrzywrocMozliwosciRozrodu() {
        for (Organizm organizm : organizmy) {
            if (!organizm.CzyMozeSieRozmnazac())
                organizm.SetZdolnoscRozrodu(true);
        }
    }

    protected void AktualizujNumerRundy() {
        numerRundy++;
    };

    public int GetNumerRundy() {
        return numerRundy;
    };

    protected boolean SprawdzCzyZostalTylkoJedenGatunek() {
        if (liczbaOrganizmow != plansza.GetLiczbaPol())
            return false;
        Organizm organizm = organizmy.get(0);
        for (Organizm organizm2:organizmy){
            if (!organizm2.MozeBycPartnerem(organizm)&&organizm2.SprawdzCzyZyje())
            return false;
        }
        return true;
    }

    ;

    protected void ZapiszAktualnyStan() throws FileNotFoundException, UnsupportedEncodingException {
        PrintWriter writer = new PrintWriter(miejsceZapisu, "UTF-8");
        writer.println(plansza.toString(TrybToString.Krotko));
        writer.println(numerRundy + " " + liczbaOrganizmow);
            for (Organizm organizm:organizmy){
                writer.println(organizm.toString(TrybToString.Krotko));
            }
        writer.close();
    }

    ;
    protected void Wczytaj() throws IOException {
        File plik = new File(miejsceZapisu);
        if(!plik.exists())
            return;
        Scanner reader = new Scanner(plik);
            ZniszczSwiat();
            ZmienneDoWczytania zmienne = new ZmienneDoWczytania(this);
            zmienne.x = reader.nextInt();
            zmienne.y = reader.nextInt();
            zmienne.numerRundy = reader.nextInt();
            zmienne.liczbaOrganizmow = reader.nextInt();;
            this.plansza.Set(zmienne.x,zmienne.y);
            this.numerRundy=zmienne.numerRundy;
            this.liczbaOrganizmow=zmienne.liczbaOrganizmow;
            for(int i=0; i<this.liczbaOrganizmow; i++){
                zmienne.znak = reader.next().charAt(0);;
                for(Organizm organizm: zmienne.tymczasoweOrganizmy){
                    if(zmienne.znak==organizm.Rysowanie()){
                        organizmy.add(organizm.Urodz());
                        zmienne.czasUrodzenia = new Date(reader.nextLong());
                        zmienne.sila = reader.nextInt();
                        zmienne.inicjatywa = reader.nextInt();
                        zmienne.x = reader.nextInt();
                        zmienne.y = reader.nextInt();
                        zmienne.x2 = reader.nextInt();
                        zmienne.y2 = reader.nextInt();
                        zmienne.czyZywy = reader.nextInt()!=0 ? true:false;
                        zmienne.zdolnyDoRozrodu = reader.nextInt()!=0 ? true:false;
                        if(organizm instanceof Czlowiek) {
                           zmienne.parametr1 = reader.nextInt()!=0 ? true:false;
                            zmienne.parametr2 = reader.nextInt();
                        }
                        zmienne.polozenie.Set(zmienne.x, zmienne.y);
                        zmienne.poprzedniePolozenie.Set(zmienne.x2, zmienne.y2);
                        organizmy.get(organizmy.size()-1).WczytajWlasciwosci(zmienne.sila, zmienne.inicjatywa, zmienne.polozenie, zmienne.poprzedniePolozenie, zmienne.czasUrodzenia, zmienne.czyZywy, zmienne.zdolnyDoRozrodu, zmienne.parametr1, zmienne.parametr2);
                        break;
                    }
                }
            }
            organizmy.get(0);
            reader.close();
    }

    protected void ZniszczSwiat() {
        for (Organizm organizm : organizmy) {
            organizm.Zabij();
            liczbaOrganizmow--;
        }
        UsunMartweOrganizmy();
    }

    public void SterujCzlowiekiem(Symulacja.KierunekRuchu kierunek) {
        Symulacja.Czlowiek org;
        kierunekCzlowieka=kierunek;
        for (Symulacja.Organizm organizm : organizmy) {
            if (organizm instanceof Symulacja.Czlowiek) {
                org = (Symulacja.Czlowiek) organizm;
                org.UstawKierunekRuchu(kierunek);
            }
        }
    }
    protected String KierunekCzlowiekaToString(){
        if(kierunekCzlowieka==KierunekRuchu.Polnoc)
            return "Gora";
        else if(kierunekCzlowieka==KierunekRuchu.Polodnie)
            return "Dol";
        else if(kierunekCzlowieka==KierunekRuchu.Zachod)
            return "Lewo";
        else if(kierunekCzlowieka==KierunekRuchu.Wschod)
            return "Prawo";
        else
            return "brak";

    }

    public void WlaczSpecjalnaUmiejetnosc() {
        Czlowiek org;
        for (Organizm organizm : organizmy) {
            if (organizm instanceof Symulacja.Czlowiek) {
                org = (Symulacja.Czlowiek) organizm;
                org.SpecjalnaUmiejetnosc();
            }
        }
    }

    public boolean IstniejeCzlowiek() {
        for (Organizm organizm : organizmy) {
            if (organizm instanceof Symulacja.Czlowiek) {
                return true;
            }
        }
        return false;
    }
};

