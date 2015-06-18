CC      = gcc

# debug CFLAGS
# CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

# release CFLAGS
CFLAGS  = -Wall -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic -O2 -g

.SUFFIXES: .c .o

.PHONY: all clean

###############################
# make all build files
###############################
all: assemble emulate testsuite IAT/interpreter IAT/trainer_branch

###############################
# main executables
###############################
assemble: assemble.o memutils.o orderedList.o firstPass.o secondPass.o ioutils.o\
	stringutils.o assembleBranch.o assembleDataprocessing.o\
	assembleMultiply.o assembleSDT.o IAT/onePass.o

emulate: emulate.o memutils.o execute.o branch.o\
	pipeline.o ioutils.o multiply.o\
	singledata.o dataprocessing.o

testsuite: testsuite.o memutils.o execute.o branch.o\
	testsuite_tests.o pipeline.o ioutils.o\
	multiply.o singledata.o dataprocessing.o\
	orderedList.o testsuite_tests2.o stringutils.o firstPass.o\
	secondPass.o assembleMultiply.o assembleBranch.o\
	assembleDataprocessing.o assembleSDT.o

temptest: temptest.o memutils.o execute.o branch.o\
	testsuite_tests.o pipeline.o ioutils.o\
	multiply.o singledata.o dataprocessing.o

IAT/interpreter: IAT/interpreter.o IAT/interpret.o IAT/onePass.o\
	memutils.o assembleBranch.o stringutils.o orderedList.o\
	assembleDataprocessing.o assembleMultiply.o\
	execute.o multiply.o singledata.o branch.o\
	pipeline.o secondPass.o assembleSDT.o ioutils.o\
	dataprocessing.o secondPass.o

IAT/trainer_branch: IAT/trainer_branch.o IAT/trainer_dp.o IAT/onePass.o\
 	memutils.o secondPass.o IAT/interpret.o orderedList.o stringutils.o\
	assembleBranch.o assembleDataprocessing.o assembleSDT.o\
	assembleMultiply.o ioutils.o execute.o multiply.o\
	singledata.o branch.o dataprocessing.o pipeline.o

###############################
# object files
###############################
# emulate.o: dataStructure.h memutils.h branch.h ioutils.h dataprocessing.h

# testsuite.o: dataStructure.h memutils.h execute.h\
#	testsuite_tests.h testsuite_tests2.h stringutils.h\
#	assembleDataprocessing.h

# memutils.o: dataStructure.h memutils.h ioutils.h

# dataprocessing.o: dataStructure.h memutils.h execute.h dataprocessing.h

# branch.o: dataStructure.h memutils.h branch.h pipeline.h

# execute.o: dataStructure.h memutils.h execute.h branch.h\
#	multiply.h singledata.h dataprocessing.h

# testsuite_tests.o: testsuite_tests.h dataStructure.h\
#	memutils.h execute.h branch.h ioutils.h multiply.h\
#	singledata.h dataprocessing.h

# singledata.o: dataStructure.h memutils.h singledata.h execute.h

# pipeline.o: dataStructure.h execute.h memutils.h pipeline.h

# ioutils.o: dataStructure.h ioutils.h stringutils.h

# multiply.o: dataStructure.h

# temptest.o: dataStructure.h memutils.h ioutils.h testsuite_tests.h

# orderedList.o: dataStructure.h orderedList.h

# stringutils.o: stringutils.h

# testsuite_tests2.o: testsuite_tests2.h stringutils.h\
#	dataStructure.h assembleMultiply.h ioutils.h

# firstPass.o: dataStructure.h memutils.h orderedList.h\
#	stringutils.h firstPass.h ioutils.h

# assembleMultiply.o: dataStructure.h stringutils.h assembleMultiply.h\
#	secondPass.h

# secondPass.o: dataStructure.h memutils.h stringutils.h\
#	orderedList.h secondPass.h assembleBranch.h ioutils.h\
#	assembleDataprocessing.h assembleMultiply.h

# assembleBranch.o: dataStructure.h memutils.h stringutils.h orderedList.h\
#	assembleBranch.h

# assemble.o: dataStructure.h memutils.h orderedList.h firstPass.h secondPass.h ioutils.h\
#	stringutils.h assembleBranch.h assembleDataprocessing.h\
#	assembleMultiply.h IAT/onePass.h IAT/references.h

# assembleDataprocessing.o: dataStructure.h stringutils.h assembleDataprocessing.h memutils.h\
#	secondPass.h

# assembleSDT.o: dataStructure.h stringutils.h memutils.h orderedList.h assembleDataprocessing.h assembleSDT.h secondPass.h

IAT/onePass.o: dataStructure.h stringutils.h IAT/onePass.h IAT/references.h orderedList.h

IAT/interpret.o: stringutils.h dataStructure.h IAT/references.h execute.h memutils.h\
	IAT/onePass.h secondPass.h IAT/interpret.h

IAT/interpreter.o: dataStructure.h IAT/references.h IAT/interpret.h\
	IAT/onePass.h memutils.h ioutils.h execute.h ioutils.h\
	stringutils.h secondPass.h

IAT/trainer_branch.o: IAT/onePass.h memutils.h\
	secondPass.h IAT/interpret.h orderedList.h stringutils.h\
	assembleBranch.h assembleDataprocessing.h assembleSDT.h\
	assembleMultiply.h ioutils.h execute.h multiply.h\
	singledata.h branch.h dataprocessing.h pipeline.h IAT/trainer_dp.h

IAT/trainer_dp.o: IAT/onePass.h memutils.h\
	secondPass.h IAT/interpret.h orderedList.h stringutils.h\
	assembleBranch.h assembleDataprocessing.h assembleSDT.h\
	assembleMultiply.h ioutils.h execute.h multiply.h\
	singledata.h branch.h dataprocessing.h pipeline.h IAT/trainer_dp.h

###############################
clean:
	rm -f assemble
	rm -f emulate
	rm -f testsuite
	rm -f temptest
	rm -rf IAT/interpreter
	rm -rf IAT/trainer_branch
	rm -rf IAT/*.o