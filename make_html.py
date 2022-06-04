#!/usr/bin/env python3

import re
import sys

html_template = open('charts-template.html', 'r').read()
charts_data = sys.stdin.read()

repls = (
    'insert_random_shuffle_range',
    'reinsert_random_shuffle_range',

    'read_random_shuffle_range',
    'insert_random_full',
    'reinsert_random_full',
    'insert_random_full_reserve',
    'read_random_full',
    'read_miss_random_full',
    'delete_random_full',
    'read_random_full_after_delete',
    'iteration_random_full',

    'insert_tiny_string',
    'reinsert_tiny_string',
    'insert_tiny_string_reserve',
    'read_tiny_string',
    'read_miss_tiny_string',
    'delete_tiny_string',
    'read_tiny_string_after_delete',

    'insert_small_string',
    'reinsert_small_string',
    'insert_small_string_reserve',
    'read_small_string',
    'read_miss_small_string',
    'delete_small_string',
    'read_small_string_after_delete',

    'insert_string',
    'reinsert_string',
    'insert_string_reserve',
    'read_string',
    'read_miss_string',
    'delete_string',
    'read_string_after_delete',
)

for l in repls:
    if charts_data.find(l) < 0:
        html_template = re.sub('BEGIN2_' + l.upper() + " (.|\\n)*END2_" + l.upper() + " ", '',
                               html_template)
        html_template = re.sub('BEGIN_' + l.upper() + " (.|\\n)*END_" + l.upper() + " ", '',
                               html_template)

html_template = re.sub('<!-- *-->', '', html_template)

for s in ['INTEGERS_RANGE', 'INTEGERS_RANDOM_FULL', 'TINY_STRINGS',
          'SMALL_STRINGS', 'STRINGS', 'INTEGERS']:
    html_template = re.sub('<!-- REAL_BEGIN_' + s + '(.|\\n)*BEGIN_' + s
                           + ' -->(\\s|\\n)*<!-- END_' + s + " -->", '', html_template)
    html_template = re.sub('<!-- REAL2_BEGIN_' + s + '.*BEGIN2_' + s
                           + ' -->(\\s|\\n)*</ul>(\\s|\\n)*</li>(\\s|\\n)*<!-- END2_' + s + " -->", '',
                           html_template, 0, re.DOTALL)

open('charts.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', charts_data))
