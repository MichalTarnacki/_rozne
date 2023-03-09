from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Plant import Plant


class WolfBerries(Plant, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_strength()

    def draw(self):
        return 'w'

    def birth(self):
        return WolfBerries(self.world)

    def get_probability(self):
        return 5

    def can_be_partner(self, other: Organism):
        if isinstance(other, WolfBerries):
            return True
        return False

    def collision(self, other: Organism):
        self.world.event_listener.add_string("Organizm: " + other.draw() + " na pozycji " + str(other.get_location()) +
                                             "\nzjada Wilcze Jagody i umiera")

    def _set_strength(self):
        self._strength = 99

    def get_color(self):
        return "#9ea3a2"
