import subprocess

kmersizes = [10, 20, 50, 100]
kmernums = [1000, 10000, 100000, 1000000]

for kmersize, kmernum in zip(kmersizes, kmernums):
    filename = 'kmers/{}mer-{}.txt'.format(str(kmersize), str(kmernum))
    print('Now working on' + filename)
    args = ('./cuckoo_filter', filename, str(kmersize), str(kmernum))
    popen = subprocess.Popen(args)