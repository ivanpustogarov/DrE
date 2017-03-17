import sys

def handleAlias(aliasee, (name,width), outfile):
	ctype = widthToCtype(width)
	outfile.write("#define %s (*(%s *)&%s)\n" % (name,ctype,aliasee))

def addRegsHeader(outfile):
	outfile.write("""
#include "isr_compat.h"
#include <stdint.h>

"""
	)

def widthToCtype(width):
	if width == 1:
		ctype = "uint8_t"
	elif width == 2:
		ctype = "uint16_t"
	elif width == 4:
		ctype = "uint32_t"
	return ctype
	

def getAddr(line):
	argstart = line.find("(")
	argend = line.find(")")
	arg_string = line[argstart + 1:argend]
	args = arg_string.split(",")
	name = args[0].strip()
	addr = args[1].strip()

	offset = 0
	if addr.endswith("+1"):
		addr = addr[0:-2]
		offset = 1

	if addr in defines_map:
		addr = int(defines_map[addr],16) + offset
	else:
		print "couldn't find ", addr
	return (name,addr)

def addAddrEntry(name,addr,width,isRO,annotations):
	global addr_map
	global anno_map
	if addr not in addr_map:
		addr_map[addr] = []
	if annotations is not None:
		anno_map[name] = annotations
	addr_map[addr].append((name,width,isRO))
	
def write_definitions(addr_map):
	regfile = open("fake_regs.c", "w")
	addRegsHeader(regfile)
	all_addrs = sorted(addr_map.keys())

	def definePeripheral(periphValue):
		name = periphValue[0]
		width = periphValue[1]
		isRO = periphValue[2]
		ctype = widthToCtype(width)
		if isRO:
			regfile.write("const volatile %s %s = 0;\n" % (ctype, name))
		else:
			regfile.write("volatile %s %s = 0;\n" % (ctype, name))
		
	for addr in all_addrs:
		values = addr_map[addr]
		if len(values) == 1:
			definePeripheral(values[0])
		elif len(values) == 2:
			if values[0][0].endswith("_L"):
				definePeripheral(values[0])
			elif values[1][0].endswith("_L"):
				definePeripheral(values[1])
			else:
				definePeripheral(values[0])
		else:
			print "TOO MANY VALUES AT ", addr


def write_declarations(addr_map, all_lines):
	decfile = open("new_decl.h", "w")

	def declarePeripheral(addr, periphValue):
		name = periphValue[0]
		width = periphValue[1]
		isRO = periphValue[2]
		ctype = widthToCtype(width)
		decfile.write("#define %s (*(volatile %s *)0x%x)\n" % (name,ctype,addr))
	
	def handleAlias(addr, (name,width,isRO)):
		ctype = widthToCtype(width)
		decfile.write("#define %s (*(volatile %s *)0x%x)\n" % (name,ctype,addr))

	def handleTypeLine(line):
		(name,addr) = getAddr(line)
		values = addr_map[addr]
		if len(values) == 1:
			declarePeripheral(addr, values[0])
		elif len(values) == 2:
			declarePeripheral(addr, values[0])
			declarePeripheral(addr, values[1])
			#if values[0][0].endswith("_L"):
			#	handleAlias(values[0][0], values[1])
			#	declarePeripheral(values[0])
			#elif values[1][0].endswith("_L"):
			#	declarePeripheral(values[1])
			#	handleAlias(values[1][0], values[0])
			#else:
			#	print "what to do about ", values, "?"
		else:
			print "TOO MANY VALUES AT ", addr

	for line in all_lines:
		if line.startswith("sfrb"):
			print "found an sfrb"
			handleTypeLine(line)
		elif line.startswith("sfrw"):
			handleTypeLine(line)
		elif line.startswith("sfra"):
			handleTypeLine(line)
		elif line.startswith("const_sfrb"):
			handleTypeLine(line)
		elif line.startswith("const_sfrw"):
			handleTypeLine(line)
		elif line.startswith("const_sfra"):
			handleTypeLine(line)
		else:
			decfile.write(line + "\n")

def write_layout(addr_map, aux_lines):
	layoutfile = open("layout.txt", "w")

	all_addrs = sorted(addr_map.keys())

	for line in aux_lines:
		layoutfile.write("%s\n" % line)
	layoutfile.write("\n")

	def writeLayoutLine(addr, addrLine):
		name = addrLine[0]
		print "writing", name, "to layout"
		width = addrLine[1]
		if name in anno_map:
			annotations = " ".join(anno_map[name])
			layoutfile.write("addr %s 0x%04x %d %s\n" % (name, addr, width,annotations))
		else:
			annotations = None
			layoutfile.write("addr %s 0x%04x %d\n" % (name, addr, width))

	for addr in all_addrs:
		values = addr_map[addr]
		if len(values) == 1:
			writeLayoutLine(addr, values[0])
		elif len(values) == 2:
			if values[0][0].endswith("_L"):
				writeLayoutLine(addr, values[0])
			elif values[1][0].endswith("_L"):
				writeLayoutLine(addr, values[1])
			else:
				print "what to do about ", values, "?"
				sys.exit(1)
		else:
			print "TOO MANY VALUES AT ", addr

if __name__ == '__main__':
	global addr_map
	global anno_map
	addr_map = {}
	anno_map = {}

	#arg 1 is the header file
	infile = open(sys.argv[1])

	aux_lines = []
	try:
		aux_layout = open(sys.argv[2])
		for line in aux_layout:
			line = line.strip()
			pieces = line.split()
			if line.startswith("#") or len(pieces) == 0:
				pass
			elif pieces[0] == "addr":
				if len(pieces) > 4:
					addAddrEntry(pieces[1],int(pieces[2],16),int(pieces[3]),True,pieces[4:])
				else:
					addAddrEntry(pieces[1],int(pieces[2],16),int(pieces[3]),True,None)
			elif pieces[0] == "anno":
				name = pieces[1]
				annotations = pieces[2:]
				anno_map[name] = annotations
			else:
				aux_lines.append(line)
	except:
		print "no aux layout, using empty"
			

	defines_map = {}
	all_lines = []

	for line in infile:
		line = line.strip()
		all_lines.append(line)
		if line.startswith("#define"):
			pieces = line.split()
			define = pieces[0].strip()
			macro = pieces[1].strip()

			if len(pieces) == 2:
				value = None
			else:
				value = pieces[2].strip()
			defines_map[macro] = value
		elif line.startswith("sfrb"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,1, False,None)
		elif line.startswith("sfrw"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,2, False,None)
		elif line.startswith("sfra"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,4, False,None)
		elif line.startswith("const_sfrb"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,1,True,None)
		elif line.startswith("const_sfrw"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,2, True,None)
		elif line.startswith("const_sfra"):
			(name,addr) = getAddr(line)
			addAddrEntry(name,addr,4, True,None)

	write_declarations(addr_map, all_lines)
	write_definitions(addr_map)
	#write_layout(addr_map, aux_lines)
	

