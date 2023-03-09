from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Plant import Plant


class Dandelion(Plant, ABC):

    def __init__(self, world):
        super().__init__(world)

    def draw(self):
        return 'm'

    def birth(self):
        return Dandelion(self.world)

    def get_probability(self):
        return 10

    def can_be_partner(self, other: Organism):
        if isinstance(other, Dandelion):
            return True
        return False

    def action(self):
        for i in range(0, 4, 1):
            super().action()

    def get_color(self):
        return "#7a3a37"
