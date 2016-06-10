from tilt_logger_database import tilt_logger_database
import pylab
import matplotlib.patches as mpatches
import os
import sys

import file_reader
from scope import read_scope, read_gps_scope
from gps_database import Gps_database

class tilt_graph():
    def __init__(self):
        pass
    def setup(self, file_name, scope):
        self.db = tilt_logger_database()
        values = file_reader.get_lines(file_name)
        if values:
            self.db.save_events(values, scope)
            #self.db.log()
        else:
            print('failure no values!')
    
    def print_to_file(self, attributes, plot_name, position):
        pylab.ylabel('Milliseconds')
        pylab.xlabel('Degrees')
        legend_labels = []
        for attribute in attributes:
            self.print_attribute(attribute)
            legend_labels.append(attribute)
        pylab.legend(legend_labels)
        pylab.draw()
        pylab.savefig(plot_name, dpi=80)
        pylab.close()
    def print_attribute(self, attribute):
        xvalues = []
        yvalues = []
        pylab.gca().get_yaxis().get_major_formatter().set_useOffset(False)
        for event_key in sorted(self.db.events):
            attribute_value = getattr(self.db.events[event_key], attribute)
            millis = self.db.events[event_key].millis
            #print "attribute % s, value %s, millis %s" % (attribute, attribute_value, millis)
            xvalues.append(attribute_value)
            yvalues.append(millis)
        lines = pylab.plot(xvalues, yvalues, label=attribute)
        pylab.draw()

class graph():
    def __init__(self, db):
        self.db = db
    
    def print_to_file(self, attribute, plot_name, position):
        pylab.figure(figsize=(110,20), dpi=280)
        #pylab.autoscale(True)
        pylab.xlabel('Time')
        pylab.ylabel(attribute)
        legend_labels = []
        self.print_attribute(attribute)
        legend_labels.append(attribute)
        pylab.legend(legend_labels)
        pylab.draw()
        pylab.savefig(plot_name)
        #pylab.savefig(plot_name)
        
        pylab.close()
    def print_attribute(self, attribute):
        time_values = []
        time_strings = []
        speed_values = []
        pylab.gca().get_yaxis().get_major_formatter().set_useOffset(False)
        time_position = 1
        for entry in self.db.entries:
            speed_values.append(entry.speed)
            time_values.append(time_position)
            time_position += 1
            time_strings.append(entry.time_str)
        locs, labels = pylab.xticks(time_values, time_strings)
        pylab.plot(time_values, speed_values, label=attribute)
        pylab.setp(labels, rotation=90, fontsize=5)
        pylab.draw()

class Options():
    def __init__(self):
        self.tilt = None
        self.acceleration = None
        self.scope = None
        self.speed = None
    def is_empty(self):
        if not self.tilt and not self.acceleration and not self.speed:
            return True
        return False
    def full_list(self):
        print "-acc: acceleration"
        print "-tilt: pitch and roll"
        print "-scope: time start and length"
        print "-gscope: ???"
        print "-speed: speed reported by GPS"
        print "-all: speed, tilt and acceleration"
    def complain(self):
        print "You need to give at least one of these: speed, tilt, acceleration."
        print "Full options are: %s" % self.full_list()
    def __str__(self):
        return 'tilt: %s, acceleration: %s, scope: %s, speed: %s' % (self.tilt, self.acceleration, self.scope, self.speed)
def parse_arguments():
    arguments = sys.argv[1:]
    input_files = None
    options = Options()
    for argument in arguments:
        if '-tilt' in argument:
            options.tilt = True
        elif '-acc' in argument:
            options.acceleration = True
        elif '-scope' in argument:
            options.scope = read_scope(argument)
        elif '-gscope' in argument:
            options.scope = read_gps_scope(argument)
        elif '-speed' in argument:
            options.speed = True
        elif '-all' in argument:
            options.speed = True
            options.tilt = True
            options.acceleration = True
        else:
            input_files = argument
    return input_files, options

def complain_about_input_file():
    print "You need to input datalog file"

def get_date(input_files):
    log_prefix = 'DATALOG_'
    if log_prefix in input_files:
        date = input_files.lstrip(log_prefix).rstrip('.TXT')
        print "date : %s" % date
        return date
    else:
        print "could not resolve date"
        return "None"

if __name__ == '__main__':
    input_files, options = parse_arguments()
    print "Input files are %s" % input_files
    print "Options are %s" % options
    if input_files is None:
        complain_about_input_file()
        exit()
    if options.is_empty():
        options.complain()
        exit()
    date = get_date(input_files)
    path = os.path.dirname(os.path.abspath(input_files))
    acc_graph = tilt_graph()
    acc_graph.setup(input_files, options.scope)
    graph_files = []
    if options.tilt:
        attributes = ('roll', 'pitch')
        for attribute in attributes:
          file_name = path + '/' + attribute + '.png'
          acc_graph.print_to_file(attribute, file_name, 'right')
          graph_files.append(file_name)
    if options.acceleration:
        attributes = ('x', 'y', 'z')
        for attribute in attributes:
            file_name = path + '/' 'acceleration_' + date + '_' + attribute + '_' + str(options.scope) + '.png'
            print "Attribute %s to file %s" % (attribute, file_name)
            acc_graph.print_to_file(attribute, file_name, 'right')
            graph_files.append(file_name)
        #file_name = path + '/' 'acceleration_' + date + '_' + str(attributes) + '_' + str(options.scope) + '.png'
        #acc_graph.print_to_file(attributes, file_name, 'right')
    if options.speed:
      gps_db = Gps_database(input_files, options.scope)
      speed_graph = graph(gps_db)
      file_name = 'Speed_' + date + '.png'
      speed_graph.print_to_file('Speed', file_name, 'right')
      graph_files.append(file_name)
    
    try:
        import web_server
        web_server.start_cherrypy_app(input_files, options, graph_files)
    except:
        print "could not import web server"

