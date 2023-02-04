import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data
import Functions

pomiary1 = data.kon1R1MOhm
czasPomiarow1 = [i for i in range(0, 10 * (len(pomiary1)), 10)]
prosta1 = [i for i in range (300)]
z1 = np.polyfit(czasPomiarow1, [np.log(i) for i in pomiary1], 1)
p1 = np.poly1d(z1)

pomiary2 = data.kon2R1MOhm
czasPomiarow2 = [i for i in range(0, 10 * (len(pomiary2)), 10)]
prosta2 = [i for i in range (300)]
z2 = np.polyfit(czasPomiarow2, [np.log(i) for i in pomiary2], 1)
p2 = np.poly1d(z2)

if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim([-2, 3])
    ax.set_xlim([0, 120])
    plt.title("Zmiana napięcia na oporze 1 MΩ w czasie ładowania kondensatora")
    plt.xticks([10*x for x in range (0,13)])
    plt.yticks([0.20*x for x in range (-10,16)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie ln(U) [V]")

    plt.plot(prosta1, p1(prosta1), linewidth=0.5, color="red", ls=('dashed'))  #
    print("Prosta dla pojedynczego kondensatora C_1: ", Functions.prosta(p1))
    print("stała czasowa: ", Functions.stala_czasowa(p1), "s", "\n")

    plt.plot(prosta2, p2(prosta2), linewidth=0.5, color = "blue", ls=('dashed')) #
    print("Prosta dla kondensatorów połączonych szeregowo: ", Functions.prosta(p2))
    print("stała czasowa: ", Functions.stala_czasowa(p2), "s", '\n')

    plt.errorbar(czasPomiarow1, [np.log(i) for i in pomiary1],
                 data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    plt.errorbar(czasPomiarow2, [np.log(i) for i in pomiary2],
                 data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    plt.scatter(czasPomiarow1, [np.log(i) for i in pomiary1], s=0.8, color="black", edgecolor='red', linewidth=3, alpha=1)
    plt.scatter(czasPomiarow2, [np.log(i) for i in pomiary2], s=0.8, color="black", edgecolor='blue', linewidth=3, alpha=1)


    plt.text(22, 2, 'C_a.1', color='red', fontsize=8, va='center', ha='center')
    plt.text(27, 1.8, 'C_a.2', color='blue', fontsize=8, va='center', ha='center')

    plt.show()