import random

f = open("input.txt", "w")
test_cases = random.randint(5, 50)
f.write(f"{test_cases}\n")
for case in range(test_cases):
    no_processes = random.randint(10, 20)
    processes = [str(random.choice(range(50))) for _ in range(no_processes)]
    algorithm = random.choice(["FCFS", "SJF", "SRTF", "P", "RR"])
    q = random.randint(1,5)
    if algorithm == "RR":
        f.write(f"{no_processes} {algorithm} {q}\n")
    else:
        f.write(f"{no_processes} {algorithm}\n")
    f.write(f"{' '.join(processes)}\n")