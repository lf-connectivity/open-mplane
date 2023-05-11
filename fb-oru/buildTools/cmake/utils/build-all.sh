#!/bin/bash

build=${1:-x86_64}
cmd=${2}

IFS='-' read -ra target <<< "$build"
echo "TARGET: $target"


dirs=(\
	common \
	hardware/common \ 
	hardware/vhi \
	hardware/ETNA \
	hardware/ETNA_FTU \ 
	hardware/ETNA_RRH \
	dpd/common \
	services/vsi \
	services/common \
    services/ART \
	services/ETNA \
	services/ETNA_RRH \
	tif/testing \
	tif/common \
	tif/ETNA \
	tif/ENA_FTU \
	tif/ENA_RRH \
	tif/ENA-ALU-RRH \
	tif/ENA-AXIS-FTU \
)
	
	
cd ~/git

if [ "$cmd" == "clean" ]
then
	for d in ${dirs[@]}
	do
		rm -rf $d/build/${build} 2>/dev/null
	done	
fi

for d in ${dirs[@]}
do
	if [ ! -d $d/build/${build} ]
	then
		mkdir -p $d/build/${build}
		pushd $d/build/${build}
		cmake -D~/git/buildTools/cmake/Toolchains/${target}.cmake ../..
		popd
	fi
		
	if [ -d $d/build/${build} ]
	then
		echo $d
		pushd $d/build/${build}
		make lib
		popd
	fi
done

for d in ${dirs[@]}
do
	if [ -d $d/build/${build} ]
	then
		echo $d
		pushd $d/build/${build}
		make
		popd
	fi
done
