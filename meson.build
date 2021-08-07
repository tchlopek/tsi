project(
    'cpprange',
    'cpp',
    default_options: ['cpp_std=c++17'])

inc = include_directories('include')
cppiter_dep = declare_dependency(include_directories: inc)

if get_option('build_utest')
    subdir('test')
endif
