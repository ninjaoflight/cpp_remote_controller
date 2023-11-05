
remote_controller_client_srcs = [
    'src/source.cpp',
    'src/controller.cpp',
    'src/JoystickHandle.cpp',
]
remote_controller_client_incl = [include_directories('include')]
remote_controller_client_args = []
remote_controller_client_link = []
remote_controller_client_deps = [
    cppzmq_dep,
    sdl2_dep,
]


executable(
    'client',remote_controller_client_srcs,
    include_directories: remote_controller_client_incl,
    link_with:remote_controller_client_link,
    cpp_args: remote_controller_client_args,
    dependencies:remote_controller_client_deps
)