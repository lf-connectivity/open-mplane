#  This file is part of pybootchartgui.

#  pybootchartgui is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  pybootchartgui is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with pybootchartgui. If not, see <http://www.gnu.org/licenses/>.

import sys
import os
import optparse

import parsing
import gui
import batch

def _mk_options_parser():
	"""Make an options parser."""
	usage = "%prog [options] PATH, ..., PATH"
	version = "%prog v0.0.0"
	parser = optparse.OptionParser(usage, version=version)
	parser.add_option("-i", "--interactive", action="store_true", dest="interactive", default=False, 
			  help="start in active mode")
	parser.add_option("-f", "--format", dest="format", default = None,
			  help="image format (...); default format ...")
	parser.add_option("-o", "--output", dest="output", metavar="PATH", default="bootchart.png",
			  help="output path (file or directory) where charts are stored")
	parser.add_option("-n", "--no-prune", action="store_false", dest="prune", default=True,
			  help="do not prune the process tree")
	parser.add_option("-q", "--quiet", action="store_true", dest="quiet", default=False,
			  help="suppress informational messages")
	parser.add_option("--very-quiet", action="store_true", dest="veryquiet", default=False,
			  help="suppress all messages except errors")
	parser.add_option("--verbose", action="store_true", dest="verbose", default=False,
			  help="print all messages")
	parser.add_option("--profile", action="store_true", dest="profile", default=False,
			  help="profile rendering of chart (only useful when in batch mode indicated by -f)")
	parser.add_option("--show-pid", action="store_true", dest="show_pid", default=False,
			  help="show process ids in the bootchart as 'processname [pid]'")	
	parser.add_option("--crop-after", dest="crop_after", metavar="PROCESS", default=None,
			  help="crop chart when idle after PROCESS is started")
	parser.add_option("--annotate", action="append", dest="annotate", metavar="PROCESS", default=None,
			  help="annotate position where PROCESS is started")
	parser.add_option("--annotate-file", dest="annotate_file", metavar="FILENAME", default=None,
			  help="filename to write annotation points to")
	return parser

class Writer:
	def __init__(self, write, options):
		self.write = write
		self.options = options
		
	def error(self, msg):
		self.write(msg)

	def warn(self, msg):
		if not self.options.quiet:
			self.write(msg)

	def info(self, msg):
		if self.options.verbose:
			self.write(msg)

	def status(self, msg):
		if not self.options.quiet:
			self.write(msg)

def _mk_writer(options):
	def write(s):
		print s
	return Writer(write, options)
	
def _get_filename(paths, options):
	"""Construct a usable filename for outputs based on the paths and options given on the commandline."""
	dir = ""
	file = "bootchart"
	if options.output and not(os.path.isdir(options.output)):
		return options.output
	if options.output:
		dir = options.output
	if len(paths) == 1:
		path = paths[0]
		if os.path.isdir(path):
			file = os.path.split(path)[-1]
		elif os.path.splitext(path)[1] in [".tar", ".tgz", ".tar.gz"]:
			file = os.path.splitext(path)[0]
	return os.path.join(dir, file + "." + options.format)

def main(argv=None):
	try:
		if argv is None:
			argv = sys.argv[1:]
	
		parser = _mk_options_parser()
		options, args = parser.parse_args(argv)
		writer = _mk_writer(options)

		if len(args) == 0:
			print "No path given, trying /var/log/bootchart.tgz"
			args = [ "/var/log/bootchart.tgz" ]
			

		res = parsing.parse(writer, args, options.prune,
				    options.crop_after, options.annotate)
		
		if options.interactive or options.output == None:
			gui.show(res, options)
		else:
			if options.annotate_file:
				f = open(options.annotate_file, "w")
				try:
					for time in res[-1]:
						if time is not None:
							print >>f, time
						else:
							print >>f
				finally:
					f.close()
			filename = _get_filename(args, options)
			def render():
				batch.render(writer, res, options, filename)
			if options.profile:
				import cProfile
				import pstats
				profile = '%s.prof' % os.path.splitext(filename)[0]
				cProfile.runctx('render()', globals(), locals(), profile)
				p = pstats.Stats(profile)
				p.strip_dirs().sort_stats('time').print_stats(20)
			else:
				render()

		return 0
	except parsing.ParseError, ex:
		print("Parse error: %s" % ex)
		return 2


if __name__ == '__main__':
	sys.exit(main())
