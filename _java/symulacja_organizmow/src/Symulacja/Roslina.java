package Symulacja;

public abstract class Roslina extends Organizm{
    protected final void SetInicjatywa(){
        this.inicjatywa=0;
    };
    protected void SetSila(){

    };
    public Roslina(Swiat swiat){
        super(swiat);
    };
    public void Akcja(){
        if(CzyMozeSieRozmnazac())
            Zasiej();
    };
    public abstract char Rysowanie();
    public abstract int GetPrawdopodobienstwo();
    public final void Zasiej(){
        int x = (int)(Math.random()*100);
        if(x>=(this.GetPrawdopodobienstwo()))
            return;
        if(!SprawdzCzyMoznaBezpiecznieRuszyc(1))
            return;
        Polozenie nowePolozenie = new Polozenie();
        boolean uniq=true;
        int randx, randy;
        while(true) {
            randx=((int)(Math.random()*3)-1);
            randy=((int)(Math.random()*3)-1);
            uniq=true;
            nowePolozenie.Set(polozenie.GetX()+randx, polozenie.GetY()+randy);
            if(!(this.swiat instanceof SwiatHex)) {
                if (nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM()) {
                    for (Organizm organizm : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm.GetPolozenie()))
                            uniq = false;
                    }
                    if (uniq) {
                        break;
                    }
                }
            }
            else{
                if(randx==-1&&randy==0)
                    nowePolozenie.Set(nowePolozenie.GetX()+2, nowePolozenie.GetY()-2);
                else if(randx==1&&randy==0)
                    nowePolozenie.Set(nowePolozenie.GetX()-2, nowePolozenie.GetY()+2);

                if (nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM() && !(randx ==-1&&randy==-1) && !(randx ==1&&randy==1)) {
                    for (Organizm organizm : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm.GetPolozenie()))
                            uniq = false;
                    }
                    if (uniq) {
                        break;
                    }
                }

            }
        }
        this.SetZdolnoscRozrodu(false);
        swiat.zdarzenia.DodajString("Roslina : " + this.Rysowanie() + " zasiala na polu: " + nowePolozenie);
        swiat.NarodzOrganizm(this, nowePolozenie, TrybNarodz.Auto);
    };
    public abstract Organizm Urodz();
    public abstract boolean MozeBycPartnerem(Organizm organizm);
}

