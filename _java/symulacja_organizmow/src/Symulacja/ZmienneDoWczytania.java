package Symulacja;
import java.util.ArrayList;
import java.util.List;
import java.util.Date;
import Symulacja.Zwierzeta.*;
import Symulacja.Rosliny.*;

public class ZmienneDoWczytania {
    public double sila, inicjatywa;
    public boolean parametr1;
    public int parametr2=0;
    public Date czasUrodzenia;
    public boolean czyZywy, zdolnyDoRozrodu;
    public char znak;
    public int liczbaOrganizmow, numerRundy, x,y, x2, y2;
    public Polozenie polozenie = new Polozenie(), poprzedniePolozenie = new Polozenie();
    public List<Organizm> tymczasoweOrganizmy = new ArrayList<>();
    public ZmienneDoWczytania(Swiat swiat){
        Trawa trawa = new Trawa(swiat);
        tymczasoweOrganizmy.add(trawa);
        Mlecz mlecz = new Mlecz(swiat);
        tymczasoweOrganizmy.add(mlecz);
        Guarana guarana = new Guarana(swiat);
        tymczasoweOrganizmy.add(guarana);
        WilczeJagody wilczeJagody = new WilczeJagody(swiat);
        tymczasoweOrganizmy.add(wilczeJagody);
        BarszczSosnowskiego barszczSosnowskiego = new BarszczSosnowskiego(swiat);
        tymczasoweOrganizmy.add(barszczSosnowskiego);
        Wilk wilk = new Wilk(swiat);
        tymczasoweOrganizmy.add(wilk);
        Owca owca = new Owca(swiat);
        tymczasoweOrganizmy.add(owca);
        Lis lis = new Lis(swiat);
        tymczasoweOrganizmy.add(lis);
        Zolw zolw = new Zolw(swiat);
        tymczasoweOrganizmy.add(zolw);
        Antylopa antylopa = new Antylopa(swiat);
        tymczasoweOrganizmy.add(antylopa);
        CyberOwca cyberOwca = new CyberOwca(swiat);
        tymczasoweOrganizmy.add(cyberOwca);
        Czlowiek czlowiek = new Czlowiek(swiat);
        tymczasoweOrganizmy.add(czlowiek);
    };
}
