import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Wolf(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 5

    def _set_strength(self):
        self._strength = 9

    def draw(self):
        return 'W'

    def birth(self):
        return Wolf(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Wolf):
            return True
        return False

    def get_color(self):
        return "#af534f"
