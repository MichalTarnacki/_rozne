package Symulacja;

public class KonfiguracjaOrganizmow {
    public int liczbaLudzi,
     liczbaWilkow,
     liczbaOwiec,
     liczbaLisow,
     liczbaZolwi,
     liczbaAntylop,
     liczbaCyberOwiec,
     liczbaTraw,
     liczbaMleczy,
     liczbaGuarany,
     liczbaWilczychJagod,
     liczbaBarszuSosnowskiego;

    public KonfiguracjaOrganizmow(
             int liczbaLudzi,
             int liczbaWilkow,
             int liczbaOwiec,
             int liczbaLisow,
             int liczbaZolwi,
             int liczbaAntylop,
             int liczbaCyberOwiec,
             int liczbaTraw,
             int liczbaMleczy,
             int liczbaGuarany,
             int liczbaWilczychJagod,
             int liczbaBarszuSosnowskiego){
        this.liczbaLudzi = liczbaLudzi;
        this.liczbaWilkow = liczbaWilkow;
        this.liczbaOwiec = liczbaOwiec;
        this.liczbaLisow = liczbaLisow;
        this.liczbaZolwi = liczbaZolwi;
        this.liczbaAntylop = liczbaAntylop;
        this.liczbaCyberOwiec = liczbaCyberOwiec;
        this.liczbaTraw = liczbaTraw;
        this.liczbaMleczy = liczbaMleczy;
        this.liczbaGuarany = liczbaGuarany;
        this.liczbaWilczychJagod = liczbaWilczychJagod;
        this.liczbaBarszuSosnowskiego = liczbaBarszuSosnowskiego;

    };
     public int getLacznaLiczbaOrganizmow(){
        return (
                liczbaWilkow +
                        liczbaOwiec +
                        liczbaLisow +
                        liczbaZolwi +
                        liczbaAntylop +
                        liczbaCyberOwiec +
                        liczbaTraw +
                        liczbaMleczy +
                        liczbaGuarany +
                        liczbaWilczychJagod +
                        liczbaBarszuSosnowskiego +
                        liczbaLudzi
        );
    }

}
