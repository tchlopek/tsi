src_test = [
    'main.cpp',
    'filter_iterator_test.cpp'
]

ut_bin = executable(
    'ut-range',
    src_test,
    dependencies: ut_deps,
    include_directories: range_incl)

test('range unit tests', ut_bin)