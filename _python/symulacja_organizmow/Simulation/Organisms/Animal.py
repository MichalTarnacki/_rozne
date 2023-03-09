import random
from abc import ABC, abstractmethod

from Core.BirthMode import BirthMode
from Core.Location import Location
from Simulation.HexWorld import HexWorld
from Simulation.Organism import Organism


class Animal(Organism, ABC):

    def __init__(self, world):
        super().__init__(world)

    @abstractmethod
    def _set_initiative(self):
        pass

    @abstractmethod
    def _set_strength(self):
        pass

    def action(self):
        self.move()

    @abstractmethod
    def draw(self):
        pass

    def move(self, move_range: int = 1):
        can_move = False
        new_location = Location()
        for i in range(-1, 2, 1):
            for j in range(-1, 2, 1):
                new_location.set(self.get_location().get_x() + j * move_range,
                                 self.get_location().get_y() + i * move_range)
                if not isinstance(self.world, HexWorld):
                    if (not new_location.__eq__(self.get_location())) and new_location.get_y() >= 0 and 0 <= \
                            new_location.get_x() < self.world.get_board().get_n()\
                            and new_location.get_y() < self.world.get_board().get_m():
                        can_move = True
                else:
                    if new_location.__eq__(Location(self._location.get_x() - move_range, self._location.get_y())):
                        new_location.set(new_location.get_x() + 2 * move_range, new_location.get_y() - 2 * move_range)
                    elif new_location.__eq__(Location(self._location.get_x() + move_range, self._location.get_y())):
                        new_location.set(new_location.get_x() - 2 * move_range, new_location.get_y() + 2 * move_range)
                    if not new_location.__eq__(self.get_location()) and new_location.get_y() >= 0 and \
                            0 <= new_location.get_x() < self.world.get_board().GetN() and \
                            new_location.get_y() < self.world.get_board().GetM() and \
                            not (i == -move_range and j == -move_range) and not (i == move_range and j == move_range):
                        can_move = True
        if not can_move:
            return
        if not isinstance(self.world, HexWorld):
            while True:
                rand_x = move_range * random.randint(-1, 1)
                rand_y = move_range * random.randint(-1, 1)
                new_location.set(self._location.get_x() + rand_x, self._location.get_y() + rand_y)
                if not(new_location.__eq__(
                        self._location) or new_location.get_x() < 0 or new_location.get_y() < 0 or new_location.get_x() >= self.world.get_board().get_n() or new_location.get_y() >= self.world.get_board().get_m()):
                    break
            self._location.set(new_location.get_x(), new_location.get_y())
        else:
            while True:
                rand_x = move_range * random.randint(-1, 1)
                rand_y = move_range * random.randint(-1, 1)
                new_location.set(self._location.get_x() + rand_x, self._location.get_y() + rand_y)
                if rand_x == -move_range and rand_y == 0:
                    new_location.set(new_location.get_x() + 2 * move_range, new_location.get_y() - 2 * move_range)
                elif rand_x == move_range and rand_y == 0:
                    new_location.set(new_location.get_x() - 2 * move_range, new_location.get_y() + 2 * move_range)
                if not(new_location.__eq__(
                        self._location) or new_location.get_x() < 0 or new_location.get_y() < 0 or new_location.get_x() >= self.world.get_board().get_n() or new_location.get_y() >= self.world.get_board().get_m() or (
                        rand_x == -move_range and rand_y == -move_range) or (
                        rand_x == move_range and rand_y == move_range)):
                    break
            self._location.set(new_location)

    def move_without_collision(self, move_range):
        if not self.check_if_there_is_safe_place_to_move():
            return False
        new_location = Location()
        while True:
            unique = True
            rand_x = move_range*random.randint(-1, 1)
            rand_y = move_range*random.randint(-1, 1)
            new_location.set(self._location.get_x() + rand_x, self._location.get_y()+rand_y)
            if not isinstance(self.world, HexWorld):
                if not new_location.__eq__(self._location) and new_location.get_x() >= 0 and new_location.get_y() >= 0 and new_location.get_x() < self.world.get_board().get_n() and new_location.get_y() < self.world.get_board().get_m():
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location()):
                            unique = False
                    if unique:
                        self.set_location(new_location)
                        break
            else:
                if new_location.__eq__(Location(self._location.get_x() - move_range, self._location.get_y())):
                    new_location.set(new_location.get_x() + 2*move_range, new_location.get_y() - 2*move_range)
                elif new_location.__eq__(Location(self._location.get_x() + move_range, self._location.get_y())):
                    new_location.set(new_location.get_x() - 2*move_range, new_location.get_y() + 2*move_range)
                if not new_location.__eq__(self._location) and new_location.get_x() >= 0 and new_location.get_y() >= 0 and new_location.get_x() < self.world.get_board().get_n() and new_location.get_y() < self.world.get_board().get_m() and not (rand_x==-move_range and rand_y==-move_range) and not(rand_x==move_range and rand_y==move_range):
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location):
                            unique = False
                        if unique:
                            self.set_location(new_location)
                            break
        return True

    @abstractmethod
    def birth(self):
        pass

    @abstractmethod
    def can_be_partner(self, other: Organism):
        pass

    def collision(self, other: Organism):
        if self.can_be_partner(other):
            other.set_location(other.get_previous_location())
            if other.check_if_it_can_reproduce() and self.check_if_it_can_reproduce():
                self.copulation(other)
        else:
            super().collision(other)

    def copulation(self, other):
        if not other.check_if_there_is_safe_place_to_move():
            return
        new_location = Location()
        while True:
            unique = True
            rand_x = random.randint(-1, 1)
            rand_y = random.randint(-1, 1)
            new_location.set(other.get_location().get_x() + rand_x, other.get_location().get_y() + rand_y)
            if not isinstance(self.world, HexWorld):
                if 0 <= new_location.get_x() < self.world.get_board().get_n() and 0 <= new_location.get_y() < self.world.get_board().get_m():
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location()) and organism.check_if_it_is_alive():
                            unique = False
                    if unique:
                        break
            else:
                if rand_x == -1 and rand_y == 0:
                    new_location.set(new_location.get_x()+2, new_location.get_y()-2)
                elif rand_x == 1 and rand_y == 0:
                    new_location.set(new_location.get_x()-2, new_location.get_y()+2)
                if 0 <= new_location.get_x() < self.world.get_board().get_n() and 0 <= new_location.get_y() < self.world.get_board().get_m() and not (rand_x == -1 and rand_y == -1) and not (rand_x == 1 and rand_y == 1):
                    for organism in self.world.get_organisms():
                        if new_location.__eq__(organism.get_location()) and organism.check_if_it_is_alive():
                            unique = False
                    if unique:
                        break
        self.set_reproduce_ability(False)
        other.set_reproduce_ability(False)
        self.world.event_listener.add_string("Zwierze : " + self.draw() + " rozmnaza sie, \n a jego dziecko laduje na polu: " + str(new_location))
        self.world.birth_organism(self, new_location, BirthMode.Auto)
