import random

MAX_TESTS = 5
MAX_PROCESSES = 5
MAX_QUANTUM = 5
MAX_ARRIVAL_CHANGE = 10
MAX_BURST = 10
MAX_PRIORITY = 10

f = open("input.txt", "w")
test = random.randint(1, MAX_TESTS)
f.write(f"{test}\n")

for case in range(test):
    process_cnt = random.randint(1, MAX_PROCESSES)
    algorithm = random.choice(["FCFS", "SJF", "SRTF", "P", "RR"])
    q = random.randint(1, MAX_QUANTUM)

    meta = f"{process_cnt} {algorithm}"
    if algorithm == "RR":
        meta += f" {q}"

    f.write(f"{meta}\n")

    arrival = 0
    for process in range(process_cnt):
        arrival += random.randint(0, MAX_ARRIVAL_CHANGE)
        burst = random.randint(0, MAX_BURST)
        priority = random.randint(-20, MAX_PRIORITY)

        f.write(f"{arrival} {burst} {priority}\n")
