# Copyright (c) 2026 Justin Wallace
# build.py - Build script


import os
import subprocess
import shutil

build_path = "build"
bin_path = "bin"

if os.path.exists(build_path):
	shutil.rmtree(build_path)

if os.path.exists(bin_path):
	shutil.rmtree(bin_path)

os.mkdir(build_path)
os.mkdir(bin_path)

os.system("make all")

os.system("start cmd /k bin\\bjcc.exe")