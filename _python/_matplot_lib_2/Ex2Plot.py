import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data

pomiary1 = data.kprR1MOhm
czasPomiarow1 = [i for i in range(0, 10 * (len(pomiary1)), 10)]
prosta1 = [i for i in range (300)]
z1 = np.polyfit(czasPomiarow1, [np.log(i) for i in pomiary1], 1)
p1 = np.poly1d(z1)

pomiary2 = data.kpr3R1Mohm
czasPomiarow2 = [i for i in range(0, 10 * (len(pomiary2)), 10)]
prosta2 = [i for i in range (300)]
z2 = np.polyfit(czasPomiarow2, [np.log(i) for i in pomiary2], 1)
p2 = np.poly1d(z2)

pomiary3 = data.kon1R1MOhm
czasPomiarow3 = [i for i in range(0, 10 * (len(pomiary3)), 10)]
prosta3 = [i for i in range (300)]
z3 = np.polyfit(czasPomiarow3, [np.log(i) for i in pomiary3], 1)
p3 = np.poly1d(z3)

if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim([-1, 12])
    ax.set_xlim([0, 180])
    plt.title("Zmiana napięcia na oporze 1 MΩ w czasie ładowania kondensatora")
    plt.xticks([10*x for x in range (0,19)])
    plt.yticks([0.6*x for x in range (-2,21)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie U [V]")

    #Pojedynczy kondensator
    plt.errorbar(czasPomiarow1, pomiary1,
                 data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    plt.errorbar(czasPomiarow2, pomiary2,
                 data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    # plt.errorbar(czasPomiarow3,  pomiary3,
    #              data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)

    plt.scatter(czasPomiarow1, pomiary1, s=0.8, color="black", edgecolor='red', linewidth=3, alpha=1)
    plt.scatter(czasPomiarow2, pomiary2, s=0.8, color="black", edgecolor='blue', linewidth=3, alpha=1)
    plt.scatter(czasPomiarow3,  pomiary3, s=0.8, color="black", edgecolor='green', linewidth=3, alpha=1)

    plt.text(17, 10.3, 'C_3', color='blue', fontsize=8, va='center', ha='center')
    plt.text(27, 8.2, 'C_2', color='red', fontsize=8, va='center', ha='center')
    plt.text(43, 1.9, 'C_1', color='green', fontsize=8, va='center', ha='center')

    plt.show()