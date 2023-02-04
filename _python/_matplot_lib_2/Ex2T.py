import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data
import Ex2LNPlot
import Functions

R = 1 #MOhm
staleCzasowe = [Functions.stala_czasowa(Ex2LNPlot.p1), Functions.stala_czasowa(Ex2LNPlot.p2), Functions.stala_czasowa(Ex2LNPlot.p3)]
pojemnosciTeor = [60, 64.7, 30]

z1 = np.polyfit(pojemnosciTeor, staleCzasowe, 1)
p1 = np.poly1d(z1)
prosta1 = [i for i in range (300)]

z2 = np.polyfit(pojemnosciTeor, [i*R for i in pojemnosciTeor], 1)
p2 = np.poly1d(z2)
prosta2 = [i for i in range (300)]


if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim([0, 60])
    ax.set_xlim([0, 100])
    plt.title("Stała czasowa w zależności od pojemności zastępczej")
    plt.xticks([10 * x for x in range(0, 11)])
    plt.yticks([5 * x for x in range(0, 19)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("pojemność C [μF]")
    plt.ylabel("stała czasowa τ [s]")

    plt.plot(prosta1, p1(prosta1), linewidth=0.5, color="red", ls=('dashed'))  #
    plt.plot(prosta2, p2(prosta2), linewidth=0.5, color="blue", ls=('dashed'))  #
    print("Kondenstatory równolegle 1 MOhm: ", Functions.prosta(p1))
    print("stała czasowa: ", Functions.stala_czasowa(p1), "s", "\n")

    # plt.errorbar(czasPomiarow1, [np.log(i) for i in pomiary1],
    #              [data.deltaU/i for i in pomiary1], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)

    plt.scatter(pojemnosciTeor, staleCzasowe, s=0.8, color="black", edgecolor='red', linewidth=3, alpha=1)
    plt.scatter(pojemnosciTeor, [i*R for i in pojemnosciTeor], s=0.8, color="black", edgecolor='blue', linewidth=3, alpha=1)

    plt.text(37, 42, 'τ_teor', color='blue', fontsize=8, va='center', ha='center')
    plt.text(30, 23, 'τ', color='red', fontsize=8, va='center', ha='center')
    # plt.text(200, 2.20, 'Kondensatory połączone równolegle', color='green', fontsize=8, va='center', ha='center')

    plt.show()