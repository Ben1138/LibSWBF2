from pathlib import Path
import os
import re
import sys

ModToolsPath = "F:\\BF2_ModTools"
namelist = set()

# Grab all ODF file names without extension
count = 0
for path in Path(ModToolsPath).rglob("*.odf"):
    name = os.path.basename(path).replace(".odf", "")
    namelist.add(name)
    count += 1
print("Found %d ODF files" % count)

# Grab all MSH files in assets\Animations without extension
count = 0
for path in Path(ModToolsPath + "\\assets\\Animations").rglob("*.msh"):
    name = os.path.basename(path).replace(".msh", "")
    namelist.add(name)
    count += 1
print("Found %d Animation MSH files" % count)

# Grab all .snd files and extract names from Name() and Sample() declarations
nameReg = re.compile(r"Name\(\"(.*)\"\)")
sampleReg = re.compile(r"Sample\(\"(.*)\"")
count = 0
for path in Path(ModToolsPath).rglob("*.snd"):
    for i, line in enumerate(open(path)):
        for match in nameReg.finditer(line):
            namelist.add(match.group(1).strip())
            count += 1
        for match in sampleReg.finditer(line):
            namelist.add(match.group(1).strip())
            count += 1
print("Found %d Names and Samples in SND files" % count)

namelist = sorted(namelist, key=lambda s: s.lower())

file = open("lookup.csv", "w")
for name in namelist:
    file.write(name + "\n")