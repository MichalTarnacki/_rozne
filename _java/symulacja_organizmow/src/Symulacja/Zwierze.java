package Symulacja;

public abstract class Zwierze extends Organizm {
    protected abstract void SetInicjatywa();
    protected abstract void SetSila();
    public Zwierze(Swiat swiat){
        super(swiat);
    };
    public void Akcja(){
        Ruch();
    };
    public abstract char Rysowanie();
    public void Ruch(){
        Ruch(1);
    };
    public void Ruch(int zasiegRuchu){
        boolean moznaRuszyc=false;
        Polozenie nowePolozenie = new Polozenie();
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1; j++) {
                nowePolozenie.Set(this.GetPolozenie().GetX() + j * zasiegRuchu, this.GetPolozenie().GetY() + i * zasiegRuchu);
                if(!(this.swiat instanceof SwiatHex)) {
                    if (!nowePolozenie.equals(this.GetPolozenie()) && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM())
                        moznaRuszyc = true;
                }
                else{
                    //dodac poprawke
                    if(nowePolozenie.equals(new Polozenie(this.polozenie.GetX()-zasiegRuchu, this.polozenie.GetY())))
                        nowePolozenie.Set(nowePolozenie.GetX()+2*zasiegRuchu, nowePolozenie.GetY()-2*zasiegRuchu);
                    else if(nowePolozenie.equals(new Polozenie(this.polozenie.GetX()+zasiegRuchu, this.polozenie.GetY())))
                    nowePolozenie.Set(nowePolozenie.GetX()-2*zasiegRuchu, nowePolozenie.GetY()+2*zasiegRuchu);
                    if (!nowePolozenie.equals(this.GetPolozenie()) && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM() && !(i==-zasiegRuchu&&j==-zasiegRuchu) && !(i==zasiegRuchu&&j==zasiegRuchu))
                        moznaRuszyc = true;
                }
            }
        }
        if(!moznaRuszyc)
            return;
        int randx, randy;
        if(!(this.swiat instanceof SwiatHex)) {
            do {
                randx=zasiegRuchu * ((int) (Math.random() * 3) - 1);
                randy=zasiegRuchu * ((int) (Math.random() * 3) - 1);
                nowePolozenie.Set(polozenie.GetX() + randx, polozenie.GetY() + randy);
            } while (nowePolozenie.equals(polozenie) || nowePolozenie.GetX() < 0 || nowePolozenie.GetY() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM());
            polozenie.Set(nowePolozenie);
        }
        else{
            do {
                randx=zasiegRuchu * ((int) (Math.random() * 3) - 1);
                randy=zasiegRuchu * ((int) (Math.random() * 3) - 1);

                nowePolozenie.Set(polozenie.GetX() + randx, polozenie.GetY() + randy);
                if(randx==-zasiegRuchu&&randy==0)
                    nowePolozenie.Set(nowePolozenie.GetX()+2*zasiegRuchu, nowePolozenie.GetY()-2*zasiegRuchu);
                else if(randx==zasiegRuchu&&randy==0)
                    nowePolozenie.Set(nowePolozenie.GetX()-2*zasiegRuchu, nowePolozenie.GetY()+2*zasiegRuchu);
            } while (nowePolozenie.equals(polozenie) || nowePolozenie.GetX() < 0 || nowePolozenie.GetY() < 0 || nowePolozenie.GetX() >= swiat.GetPlansza().GetN() || nowePolozenie.GetY() >= swiat.GetPlansza().GetM() || (randx ==-zasiegRuchu && randy==-zasiegRuchu) || (randx==zasiegRuchu && randy==zasiegRuchu));
            System.out.println("zmiana z " + polozenie);
            System.out.println(nowePolozenie);
            polozenie.Set(nowePolozenie);
        }
    };
    public boolean RuchBezKolizji(int zasiegRuchu){
        if(!SprawdzCzyMoznaBezpiecznieRuszyc(zasiegRuchu))
            return false;
        Polozenie nowePolozenie = new Polozenie();
        boolean uniq=true;
        int randx, randy;
        while(true) {
            uniq=true;
            randx=zasiegRuchu*((int)(Math.random()*3)-1);
            randy=zasiegRuchu*((int)(Math.random()*3)-1);
            nowePolozenie.Set(polozenie.GetX()+randx, polozenie.GetY()+randy);
            if(!(this.swiat instanceof SwiatHex)) {
                if (!(nowePolozenie.equals(polozenie)) && nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM()) {
                    for (Organizm organizm : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm.GetPolozenie()))
                            uniq = false;
                    }
                    if (uniq) {
                        this.SetPolozenie(nowePolozenie);
                        break;
                    }
                }
            }
            else{
                if(nowePolozenie.equals(new Polozenie(this.polozenie.GetX()-zasiegRuchu, this.polozenie.GetY())))
                    nowePolozenie.Set(nowePolozenie.GetX()+2*zasiegRuchu, nowePolozenie.GetY()-2*zasiegRuchu);
                else if(nowePolozenie.equals(new Polozenie(this.polozenie.GetX()+zasiegRuchu, this.polozenie.GetY())))
                    nowePolozenie.Set(nowePolozenie.GetX()-2*zasiegRuchu, nowePolozenie.GetY()+2*zasiegRuchu);

                if (!(nowePolozenie.equals(polozenie)) && nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM() && !(randx==-zasiegRuchu&&randy==-zasiegRuchu) && !(randx==zasiegRuchu&&randy==zasiegRuchu)) {
                    for (Organizm organizm : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm.GetPolozenie()))
                            uniq = false;
                    }
                    if (uniq) {
                        this.SetPolozenie(nowePolozenie);
                        break;
                    }
                }

            }
        }
        return true;
    };
    public abstract Organizm Urodz();
    public abstract boolean MozeBycPartnerem(Organizm organizm);
    public void Kolizja(Organizm organizm){
        if(MozeBycPartnerem(organizm)){
            organizm.SetPolozenie(organizm.GetPoprzedniePolozenie());
            if(organizm.CzyMozeSieRozmnazac()&&this.CzyMozeSieRozmnazac())
                Kopulacja(organizm);
        }
        else
            super.Kolizja(organizm);

    };
    public void Kopulacja(Organizm organizm){
        if(!organizm.SprawdzCzyMoznaBezpiecznieRuszyc(1))
            return;
        Polozenie nowePolozenie = new Polozenie();
        boolean uniq=true;
        int randx, randy;
        while(true) {
            uniq=true;
            randx=(int)(Math.random()*3)-1;
            randy=(int)(Math.random()*3)-1;
            nowePolozenie.Set(organizm.GetPolozenie().GetX()+randx, organizm.GetPolozenie().GetY()+randy);
            if(!(this.swiat instanceof SwiatHex)) {
                if (nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM()) {
                    for (Organizm organizm1 : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm1.GetPolozenie()))
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
                if (nowePolozenie.GetX() >= 0 && nowePolozenie.GetY() >= 0 && nowePolozenie.GetX() < swiat.GetPlansza().GetN() && nowePolozenie.GetY() < swiat.GetPlansza().GetM() && !(randx==-1&&randy==-1) && !(randx==1&&randy==1)){
                    for (Organizm organizm1 : swiat.GetOrganizmy()) {
                        if (nowePolozenie.equals(organizm1.GetPolozenie()))
                            uniq = false;
                    }
                    if (uniq) {
                        break;
                    }
                }

            }
        }
        this.SetZdolnoscRozrodu(false);
        organizm.SetZdolnoscRozrodu(false);
        swiat.zdarzenia.DodajString("Zwierze : " + this.Rysowanie() + " rozmnaza sie, a jego dziecko laduje na polu: " + nowePolozenie);
        swiat.NarodzOrganizm(this, nowePolozenie, TrybNarodz.Auto);
    }

}
