import subprocess

kmersizes = [10, 20, 50, 100]
kmernums = [1000, 10000, 100000, 1000000]


l= []
for i in kmernums:
    for j in kmersizes:
        l.append((j,i))

for kmersize, kmernum in l:
    filename = 'kmers/{}mer-{}.txt'.format(str(kmersize), str(kmernum))
    print('Now working on' + filename)
    args = ('./cuckoo_filter', filename, str(kmersize), str(kmernum), str(kmernum/4))
    popen = subprocess.Popen(args)
    popen.wait()
print('ScriptDone')