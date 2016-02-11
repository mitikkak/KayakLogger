class tilt_logger_database():
    def __init__(self):
        self.events = {}
    def save_events(self, lines, scope):
        for line in lines:
            if line:
                ev = Event(line)
                if ev.within(scope): self.events[ev.id()] = ev
        print len(self.events)
    def average(self):
        keys = sorted(self.events.keys())
        total = Event(self.events[keys[0]].line)
        for key_idx in range(1, len(keys)):
            total.add(self.events[keys[key_idx]])
        total.divide_by(len(keys))
        return total
    def log(self):
        for ev in sorted(self.events):
            print self.events[ev]
class Event():
    def __init__(self, line):
        self.line = line
        self.millis = self.read_element(line,'millis')
        self.roll = self.read_element(line,'roll')
        self.pitch = self.read_element(line,'pitch')
        self.x = self.read_element(line,'x')
        self.y = self.read_element(line,'y')
        self.z = self.read_element(line,'z')
    def id(self):
        return self.millis
    def read_element(self, line, name):
        elements = line.split(';')
        value = 0
        for element in elements:
            if name in element:
                element_parts = element.split(':')
                value = element_parts[1]
        return float(value)
    def within(self, scope):
        if scope is None: return 1
        if self.millis < scope.start_time: return None
        if self.millis > scope.end_time: return None
        return 1
    def add(self, another):
        self.millis += another.millis
        self.roll += another.roll
        self.pitch += another.pitch
        self.x += another.x
        self.y += another.y
        self.z += another.z
    def divide_by(self, divider):
        self.millis = self.millis / divider
        self.roll = self.roll / divider
        self.pitch = self.pitch / divider
        self.x = self.x / divider
        self.y = self.y / divider
        self.z = self.z / divider
    def __str__(self):
        return '[millis] %s [roll] %s [pitch] %s [x] %s [y] %s [z] %s' % (str(self.millis), str(self.roll), str(self.pitch), str(self.x), str(self.y), str(self.z))
