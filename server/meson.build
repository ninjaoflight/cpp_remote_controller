
remote_controller_server_srcs = [
    'src/source.cpp',
]
remote_controller_server_incl = [include_directories('include')]
remote_controller_server_args = []
remote_controller_server_link = []
remote_controller_server_deps = [cppzmq_dep]


executable(
    'server',remote_controller_server_srcs,
    include_directories: remote_controller_server_incl,
    link_with:remote_controller_server_link,
    cpp_args: remote_controller_server_args,
    dependencies:remote_controller_server_deps
)