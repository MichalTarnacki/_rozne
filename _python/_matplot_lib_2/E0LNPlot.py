import array
import matplotlib.pyplot as plt
import numpy as np
import Data as data




#Wykres
if __name__ == "__main__":
    f, ax = plt.subplots(1)
    ax.set_ylim(ymin=0)
    ax.set_xlim([0, 40])
    plt.title("Zależność ln napięcia ustawionego na generatorze od czasu")
    plt.xticks([5*x for x in range (0,8)])
    plt.yticks([0.05*x for x in range (0,21)])
    plt.style.use('seaborn-v0_8')
    plt.xlabel("czas t [s]")
    plt.ylabel("napięcie ln(U) [V]")


# Linie trendu
prosta = [i for i in range (300)]
z = np.polyfit(data.czasPomiarow, [np.log(data.U0/i) if i != 0 else data.U0 for i in data.czasPomiarow], 1)
p = np.poly1d(z)


print("Prosta dla kondensatora", round((p(1)-p(0))/1, 4), "x +", round(p(0),2), '\n')


plt.plot(prosta, p(prosta), linewidth=0.5, color = "blue", ls=('dashed')) #Linia trendu a = 10

plt.errorbar(data.czasPomiarow, [np.log(i) if i is not None else 0 for i in data.kps1MOhm],
             [data.deltaU if i is not None else 0 for i in data.kps1MOhm], data.deltaT, elinewidth=2, linewidth=0, alpha=0.2)

plt.scatter(data.czasPomiarow, [np.log(data.U0/i) if i !=  0 else data.U0 for i in data.czasPomiarow], s=0.8, color="green", edgecolor='black', linewidth=3, alpha=1) #wykres s=f(tsr) dla alfa = 10

plt.show()