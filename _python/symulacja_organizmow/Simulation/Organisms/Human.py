import copy
import random
from abc import ABC
from datetime import datetime

from Core.HumanDirection import HumanDirection
from Core.Location import Location
from Core.Mode import ToStringMode
from Simulation.HexWorld import HexWorld
from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Human(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()
        self.__is_antilope_movement_active = False
        self.__activation_time = - 1
        self.__direction = HumanDirection.DoNotMove

    def _set_initiative(self):
        self._initiative = 5

    def _set_strength(self):
        self._strength = 9

    def action(self):
        if self.__is_antilope_movement_active:
            if self.world.get_round_number() - self.__activation_time < 3:
                self.move(2)
            elif self.world.get_round_number() - self.__activation_time < 5:
                x = random.randint(0, 100)
                if x >= 50:
                    self.move(2)
                else:
                    self.move()
            else:
                self.__is_antilope_movement_active = False
                self.action()
        else:
            super().action()

    def draw(self):
        return '+'

    def move(self, move_range: int = 1):
        new_location = Location()
        if not isinstance(self.world, HexWorld):
            if self.__direction == HumanDirection.West:
                new_location.set(self.get_location().get_x() - move_range, self.get_location().get_y())
            elif self.__direction == HumanDirection.East:
                new_location.set(self.get_location().get_x() + move_range, self.get_location().get_y())
            elif self.__direction == HumanDirection.North:
                new_location.set(self.get_location().get_x(), self.get_location().get_y() - move_range)
            elif self.__direction == HumanDirection.South:
                new_location.set(self.get_location().get_x(), self.get_location().get_y() + move_range)
            if new_location.get_x() < 0 or new_location.get_y() < 0 or new_location.get_x() >= self.world.get_board().get_n() or new_location.get_y() >= self.world.get_board().get_m():
                new_location = copy.copy(self.get_location())
        else:
            if self.__direction == HumanDirection.West:
                new_location.set(self.get_location().get_x() - move_range, self.get_location().get_y() + move_range)
            elif self.__direction == HumanDirection.East:
                new_location.set(self.get_location().get_x() + move_range, self.get_location().get_y() - move_range)
            elif self.__direction == HumanDirection.North:
                new_location.set(self.get_location().get_x(), self.get_location().get_y() - move_range)
            elif self.__direction == HumanDirection.South:
                new_location.set(self.get_location().get_x(), self.get_location().get_y() + move_range)
            # elif self.__direction == HumanDirection.HexUp:
            # new_location.set(self.get_location().get_x(), self.get_location().get_y() - move_range)
            # elif self.__direction == HumanDirection.HexDown:
            #     new_location.set(self.get_location().get_x(), self.get_location().get_y() + move_range)
            if new_location.get_x() < 0 or new_location.get_y() < 0 or new_location.get_x() >= self.world.get_board().get_n or new_location.get_y() >= self.world.get_board().get_m:
                new_location = copy.copy(self.get_location())
        self.set_location(new_location)

    def birth(self):
        return Human(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Human):
            return True
        return False

    def special_ability(self):
        if not self.__is_antilope_movement_active:
            if self.__activation_time == -1 or self.world.get_round_number() - self.__activation_time > 9:
                self.__is_antilope_movement_active = True
                self.__activation_time = self.world.get_round_number()
                self.world.event_listener.add_string("Czlowiek aktywowal specjalna umiejetnosc")
            else:
                self.world.event_listener.add_string("Nie można aktywować umiejetności")
        else:
            self.world.event_listener.add_string("Nie można aktywować umiejetności")

    def load_properties(self, strength, initiative, location: Location, location_before: Location,
                        date_of_birth: datetime, is_alive: bool, capable_of_reproduction: bool, opt_par1: bool = None,
                        opt_par2: int = None):
        if opt_par1 is not None:
            self.__is_antilope_movement_active = opt_par1
        if opt_par2 is not None:
            self.__activation_time = opt_par2
        super().load_properties(strength, initiative, location, location_before,
                        date_of_birth, is_alive, capable_of_reproduction, opt_par1,
                        opt_par2)

    def set_move_direction(self, direction: HumanDirection):
        self.__direction = direction

    def __str__(self, mode: ToStringMode = ToStringMode.Pretty):
        if mode == ToStringMode.Pretty:
            return super().__str__() + " Ruch antylopy aktywny: " + str(self.__is_antilope_movement_active) + " Czas aktywacji:" + str(self.__activation_time)
        else:
            return super().__str__(ToStringMode.Simple) + " " + str(self.__is_antilope_movement_active) + " " + str(self.__activation_time)

    def get_color(self):
        return "#9ea3b0"