import random
from abc import ABC
from abc import abstractmethod
from Core.BirthMode import BirthMode
from Core.Location import Location
from Simulation.HexWorld import HexWorld
from Simulation.Organism import Organism


class Plant(Organism, ABC):
    def __init__(self, world):
        super().__init__(world)

    def _set_initiative(self):
        self.initiative = 0

    def _set_strength(self):
        pass

    def action(self):
        if self.check_if_it_can_reproduce():
            self.sow()

    @abstractmethod
    def draw(self):
        pass

    @abstractmethod
    def get_probability(self):
        pass

    def sow(self):
        x = random.randint(0, 100)
        if x >= self.get_probability():
            return
        if not self.check_if_there_is_safe_place_to_move(1):
            return
        new_location = Location()
        while True:
            rand_x = random.randint(-1, 1)
            rand_y = random.randint(-1, 1)
            unique = True
            new_location.set(self.get_location().get_x() + rand_x, self.get_location().get_y() + rand_y)
            if not isinstance(self.world, HexWorld):
                if 0 <= new_location.get_x() < self.world.get_board().get_n() \
                        and 0 <= new_location.get_y() < self.world.get_board().get_m():
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location()):
                            unique = False
                    if unique:
                        break
            else:
                if rand_x == -1 and rand_y == 0:
                    new_location.set(new_location.get_x()+2, new_location.get_y()-2)
                elif rand_x == 1 and rand_y == 0:
                    new_location.set(new_location.get_x()-2, new_location.get_y()+2)
                if 0 <= new_location.get_x() < self.world.get_board().get_n() \
                        and 0 <= new_location.get_y() < self.world.get_board().get_m() and not (rand_x ==-1 and rand_y==-1) and not(rand_x ==1 and rand_y==1):
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location()):
                            unique = False
                    if unique:
                        break
        self.set_reproduce_ability(False)
        self.world.event_listener.add_string("Roslina : " + self.draw() + " zasiala na polu: " + str(new_location))
        self.world.birth_organism(self, new_location, BirthMode.Auto)

    @abstractmethod
    def birth(self):
        pass

    @abstractmethod
    def can_be_partner(self, other: Organism):
        pass
