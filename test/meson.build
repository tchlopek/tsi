src_test = [
    'main.cpp',
    'enumerate_range_test.cpp',
    'filter_range_test.cpp',
    'map_range_test.cpp',
    'replace_range_test.cpp',
    'reverse_range_test.cpp',
    'skip_range_test.cpp',
    'stride_range_test.cpp',
    'take_range_test.cpp',
    'unique_range_test.cpp'
]

ut_bin = executable(
    'ut-range',
    src_test,
    dependencies: ut_deps,
    include_directories: range_incl)

test('range unit tests', ut_bin)