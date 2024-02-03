cmake = import('cmake')
cmake_opt = cmake.subproject_options()
cmake_opt.add_cmake_defines({'INSTALL_GTEST': false})
gtest = cmake.subproject('googletest', options: cmake_opt)

ut_deps = [
    gtest.dependency('gtest'),
    gtest.dependency('gtest_main'),
    gtest.dependency('gmock'),
    gtest.dependency('gmock_main'),
    cppiter_dep
]

src_test = [
    'main.cpp',
    'bound_generate_range_test.cpp',
    'collect_test.cpp',
    'dereference_range_test.cpp',
    'enumerate_range_test.cpp',
    'filter_range_test.cpp',
    'flatten_range_test.cpp',
    'fold_test.cpp',
    'map_range_test.cpp',
    'replace_range_test.cpp',
    'reverse_range_test.cpp',
    'skip_range_test.cpp',
    'step_range_test.cpp',
    'take_range_test.cpp',
    'unbound_generate_range_test.cpp',
    'unique_range_test.cpp',
    'zipped_range_test.cpp'
]

ut_bin = executable(
    'ut-range',
    src_test,
    dependencies: ut_deps
)

test('range unit tests', ut_bin)