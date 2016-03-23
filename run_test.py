'''
command line syntax
run_test.py all                         run all tests on all executables
run_test.py                             Identical to run_test.py all
run_test.py all <testint>               run specific test on all executables
run_test.py <execname> <testint>        run specific test on specific executabl
run_test.py <execname>                  run all tests on specific executable

Additional options:
-v          output stderr after crashes
-vv         output stdout and stderr always
'''
import subprocess
import sys

num_of_tests = 32

verbose_level = 0

execnames = [
"./tests/create_akosik",
"./tests/create_aledger",
"./tests/create_apan",
"./tests/create_bblack",
"./tests/create_jcosel",
"./tests/create_jhepworth",
"./tests/create_zzhong"
]
PASSED_VAL = 0
FAILED_VAL = 0x92
TIMOUT_VAL = 0x91

class TestRes:
    def __init__(self,exec_name,testnum):
        pobj = subprocess.Popen([exec_name,str(testnum)],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        try:
            output, err = pobj.communicate(timeout=0.5)
        except subprocess.TimeoutExpired:
            pobj.kill()
            output, err = pobj.communicate()
            retval = TIMOUT_VAL
        else:
            retval = int(pobj.returncode)
        output = output.decode("utf-8")
        error = err.decode("utf-8")
        self.testname = output + err if verbose_level > 0 else ("????????????" if "\n" not in output else output[:output.index("\n")])
        self.retval = retval

class Sumary:
    def __init__(self,exec_name):
        self.exec_name = exec_name
        self.tests = []

    def __iadd__(self,testres):
        self.tests.append(testres)
        return self

    def __str__(self):
        passed = 0
        failed = 0
        timeout = 0
        crashed = 0
        resstr = self.exec_name + " :\n"
        for t in self.tests:
            resstr += t.testname + "\n"
            if(t.retval == PASSED_VAL):
                passed += 1
                resstr += "passed\n"
            elif t.retval == FAILED_VAL:
                failed += 1
                resstr += "failed\n"
            elif t.retval == TIMOUT_VAL:
                timeout += 1
                resstr += "timed out\n"
            else:
                crashed += 1
                resstr += "crashed\n"
        resstr += "passed: " + str(passed) + "\n"
        resstr += "failed: " + str(failed) + "\n"
        resstr += "crashed: " + str(crashed) + "\n"
        resstr += "timed out: " + str(timeout) + "\n"
        return resstr

    def get_passed_line(self):
        #resstr = self.exec_name + " :\n"
        line = [self.exec_name]
        for t in self.tests:
            if(t.retval == PASSED_VAL):
                line.append("PASS")
            elif t.retval == FAILED_VAL:
                line.append("FAIL")
            elif t.retval == TIMOUT_VAL:
                line.append("TIME")
            else:
                line.append("CRASH")
        return ", ".join(line)

    def get_func_names(self):
        fnames = [""]
        for t in self.tests:
            fnames.append(t.testname)
        return fnames

    __repr__ = __str__

def run_one(execname,testnum):
    sumar = Sumary(execname)
    sumar += TestRes(execname,testnum)
    print(sumar)

def run_all(execname):
    sumar = Sumary(execname)
    for tn in range(num_of_tests):
        sumar += TestRes(execname,tn)
    print(sumar)

def run_on_all(testnum):
    for en in execnames:
        run_one(en,testnum)

def run_all_execs():
    for en in execnames:
        sumar = Sumary(en)
        for tn in range(num_of_tests):
            sumar += TestRes(en,tn)
        if en is execnames[0]:
            print(", ".join(sumar.get_func_names()))
        print(sumar.get_passed_line())

if "-vv" in sys.argv:
    verbose_level = 2
    sys.argv.remove("-vv")
elif "-v" in sys.argv:
    verbose_level = 1
    sys.argv.remove("-v")

if len(sys.argv) == 1:
    run_all_execs()
elif len(sys.argv) == 2:
    arg = sys.argv[1]
    if arg == "all":
        run_all_execs()
    else:
        run_all(sys.argv[1])
elif len(sys.argv) == 3:
    arg1 = sys.argv[1]
    if arg1 == "all":
        testnum = int(sys.argv[2])
        run_on_all(testnum)
    else:
        run_one(sys.argv[1],int(sys.argv[2]))
