from __future__ import annotations
import copy

from Core.Dimension import Dimension
from Core.Mode import ToStringMode


class Board:
    """Creates board with N (x), M (y)"""

    def __init__(self, dimension: Dimension):
        self.dimension = copy.copy(dimension)

    def get_m(self):
        return self.dimension.y

    def get_n(self):
        return self.dimension.x

    def get_field_number(self):
        return self.dimension.x * self.dimension.y

    def set(self, other: Board):
        self.dimension = copy.copy(other.dimension)

    def __str__(self, mode: ToStringMode = ToStringMode.Pretty):
        if mode == ToStringMode.Pretty:
            return self.dimension.__str__()
        else:
            return self.dimension.__str__(ToStringMode.Simple)
