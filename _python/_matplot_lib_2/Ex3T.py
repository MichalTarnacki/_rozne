import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data
import Ex2LNPlot
import Ex3LNPlot
import Functions

C = 30 #MOhm
staleCzasowe = [Functions.stala_czasowa(Ex3LNPlot.p1), Functions.stala_czasowa(Ex3LNPlot.p2)]
oporyTeor = [1, 2]

z1 = np.polyfit(oporyTeor, staleCzasowe, 1)
p1 = np.poly1d(z1)
prosta1 = [i for i in range (300)]

z2 = np.polyfit(oporyTeor, [i*C for i in oporyTeor], 1)
p2 = np.poly1d(z2)
prosta2 = [i for i in range (300)]


if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim([0, 60])
    ax.set_xlim([0, 7])
    plt.title("Wykres stałej czasowej w zależności od oporu zastępczego")
    plt.xticks([1 * x for x in range(0, 8)])
    plt.yticks([10 * x for x in range(0, 19)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("opór R [MΩ]")
    plt.ylabel("stała czasowa τ [s]")

    plt.plot(prosta1, p1(prosta1), linewidth=0.5, color="red", ls=('dashed'))  #
    plt.plot(prosta2, p2(prosta2), linewidth=0.5, color="blue", ls=('dashed'))  #

    # plt.errorbar(czasPomiarow1, [np.log(i) for i in pomiary1],
    #              [data.deltaU/i for i in pomiary1], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)

    plt.scatter(oporyTeor, staleCzasowe, s=0.8, color="black", edgecolor='red', linewidth=3, alpha=1)
    plt.scatter(oporyTeor, [i*C for i in oporyTeor], s=0.8, color="black", edgecolor='blue', linewidth=3, alpha=1)

    plt.text(2.4, 85, 'τ_teor', color='blue', fontsize=8, va='center', ha='center')
    plt.text(2, 45, 'τ', color='red', fontsize=8, va='center', ha='center')
    # plt.text(200, 2.20, 'Kondensatory połączone równolegle', color='green', fontsize=8, va='center', ha='center')

    plt.show()