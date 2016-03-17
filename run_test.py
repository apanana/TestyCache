import subprocess
num_of_tests = 3
execnames = [
"tests/create_akosik",
"tests/create_aledger",
"tests/create_apan",
"tests/create_bblack",
"tests/create_jcosel",
"tests/create_jhepworth",
"tests/create_zzhong"
]
for en in execnames:
    print(en " test running:\n")
    for tn in range(num_of_tests):
        subprocess.call([en,str(tn)])
