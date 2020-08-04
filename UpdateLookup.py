from pathlib import Path
import os
import re
import sys

LookupFile = "lookup.csv"
ModToolsPath = "F:\\BF2_ModTools"
namelist = set()

def AddToList(item):
    # strip first
    item = item.strip()
    # ignore template project stuff and comments
    if not item.startswith('@') and not item.startswith("--") and not item.startswith("//") and not item.startswith(r"\\") and not item.startswith("#"):
        namelist.add(item)

# read current list, so we can actually add stuff manually to the
# lookup file that doesn't get deleted once this script is run
for i, line in enumerate(open(LookupFile)):
    AddToList(line)

# Grab all ODF file names without extension and additionally
# crawl them for property names
propertyReg = re.compile(r"^(\w*)\s*=\s*.*$")
count = 0
count2 = 0
for path in Path(ModToolsPath).rglob("*.odf"):
    name = os.path.basename(path).replace(".odf", "")
    AddToList(name)
    count += 1
    for i, line in enumerate(open(path)):
        for match in propertyReg.finditer(line):
            found = match.group(1)
            if not found.startswith("//") and "//" in found:
                print("NOOO: " + found)
                print(match)
                print(match.groups())
                print("In File: %s at line: %d", path, i)
            AddToList(match.group(1))
            count2 += 1
print("Found %d ODF files" % count)
print("Found %d Property Names in ODF files" % count2)

# Grab all req files
count = 0
for path in Path(ModToolsPath).rglob("*.req"):
    name = os.path.basename(path).replace(".req", "")
    AddToList(name)
    count += 1
print("Found %d REQ files" % count)

# Grab all MSH files in assets\Animations without extension
count = 0
for path in Path(ModToolsPath + "\\assets\\Animations").rglob("*.msh"):
    name = os.path.basename(path).replace(".msh", "")
    AddToList(name)
    count += 1
print("Found %d Animation MSH files" % count)

# Grab all .snd files and extract names from Name() and Sample() declarations
nameReg = re.compile(r"Name\(\"(.*)\"\)")
sampleReg = re.compile(r"Sample\(\"(.*)\"")
count = 0
count2 = 0
for path in Path(ModToolsPath).rglob("*.snd"):
    name = os.path.basename(path).replace(".snd", "")
    AddToList(name)
    count += 1
    for i, line in enumerate(open(path)):
        for match in nameReg.finditer(line):
            AddToList(match.group(1))
            count2 += 1
        for match in sampleReg.finditer(line):
            AddToList(match.group(1))
            count2 += 1
print("Found %d SND files" % count)
print("Found %d Names and Samples in SND files" % count2)

# Grab all wld (world) files
count = 0
for path in Path(ModToolsPath).rglob("*.wld"):
    name = os.path.basename(path).replace(".wld", "")
    AddToList(name)
    count += 1
print("Found %d WLD files" % count)

# Grab all lyr (world layer) files
count = 0
for path in Path(ModToolsPath).rglob("*.lyr"):
    name = os.path.basename(path).replace(".lyr", "")
    AddToList(name)
    count += 1
print("Found %d LYR files" % count)

# Grab all .ldx files and extract names from Layer() and GameMode() declarations
layerReg = re.compile(r"Layer\(\"(.*)\"")
gameModeReg = re.compile(r"GameMode\(\"(.*)\"")
count = 0
for path in Path(ModToolsPath).rglob("*.ldx"):
    for i, line in enumerate(open(path)):
        for match in layerReg.finditer(line):
            AddToList(match.group(1))
            count += 1
        for match in gameModeReg.finditer(line):
            AddToList(match.group(1))
            count += 1
print("Found %d Layer and GameMode Names in LDX files" % count)

namelist = sorted(namelist, key=lambda s: s.lower())

file = open(LookupFile, "w")
for name in namelist:
    file.write(name + "\n")
file.close()