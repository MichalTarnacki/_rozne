import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Fox(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 7

    def _set_strength(self):
        self._strength = 3

    def draw(self):
        return 'L'

    def birth(self):
        return Fox(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Fox):
            return True
        return False

    def action(self):
        super().action()
        for organism in self.world.get_organisms():
            if organism.get_strength() > self.get_strength() and organism.get_location().__eq__(self.get_location()):
                self.set_location(self.get_previous_location())
                self.world.event_listener.add_string("Lis chcial isc na pozycje: " + str(organism.get_location()) + " ale wytropil: " + organism.draw() + " i nie idzie dalej ")

    def get_color(self):
        return "#ccbbee"
