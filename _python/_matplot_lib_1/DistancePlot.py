import array
import matplotlib.pyplot as plt
import numpy as np
import Measurement as measure

bramka_alfa = [[], []]
for i in range (0, len(measure.s)):
    bramka_alfa[0].append([(x,measure.s[i]) for x in measure.t[0][i]])
    bramka_alfa[1].append([(x, measure.s[i]) for x in measure.t[1][i]])

x = [[], []] #t alfa = 10
y = [[], []] #s alfa = 10

xsr = [[],[],[],[]] #Sredni czas alfa = 10
xsr2 = [[],[],[],[]] #Sredni czas alfa = 6

for i in range (0, len(bramka_alfa[0])): #x i y dla alfa = 10
    for j in range (0, len(bramka_alfa[0][i])):
        x[0].append(bramka_alfa[0][i][j][0])
        y[0].append(bramka_alfa[0][i][j][1])

for i in range (0, len(bramka_alfa[1])): #x i y dla alfa = 6
    for j in range (0, len(bramka_alfa[1][i])):
        x[1].append(bramka_alfa[1][i][j][0])
        y[1].append(bramka_alfa[1][i][j][1])

for i in range (0, len(bramka_alfa[0])): #x i y dla alfa = 10
    xsr[i] = np.average(list(zip(*bramka_alfa[0][i]))[0])

for i in range (0, len(bramka_alfa[1])): #x i y dla alfa = 6
    xsr2[i] = np.average(list(zip(*bramka_alfa[1][i]))[0])

#Wykres

f, ax = plt.subplots(1)
ax.set_ylim(ymin=0)
ax.set_xlim(xmin=0)

plt.xticks([100*x for x in range (0,12)])
plt.yticks([0.15*x for x in range (0,12)])
plt.title("Zależność drogi od czasu")

plt.errorbar(xsr, measure.s, measure.niepewnosc_drogi, 1000*measure.niepewnosc_pomiaru_czasu, elinewidth=4, linewidth=0, alpha=0.2) #Błąd pomiarowy a = 10
plt.errorbar(xsr2, measure.s, measure.niepewnosc_drogi, 1000*measure.niepewnosc_pomiaru_czasu, color = "red", elinewidth=2, linewidth=0, alpha=0.2) #Błąd pomiarowy a = 6
plt.style.use('seaborn-v0_8')
plt.xlabel("czas t [ms]")
plt.ylabel("droga s [m]")

plt.annotate('α = 10°', xy=(600, 0.8), xytext=(500, 0.9), color = "blue")
plt.annotate('α = 6°', xy=(750, 0.9), xytext=(700, 0.7), color = "red")

# Linie trendu, niekoniecznie najlepszy pomysł
# prosta = [i for i in range (1100)]
# z = np.polyfit(xsr, measure.s, 1)
# p = np.poly1d(z)
# plt.plot(prosta, p(prosta), linewidth=0.5, color = "blue", ls=('dashed')) #Linia trendu a = 10
#
# z2 = np.polyfit(xsr2, measure.s, 1)
# p2 = np.poly1d(z2)
# plt.plot(prosta, p2(prosta), linewidth=0.5, color = "red", ls=('dashed')) #Linia trendu a = 10

plt.scatter(xsr, measure.s, s=5, color="blue", edgecolor='black', linewidth=0, alpha=1) #wykres s=f(tsr) dla alfa = 10
plt.scatter(xsr2, measure.s, s=5, color="red", edgecolor='black', linewidth=0, alpha=1) #wykres s=f(tsr) dla alfa = 10

plt.show()