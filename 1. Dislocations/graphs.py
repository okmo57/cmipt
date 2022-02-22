from matplotlib import pyplot as plt


def first_task():
    x = []
    y = []
    with open('first_task.dat', 'r') as file:
        for line in file.readlines():
            point = list(line.split())
            x.append(float(point[0]))
            y.append(float(point[1]))
    plt.plot(x, y)
    plt.savefig('first_task.png')
    plt.show()
    print(x, y)


def second_task():
    x = []
    y = []
    with open('second_task.dat', 'r') as file:
        for line in file.readlines():
            point = list(line.split())
            x.append(float(point[0]))
            y.append(float(point[1]))
    plt.plot(x, y)
    plt.savefig('second_task.png')
    plt.show()
    print(x, y)


def third_task():
    x = []
    y = []
    with open('third_task_1.dat', 'r') as file:
        for line in file.readlines():
            point = list(line.split())
            x.append(float(point[0]))
            y.append(float(point[1]))
    plt.plot(x, y)
    plt.savefig('third_task_1.png')
    plt.show()
    print(x, y)
    x = []
    y = []
    with open('third_task_2.dat', 'r') as file:
        for line in file.readlines():
            point = list(line.split())
            x.append(float(point[0]))
            y.append(float(point[1]))
    plt.plot(x, y)
    plt.savefig('third_task_2.png')
    plt.show()
    print(x, y)


first_task()
second_task()
third_task()
