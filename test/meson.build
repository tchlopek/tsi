src_test = [
    'main.cpp',
    'filter_range_test.cpp',
    'reverse_range_test.cpp',
    'map_range_test.cpp'
]

ut_bin = executable(
    'ut-range',
    src_test,
    dependencies: ut_deps,
    include_directories: range_incl)

test('range unit tests', ut_bin)