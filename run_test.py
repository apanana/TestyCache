'''
command line syntax
run_test.py all                         run all tests on all executables
run_test.py all <testint>               run specific test on all executables
run_test.py <execname> <testint>        run specific test on specific executabl
'''
import subprocess
import sys
execnames = [
"./tests/create_akosik",
"./tests/create_aledger",
"./tests/create_apan",
"./tests/create_bblack",
"./tests/create_jcosel",
"./tests/create_jhepworth",
"./tests/create_zzhong"
]
num_of_tests = 5

class sumary:
    def __init__()
def run_one(exec_name,num):
    retval = subprocess.call([exec_name,str(num)])
    if(retval == 0):
        print("passed")
    elif(retval == 0x5929192):
        print("failed")
    elif(retval == 0x5929192):
        print("crashed")

def run_all(execname):
    print(execname + " tests running:\n")
    for tn in range(num_of_tests):
        run_one(execname,tn)

def run_on_all(testnum):
    for en in execnames:
        run_one(en,testnum)

def run_all_execs():
    for en in execnames:
        run_all(en)


if len(sys.argv) == 2:
    arg = sys.argv[1]
    if arg == "all":
        run_all_execs()
    else:
        run_all(sys.argv[1])
elif len(sys.argv) == 3:
    arg1 = sys.argv[1]
    if arg1 == "all":
        testnum = int(sys.argv[2])
    else:
        run_one(sys.argv[1],int(sys.argv[2]))
