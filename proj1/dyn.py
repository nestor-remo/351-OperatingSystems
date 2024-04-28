def dynamic(stocks_array, amount, size_of_array):
    if size_of_array == 0 or amount == 0:
        return 0

    if stocks_array[size_of_array-1][1] > amount:
        return dynamic(stocks_array, amount, size_of_array-1)
    else:
        include_stock = stocks_array[size_of_array-1][0] + dynamic(stocks_array, amount-stocks_array[size_of_array-1][1], size_of_array-1)
        exclude_stock = dynamic(stocks_array, amount, size_of_array-1)
        return max(include_stock, exclude_stock)

with open('input.txt', 'r') as file:
    lines = file.readlines()

i = 0
with open('DP.txt', 'w') as outfile:
    while i < len(lines):
        if lines[i] == "\n":
            i += 1
        size_of_array = int(lines[i])
        stocks_array = eval(lines[i+1])
        amount = int(lines[i+2])
        i += 3

        outfile.write(f"DP Output: {dynamic(stocks_array, amount, size_of_array)}\n\n")
