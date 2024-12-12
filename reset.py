import os

years = range(1995, 2025)
for year in years:
    if os.path.exists(f"{year}"):
        os.rmdir(f"{year}")


for year in years:
    for i in range(1,3):
        os.remove(rf"{year}/Q{i}.py")
        os.remove(rf"{year}/Q{i}.txt") 
        os.remove(rf"{year}/Q{i}.c")           