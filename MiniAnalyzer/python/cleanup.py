import os, sys

junk = [
    "*~",
    "*/*~",
    "../plugins/*~",
    "*#",
    "__pycache__",
    "*.root",
    "*/.log"
]

print("Running the following commands ...")
for item in junk:
    processline = "rm -rf "+item
    print(processline)
    os.system(processline)
print("Done!")
