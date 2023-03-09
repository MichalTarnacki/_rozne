package Symulacja;

public class Plansza {
    private int N, M; //N to X, M to y
    public Plansza(){
        Set(0,0);
    }
    public Plansza(int N, int M){
        Set(N, M);
    }
    public Plansza(Plansza innaPlansza){
        Set(innaPlansza.GetN(), innaPlansza.GetM());
    }
    public int GetM(){
        return this.M;
    }
    public int GetN(){
        return this.N;
    }
    public int GetLiczbaPol(){
        return N*M;
    }
    public void Set(int N, int M){
        this.N=N;
        this.M=M;
    }
    public void Set(Plansza innaPlansza){
        Set(innaPlansza.GetN(), innaPlansza.GetM());
    }
    @Override
    public String toString(){
        return toString(TrybToString.Ladnie);
    }
    public String toString(TrybToString tryb){
        if(tryb==TrybToString.Ladnie)
            return "[" + N + "x" + M + "]";
        else
            return N + " " + M;
    }
}
