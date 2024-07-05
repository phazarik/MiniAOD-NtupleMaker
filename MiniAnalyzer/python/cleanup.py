import os, sys

junk = [
    "*~",
    "*#",
    "__pycache__",
    ".root"
]

print("Running the following commands ...")
for item in junk:
    processline = "rm -rf "+item
    print(processline)
    os.system(processline)
print("Done!")
