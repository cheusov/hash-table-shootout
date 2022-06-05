#!/usr/bin/env python3

import sys, json
from collections import OrderedDict

######################################################################
### Fill free to change the following defaults

# do them in the desired order to make the legend not overlap
# the chart data too much
program_slugs = [
    'judyL',
    'nata88',
    'nataF8',
    'judyHS',
    'khash',
    'std_unordered_map',
    'google_dense_hash_map',
    'qt_qhash',
    'tsl_sparse_map',
    'tsl_hopscotch_map',
    'tsl_robin_map',
    'tsl_hopscotch_map_store_hash',
    'tsl_robin_map_store_hash',
    'tsl_hopscotch_map_mlf_0_5',
    'tsl_robin_map_mlf_0_9',
    'tsl_ordered_map',
    'tsl_robin_pg_map',
    'ska_flat_hash_map',
    'ska_bytell_hash_map',
    'google_dense_hash_map_mlf_0_9',
    'ska_flat_hash_map_power_of_two',
    'google_sparse_hash_map',
    'boost_unordered_map',
    'spp_sparse_hash_map',
    'emilib_hash_map',
    'tsl_array_map',
    'tsl_array_map_mlf_1_0',
    'glib_tree',
    'glib_hash_table',
    'cuckoohash_map'
]

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
    nbytes = float(nbytes) / nkeys # bytes per (key,value) pair
    runtime = float(runtime) * 1000000000 / nkeys # microseconds per operation
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

for i, (benchtype, programs) in enumerate(by_benchtype.items()):
    chart_data[benchtype] = []
    for program in program_slugs:
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

json_text = json.dumps(chart_data)
json_text = json_text.replace("}], ", "}], \n")
print('chart_data = ' + json_text + ';')
print('\nprograms = ' + json.dumps(existing_programs, indent=1) + ';')
print('\ndefault_programs_show = ' + str(list(real_default_programs_show)) + ';')
