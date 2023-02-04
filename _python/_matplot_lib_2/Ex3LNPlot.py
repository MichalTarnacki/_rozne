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

pomiary2 = data.kon1R2MOhm
czasPomiarow2 = [i for i in range(0, 10 * (len(pomiary2)), 10)]
prosta2 = [i for i in range (300)]
z2 = np.polyfit(czasPomiarow2, [np.log(i) for i in pomiary2], 1)
p2 = np.poly1d(z2)

# pomiary3 = data.k1s1kOhm47kOhm
# czasPomiarow3 = [i for i in range(0, 10 * (len(pomiary3)), 10)]
# prosta3 = [i for i in range (300)]
# z3 = np.polyfit(czasPomiarow3, [np.log(i) for i in pomiary3], 1)
# p3 = np.poly1d(z3)

if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim([-1, 3])
    ax.set_xlim([0, 190])
    plt.title("Zmiana napięcia w czasie ładowania kondensatora o pojemności C = 30 μF")
    plt.xticks([10 * x for x in range(0, 20)])
    plt.yticks([0.20 * x for x in range(-5, 16)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie ln(U) [V]")

    plt.plot(prosta1, p1(prosta1), linewidth=0.5, color = "red", ls=('dashed')) #
    print("Prosta dla oporu 2 Mohm: ", Functions.prosta(p1))
    print("stała czasowa: ", Functions.stala_czasowa(p1), "s", '\n')

    plt.plot(prosta2, p2(prosta2), linewidth=0.5, color = "blue", ls=('dashed')) #
    print("Prosta dla oporu 1 Mohm: ", Functions.prosta(p2), '\n')
    print("stała czasowa: ", Functions.stala_czasowa(p2), "s", '\n')

    # plt.plot(prosta3, p3(prosta3), linewidth=0.5, color = "green", ls=('dashed')) #
    # print("Prosta dla oporu 5,7 kOhm: ", Functions.prosta(p3) , '\n')
    # print("stała czasowa: ", Functions.stala_czasowa(p3), "s", '\n')

    #Pojedynczy kondensator
    plt.errorbar(czasPomiarow1, [np.log(i) for i in pomiary1],
                 [data.deltaU/i for i in pomiary1], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    plt.errorbar(czasPomiarow2, [np.log(i) for i in pomiary2],
                 [data.deltaU/i for i in pomiary2], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    # plt.errorbar(czasPomiarow3, [np.log(i) for i in pomiary3],
    #              [data.deltaU/i for i in pomiary3], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)

    plt.scatter(czasPomiarow1, [np.log(i) for i in pomiary1], s=0.8, color="black", edgecolor='red', linewidth=3, alpha=1)
    plt.scatter(czasPomiarow2, [np.log(i) for i in pomiary2], s=0.8, color="black", edgecolor='blue', linewidth=3, alpha=1)
    # plt.scatter(czasPomiarow3, [np.log(i) for i in pomiary3], s=0.8, color="black", edgecolor='green', linewidth=3, alpha=1)
    plt.text(40, 1.9, 'R_2', color='blue', fontsize=8, va='center', ha='center')
    plt.text(35, 1.5, 'R_1', color='red', fontsize=8, va='center', ha='center')
    # plt.text(50, 2.55, 'Opór teoretyczny 5,7 kOhm', color='green', fontsize=8, va='center', ha='center')

    plt.show()
