line = raw_input("please input a line:")
char_stat_dict = {'letter':0, 'blank':0, 'digit':0, 'other':0}
for char in line:
    if char.isalpha():
        char_stat_dict['letter'] += 1
    elif char.isdigit():
        char_stat_dict['digit'] += 1
    elif char.isspace():
        char_stat_dict['blank'] += 1
    else:
        char_stat_dict['other'] += 1
print char_stat_dict
