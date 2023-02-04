#Pojemność teoretyczna kondensatora deklarowana przez producenta oraz jej niepewność
C = 30 #[μF]
deltaC = 0.08*C #[μF], niepewność 8%
#Pojemność zastępcza teoretyczna połączonych szeregowo dwóch kondensatorów C oraz jej niepewność
Cs = 1/(1/C + 1/C) #[μF]
deltaCs = 1/2 * deltaC
#Pojemność zastępcza teoretyczna połączonych równolegle dwóch kondensatorów C oraz jej niepewność
Cr = C + C #[μF]
deltaCr = 2*deltaC
#Niepewność mierzonego napięcia
deltaU = 0.01 #0.5%
#Niepewność pomiaru czasu
deltaT = 0.26 #[s]

#Napięcie ustawione na generatorze
U0 = 12

#Czas pomiarów
czasPomiarow = [i for i in range(0, 10*31, 10)]

#Testowane opory dla pojedynczego kondenatora
R = [1000000, 2000000, 5700]

#Testowane pojemności kondensatorów
C = [C, Cs, Cr]

#Od tego momentu zaczynają się pomiary z drugich zajęć (dzisiejszych)

#1
kon1R1MOhm = [11.88, 
	      8.46, 5.84, 4.04, 2.79, 1.92, 1.31, 0.91, 0.63,
	      0.43, 0.29, 0.20, 0.14, 0.09, 0.06, 0.04]

#2
kon2R1MOhm = [11.85,
	      8.43, 5.82, 4.02, 2.78, 1.92, 1.32, 0.91, 0.63,
	      0.43, 0.30, 0.20, 0.14, 0.09, 0.06, 0.04]

#1
kprR1MOhm = [11.98,
	     9.96, 8.28, 6.93, 5.72, 4.75, 3.95, 3.28, 2.73,
	     2.27, 1.88, 1.56, 1.30, 1.08, 0.89, 0.74, 0.62, 0.51]

#2
kon1R2MOhm = [11.98,
	     9.06, 8.34, 6.87, 5.71, 4.74, 3.93, 3.27, 2.71,
	     2.25, 1.87, 1.55, 1.29, 1.07, 0.89, 0.74, 0.61, 0.50]

#3
kpr3R1Mohm = [11.91,
	      10.10, 8.58, 7.21, 6.07, 5.11, 4.33, 3.62, 3.05,
	      2.57, 2.16, 1.81, 1.53, 1.29, 1.07, 0.91, 0.76, 0.64]
