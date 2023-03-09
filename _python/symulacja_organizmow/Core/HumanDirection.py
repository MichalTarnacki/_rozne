from enum import Enum, unique


@unique
class HumanDirection(Enum):
    North = 1
    South = 2
    East = 3
    West = 4
    HexUp = 5
    HexDown = 6
    DoNotMove = 7
