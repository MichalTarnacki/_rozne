import array
import matplotlib.pyplot as plt
import numpy as np
import Measurement as measure

t_prim = [[], []]
for i in range(len(measure.alfa)):
    for j in range(len(measure.s)):
        t_prim[i].append(np.average(measure.t[i][j])+np.average(measure.deltat[i][j])/2)

v = [[], []]
for i in range(len(measure.alfa)):
    for j in range(len(measure.s)):
        v[i].append(measure.dlugosc_wozka/(np.average(measure.deltat[i][j]))*1000)

niepewnosc_v = [[],[]]

for i in range(len(measure.alfa)):
    for j in range(len(measure.s)):
        niepewnosc_v[i].append(np.abs(1/(np.average(measure.deltat[i][j])/1000))*measure.niepewnosc_dlugosci_wozka
        + np.abs(measure.dlugosc_wozka/((np.average(measure.deltat[i][j])/1000)**2))*measure.niepewnosc_pomiaru_czasu)

niepewnosc_t_prim = [[],[]]

for i in range(len(measure.alfa)):
    for j in range(len(measure.s)):
        niepewnosc_t_prim[i].append(np.abs(1)*measure.niepewnosc_pomiaru_czasu
        + np.abs(1/2)*measure.niepewnosc_pomiaru_czasu)

    prosta = [i for i in range(1100)]
    z = np.polyfit(t_prim[0], v[0], 1)
    p = np.poly1d(z)

    z1 = np.polyfit(t_prim[1], v[1], 1)
    p1 = np.poly1d(z1)


    a = []
    a.append((p(100)-p(0))/(100-0)*1000)
    a.append((p1(100)-p1(0))/(100-0)*1000)

if __name__ == "__main__":
    #Wykres

    f, ax = plt.subplots(1)

    plt.errorbar(t_prim[0], v[0], niepewnosc_v[0], [niepewnosc_t_prim[0][i]*1000 for i in range (len(niepewnosc_t_prim[0]))], elinewidth=2, linewidth=0, alpha=0.2)  # Niepewnosc pomiarowa alfa = 10 st.
    plt.errorbar(t_prim[1], v[1], niepewnosc_v[1], [niepewnosc_t_prim[1][i]*1000 for i in range (len(niepewnosc_t_prim[1]))], color = "red", elinewidth=2, linewidth=0, alpha=0.2)  # Niepewnosc pomiarowa alfa = 6 st.

    plt.plot(prosta, p(prosta), linewidth=0.5, color = "blue", ls=('dashed'))  # Linia trendu alfa = 10 st.
    plt.plot(prosta, p1(prosta), linewidth=0.5, color = "red", ls=('dashed'))  # Linia trendu alfa = 6 st.
    ax.set_ylim(ymin=0)
    ax.set_xlim(xmin=0)
    plt.title("Zależność szybkości od czasu")
    plt.xticks([75*x for x in range (0,16)])
    plt.yticks([0.15*x for x in range (0,18)])


    print ("Dla α = 10°, v0 = ", p(0), "a a = ", a[0])
    print ("Dla α = 6°, v0 = ", p1(0), "a a = ", a[1])

    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t' [ms]")
    plt.ylabel("szybkość v [m/s]")


    plt.annotate('α = 10°', xy=(650, 1.85), xytext=(550, 2), color = "blue",
                arrowprops=dict(facecolor='blue', shrink=0.05, width=1, headwidth=5,
                                 headlength=5))
    plt.annotate('α = 6°', xy=(770, 1.6), xytext=(800, 1.4), color = "red",
                arrowprops=dict(facecolor='red', shrink=0.05, width=1, headwidth=5,
                                 headlength=5))

    plt.scatter(t_prim[0], v[0], s=0.8, color="green", edgecolor='black', linewidth=3, alpha=1) #wykres s=f(tsr) dla alfa = 10
    plt.scatter(t_prim[1],  v[1], s=0.8, color="orange", edgecolor='black', linewidth=3, alpha=1) #wykres s=f(tsr) dla alfa = 10
    plt.axvline(x=300, linestyle="dotted", linewidth = 1, color="black")
    plt.axvline(x=600, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=1.13, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=1.45, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=1.76, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=1.3, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=0.84, linestyle="dotted", linewidth = 1, color="black")
    plt.axhline(y=0.80, linestyle="dotted", linewidth = 1, color="black")
    plt.text(75, 1.13, '1.13', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.text(75, 1.45, '1.45', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.text(75, 1.30, '1.30', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.text(140, 0.84, '0.84', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.text(200, 0.80, '0.80', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.text(75, 1.76, '1.76', fontsize=7, va='center', ha='center', backgroundcolor='w')
    plt.show()
