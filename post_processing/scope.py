
def read_scope(argument):
    start_time, length = argument.split('=')[1].split(':')
    return Scope(start_time, length)
def as_milliseconds(gps_timestamp):
    gps_timestamp = gps_timestamp.split('.')
    hours = int(gps_timestamp[0])
    minutes = int(gps_timestamp[1])
    seconds = int(gps_timestamp[2])
    milliseconds = (seconds + (minutes*60) + (hours*60*60)) * 1000
    return milliseconds
def read_gps_scope(argument):
    start_time, end_time = argument.split('=')[1].split(':')
    start_time = as_milliseconds(start_time)
    end_time = as_milliseconds(end_time)
    return Scope(start_time, end_time-start_time)
class Scope():
    def __init__(self, start_time, length):
        self.start_time = float(start_time)
        self.end_time = self.start_time + float(length)
    def __str__(self):
        return '_from_%s_to_%s' % (str(self.start_time), str(self.end_time))
    def within(self, entry):
        return ((entry.as_milliseconds() >= self.start_time) and (entry.as_milliseconds() <= self.end_time))
