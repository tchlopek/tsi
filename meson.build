project(
    'cpprange',
    'cpp',
    default_options : [
    'buildtype=debug',
    'cpp_std=c++11'
])

cmake = import('cmake')
gtest = cmake.subproject('googletest')

ut_deps = [
    gtest.dependency('gtest'),
    gtest.dependency('gtest_main'),
    gtest.dependency('gmock'),
    gtest.dependency('gmock_main')
]

range_incl = include_directories('range')

subdir('test')