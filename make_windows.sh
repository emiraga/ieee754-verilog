#/bin/sh
#
# Used on MS Windows together with:
#
# * msysgit       - http://code.google.com/p/msysgit/
# * iverilog      - http://bleyer.org/icarus/
# * python        - http://www.python.org/
# * verilogscript - http://github.com/emiraga/verilogscript
#

echo 'Configuring environment'
export PATH=$PATH:/x/verilog/iverilog/bin:/c/python27/
export VSCRIPT=/x/VerilogScript/VerilogScript.py

echo 'Generating pipeline'
python $VSCRIPT src/ieee.vs || exit
cd src
python generate.py || exit
cd ..
rm src/ieee.v

echo 'Compiling verilog'
rm -f bin/single.out
python $VSCRIPT src/ieee.vs src/ieee_adder.v test/testbench.v -e "iverilog -Wall -o bin/single.out" || exit

echo 'Running simulation'
rm -f bin/simulation.out
vvp bin/single.out | tee bin/simulation.out

echo 'Compiling test'
rm -f bin/test.exe
gcc test/test_simulation.c -o bin/test.exe || exit

echo 'Running test'
bin/test.exe < bin/simulation.out
