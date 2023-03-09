import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Sheep(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 3

    def _set_strength(self):
        self._strength = 3

    def draw(self):
        return 'O'

    def birth(self):
        return Sheep(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Sheep):
            return True
        return False

    def get_color(self):
        return "#eb4255"
