package Symulacja;

public class Polozenie {
    private int x,y;
    public Polozenie(int x, int y){
        Set(x,y);
    }
    public Polozenie(){
        Set(0,0);
    }
    public Polozenie(Polozenie polozenie){
        Set(polozenie.GetX(), polozenie.GetY());
    }
    public void Set(int x, int y){
        this.x=x;
        this.y=y;
    }
    public void Set(Polozenie innePolozenie){
        Set(innePolozenie.GetX(), innePolozenie.GetY());
    }
    public int GetX(){
        return x;
    }
    public int GetY(){
        return y;
    }
    @Override
    public String toString(){
     return toString(TrybToString.Ladnie);
    }
    public String toString(TrybToString tryb){
        if(tryb==TrybToString.Ladnie)
           return "(" + x + "," + y + ")";
        else
            return x + " " + y;
    }
    @Override
    public boolean equals(Object obiekt){
        if(obiekt instanceof Polozenie){
           if(((Polozenie) obiekt).x==this.x && (((Polozenie) obiekt).y==this.y))
                return true;
        }
        return false;
    }
}
