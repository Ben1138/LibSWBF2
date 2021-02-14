#!/bin/bash


replaceString="REPLACEME"

cd ../build
make all -j4
cd ../LibSWBF2.NET.Test

for fileName in test*.cs; do
	testName=${fileName:0:-3}

	sed -i "s/${replaceString}/${testName}/" LibSWBF2.NET.Test.csproj
	xbuild LibSWBF2.NET.Test.csproj 1> /dev/null
	sed -i "s/${testName}/REPLACEME/" LibSWBF2.NET.Test.csproj

	if [[ "$testName" != *"Anim"* ]]; then
		echo -e "\n\nRunning $testName..."
		echo "====================================================================="
		mono bin/Debug/LibSWBF2.NET.Test.exe "$@"
		echo "====================================================================="
	fi

done


