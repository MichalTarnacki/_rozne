import array
import matplotlib.pyplot as plt
import numpy as np
import Measurement as measure
from VelocityPlot import v as velocity
from VelocityPlot import a as acceleration

#Wykres

f, ax = plt.subplots(1)

ax.set_ylim(ymin=0)
ax.set_xlim([0, 0.1])
plt.title("Zależność przyspieszenia od kąta")
plt.xticks([0.03*x for x in range (0,10)])
plt.yticks([0.15*x for x in range (0,18)])

plt.style.use('seaborn-v0_8')
plt.xlabel("kąt α [RAD]")
plt.ylabel("przyspieszenie a [m/s^2]")
plt.errorbar([(measure.alfa[i]*np.pi/180) for i in range (len(measure.alfa))], acceleration, 0, [measure.niepewnosc_pomiaru_kata[i]*np.pi/180 for i in range (len(measure.niepewnosc_pomiaru_kata))], elinewidth=2, linewidth=0, alpha=0.2)

prosta = [i for i in range (13)]
z = np.polyfit([(measure.alfa[i]*np.pi/180) for i in range (len(measure.alfa))], acceleration, 1)
p = np.poly1d(z)
plt.plot(prosta, p(prosta), linewidth=0.5, color = "blue", ls=('dashed')) #Linia trendu a = 10

plt.scatter([(measure.alfa[i]*np.pi/180) for i in range (len(measure.alfa))], acceleration, s=0.8, color="green", edgecolor='black', linewidth=3, alpha=1) #wykres s=f(tsr) dla alfa = 10

plt.axvline(x=0.06, linestyle="dotted", linewidth = 1, color="black")
plt.axvline(x=0.18, linestyle="dotted", linewidth = 1, color="black")
plt.axhline(y=0.74, linestyle="dotted", linewidth = 1, color="black")
plt.axhline(y=1.58, linestyle="dotted", linewidth = 1, color="black")

plt.text(0.03, 1.58, '1.58', fontsize=7, va='center', ha='center', backgroundcolor='w')
plt.text(0.03, 0.74, '0.74', fontsize=7, va='center', ha='center', backgroundcolor='w')

plt.show()
