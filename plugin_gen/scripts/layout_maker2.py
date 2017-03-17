#!/usr/bin/python
import sys
import os
import os.path


if __name__ == "__main__":
	arch_name = sys.argv[1]
	mcu_directory = sys.argv[2]

	output = open("layout.txt", 'w')

	peripherals8_begin = -1
	peripherals8_end = -1
	peripherals16_begin = -1
	peripherals16_end = -1
	sfr_begin = -1
	sfr_end = -1
	info_begin = -1
	info_end = -1

	#build memory regions from msp430-gcc files
	in_memory = False
	mem_subdir = os.path.join("analysis", "ldscripts", arch_name, "memory.x")
	gcc_mem_layout_filename = os.path.join(mcu_directory, mem_subdir)
	gcc_mem_layout_file = open(gcc_mem_layout_filename)
	output.write("layout 0x10000\n")
	flash_regions = []
	for line in gcc_mem_layout_file:
		if "}" in line:
			in_memory = False

		if in_memory:
			#strip comment from line
			line = line.strip()
			comment_start = line.find("/*")
			print line
			if comment_start >= 0:
				comment_end = line.find("*/", comment_start)
				line = line[0:comment_start]
			if len(line) == 0:
				continue
			(region,region_details) = line.split(":")
			region = region.strip()
			region_split = region.split()
			region_name = region_split[0]
			attributes = ""
			if len(region_split) == 2:
				attributes = region_split[1]
			print "region: ", region_name
			layout = region_details.split(",")
			origin_string = layout[0]
			length_string = layout[1]
			origin_value = origin_string.split("=")[1].strip()
			print "origin: %s" % origin_value
			length_value = length_string.split("=")[1].strip()
			print "length: %s" % length_value
			print "attrs: %s" % attributes
			print "-------\n"
			origin = int(origin_value, 16)
			length = int(length_value, 16)
			end = origin + length - 1
			if region_name == 'infomem':
				output.write("range 0x%x 0x%x persistent information_memory\n" % (origin, end))
				info_begin = origin
				info_end = origin + end
			if region_name == "infoa" or region_name == "infob" or region_name == "infoc" or region_name == "infod":
				if not (origin == end or end < 0):
					output.write("range 0x%x 0x%x flash\n" % (origin, end))
					flash_regions.append((origin,end))
				else:
					print "END < 0 or ORIGIN = END"
			if region_name == "peripheral_8bit":
				peripherals8_begin = origin
				peripherals8_end = end
			if region_name == "peripheral_16bit":
				peripherals16_begin = origin
				peripherals16_end = end
			if region_name == "sfr":
				sfr_begin = origin
				sfr_end = end

		if "MEMORY {" in line:
			in_memory = True
	
	#build addrs
	periph_subdir = os.path.join("analysis", "ldscripts", arch_name, "periph.x")
	gcc_periphs_filepath = os.path.join(mcu_directory, periph_subdir)
	gcc_periphs_file = open(gcc_periphs_filepath)
	for line in gcc_periphs_file:
		line = line.strip()
		pieces = line.split()
		name = pieces[0][2:]
		location = int(pieces[2][0:-1], 16)
		length = 1
		if location >= peripherals8_begin and location < peripherals8_end:
			length = 1
		elif location >= peripherals16_begin and location < peripherals16_end:
			length = 2
		elif location >= sfr_begin and location < sfr_end:
			length = 1
		elif location >= info_begin and location < info_end:
			length = 1
		else:
			print "out of bounds %s: 0x%x" % (name, location)
		output.write("addr %s 0x%04x %d\n" % (name, location, length))
		#print name, location

	interrupt_aggregate = open("../all_interrupts.txt", 'a')

	#build interrupts
	gcc_header_filename = os.path.join(mcu_directory, "upstream", arch_name + ".h")
	gcc_header_file = open(gcc_header_filename, 'r')
	for line in gcc_header_file:
		pieces = line.split()
		if len(pieces) < 3:
			continue
		define = pieces[0].strip()
		vec = pieces[1].strip()
		if not define == "#define":
			continue
		if not vec.endswith("_VECTOR"):
			continue
		pieces = vec.split("_VECTOR")
		isr = pieces[0]
		if "VECTOR" in isr:
			print "VEC1"
			sys.exit(1)
		output.write("interrupt %s_ISR check_%s\n" % (isr, isr))
		interrupt_aggregate.write(isr + "\n")
	
	gcc_peripherals_filename = os.path.join(mcu_directory, "analysis", "peripherals.lst")
	gcc_periperhals_file = open(gcc_peripherals_filename, 'r')
	for line in gcc_periperhals_file:
		line = line.strip()
		if "VECTOR" in line:
			print "VEC2"
			sys.exit(1)
		output.write("interrupt %s_ISR check_%s\n" % (line, line))
		interrupt_aggregate.write(line + "\n")
