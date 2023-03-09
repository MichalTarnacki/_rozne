--Wyswietl wszystkie relacje klient-firma z jakimi klient zawieral umowe kupna-sprzedazy. Serwis chce wyslac powiadomienie do uzytkownikow powiadomienie o zmianie warunkow korzystania z serwisu
select DISTINCT Klient.ID as ID_Klienta, Klient.Imie, Klient.Nazwisko, Firma.ID as ID_Firmy, Firma.Nazwa as Nazwa_Firmy from Zamowienie
join Klient on Klient.ID = Zamowienie.ID_Klienta
join Punkt_Sprzedazy on ID_Punktu_Sprzedazy = Punkt_Sprzedazy.ID
join Firma on Punkt_Sprzedazy.ID_Firmy = Firma.ID
order by Klient.Nazwisko asc;

--Licz procentowy udzial krajow w zamowieniach realizowanych po 14. Serwis opracowuje nowe metody reklamowania konkretnych produktow
select Kraj, 100 * Count(*) / SUM(Count(*)) over () as Udzial_Procentowy
from Zamowienie
join Klient on Zamowienie.ID_Klienta = Klient.ID
join Adres on Adres.ID = Klient.ID_Adresu
where Godzina > '14:00'
group by Kraj
order by Udzial_Procentowy desc

--Wyswietl opisy 3 gatunkow jakie najczesciej zamawiaja klienci. Sprzedawcy chca wiedziec jakie sa aktualnie trendy i dostosowac do nich sprzedaz
GO
CREATE VIEW El_Zamowienia_Gatunek
as select Element_zamowienia.ID_Dystrybucji, Gatunek.Nazwa, Gatunek.Opis, Gatunek.Cechy
from Element_zamowienia, Dystrybucja, Gra, Nalezy, Gatunek
where Dystrybucja.ID = Element_zamowienia.ID_Dystrybucji
and Gra.ID = Dystrybucja.ID_Gry
and Gra.ID = Nalezy.ID_Gry
and Nalezy.Nazwa_Gatunku = Gatunek.Nazwa;
GO

select Nazwa, Opis
from
	(
	select top 3 Nazwa, Opis, Cechy, Count (*) as Ilosc
	from El_Zamowienia_Gatunek
	group by Nazwa, Opis, Cechy
	order by Ilosc desc
	)
AS TOP3;

GO
DROP VIEW El_Zamowienia_Gatunek
GO

--Wyswietl wszystkie fimy ktore jednoczesnie prowadza sprzedaz, produkuja gry na komputery oraz je dystrybuuja
select Nazwa, Opis from Firma
where ID in
	(
	select ID_Firmy from Gra
	)
and ID in
	(
	select ID_Firmy from Dystrybucja
	)
and ID in
	(
	select ID_Firmy from Punkt_Sprzedazy
	);
-------------

--Ile zamowien zlozonych w ciagu ostatniego miesiaca zrealizowaly poszczegolne punkty sprzedazy firmy Licomp Empirical Multimedia? Podaj dla kazdego z punktow ID, nazwe i typ).
--(Firma analizuje uzytecznosc i popularnosc swoich punktow sprzedazy).

GO
CREATE VIEW Zebrane_Zam_Licomp_Short
as select Punkt_Sprzedazy.ID, Nazwa, Punkt_Sprzedazy.Typ, Count(*) as Liczba_Zamowien
from Punkt_Sprzedazy
join Zamowienie on ID_Punktu_sprzedazy = Punkt_Sprzedazy.ID
where Data between DATEADD(m, -1, GETDATE()) and GETDATE() and Status = 'Zrealizowane' and ID_Firmy in (
select ID from Firma where Nazwa = 'Licomp Empirical Multimedia')
group by Punkt_Sprzedazy.ID, Nazwa, Punkt_Sprzedazy.Typ;
--order by Liczba_Zamowien desc;
GO

select ID, Nazwa, Typ, Liczba_Zamowien
from Zebrane_Zam_Licomp_Short
union
select ID, Nazwa, Typ, 0 as Liczba_Zamowien
from Punkt_Sprzedazy where ID_Firmy in
	(
	select ID from Firma
	where Nazwa = 'Licomp Empirical Multimedia'
	)
and ID not in
	(
	select ID from Zebrane_Zam_Licomp_Short
	)
order by Liczba_Zamowien desc, Nazwa asc;

GO
DROP VIEW Zebrane_Zam_Licomp_Short
GO

--Dystrybucje gier produkowanych przez ktore firmy (podac ID i nazwe) ze Stanow Zjednoczonych byly najczesciej elementami zamowienia skladanego przez klientow posiadajacych adres poza Stanami?
-- (Analitycy rynku prowadza badania sukcesow odnoszonych przez polskie firmy za granica).
select Firma.ID, Firma.Nazwa, Sum(Ilosc) as Ilosc
from Element_zamowienia
join Dystrybucja on Dystrybucja.ID = Element_zamowienia.ID_Dystrybucji
join Gra on Dystrybucja.ID_Gry = Gra.ID
join Firma on Firma.ID = Gra.ID_Firmy
join Zamowienie on Element_zamowienia.ID_Zamowienia = Zamowienie.ID
join Klient on Zamowienie.ID_Klienta = Klient.ID
join Adres on Klient.ID_Adresu = Adres.ID
where Gra.ID_Firmy in
	(
	select ID from Firma
	where Kraj = 'Stany Zjednoczone'
	)
and Adres.Kraj not like 'Stany Zjednoczone'
group by  Firma.ID, Firma.Nazwa
order by Ilosc desc;

--Ktore gry (podac ID i nazwe) z gatunku TPP sa produkowane na konsole Xbox 360 z ograniczeniem PAL?
--(Pracownicy serwisu tworza aplikacje ulatwiajaca wyszukiwanie gier przez uzytkownikow).
select  Gra.ID, Gra.Nazwa
from Jest_na
join Konsola on ID_Konsoli = Konsola.ID
join Gra on Gra.ID = ID_Gry
where Jest_na.ID_Gry in
	(
	select ID_Gry from Nalezy
	where Nazwa_Gatunku = 'TPP'
	)
and Konsola.Nazwa = 'Xbox 360' and Ograniczenie_regionalne = 'PAL'

--Ruszyla kampania "Na Macintoshu tez mozna grac!": wypisz tytuly wszystkich gier, ktore premiere na rynku polskim mialy po 2005 roku, ktore mozna uruchomic na systemie MacOS.
select DISTINCT Nazwa from
Wymagania_sprzetowe
join Gra on ID = ID_Gry
where ID_Gry in
	(
	select ID_Gry
	from Dystrybucja
	where Data_premiery > '2005-12-31' and Rynek = 'Polska'
	)
and System = 'MacOs'

--Potrzebne jest zestawienie kompatybilnosci platformowej nowych gier: Wypisz ile tytulow, ktore premiere w Polsce mialy po 2009 roku, zostalo wydanych na poszczegolne platformy. Liste posortuj alfabetycznie wzgledem nazwy platformy.

GO
CREATE VIEW IL_Na_Poszcz_Kons
as select  Nazwa, COUNT(*) as Ile_Gier
from Jest_na
join Konsola on ID = ID_Konsoli
where ID_Gry in (
select ID_Gry
from Dystrybucja
where Data_premiery > '2008-12-31' and Rynek = 'Polska'
group by ID_Gry )
group by Nazwa
GO

select  Nazwa, Ile_Gier
from IL_Na_Poszcz_Kons
union
select Nazwa, 0 as Ile_Gier
from Konsola where Nazwa not in
	(
	select Nazwa from IL_Na_Poszcz_Kons
	)
order by Nazwa asc;

GO
DROP VIEW IL_Na_Poszcz_Kons
GO

--Planowana jest ekspansja serwisu: przygotuj zestawienie punktow sprzedazy posortowanych malejaco ze wzgledu na sume skompletowanych przedmiotow w 2023 roku (sumy rowniez zawrzec w zestawieniu).
select ID_Punktu_sprzedazy, Nazwa, SUM(Ilosc) as Ile_Przedmiotow
from Element_zamowienia
join Zamowienie on ID_Zamowienia = ID
join Punkt_Sprzedazy on Punkt_Sprzedazy.ID = ID_Punktu_sprzedazy
where YEAR(Data) = 2023 and Status = 'Zrealizowane'
group by ID_Punktu_sprzedazy, Nazwa
order by Ile_Przedmiotow  desc;
