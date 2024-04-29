#!/usr/bin/env python3

import sys, json
from collections import OrderedDict

######################################################################
### Fill free to change the following defaults

# hashmap which will be shown (checkbox checked),
# by default all hashmaps are enabled.
#default_programs_show = [
#    'std_unordered_map',
#    'google_dense_hash_map',
#    'qt_qhash',
#    'tsl_sparse_map',
#    'tsl_hopscotch_map',
#    'tsl_robin_map',
#    'tsl_hopscotch_map_store_hash',
#    'tsl_robin_map_store_hash']

######################################################################
lines = [ line.strip() for line in sys.stdin if line.strip() ]

by_benchtype = {}

all_programs = set()
for line in lines:
    if len(line) == 0:
        next
    benchtype, nkeys, program, load_factor, nbytes, runtime = line.split(',')
    nkeys = int(nkeys)
    nbytes = float(nbytes) # bytes per (key,value) pair
    runtime = float(runtime) * 1000.0 # nanoseconds per operation
    load_factor = float(load_factor)
    all_programs.add(program)

    if runtime > 0 and nbytes > 0:
        by_benchtype.setdefault("%s_runtime" % benchtype, {}).setdefault(program, []).append([nkeys, runtime, load_factor])
        by_benchtype.setdefault("%s_bopsnsec" % benchtype, {}).setdefault(program, []).append([nkeys, runtime * nbytes, load_factor])
        if benchtype in ('insert_random_shuffle_range',
                         'insert_random_full',
                         'insert_tiny_string',
                         'insert_small_string',
                         'insert_string',
                         'insert_huge_string',
                         'insert_random_full_reserve',
                         'insert_tiny_string_reserve',
                         'insert_small_string_reserve',
                         'insert_string_reserve',
                         'insert_huge_string_reserve'):
            by_benchtype.setdefault("%s_memory"  % benchtype, {}).setdefault(program, []).append([nkeys, nbytes, load_factor])

chart_data = {}
existing_programs = {}
real_default_programs_show = set()
nkeys_set = set()

for i, (benchtype, programs) in enumerate(by_benchtype.items()):
    chart_data[benchtype] = []
    for program in all_programs:
        if (program not in all_programs) or (program not in programs):
            continue

        existing_programs[program] = program
        if "default_programs_show" not in dir() or (program in default_programs_show):
            real_default_programs_show.add(program);
        data = programs[program]
        chart_data[benchtype].append({
            'program': program,
            'label': program,
            'data': [],
        })

        for k, (nkeys, value, load_factor) in enumerate(data):
            chart_data[benchtype][-1]['data'].append([nkeys, value, load_factor])
            nkeys_set.add(nkeys)

def get_ticks(keys):
    keys = sorted(keys)
    ticks = []
    last = keys[-1]
    keys = keys[0:-1]
    step = len(keys) / 10
    index = 0
    while index < len(keys) - 0.5:
        ticks.append(keys[int(index + 0.5)])
        index += step
    ticks.append(last)
    return ticks

ticks = get_ticks(list(nkeys_set))
json_text = json.dumps(chart_data)
json_text = json_text.replace("}], ", "}], \n")
print('chart_data = ' + json_text + ';')
print('\nprograms = ' + json.dumps(existing_programs, sort_keys=True, indent=1) + ';')
print('\ndefault_programs_show = ' + str(list(real_default_programs_show)) + ';')
print('\nticks = ' + str(ticks) + ';')
