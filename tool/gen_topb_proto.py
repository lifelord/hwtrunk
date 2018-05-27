# -*- coding: cp936 -*-
#!/usr/bin/python

import os
import shutil
import sys
import os.path
import re
import string

self_path=os.path.normpath(os.path.join(os.getcwd(),os.path.dirname(__file__)))
proto_path = os.path.dirname(self_path)
proto_file_path = proto_path+"/protocal/proto/"

des_path = proto_path+"/protocal/pbc/"
#寻找目标文件
def find_file_by_pattern(pattern='.proto', base=proto_file_path, circle=True):
	re_file = re.compile(pattern) 
	if base == ".": 
		base = os.getcwd() 
	
	final_file_list = [] 
	#print base 
	cur_list = os.listdir(base)
	for item in cur_list: 
		if item == ".svn": 
			continue 
		
		#print item
		full_path = os.path.join(base, item) 
		# print full_path 
		bfile = os.path.isfile(item) 
		if os.path.isfile(full_path): 
			if re_file.search(full_path):
				#print full_path
				#final_file_list.append(full_path) 
				proto_prefix = string.replace(string.replace(full_path, proto_file_path, ""),item,"")
				final_file_list.append([full_path, proto_prefix, string.replace(item, ".proto", ".pb")])
		else:
			#print full_path
			final_file_list += find_file_by_pattern(pattern, full_path) 
	return final_file_list

if os.path.exists(des_path):
	shutil.rmtree(des_path)

os.mkdir(des_path)

proto_file_list = find_file_by_pattern()
for protofile in proto_file_list:
	if not os.path.exists(des_path+protofile[1]):
		os.makedirs(des_path+protofile[1])
	os.system("protoc --proto_path="+proto_path+" -o"+des_path+protofile[1]+protofile[2]+" "+protofile[0])
	
print "gen all topb ok"