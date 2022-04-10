import os

pcd_file_name = os.listdir(r'/home/neousys/hailong/project1_ws/src/car_segmentation/data/pcd_data/')

with open("/home/neousys/hailong/project1_ws/src/car_segmentation/data/data_seq.txt", 'w') as file:
    for i in range(len(pcd_file_name)):
        line2 = pcd_file_name[i]+ "\n"
        file.writelines(line2)
file.close()