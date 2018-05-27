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
des_path = proto_path+"/protocal/proto.conf"

#心跳包特殊处理
heartbeat_proto_name = "S2c_hero_beat"
heartbeat_proto_idx = 10000
move_proto_name = "S2c_aoi_move"
move_proto_idx = 10000		#move协议 30000

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
				proto_prefix = string.replace(string.replace(full_path, proto_file_path, ""),".proto","")
				final_file_list.append([full_path, proto_prefix])
		else:
			#print full_path
			final_file_list += find_file_by_pattern(pattern, full_path)
	return final_file_list

proto_name_list = []
aoi_name_list = []
proto_name_dic = {}
#解析协议文件
def get_protoname(file_path,prefix,name_list):
	global heartbeat_proto_name
	global move_proto_name
	p = re.compile('message *([0-9a-zA-Z_]*) *{')
	file_handle = open(file_path) 
	content = file_handle.read()
	l = p.findall(content)
	for i in range(len(l)):
		proto_name = l[i]
		if proto_name in proto_name_dic:
			print "<"+proto_name+"> has the same name message!!!"
			sys.exit()
		proto_name_dic[proto_name]=1
		l[i] = prefix+"."+proto_name
		if proto_name==heartbeat_proto_name:
			heartbeat_proto_name = l[i]
		elif proto_name==move_proto_name:
			move_proto_name = l[i]
	name_list += l
	file_handle.close()

proto_file_list = find_file_by_pattern()
for protofile in proto_file_list:
	if protofile[1]!='aoi/aoi':
		get_protoname(protofile[0],protofile[1],proto_name_list)
	else:
		get_protoname(protofile[0],protofile[1],aoi_name_list)
		

proto_conf = ""
for i in range(len(proto_name_list)):
	idx = i
	if proto_name_list[i]==heartbeat_proto_name:
		idx = heartbeat_proto_idx-1
	proto_conf+=str(idx+1)+","+proto_name_list[i]+"\n"

for i in range(len(aoi_name_list)):
	idx = i
	if aoi_name_list[i]==move_proto_name:
		idx = move_proto_idx-1
	proto_conf+=str(idx+20001)+","+aoi_name_list[i]+"\n"

#print proto_conf
if os.path.isfile(des_path): 
	os.remove(des_path)
f=open(des_path,"a")
f.write(proto_conf)
f.close()

print "gen proto conf ok"