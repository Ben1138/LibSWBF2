import os
import subprocess
import shutil
from pathlib import Path

PackageTmp = "PackageTmp"
Destination = os.path.join(PackageTmp, "LibSWBF2")

def copy_headers(directory):
    for path in Path(directory).rglob("*.h"):
        copy_header(path)

def copy_header(path):
    dst = os.path.join(Destination, "include", os.path.relpath(path, "LibSWBF2"))
    dstDir = os.path.dirname(dst)

    if not os.path.exists(dstDir):
        os.makedirs(dstDir)

    print("Copy from '%s' to '%s'" % (path, dst))
    shutil.copy(path, dst)

if os.path.exists(PackageTmp):
    shutil.rmtree(PackageTmp)

if os.path.exists("LibSWBF2.zip"):
    os.remove("LibSWBF2.zip")

copy_headers("LibSWBF2/Chunks")
copy_headers("LibSWBF2/Logging")
copy_headers("LibSWBF2/Types")
copy_headers("LibSWBF2/Wrappers")

copy_header("LibSWBF2/LibSWBF2.h")
copy_header("LibSWBF2/req.h")
copy_header("LibSWBF2/API.h")
copy_header("LibSWBF2/Hashing.h")
copy_header("LibSWBF2/Container.h")
copy_header("LibSWBF2/DirectX/D3D9FORMAT.h")

shutil.copy("x64/Release/LibSWBF2.dll", os.path.join(Destination, "LibSWBF2.dll"))
shutil.copy("x64/Release/LibSWBF2.lib", os.path.join(Destination, "LibSWBF2.lib"))

subprocess.check_call(["7za", "a", "LibSWBF2.zip", "LibSWBF2"], cwd=PackageTmp)
shutil.move(os.path.join(PackageTmp, "LibSWBF2.zip"), "LibSWBF2.zip")
shutil.rmtree(PackageTmp)