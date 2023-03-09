from enum import Enum, unique


@unique
class ToStringMode(Enum):
    Pretty = 1
    Simple = 2
