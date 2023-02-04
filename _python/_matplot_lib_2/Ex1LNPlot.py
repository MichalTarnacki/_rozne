import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data
import Functions

pomiary = data.kprR1MOhm
czasPomiarow = [i for i in range(0, 10 * (len(pomiary)), 10)]
# Linie trendu
prosta = [i for i in range(300)]
z = np.polyfit(czasPomiarow, [np.log(i) for i in pomiary], 1)
p = np.poly1d(z)

if __name__ == "__main__":
    # Wykres


    f, ax = plt.subplots(1)
    ax.set_ylim([-1, 3])
    ax.set_xlim([0, 190])
    plt.title("Zależność logartmu naturalnego napięcia od czasu")
    plt.xticks([10 * x for x in range(0, 20)])
    plt.yticks([0.20 * x for x in range(-5, 16)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie ln(U) [V]")

    print("Prosta dla pojedynczego kondensatora ", Functions.prosta(p))
    print("stała czasowa: ", Functions.stala_czasowa(p), "s")

    plt.plot(prosta, p(prosta), linewidth=0.5, color="blue", ls=('dashed'))
    plt.errorbar(czasPomiarow, [np.log(i) for i in pomiary], [data.deltaU/i for i in pomiary], data.deltaT, elinewidth=2, linewidth=0,
                 alpha=0.2)
    plt.scatter(czasPomiarow, [np.log(i) for i in pomiary], s=0.8, color="green", edgecolor='black', linewidth=3,
                alpha=1)
    plt.show()
