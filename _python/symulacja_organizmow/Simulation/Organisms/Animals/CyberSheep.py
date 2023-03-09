import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class CyberSheep(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 4

    def _set_strength(self):
        self._strength = 11

    def draw(self):
        return 'C'

    def birth(self):
        return CyberSheep(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, CyberSheep):
            return True
        return False

    def get_color(self):
        return "#874676"
