
def read_scope(argument):
    start_time, length = argument.split('=')[1].split(':')
    return Scope(start_time, length)
class Scope():
    def __init__(self, start_time, length):
        self.start_time = float(start_time)
        self.end_time = self.start_time + float(length)
    def __str__(self):
        return '_from_%s_to_%s' % (str(self.start_time), str(self.end_time))
