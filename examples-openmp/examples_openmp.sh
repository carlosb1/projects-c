#!/bin/bash

NAME_EXEC=$(echo  "$0"  | cut -f 2  -d '.' | cut -f 2 -d '/')
usage () { echo "Usage: $0 run|build|gprof|valgrind|install|clean "; }
build () { cmake ./ && make && "./$NAME_EXEC"; }
run() { "./$NAME_EXEC"; }
clean ()  { rm -rf cmake_install.cmake CMakeFiles CMakeCache.txt examples_openmp_prof examples_openmp_debug examples_openmp gmon.out; }
run_gprof() { "./$NAME_EXEC""_prof" && gprof "$NAME_EXEC" gmon.out; }
run_valgrind() { valgrind "./$NAME_EXEC"; }
install() { sudo apt-get install valgrind binutils; }

E_BADARGS=85

#create flags
FLAG_RUN="0"
FLAG_CLEAN="0"
FLAG_BUILD="0"
FLAG_GPROF="0"
FLAG_VALGRIND="0"
FLAG_INSTALL="0"


#read arguments
if [ "$#" == "0" ]; then
	usage;
	exit $E_BADARGS;
fi

for var in "$@"
do 
	if [ "$var"  == "build" ]; then 
		FLAG_BUILD="1"
	elif [ "$var" == "run" ]; then
		FLAG_RUN="1"
	elif [ "$var" == "clean" ]; then
		FLAG_CLEAN="1"
	elif [ "$var" == "gprof" ]; then
		FLAG_GPROF="1"
	elif [ "$var" == "valgrind" ]; then
		FLAG_VALGRIND="1"
	elif [ "$var" == "install" ]; then
		FLAG_INSTALL="1"
	else
		usage;
		exit $E_BADARGS;
	fi
done

if [ "$FLAG_INSTALL" == "1" ]; then
	install;
	exit 0;
fi

if [ "$FLAG_CLEAN" == "1" ]; then
	clean;
	exit 0;
fi

if [ "$FLAG_BUILD" == "1" ]; then
	clean;
	build;
fi

if [ "$FLAG_RUN" == "1" ]; then
	run;
fi

if [ "$FLAG_GPROF" == "1" ]; then
	run_gprof;
fi

if [ "$FLAG_VALGRIND" == "1" ]; then
	run_valgrind;
fi


