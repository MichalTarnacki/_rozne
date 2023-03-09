import copy
from tkinter import Tk, Button, Canvas, PhotoImage, Toplevel

from Core.BirthMode import BirthMode
from Core.Dimension import Dimension
from Core.Location import Location
from Core.OrganismsConfiguration import OrganismsConfiguration
from Simulation.Organisms.Animals.Antilope import Antilope
from Simulation.Organisms.Animals.CyberSheep import CyberSheep
from Simulation.Organisms.Animals.Sheep import Sheep
from Simulation.Organisms.Animals.Turtle import Turtle
from Simulation.Organisms.Animals.Wolf import Wolf
from Simulation.Organisms.Human import Human
from Simulation.Organisms.Plants.Dandelion import Dandelion
from Simulation.Organisms.Plants.Grass import Grass
from Simulation.Organisms.Plants.Guarana import Guarana
from Simulation.Organisms.Plants.PineBrosht import PineBrosht
from Simulation.Organisms.Plants.WolfBerries import WolfBerries
from Simulation.World import World


class AddOrganismWindow(Toplevel):

    def __init__(self, world_window, location):
        super().__init__(world_window)
        self.title("")
        self.resizable(False, False)
        self.world = world_window.world
        self.world_window = world_window
        self.height = 300
        self.width = 300
        self.location = location
        self.geometry("130x340")
        for i in range(3):
            for j in range(4):
                button = Button(self)
                s = "" + str(i) + "" + str(j)
                if s == "00":
                    button.config(text="Barszcz", command=copy.copy(lambda i=i, j=j: self.add_organism(button, PineBrosht(self.world))))
                elif s == "01":
                    button.config(text="Guarana", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Guarana(self.world))))
                elif s == "02":
                    button.config(text="Mlecz", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Dandelion(self.world))))
                elif s == "03":
                    button.config(text="Trawa", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Grass(self.world))))
                elif s == "10":
                    button.config(text="Wilcze Jagody",
                                  command=copy.copy(lambda i=i, j=j: self.add_organism(button, WolfBerries(self.world))))
                elif s == "11":
                    button.config(text="Antylopa", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Antilope(self.world))))
                elif s == "12":
                    button.config(text="CyberOwca", command=copy.copy(lambda i=i, j=j: self.add_organism(button, CyberSheep(self.world))))
                elif s == "13":
                    button.config(text="Lis", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Wolf(self.world))))
                elif s == "20":
                    button.config(text="Owca", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Sheep(self.world))))
                elif s == "21":
                    button.config(text="Wilk", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Wolf(self.world))))
                elif s == "22":
                    button.config(text="Zółw", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Turtle(self.world))))
                elif s == "23":
                    button.config(text="Czlowiek", command=copy.copy(lambda i=i, j=j: self.add_organism(button, Human(self.world))))
                else:
                    pass
                button.grid()
        self.mainloop()

    def add_organism(self, button, organism):
        self.world.birth_organism(organism.birth(), self.location, BirthMode.Add)
        self.protocol("WM_DELETE_WINDOW", self.world_window.update())
        self.destroy()
