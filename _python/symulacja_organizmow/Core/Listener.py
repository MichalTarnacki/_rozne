class Listener:
    def __init__(self):
        self.events = []

    def add_string(self, s):
        self.events.append(s + "\n")

    def __str__(self):
        text = ""
        for s in self.events:
            text += s
        return text

    def clear(self):
        self.events.clear()


