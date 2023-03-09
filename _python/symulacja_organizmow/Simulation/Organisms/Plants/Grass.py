from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Plant import Plant


class Grass(Plant, ABC):

    def __init__(self, world):
        super().__init__(world)

    def draw(self):
        return 't'

    def birth(self):
        return Grass(self.world)

    def get_probability(self):
        return 30

    def can_be_partner(self, other: Organism):
        if isinstance(other, Grass):
            return True
        return False

    def get_color(self):
        return "#e08d7f"
