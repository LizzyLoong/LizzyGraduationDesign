import csv

def convert_csv_to_special_format(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as infile, \
         open(output_path, 'w', encoding='utf-8') as outfile:
        
        csv_reader = csv.reader(infile)
        
        for row in csv_reader:
            if not row:
                continue
        
            front_columns = row[:5]
            back_columns = row[5:8]

            front_part = '"' + '","'.join(front_columns) + '"'
            back_part = '"' + '","'.join(back_columns) + '"'
            formatted_line = f'{{{{{front_part}}}, {{{back_part}}}}},'

            outfile.write(formatted_line + '\n')

if __name__ == "__main__":
    input_file = "train.csv"
    output_file = "output.txt"
    
    convert_csv_to_special_format(input_file, output_file)
    print(f"转换完成！结果保存至：{output_file}")