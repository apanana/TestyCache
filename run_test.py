import subprocess
import sys
num_of_tests = 3
execnames = [
"./tests/create_akosik",
"./tests/create_aledger",
"./tests/create_apan",
"./tests/create_bblack",
"./tests/create_jcosel",
"./tests/create_jhepworth",
"./tests/create_zzhong"
]
def run_exec(execname):
    print(execname + " test running:\n")
    for tn in range(num_of_tests):
        retval = subprocess.call([execname,str(tn)])
        if(retval != 0):
            print("test crashed")



if len(sys.argv) == 2:
    run_exec(sys.argv[1])
else:
    for en in execnames:
        run_exec(en)
