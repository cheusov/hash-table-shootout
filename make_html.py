#!/usr/bin/env python3

import re
import sys

html_template = open('charts-template.html', 'r').read()
charts_data = sys.stdin.read()

repls = (
    ('insert_random_shuffle_range',    'INSERT_RANDOM_SHUFFLE_RANGE'),
    ('reinsert_random_shuffle_range',  'REINSERT_RND_SHUFFLE_RANGE'),

    ('read_random_shuffle_range',      'READ_RANDOM_SHUFFLE_RANGE'),
    ('insert_random_full',             'INSERT_RANDOM_FULL'),
    ('reinsert_random_full',           'REINSERT_RND_FULL'),
    ('insert_random_full_reserve',     'INSERT_RANDOM_F_RESERVE'),
    ('read_random_full',               'READ_RANDOM_FULL'),
    ('read_miss_random_full',          'READ_MISS_RANDOM_FULL'),
    ('delete_random_full',             'DELETE_RANDOM_FULL'),
    ('read_random_full_after_delete',  'READ_RANDOM_F_AFTER_DELETE'),
    ('iteration_random_full',          'ITERATION_RANDOM_FULL'),

    ('insert_small_string',            'INSERT_SMALL_STRING'),
    ('reinsert_small_string',          'REINSERT__SMALL__STRING'),
    ('insert_small_string_reserve',    'RESERVE_SMALL_STRING'),
    ('read_small_string',              'READ_SMALL_STRING'),
    ('read_miss_small_string',         'READ_MISS_SMALL_STRING'),
    ('delete_small_string',            'READ_AFTER_DEL_SMALL_STRING'),
    ('read_small_string_after_delete', 'DELETE_SMALL_STRING'),

    ('insert_string',                  'INSERT_STRING'),
    ('reinsert_string',                'REINSERT__STRING'),
    ('insert_string_reserve',          'RESERVE_STRING'),
    ('read_string',                    'READ_STRING'),
    ('read_miss_string',               'READ_MISS_STRING'),
    ('delete_string',                  'READ_AFTER_DEL_STRING'),
    ('read_string_after_delete',       'DELETE_STRING'),
)

for l in repls:
    if charts_data.find(l[0]) < 0:
        html_template = re.sub('BEGIN_' + l[1] + "(.|\\n)*END_" + l[1], '',
                               html_template)

html_template = re.sub('<!-- *-->', '', html_template)

for s in ['INTEGERS', 'SMALL_STRINGS', 'STRINGS']:
    html_template = re.sub('REAL_BEGIN_' + s + '(.|\\n)*BEGIN_' + s
                           + ' -->(\\s|\\n)*<!-- END_' + s, '', html_template)

open('charts.html', 'w').write(html_template.replace('__CHART_DATA_GOES_HERE__', charts_data))
