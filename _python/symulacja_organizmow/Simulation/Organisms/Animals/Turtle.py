import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Turtle(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 1

    def _set_strength(self):
        self._strength = 2

    def draw(self):
        return 'Z'

    def birth(self):
        return Turtle(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Turtle):
            return True
        return False

    def action(self):
        x = random.randint(0, 100)
        if x >= 75:
            super().action()

    def collision(self, other: Organism):
        if other.get_strength() < 5 and not isinstance(other, Turtle):
            other.set_location(other.get_previous_location())
            self.world.event_listener.add_string(
                "Organizm: " + str(other.get_location()) + "jest za slaby zeby walczyc z zolwiem, wraca na poprzenia "
                                                      "pozycje: " + str(
                    other.get_location()))

    def get_color(self):
        return "#821d33"
