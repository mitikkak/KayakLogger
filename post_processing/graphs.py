from tilt_logger_database import tilt_logger_database
import pylab
import matplotlib.patches as mpatches
import os
import sys

import file_reader
from scope import read_scope


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
            print "attribute % s, value %s, millis %s" % (attribute, attribute_value, millis)
            xvalues.append(attribute_value)
            yvalues.append(millis)
        lines = pylab.plot(xvalues, yvalues, label=attribute)
        pylab.draw()

class Options():
    def __init__(self):
        self.tilt = None
        self.acceleration = None
        self.scope = None
    def __str__(self):
        return 'tilt: %s, acceleration: %s, scope: %s' % (self.tilt, self.acceleration, self.scope)
def parse_arguments():
    arguments = sys.argv[1:]
    input_files = None
    options = Options()
    for argument in arguments:
        if '-tilt' in argument:
            options.tilt = 1
        elif '-acc' in argument:
            options.acceleration = 1
        elif '-scope' in argument:
            options.scope = read_scope(argument)
        else:
            input_files = argument
    return input_files, options

if __name__ == '__main__':
    input_files, options = parse_arguments()
    print "Input files are %s" % input_files
    print "Options are %s" % options
    path = os.path.dirname(os.path.abspath(input_files))
    graph = tilt_graph()
    graph.setup(input_files, options.scope)
    if options.tilt:
        attributes = ('roll', 'pitch')
        graph.print_to_file(attributes, path + '/' 'tilt.png', 'right')
    if options.acceleration:
        attributes = ('x', 'y', 'z')
        for attribute in attributes:
            file_name = path + '/' 'acceleration_' + attribute + '_' + str(options.scope) + '.png'
            print "Attribute %s to file %s" % (attribute, file_name)
            graph.print_to_file(attribute, file_name, 'right')
        file_name = path + '/' 'acceleration_' + str(attributes) + '_' + str(options.scope) + '.png'
        graph.print_to_file(attributes, file_name, 'right')
