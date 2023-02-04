import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data

pomiary = data.kprR1MOhm
czasPomiarow = [i for i in range(0, 10 * (len(pomiary)), 10)]

if __name__ == "__main__":
    #Wykres
    f, ax = plt.subplots(1)
    ax.set_ylim(ymin=0)
    ax.set_xlim([0, 180])
    plt.title("Zależność napięcia od czasu")
    plt.xticks([10*x for x in range (0,19)])
    plt.yticks([0.6*x for x in range (0,21)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie U [V]")

    plt.errorbar(czasPomiarow, pomiary,
                 data.deltaU, data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)
    plt.scatter(czasPomiarow, pomiary, s=0.8, color="green", edgecolor='black', linewidth=3, alpha=1)
    plt.show()
