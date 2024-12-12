import os

years = range(1995, 2025)
for year in years:
    if not os.path.exists(f"{year}"):
        os.mkdir(f"{year}")


for year in years:
    for i in range(1,3+1):
        _ = open(rf"{year}/Q{i}.py", "x")
        _ = open(rf"{year}/Q{i}.txt", "x") 
        _ = open(rf"{year}/Q{i}.c", "x")           