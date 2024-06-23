import csv
import os

sensor_num_arrays = {"1":[1, 2, 3, 4], "2":[2, 3, 4, 1], "3":[3, 4, 1, 2], "4":[4, 1, 2, 3]}
data = {"Region":[], "Distance (mm)":[], "Bus Voltage (V)":[], "Shunt Voltage (V)":[], "Load Voltage (V)":[], "Current (mA)":[], "Power (mW)":[], "Sensor #":[]}
headers = data.keys()

region_dict = {"2.0":1, "100":1, "200":2, "300":3, "400":4}

txt_folder_path1 = "..."
txt_folder_path2 = "..."
csv_file_path = "..."

# Open the CSV file once, before processing all text files
with open(csv_file_path, 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(headers)

    def convert(txt_file_path, motion):
        with open(txt_file_path, "r") as txt_file: txt_lines = txt_file.readlines()

        sensor_nums = sensor_num_arrays[txt_file_path[-5]]
        sensor = 0
        line_num = 0

        while line_num < len(txt_lines):
            if sensor == 4: sensor = 0
            data["Sensor #"].append(sensor_nums[sensor])
            if motion==0: data["Region"].append(region_dict[txt_file_path[-11:-8]])
            elif motion==1: data["Region"].append(txt_file_path[-16])
            data["Distance (mm)"].append(txt_lines[line_num + 1][10:-5])
            data["Bus Voltage (V)"].append(txt_lines[line_num + 2][15:-3])
            data["Shunt Voltage (V)"].append(txt_lines[line_num + 3][15:-4])
            data["Load Voltage (V)"].append(txt_lines[line_num + 4][15:-3])
            data["Current (mA)"].append(txt_lines[line_num + 5][15:-4])
            data["Power (mW)"].append(txt_lines[line_num + 6][15:-4])

            row = [data["Region"][-1], data["Distance (mm)"][-1], data["Bus Voltage (V)"][-1], data["Shunt Voltage (V)"][-1], 
                   data["Load Voltage (V)"][-1], data["Current (mA)"][-1], data["Power (mW)"][-1], data["Sensor #"][-1]]
            csvwriter.writerow(row)

            sensor += 1
            line_num += 8

        # Clear data for the next file
        for key in data.keys(): data[key] = []

    # Process each text file
    for txt_filename1 in os.listdir(txt_folder_path1):
        if txt_filename1[:13] == "4_ultrasonic_":
            txt_file_path1 = os.path.join(txt_folder_path1, txt_filename1)
            print(txt_file_path1)
            convert(txt_file_path1, 1)
    for txt_filename2 in os.listdir(txt_folder_path2):
        if txt_filename2[:13] == "4_ultrasonic_":
            txt_file_path2 = os.path.join(txt_folder_path2, txt_filename2)
            print(txt_file_path2)
            convert(txt_file_path2, 0)