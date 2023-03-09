package Symulacja;

import java.util.ArrayList;
import java.util.List;

public class Sluchacz {
    public Sluchacz(){

    }
    List<String> zdarzenia = new ArrayList<>();
    public void DodajString(String s){
        String text = new String();
        text = s + " <br/>";
        zdarzenia.add(text);
    }
    public String Wypisz(){
        String calyTekst = new String();
        for(String zdarzenie:zdarzenia){
            calyTekst+=zdarzenie;
        }
        return calyTekst;
    }
    public void Wyczysc(){
        zdarzenia.clear();
    }


}
