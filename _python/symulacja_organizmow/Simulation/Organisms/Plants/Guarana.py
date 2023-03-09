from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Plant import Plant


class Guarana(Plant, ABC):

    def __init__(self, world):
        super().__init__(world)

    def draw(self):
        return 'g'

    def birth(self):
        return Guarana(self.world)

    def get_probability(self):
        return 20

    def can_be_partner(self, other: Organism):
        if isinstance(other, Guarana):
            return True
        return False

    def collision(self, other: Organism):
        self.world.event_listener.add_string(
            "Organizm: " + other.draw() + " na pozycji " + str(other.get_location()) + "\nzjada Guarane, jego sila "
                                                                                       "rosnie")
        other.increase_strength(3)
        super().collision(other)

    def get_color(self):
        return "#4a2c41"