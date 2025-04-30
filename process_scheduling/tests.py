import random

f = open("input.txt", "w")
test_cases = random.randint(5, 50)
f.write(f"{test_cases}\n")
for case in range(test_cases):
    process_cnt = random.randint(1, 20)
    algorithm = random.choice(["FCFS", "SJF", "SRTF", "P", "RR"])
    q = random.randint(1, 5)
    meta = f"{process_cnt} {algorithm}"
    if algorithm == "RR":
        meta += f" {q}"
    f.write(f"{meta}\n")
    for process in range(process_cnt):
        arrival = random.randint(0, 20)
        burst = random.randint(0, 20)
        priority = random.randint(-20, 20)
        f.write(f"{arrival} {burst} {priority}\n")
