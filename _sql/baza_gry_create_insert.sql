	 use master
ALTER DATABASE sad SET SINGLE_USER WITH ROLLBACK IMMEDIATE
	Drop DATABASE sad;

CREATE DATABASE sad
use sad;

CREATE TABLE Firma( 
ID CHAR(4) PRIMARY KEY, --CHECK(ID not like '%^[^A-Z][^a-z][^A-Z][^a-z]%')
Nazwa VARCHAR(MAX) NOT NULL, 
Opis VARCHAR(200) NOT NULL, 
Data_zalozenia DATE NOT NULL, 
Dodatkowe_informacje VARCHAR(MAX), 
Kraj VARCHAR(MAX) CHECK(Kraj not like '%[^A-Z ]%') NOT NULL, 
); 

CREATE TABLE Gatunek( 
Nazwa VARCHAR(30) CHECK(Nazwa not like '%[^A-Z ]%') PRIMARY KEY, 
Cechy VARCHAR(MAX) NOT NULL, ---??????
Opis VARCHAR(300) NOT NULL, 
); 

CREATE TABLE Konsola( 
ID VARCHAR(8) CHECK(ID not like '%[^A-Z0-9]%' and DATALENGTH(ID) >= 2 and upper(ID) = ID collate SQL_Polish_CP1250_CS_AS) PRIMARY KEY, 
Nazwa VARCHAR(MAX) NOT NULL, 
Ograniczenie_regionalne VARCHAR(4) COLLATE SQL_Polish_CP1250_CS_AS CHECK(Ograniczenie_regionalne IN('NTSC', 'PAL')), 
ID_Firmy CHAR(4) REFERENCES Firma ON DELETE SET NULL ON UPDATE CASCADE, 
) 
--okej 
CREATE TABLE Gra( 
ID VARCHAR(10) CHECK(ID not like '%[^A-Z0-9]%' and DATALENGTH(ID) >= 2 and upper(ID) = ID collate SQL_Polish_CP1250_CS_AS) PRIMARY KEY, 
Nazwa VARCHAR(MAX) NOT NULL, 
Liczba_graczy VARCHAR(MAX) CHECK(Liczba_graczy not like '%[^0-9\/\-]%') NOT NULL, --CHECK((Liczba_graczy not like '%[^0-9]%') or Liczba_graczy not like '%[^A-Z0-9]%') 
Opis VARCHAR(300) CHECK(DATALENGTH(Opis) >= 50) NOT NULL, 
Funkcje_sieciowe CHAR(3) CHECK(Funkcje_sieciowe IN('tak', 'nie') and lower(Funkcje_sieciowe) = Funkcje_sieciowe collate SQL_Polish_CP1250_CS_AS) NOT NULL, 
Data_zapowiedzi DATE NOT NULL, 
ID_Firmy CHAR(4) REFERENCES Firma ON DELETE SET NULL ON UPDATE CASCADE, 
); 

CREATE TABLE Wymagania_sprzetowe( 
ID_Gry VARCHAR(10) REFERENCES Gra ON UPDATE CASCADE, 
System VARCHAR(30) CHECK((System not like '%[^A-Z0-9 \.\(\)\/\-]%')), 
Typ VARCHAR(9) CHECK(Typ IN('minimalne', 'zalecane') and (lower(Typ) = Typ collate SQL_Polish_CP1250_CS_AS)), 
Miejsce_na_dysku VARCHAR(MAX) CHECK(Miejsce_na_dysku not like '%[^A-Z0-9 ,]%' and (upper(Miejsce_na_dysku) = Miejsce_na_dysku collate SQL_Polish_CP1250_CS_AS)) NOT NULL, 
Procesor VARCHAR(MAX) NOT NULL, 
Karta_graficzna VARCHAR(MAX) NOT NULL, 
Ilosc_RAM VARCHAR(MAX) CHECK(Ilosc_RAM not like '%[^A-Z0-9 ,]%' and (upper(Ilosc_RAM) = Ilosc_RAM collate SQL_Polish_CP1250_CS_AS)) NOT NULL, 
PRIMARY KEY(ID_Gry, System, Typ) 
); 

CREATE TABLE Dystrybucja( 
ID VARCHAR(30) CHECK(ID not like '%[^A-Z0-9/]%' and DATALENGTH(ID) >= 2 and (upper(ID) = ID collate SQL_Polish_CP1250_CS_AS)) PRIMARY KEY, 
Rynek VARCHAR(MAX) CHECK(Rynek not like '%[^A-Z0-9/ ]%' and DATALENGTH(Rynek) >= 2) NOT NULL, 
Klasyfikacja VARCHAR(MAX) CHECK(Klasyfikacja not like '%[^A-Z0-9:, \/]%'), 
Jezyk VARCHAR(MAX) CHECK(Jezyk not like '%[^A-Z/]%') NOT NULL, 
Data_premiery DATE NOT NULL, 
ID_Firmy CHAR(4) REFERENCES Firma ON DELETE SET NULL ON UPDATE CASCADE , 
ID_Gry VARCHAR(10) REFERENCES Gra, 
); 
--okej ^
CREATE TABLE Nalezy( 
Nazwa_Gatunku VARCHAR(30) REFERENCES Gatunek ON UPDATE CASCADE, 
ID_Gry VARCHAR(10) REFERENCES Gra, 
PRIMARY KEY(ID_Gry, Nazwa_Gatunku), 
); 
CREATE TABLE Jest_na( 
ID_Gry VARCHAR(10) REFERENCES Gra, 
ID_Konsoli VARCHAR(8) REFERENCES Konsola ON UPDATE CASCADE, 
PRIMARY KEY(ID_Gry, ID_Konsoli), 
); 
--check
CREATE TABLE Adres(
ID CHAR(4) COLLATE SQL_Polish_CP1250_CS_AS CHECK(ID not like '%[^A-Za-z0-9]%') PRIMARY KEY,
Kraj VARCHAR(MAX) CHECK(Kraj not like '%[^A-Z ]%') NOT NULL,
Miasto VARCHAR(MAX) CHECK(Miasto not like '%[^A-Z]%') NOT NULL,
Kod_pocztowy VARCHAR(MAX) CHECK(Kod_pocztowy not like '%[^A-Z0-9]%' and (upper(Kod_pocztowy) = Kod_pocztowy collate SQL_Polish_CP1250_CS_AS)) NOT NULL,
Ulica VARCHAR(MAX) NOT NULL,
Numer VARCHAR(MAX) NOT NULL,
);

CREATE TABLE Punkt_Sprzedazy( 
ID CHAR(7) CHECK(ID not like '%[^A-Z0-9]%') PRIMARY KEY, 
Nazwa VARCHAR(40) NOT NULL, 
Typ VARCHAR(MAX) CHECK(Typ IN('stacjonarny', 'internetowy', 'brak') and (lower(Typ) = Typ collate SQL_Polish_CP1250_CS_AS)) NOT NULL, 
ID_Firmy CHAR(4) REFERENCES Firma ON DELETE CASCADE ON UPDATE CASCADE, 
ID_Adresu CHAR(4) COLLATE SQL_Polish_CP1250_CS_AS REFERENCES Adres ON DELETE SET NULL, 
); 

CREATE TABLE Klient( 
ID CHAR(4) COLLATE SQL_Polish_CP1250_CS_AS CHECK(ID not like '%[^A-Za-z0-9]%') PRIMARY KEY, 
Imie VARCHAR(MAX) CHECK(Imie not like '%[^A-Z]%') NOT NULL, 
Nazwisko VARCHAR(MAX) CHECK(Nazwisko not like '%[^A-Z-/ "|]%') NOT NULL, 
Plec VARCHAR(9) CHECK(Plec IN('mezczyzna', 'kobieta')  and (lower(Plec) = Plec collate SQL_Polish_CP1250_CS_AS)), 
Wiek TINYINT, 
ID_Adresu CHAR(4) COLLATE SQL_Polish_CP1250_CS_AS REFERENCES Adres 
); 

CREATE TABLE Zamowienie( 
ID CHAR(13) COLLATE SQL_Polish_CP1250_CS_AS CHECK(ID not like '%[^A-Za-z0-9]%') PRIMARY KEY, 
Data DATE NOT NULL, 
Godzina TIME NOT NULL, 
Typ VARCHAR(MAX) CHECK(Typ IN('stacjonarne', 'internetowe') and lower(Typ) = Typ collate SQL_Polish_CP1250_CS_AS) NOT NULL, 
Status VARCHAR(MAX) CHECK(Status IN('w realizacji', 'zrealizowane', 'anulowane') and lower(Status) = Status collate SQL_Polish_CP1250_CS_AS) NOT NULL, 
ID_Klienta CHAR(4) COLLATE SQL_Polish_CP1250_CS_AS REFERENCES Klient NOT NULL  , 
ID_Punktu_sprzedazy CHAR(7) REFERENCES Punkt_sprzedazy ON DELETE CASCADE ON UPDATE CASCADE NOT NULL, 
); 

CREATE TABLE Element_zamowienia(
ID_Dystrybucji VARCHAR(30) REFERENCES Dystrybucja,
ID_Zamowienia CHAR(13) COLLATE SQL_Polish_CP1250_CS_AS REFERENCES Zamowienie ON DELETE CASCADE ON UPDATE CASCADE,
Ilosc Int NOT NULL,
Cena_jednostkowa VARCHAR(MAX) CHECK(Cena_jednostkowa not like '%[^A-Z0-9 ,]%') NOT NULL,
PRIMARY KEY(ID_Dystrybucji, ID_Zamowienia),
);


INSERT INTO Firma
Values
('NeHo', 'The Neverhood, Inc.', 'Firma The Neverhood, Inc. zaczela dzialac na rynku juz przed 1996 rokiem. Jej pierwszym i jak dotad jedynym projektem byla gra The Neverhood.', '1995-10-31', NULL , 'Stany Zjednoczone'),
('AcBz', 'Activision', 'Activision zalozyli byli programisci Atari, tacy jak David Crane, Larry Kaplan, Alan Miller czy Bob Whitehead, skonfliktowani z prezesem firmy, Rayem Kassarem.', '1979-10-01', 'ISIN:
US00507V1098', 'Stany Zjednoczone'),
('DwIn', 'DreamWorks Interactive', 'Firma zostala zalozona w 1995 roku jako DreamWorks Interactive LLC, filia DreamWorks SKG', '1995-09-15', NULL, 'Stany Zjednoczone'),
('RhSt', 'Riverhillsoft', 'Japonski producent oraz wydawca gier komputerowych', '1982-08-10', 'Firma zbankrutowala w 2004', 'Japonia'),
('ScOe', 'Sony Computer Entertainment', 'Poboczna firma Sony. Zajmuje sie rozwojem, produkcja oraz sprzedaza sprzetu i oprogramowania dla serii konsoli PlayStation.', '1993-11-16', 'Forma prawna: LLC', 'Japonia'),
('LiEm', 'Licomp Empirical Multimedia', 'Istniejacy na rynku polskim od 1997 roku (poczatkowo jako Licomp Empik Multimedia) wydawca i dystrybutor gier wideo na komputery osobiste oraz konsole', '1997-10-12', 'Nr KRS: 0000065089', 'Polska'),
('CeGa', 'Cenega S.A.', 'Jeden z najwiekszych i najstarszych polskich wydawcow gier na komputery PC oraz konsole', '2000-10-31', NULL, 'Polska'),
('CrDy', 'Crystal Dynamics', 'Amerykanskie studio deweloperskie (a poczatkowo rowniez wydawca gier) na komputery osobiste oraz konsole. Od roku 2009 firma jest czescia japonskiego giganta wydawniczego, koncernu Square Enix', '1992-12-01', NULL, 'Stany Zjednoczone'),
('SqEn', 'Square Enix', 'Jeden z najwiekszych producentow i wydawcow w branzy gier wideo', '2003-04-01', NULL, 'Japonia'),
('NeSt', 'Neversoft Entertainment', 'Amerykanski tworca gier wideo', '1997-09-20', NULL, 'Stany Zjednoczone'),
('RoGa', 'Rockstar Games', 'Swoja dzialalnosc deweloperska firma Rockstar Games prowadzi obecnie poprzez dziesiec studiow deweloperskich, ulokowanych w Stanach Zjednoczonych, Kanadzie, Europie oraz Azji', '1998-03-17', NULL, 'Stany Zjednoczone'),
('MiSo', 'Microsoft', 'Amerykanskie przedsiebiorstwo informatyczne', '1975-04-04', 'ISIN: US5949181045', 'Stany Zjednoczone'),
('NiDo', 'Nintendo', 'Miedzynarodowa Japonska firma produkujaca konsole oraz gry wideo', '1889-08-23', 'ISIN: JP3756600007', 'Japonia');

INSERT INTO Gatunek
Values
('jRPG', 'Otwarty swiat, nieliniowa fabula', 'Gracz wciela sie w bohatera ktorego rozwija'),
('Przygodowe', 'Eksploracja, rozwiazywanie zagadek, zaakcentowana fabula', 'Gracz zbiera przedmioty aby rozwiazywac zagadki i popychac historie do przodu'),
('Point and click', 'Sterowanie mysza, widok trzecioosobowy', 'Gracz wciela sie obserwatora swiata, ktorym moze sterowac z gory'),
('FPS', 'Widok pierwszoosobowy, strzelanie, przemoc', 'Gracz wciela sie w postac strzelajaca bronia do przeciwnikow. Akcje widzi z perspektywy pierwszoosobowej'),
('TPP', 'Widok trzecioosobowy, akcja, zagadki', 'Gracz wciela sie w postac o znanym wizerunku, sterujac nia z perspektywy znajdujacej sie za jej plecami'),
('Platformowe', 'Widok z boku, wymagana zrecznosc','Gracz wciela sie w postac, ktora porusza po platformach'),
('Zrecznosciowe', 'Wymagana zwinnosc', 'Glownym zadaniem gracza jest dotarcie do wyznaczonego celu lub pokonanie przeciwnikow, wykazujac sie przy tym sprawnym kontrolowaniem prowadzonej postaci lub pojazdu'),
('Logiczne', 'Wymagane logiczne myslenie, strategia i spostrzegawczosc', 'Gatunek gier, w ktorych nadrzednym celem jest rozwiazywanie zagadek logicznych'),
('Akcji', 'Wymagany refleks, celnosc oraz zrecznosc', 'Najczesciej w produkcjach tego typu gracz kontroluje bohatera, ktorego zadaniem jest pokonanie wrogow i dotarcie do z gory okreslonego celu.'),
('Sportowe', 'Wymagana zrecznosc, refleks, szybkosc oraz taktyczne planowanie dzialan', 'Gry symulujace okreslona dyscypline sportowa, np. pilke nozna, koszykowke czy siatkowke');

INSERT INTO Gra
VALUES
('CODBO2', 'Call of Duty: Black Ops II','2/4','Kontynuacja przebojowej strzelaniny (FPS) z 2010 roku. Call of Duty: Black Ops II jest dziewiata odslona cyklu Call of Duty i jednoczesnie czwarta wyprodukowana przez studio deweloperskie Treyarch. Fabula gry osadzona zostala w niedalekiej przyszlosci.','tak', '2011-11-08', 'AcBz'),
('NEHO', 'The Neverhood','1','Oryginalna przygodowka point-and-click, opracowana we wspolpracy tworcy gry Earthworm Jim, Douga TenNapela, z wytwornia filmowa DreamWorks Interactive oraz samym Stevenem Spielbergiem.','nie', '1995-04-25', 'NeHo'),
('CODBO4', 'Call of Duty: Black Ops IIII','2-4','Czwarta strzelanka spod szyldu Black Ops, za ktorej opracowaniem stoi studio Treyarch. Call of Duty: Black Ops IIII nie posiada kampanii dla pojedynczego gracza, zamiast tego autorzy wzbogacili liste trybow o multiplayerowe zmagania battle royale, noszace miano Blackout.','tak', '2018-03-08', 'AcBz'),
('TR', 'Tomb Raider', '1', 'Dziesiata odslona przygod Lary Croft, stanowiaca zarazem reboot serii przygodowych gier akcji Tomb Raider','tak','2011-06-01', 'CrDy'),
('FFVIIR', 'Final Fantasy VII Remake','1','Nowa wersja jednej z najpopularniejszych gier jRPG wszech czasow, opracowana przez Square Enix.','nie', '2015-06-16', 'SqEn'),
('FFXVI', 'Final Fantasy XVI','1','Szesnasta glowna czesc bestsellerowej serii japonskich RPG-ow.','nie', '2022-12-15', 'SqEn'),
('THPS2', 'Tony Hawks Pro Skater 2','1', 'Kontynuacja wydanej w 1999 roku gry sportowej o jezdzie na deskorolce, sygnowanej nazwiskiem slynnego skateboardzisty','nie','1999-04-20', 'NeSt'),
('GTAV', 'Grand Theft Auto V','1','Piata pelnoprawna odslona niezwykle popularnej serii gier akcji','tak','2012-09-12', 'RoGa'),
('GTASA', 'Grand Theft Auto: San Andreas','1','Kontynuacja kontrowersyjnego cyklu Grand Theft Auto','nie', '2003-12-01','RoGa'),
('GTAIV', 'Grand Theft Auto IV','1','Czwarta czesc bijacego rekordy popularnosci cyklu gier akcji','tak','2006-12-06', 'RoGa');

INSERT INTO Wymagania_sprzetowe
Values 
('CODBO2', 'Windows Vista(SP2)/7', 'zalecane', '16 GB', 'Intel Core 2 Duo 2.66 GHz', 'Nvidia GeForce 8800 GT', '4 GB'),
('NEHO', 'Windows', 'zalecane', '595 MB', 'Intel Pentium 166MHz', 'nd.', '32 MB'),
('CODBO4', 'Windows 7 64-bit', 'minimalne', '60 GB', 'Intel Core i3-4340 3.6 GHz / AMD FX-6300 3.5 GHz', 'Nvidia GeForce GTX 660 / Amd Radeon HD 7850', '8 GB'),
('CODBO4', 'Windows 10 64-bit', 'zalecane', '60 GB', 'Intel Core i5-2500K 3.3 GHz / AMD Ryzen R5 1600X 3.6 GHz', 'Nvidia GeForce GTX 970 / Amd Radeon R9 390', '12 GB'),
('TR', 'Windows XP', 'zalecane', '10 GB', 'Intel Core i5 2.66 GHz', 'GeForce GTX 480', '1 GB'),
('FFVIIR', 'Windows 10 64-bit', 'minimalne', '100 GB', 'Intel Core i5-3330 3.0 GHz / AMD FX-8350 4.0 GHz', 'Nvidia GeForce GTX 780 / Amd Radeon RX 480', '8 GB'),
('FFVIIR', 'Windows 10 64-bit', 'zalecane', '100 GB', 'Intel Core i7-3770 3.4 GHz / AMD Ryzen 3 3100 3.1 GHz', 'Nvidia GeForce GTX 1080 / Amd Radeon RX 5700', '12 GB'),
('THPS2', 'Windows', 'zalecane', '518 MB', 'Intel Pentium II 300 Mhz', 'akcelerator 3D', '64 MB'),
('GTAV', 'Windows 7(SP1)', 'minimalne', '72 GB', 'Intel Core 2 Quad Q6600 2.4 GHz / AMD Phenom X4 9850 2.5 GHz', 'Nvidia GeForce 9800 GT / AMD Radeon HD 4870', '4 GB'),
('GTAV', 'Windows 7(SP1)', 'zalecane', '72 GB', 'Intel Core i5-3470 3.2 GHz / AMD FX-8350 4.0 GHz', 'Nvidia GeForce GTX 660 / AMD Radeon HD 7870', '8 GB'),
('CODBO2', 'MacOs', 'zalecane', '16 GB', 'Intel Core 2 Duo 2.66 GHz', 'Nvidia GeForce 8800 GT', '4 GB'),
('NEHO', 'MacOs', 'zalecane', '595 MB', 'Intel Pentium 166MHz', 'nd.', '32 MB'),
('CODBO4', 'MacOs', 'minimalne', '60 GB', 'Intel Core i3-4340 3.6 GHz / AMD FX-6300 3.5 GHz', 'Nvidia GeForce GTX 660 / Amd Radeon HD 7850', '8 GB'),
('CODBO4', 'MacOs', 'zalecane', '60 GB', 'Intel Core i5-2500K 3.3 GHz / AMD Ryzen R5 1600X 3.6 GHz', 'Nvidia GeForce GTX 970 / Amd Radeon R9 390', '12 GB'),
('TR', 'MacOs', 'zalecane', '10 GB', 'Intel Core i5 2.66 GHz', 'GeForce GTX 480', '1 GB'),
('FFVIIR', 'MacOs', 'minimalne', '100 GB', 'Intel Core i5-3330 3.0 GHz / AMD FX-8350 4.0 GHz', 'Nvidia GeForce GTX 780 / Amd Radeon RX 480', '8 GB'),
('FFVIIR', 'MacOs', 'zalecane', '100 GB', 'Intel Core i7-3770 3.4 GHz / AMD Ryzen 3 3100 3.1 GHz', 'Nvidia GeForce GTX 1080 / Amd Radeon RX 5700', '12 GB'),
('THPS2', 'MacOs', 'zalecane', '518 MB', 'Intel Pentium II 300 Mhz', 'akcelerator 3D', '64 MB'),
('GTAV', 'MacOs', 'minimalne', '72 GB', 'Intel Core 2 Quad Q6600 2.4 GHz / AMD Phenom X4 9850 2.5 GHz', 'Nvidia GeForce 9800 GT / AMD Radeon HD 4870', '4 GB'),
('GTAV', 'MacOs', 'zalecane', '72 GB', 'Intel Core i5-3470 3.2 GHz / AMD FX-8350 4.0 GHz', 'Nvidia GeForce GTX 660 / AMD Radeon HD 7870', '8 GB');

INSERT INTO Dystrybucja
VALUES('NEHO/NA', 'Ameryka Polnocna', 'ESRB: T', 'Angielski', '1996-10-31',  'DwIn', 'NEHO'),
('NEHO/JP', 'Japonia', NULL , 'Japonski', '1998-04-23',  'RhSt', 'NEHO'),
('CODBO2/EU', 'Europa', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online', 'Angielski', '2012-11-13',  'AcBz', 'CODBO2'),
('CODBO2/PL', 'Polska', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online', 'Polski', '2012-11-15',  'LiEm', 'CODBO2'),
('CODBO4/EU', 'Europa', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online', 'Angielski', '2018-11-12',  'AcBz', 'CODBO4'),
('CODBO4/PL', 'Polska', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online', 'Polski', '2018-11-12',  'CeGa', 'CODBO4'),
('TR/US', 'Stany Zjednoczone', 'ESRB: M, inne: przemoc, wulgarny jezyk, krew', 'Angielski', '2013-03-05',  'SqEn', 'TR'),
('TR/PL', 'Polska', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online', 'Polski', '2013-03-25',  'CeGa', 'TR'),
('FFVIIR/WW', 'swiat', 'Pegi: 18 / ESRB: M, inne: przemoc, wulgarny jezyk, online', 'Angielski', '2020-04-10',  'SqEn', 'FFVIIR'),
('THPS2/WW', 'swiat', NULL, 'Angielski', '2000-09-20',  'AcBz', 'THPS2'),
('THPS2/PL', 'Polska', NULL, 'Angielski', '2000-10-25',  'LiEm', 'THPS2'),
('GTAV/PL', 'Polska', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online, narkotyki', 'Polski', '2013-09-17',  'CeGa', 'GTAV'),
('GTAIV/PL', 'Polska', 'Pegi: 18, inne: przemoc, wulgarny jezyk, online, narkotyki', 'Polski', '2008-04-29',  'CeGa', 'GTAIV');

INSERT INTO Konsola
VALUES('PSXA', 'Playstation 1', 'NTSC', 'ScOe'),
('PS2A', 'Playstation 2', 'NTSC', 'ScOe'),
('PS2E', 'Playstation 2', 'PAL', 'ScOe'),
('PS3A', 'Playstation 3', 'NTSC', 'ScOe'),
('PS3E', 'Playstation 3', 'PAL', 'ScOe'),
('PS4', 'Playstation 4', NULL, 'ScOe'),
('X360A', 'Xbox 360', 'NTSC', 'MiSo'),
('X360E', 'Xbox 360', 'PAL', 'MiSo'),
('XONE', 'Xbox One', NULL, 'MiSo'),
('NS', 'Switch', NULL , 'NiDo');

INSERT INTO Adres
VALUES('Rx2A', 'Polska', 'Gdansk', '80180', 'Fryderyka Chopina', '49A'),
('RX2A', 'Polska', 'Gdansk', '80180', 'Politechniczna', '2'),
('a8Fs', 'Niemcy', 'Dusseldorf', '43212', 'Wurststrasse', '2/3'),
('asd2', 'Polska', 'Warszawa', '87453', 'Aleje Jerozolimskie', '2'),
('TDS1', 'Rosja', 'Moskwa', '45321', 'Czerwona', '7'),
('ASD1', 'Niemcy', 'Berlin', '21312', 'Kartofelnstrasse', '12'),
('OPI2', 'Hiszpania', 'Barcelona', '13231', 'Siesta', '2-2'),
('Pol2', 'Niemcy', 'Monachium', '21345', 'Eins', '2-3'),
('Kx3E', 'Wielka Brytania', 'Londyn', '1313A', 'Queens', '99'),
('G2Hc', 'Wielka Brytania', 'Londyn', '213A1', 'Elizabeths route', '2'),
('es2A', 'Polska', 'Gdansk', '80391', 'Kolobrzeska', '41C'),
('ev1A', 'Polska', 'Gdansk', '80806', 'Targ Sienny', '7'),
('ea23', 'Polska', 'Gdansk', '80264', 'Aleja Grunwaldzka', '141'),
('eF23', 'Polska', 'Gdansk', '80244', 'Aleja Grunwaldzka', '82'),
('eFc3', 'Polska', 'Gdansk', '80172', 'Schuberta', '102A'),
('7Fc3', 'Polska', 'Gdansk', '80034', 'Nieborowska', '8'),
('7Cd3', 'Polska', 'Gdansk', '80398', 'Obroncow Wybrzeza', '1'),
('2Cd3', 'Polska', 'Gdansk', '80286', 'Rakoczego', '19/0.08'),
('7Cx3', 'Polska', 'Gdansk', '80001', 'Przywidzka', '7'),
('7vb3', 'Polska', 'Gdansk', '80176', 'Szczesliwa', '3');

INSERT INTO Jest_na
VALUES('CODBO2', 'PS3A'),
('CODBO2', 'PS3E'),
('CODBO2', 'X360A'),
('CODBO2', 'X360E'),
('CODBO4', 'PS4'),
--('CODBO4', 'XONE'),
('TR', 'PS3A'),
('TR', 'PS3E'),
('TR', 'X360A'),
('TR', 'X360E'),
('THPS2', 'PSXA'),
('GTAV', 'PS3A'),
('GTAV', 'PS3E'),
--('GTAV', 'X360A'),
--('GTAV', 'X360E'),
('GTAIV', 'PS3A'),
('GTAIV', 'PS3E'),
('GTAIV', 'X360A'),
('GTAIV', 'X360E'),
('GTASA', 'PS2A'),
('GTASA', 'PS2E'),
('FFVIIR', 'PS2A');

INSERT INTO Klient
VALUES('asdA','Jan','Kowalki','mezczyzna', NULL,'Rx2A'),
('12dA','Jan','Drwno', NULL , '21','RX2A'),
('a13A','Malgorzata','Kowalki','kobieta', '30','Rx2A'),
('a163','Richard','Johnson', NULL , '35','G2Hc'),
('agh3','Ulrich','von Jungingen', NULL , NULL,'ASD1'),
('aGh3','Alvaro','Solero', 'mezczyzna' , '16' ,'OPI2'),
('aas1','Lady','Solero', 'kobieta' , '12' ,'OPI2'),
('a1sx','Dimitr','Poroshenko', 'mezczyzna' , '65' ,'TDS1'),
('xccx','Svietlana','Koval', NULL , '24' , NULL),
('atWx','Peter','Parker', NULL , '37' , NULL);

INSERT INTO Nalezy
VALUES('TPP', 'GTAV'),
('Akcji','GTAV'),
('Przygodowe','GTAV'),
('Logiczne','NEHO'),
('Przygodowe','NEHO'),
('Platformowe','NEHO'),
('Sportowe','THPS2'),
('TPP', 'GTAIV'),
('jRPG','FFXVI'),
('jRPG','FFVIIR'),
('TPP','FFXVI'),
('TPP','FFVIIR'),
('TPP','TR'),
('Akcji','TR');

INSERT INTO Punkt_Sprzedazy
VALUES('LiEm001', 'Salon Empik nr 1', 'stacjonarny', 'LiEm', 'es2A'),
('LiEm002', 'Salon Empik nr 2', 'stacjonarny', 'LiEm', 'ev1A'),
('LiEm003', 'Salon Empik nr 3', 'stacjonarny', 'LiEm', 'ea23'),
('LiEm004', 'Salon Empik nr 4', 'stacjonarny', 'LiEm', 'eF23'),
('LiEm005', 'Salon Empik nr 5', 'stacjonarny', 'LiEm', 'eFc3'),
('LiEm006', 'Salon Empik nr 6', 'stacjonarny', 'LiEm', '7Fc3'),
('LiEm007', 'Salon Empik nr 7', 'stacjonarny', 'LiEm', '7Cd3'),
('LiEm008', 'Salon Empik nr 8', 'stacjonarny', 'LiEm', '2Cd3'),
('LiEm009', 'Salon Empik nr 9', 'stacjonarny', 'LiEm', '7Cx3'),
('LiEm00A', 'Salon Empik nr 10', 'internetowy', 'LiEm', '7vb3'),
('AcBz001', 'Oficjalny Sklep Activision Blizzard no.1', 'internetowy', 'AcBz', 'a8Fs'),
('AcBz002', 'Oficjalny Sklep Activision Blizzard no.2', 'internetowy', 'AcBz', 'asd2');

INSERT INTO Zamowienie
VALUES
('12321FLiEm009','2020-10-01', '22:13:00', 'stacjonarne', 'zrealizowane', 'asdA', 'LiEm009' ),
('00001FLiEm00A','2021-12-04', '21:23:57', 'internetowe', 'w realizacji', 'a13A', 'LiEm00A' ),
('21312CLiEm003','2019-02-02', '18:28:00', 'stacjonarne', 'anulowane', 'agh3', 'LiEm003' ),
('21005CLiEm003','2022-07-17', '17:02:21', 'stacjonarne', 'anulowane', 'aGh3', 'LiEm003' ), --
('000001LiEm005','2022-08-23', '22:16:13', 'internetowe', 'w realizacji', 'a1sx', 'LiEm005' ), --
('12321FLiEm00A','2023-01-10', '12:13:00', 'internetowe', 'zrealizowane', 'aas1', 'LiEm00A' ),
('100F1CLiEm009','2020-12-31', '22:13:30', 'stacjonarne', 'zrealizowane', 'xccx', 'LiEm001' ),
('1F121FLiEm00A','2022-12-20', '17:22:51', 'stacjonarne', 'zrealizowane', 'asdA', 'LiEm00A' ), --
('15431FLiEm002','2022-12-23', '16:12:12', 'stacjonarne', 'w realizacji', 'a163', 'LiEm002' ), --
('12321FLiEm002','2023-01-05', '12:34:29', 'internetowe', 'zrealizowane', 'xccx', 'LiEm002' ), --
('12131FAcBz001','2023-01-02', '12:34:29', 'internetowe', 'zrealizowane', 'a163', 'AcBZ001' ), --
('12131FAcBz002','2023-01-01', '14:34:29', 'internetowe', 'zrealizowane', 'xccx', 'AcBZ002' ); --

INSERT INTO Element_zamowienia
VALUES
('CODBO4/EU', '12321FLiEm009', '1', '119,99 zl'),
('GTAV/PL', '12321FLiEm009', '1', '259,99 zl'), --
('CODBO2/EU', '00001FLiEm00A', '1', '59,99 zl'),
('TR/PL', '00001FLiEm00A', '1', '79,99 zl'),
('GTAV/PL', '21312CLiEm003', '10', '259,99 zl'), --niemcy
('GTAIV/PL', '21005CLiEm003', '2', '79,99 zl'), --
('NEHO/NA', '000001LiEm005', '1', '999,99 zl'),
('TR/PL', '12321FLiEm00A', '1', '79,99 zl'),
('GTAV/PL', '12321FLiEm00A', '1', '259,99 zl'), --
('GTAIV/PL', '12321FLiEm00A', '1', '79,99 zl'), -- hisz
('TR/PL', '100F1CLiEm009', '2', '79,99 zl'),
('THPS2/PL', '100F1CLiEm009', '1', '10,99 zl'),
('THPS2/PL', '1F121FLiEm00A', '1', '10,99 zl'),
('FFVIIR/WW','15431FLiEm002', '1',  '125,99 zl'),
('THPS2/PL', '12321FLiEm002', '3', '10,99 zl'),
('THPS2/PL', '12131FAcBz001', '2', '10,99 zl'),
('GTAV/PL', '12131FAcBz002', '1', '259,99 zl');




SELECT * FROM Gra
SELECT * FROM Firma
SELECT * FROM Gatunek
SELECT * FROM Wymagania_sprzetowe
SELECT * FROM Dystrybucja
Select * FROM Konsola
Select * FROM Adres
Select * FROM Klient
Select * FROM Punkt_Sprzedazy
Select * From Zamowienie
Select * from Element_zamowienia

	--Where ID_zamowienia = '12321FLiEm00A' ;

	--Update Firma set ID='EmpK' where ID='LiEm' --ajtualizuje id firmy w grze i punktach sprzedazy

	
	--Select * From Element_zamowienia where ID_Zamowienia = '12321FLiEm00A' 
	--Select * From Zamowienie
	--Delete From Zamowienie where ID = '12321FLiEm00A'  --usuniete zostana wszystkie elementy powiazane z zamwieniem

--	Select * from Element_zamowienia
	--Select * FROM Punkt_Sprzedazy
	--Delete From Firma where ID = 'EmpK' --usuniete zostana punkty sprzedazy, wszystkie ich zamowienia oraz elementy zamowien

--	SELECT * FROM Gatunek
	--SELECT * FROM Nalezy
	--Update Gatunek set Nazwa='ThirdPersonPerspective' where Nazwa='TPP'

--	Select * FROM Konsola
--	Select * FROM Jest_na
--	Update Konsola set ID='XBONE' where ID='XONE'

--zrodla:
--www.gry-online.pl, wikipedia.pl