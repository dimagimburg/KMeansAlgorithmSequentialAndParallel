import random

file_name = raw_input("please enter input points file name (add .txt extension): ")
number_of_points = int(raw_input("please enter number of points: "))
number_of_clusters = int(raw_input("please enter number of cluster: "))
delta_t = float(raw_input("please enter delta t: "))
time_interval = float(raw_input("please enter time interval T: "))
limit = int(raw_input("please enter limit of iterations: "))

a_top = float(raw_input("please enter top limit for a of points: "))
a_bottom = float(raw_input("please enter bottom limit for a of points: "))
b_top = float(raw_input("please enter top limit for b of points: "))
b_bottom = float(raw_input("please enter bottom limit for b of points: "))
r_top = float(raw_input("please enter top limit for R of points: "))
r_bottom = float(raw_input("please enter bottom limit for R of points: "))

first_line = str(number_of_points) + " " + str(number_of_clusters) + " " + str(delta_t) + " " + str(time_interval) + " " + str(limit) + "\n"

file = open(file_name, 'w+')

file.write(first_line)
for i in range(number_of_points):
    point_number = i
    a = random.uniform(a_bottom, a_top)
    b = random.uniform(b_bottom, b_top)
    r = random.uniform(r_bottom, r_top)
    file.write(str(point_number) + " " + str('%.2f' % a) + " " + str('%.2f' % b) + " " + str('%.2f' % r) + "\n")

file.close()

print "done.\n\n"
