
import file_reader
import re
import gpxpy
import gpxpy.gpx
import sys
from __builtin__ import float
from copy import deepcopy
from math import radians, cos, sin, asin, sqrt

pause_limit = 20
pause_speed_limit = 0.2

def haversine(lon1, lat1, lon2, lat2):
    """
    Calculate the great circle distance between two points 
    on the earth (specified in decimal degrees)
    """
    # convert decimal degrees to radians 
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

    # haversine formula 
    dlon = lon2 - lon1 
    dlat = lat2 - lat1 
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * asin(sqrt(a)) 
    r = 6371 # Radius of earth in kilometers. Use 3956 for miles
    return c * r

def parse_arguments():
    arguments = sys.argv[1:]
    return arguments[0]

class Entry():
    def __init__(self, speed, latitude, longitude, seconds, minutes, hours, line):
        self.speed = speed
        self.latitude = latitude
        self.longitude = longitude
        self.line = line
        self.seconds = seconds
        self.minutes = minutes
        self.hours = hours
        self.time_str = str(hours) + ':' + str(minutes) + ':' + str(seconds)
        self.time = (hours * 60 * 60) + (minutes * 60) + seconds
    def __str__(self):
        return self.line
    def when_and_where(self):
        return 'LAT: %s, LON: %s at %d:%d:%d' % (self.latitude, self.longitude, self.hours, self.minutes, self.seconds)
    def as_seconds(self):
        return self.seconds + self.minutes*60 + self.hours*60*60
    def as_milliseconds(self):
        return self.as_seconds()*1000
    def __eq__(self, other):
        return (self.line in other.line)

class Gps_database():
    def __init__(self, file_name, scope=None):
        lines = file_reader.get_lines(file_name, 'HDOP')
        valid_lines = self.get_valid_lines(lines)
        print 'number of GPS entries: %d, valid: %d' % (len(lines), len(valid_lines))
        self.create_entries(valid_lines, scope)
        print 'Pauses:'
        pauses, pause_entries = self.pauses()
        for pause in pauses:
            print pause
        print len(pause_entries)
        travel_entries = self.remove_entries(pause_entries)
        print len(travel_entries)
        travel_speed = self.average('speed', travel_entries)
        average_speed = self.average('speed', self.entries)
        highest_speed, highest_speed_location = self.highest('speed')
        #lowest_speed_limit = 0.1
        #number_of_slow = self.below(lowest_speed_limit, 'speed')
        print('Speed:: highest: %s at %s, average: %f, travel: %f' % (highest_speed, highest_speed_location, average_speed, travel_speed))
        print('Total distance: %f' % self.distance())

    def create_entries(self, lines, scope):
        entries = []
        for line in lines:
            speed = float(re.search(r'Spe:(.*);', line).group(1))
            latitude = float(re.search(r'Lat:(.*); Lon:', line).group(1))
            longitude = float(re.search(r'Lon:(.*); Y:', line).group(1))
            seconds = int(re.search(r'S:(.*); Spe:', line).group(1))
            minutes = int(re.search(r'Mi:(.*); S:', line).group(1))
            hours = int(re.search(r'H:(.*); Mi:', line).group(1))
            entry = Entry(speed, latitude, longitude, seconds, minutes, hours, line)
            if scope is None:
              entries.append(entry)
            elif (scope.within(entry)):
              entries.append(entry)
        duplicate_entries = []
        non_duplicate_entries = []
        for entry_index in range (1, len(entries)):
            if entries[entry_index] == entries[entry_index-1]:
                duplicate_entries.append(entries[entry_index])
            else:
                non_duplicate_entries.append(entries[entry_index])
        if duplicate_entries:
            print "Duplicate entries: %d between %s" % (len(duplicate_entries), duplicate_entries[0].line)
        else:
            print "No duplicate entries!"
        self.entries = non_duplicate_entries
        print "Entries: %d" % len(self.entries)
    def remove_entries(self, pause_entries):
        return [entry for entry in self.entries if entry not in pause_entries]
    def get_valid_lines(self, lines):
        hdop_valid_entries = []
        position_valid_entries = []
        first_reliable = None
        for line in lines:
            value = int(line.split(';')[0].split(':')[1])
            if value < 900:
                hdop_valid_entries.append(line)
            if (value < 200) and first_reliable is None:
                first_reliable = line
        for line in hdop_valid_entries:
            latitude = float(line.split(';')[1].split(':')[1])
            longitude = float(line.split(';')[2].split(':')[1])
            reliable_latitude = float(first_reliable.split(';')[1].split(':')[1])
            reliable_longitude = float(first_reliable.split(';')[2].split(':')[1])
            if ((abs(latitude - reliable_latitude) > 2.0) or (abs(longitude - reliable_longitude) > 2.0)):
                print 'prblematic latitude/longitude at %s' % line
            else:
                position_valid_entries.append(line)
        return position_valid_entries
    def highest(self, attribute):
        highest = None
        highest_entry = None
        for entry in self.entries:
            value = getattr(entry, attribute)
            if value > highest:
                highest = value
                highest_entry = entry
        return str(highest), str(highest_entry)
    def average(self, attribute, entries):
        total = 0
        for entry in entries:
            value = getattr(entry, attribute)
            total += float(value)
        return total / len(entries)
    def below(self, limit, attribute):
        total = 0
        for entry in self.entries:
            value = getattr(entry, attribute)
            if float(value) <= limit: total += 1
        return total
    def distance(self):
        total = 0
        for entry_idx in range (1, len(self.entries)):
            prev = self.entries[entry_idx-1]
            curr = self.entries[entry_idx]
            delta = haversine(prev.longitude, prev.latitude, curr.longitude, curr.latitude)
            total += delta
        return total
    def get_gpx(self):
        gpx = gpxpy.gpx.GPX()
        gpx_track = gpxpy.gpx.GPXTrack()
        gpx.tracks.append(gpx_track)
        gpx_segment = gpxpy.gpx.GPXTrackSegment()
        gpx_track.segments.append(gpx_segment)
        for entry in self.entries:
            gpx_segment.points.append(gpxpy.gpx.GPXTrackPoint(entry.latitude, entry.longitude, elevation=0))
        return gpx
    def pauses(self):
        pauses = []
        candidate = None
        for entry in self.entries:
            if float(entry.speed) < pause_speed_limit:
                if candidate is None:
                    candidate = self.Pause(entry)
                if candidate.long_enough(entry) and candidate not in pauses:
                    pauses.append(candidate)
            else: candidate = None
        pause_entries = []
        for pause in pauses:
            pause_entries += self.get_pause_entries(pause)
        return pauses, pause_entries
    def get_pause_entries(self, pause):
        pause_entries = []
        for entry in self.entries:
            if pause.contains(entry):
                #print "adding pause entry %s" % entry.line
                pause_entries.append(entry)
        return pause_entries
    class Pause():
        def __init__(self, entry):
            self.start = entry
            self.end = None
        def long_enough(self, entry):
            self.end = entry
            if self.end.as_seconds() - self.start.as_seconds() > pause_limit:
                return 1
            return None
        def contains(self, entry):
            return ((entry.as_seconds >= self.start.as_seconds) and (entry.as_seconds <= self.end.as_seconds) and (float(entry.speed) < pause_speed_limit))
        def __str__(self):
            ret_value = '\t started %s\n' % self.start.when_and_where()
            ret_value += '\t ended %s\n' % self.end.when_and_where()
            ret_value += '\t ===> lasted %d seconds' % (self.end.as_seconds() - self.start.as_seconds())
            return ret_value
if __name__ == '__main__':
    import os
    input_files = parse_arguments()
    path = os.path.dirname(os.path.abspath(input_files))
    gps_db = Gps_database(input_files)
    gpx = gps_db.get_gpx()
    gpx_file = open(path + '/' + 'route.gpx', 'w')
    gpx_file.write(gpx.to_xml())
