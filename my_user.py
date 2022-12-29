import sys
"""
    В procfs выводим только числа, чтобы они влезли в буффер, а затем здесь всё будем парсить и добавлять пояснения в вывод
    task_cputime, можно либо прямо передать из файла или состолковать здесь из чисел, что лежат в signal_struct (или они дежат в другой структуре? task_struct)

"""
if __name__ =='__main__':
    with open("/proc/maks_module", 'w') as file:
        print(file.write('5850'))
    with open("/proc/maks_module", 'rb') as file:
        print(int(file.read(4)))
        print(file.read(4))
        print(file.read(4))
        
    # print("dfs")
    # print(sys.argv)  