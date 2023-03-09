from Simulation.Organisms.Animals.Antilope import Antilope
from Simulation.Organisms.Animals.CyberSheep import CyberSheep
from Simulation.Organisms.Animals.Fox import Fox
from Simulation.Organisms.Animals.Sheep import Sheep
from Simulation.Organisms.Animals.Turtle import Turtle
from Simulation.Organisms.Animals.Wolf import Wolf
from Simulation.Organisms.Human import Human
from Simulation.Organisms.Plants.Dandelion import Dandelion
from Simulation.Organisms.Plants.Grass import Grass
from Simulation.Organisms.Plants.Guarana import Guarana
from Simulation.Organisms.Plants.PineBrosht import PineBrosht
from Simulation.Organisms.Plants.WolfBerries import WolfBerries


class VariablesToLoad:
    def __init__(self, world):
        self.world = world
        self.strength = None
        self.initiative = None
        self.opt_par1 = None
        self.opt_par2 = 0
        self.date_of_birth = None
        self.is_alive = None
        self.capable_of_reproduction = None
        self.sign = None
        self.number_of_organisms = None
        self.round_number = None
        self.x = None
        self.y = None
        self.x2 = None
        self.y2 = None
        self.location = None
        self.previous_location = None
        self.temp_organisms = []
        self.variables_to_load()

    def variables_to_load(self):
        self.temp_organisms.append(Grass(self.world))
        self.temp_organisms.append(Dandelion(self.world))
        self.temp_organisms.append(Guarana(self.world))
        self.temp_organisms.append(WolfBerries(self.world))
        self.temp_organisms.append(PineBrosht(self.world))
        self.temp_organisms.append(Wolf(self.world))
        self.temp_organisms.append(Sheep(self.world))
        self.temp_organisms.append(Fox(self.world))
        self.temp_organisms.append(Turtle(self.world))
        self.temp_organisms.append(Antilope(self.world))
        self.temp_organisms.append(CyberSheep(self.world))
        self.temp_organisms.append(Human(self.world))
