def override_build_output_messages(sys, env):

    colors = {}

    # Colors are disabled in non-TTY environments such as pipes. This means
    # that if output is redirected to a file, it will not contain color codes
    if sys.stdout.isatty():
        colors["cyan"] = "\033[96m"
        colors["purple"] = "\033[95m"
        colors["blue"] = "\033[94m"
        colors["green"] = "\033[92m"
        colors["yellow"] = "\033[93m"
        colors["red"] = "\033[91m"
        colors["end"] = "\033[0m"
    else:
        colors["cyan"] = ""
        colors["purple"] = ""
        colors["blue"] = ""
        colors["green"] = ""
        colors["yellow"] = ""
        colors["red"] = ""
        colors["end"] = ""

    compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    compile_shared_source_message = "{}Compiling shared {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_program_message = "{}Linking Program        {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_library_message = "{}Linking Static Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    ranlib_library_message = "{}Ranlib Library         {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_shared_library_message = "{}Linking Shared Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_library_message = "{}Creating Java Archive  {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )

    env.Append(CXXCOMSTR=[compile_source_message])
    env.Append(CCCOMSTR=[compile_source_message])
    env.Append(SHCCCOMSTR=[compile_shared_source_message])
    env.Append(SHCXXCOMSTR=[compile_shared_source_message])
    env.Append(ARCOMSTR=[link_library_message])
    env.Append(RANLIBCOMSTR=[ranlib_library_message])
    env.Append(SHLINKCOMSTR=[link_shared_library_message])
    env.Append(LINKCOMSTR=[link_program_message])
    env.Append(JARCOMSTR=[java_library_message])
    env.Append(JAVACCOMSTR=[java_compile_source_message])

def get_build_output_messages(sys):
    colors = {}

    # Colors are disabled in non-TTY environments such as pipes. This means
    # that if output is redirected to a file, it will not contain color codes
    if sys.stdout.isatty():
        colors["cyan"] = "\033[96m"
        colors["purple"] = "\033[95m"
        colors["blue"] = "\033[94m"
        colors["green"] = "\033[92m"
        colors["yellow"] = "\033[93m"
        colors["red"] = "\033[91m"
        colors["end"] = "\033[0m"
    else:
        colors["cyan"] = ""
        colors["purple"] = ""
        colors["blue"] = ""
        colors["green"] = ""
        colors["yellow"] = ""
        colors["red"] = ""
        colors["end"] = ""

    compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    compile_shared_source_message = "{}Compiling shared {}==> {}$SOURCE{}".format(
        colors["blue"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_program_message = "{}Linking Program        {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_library_message = "{}Linking Static Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    ranlib_library_message = "{}Ranlib Library         {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    link_shared_library_message = "{}Linking Shared Library {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )
    java_library_message = "{}Creating Java Archive  {}==> {}$TARGET{}".format(
        colors["red"], colors["purple"], colors["yellow"], colors["end"]
    )

    return {
        'CXXCOMSTR': [compile_source_message],
        'SHCCCOMSTR': [compile_shared_source_message],
        'SHCXXCOMSTR': [compile_shared_source_message],
        'ARCOMSTR': [link_library_message],
        'RANLIBCOMSTR': [ranlib_library_message],
        'SHLINKCOMSTR': [link_shared_library_message],
        'LINKCOMSTR': [link_program_message],
        'JARCOMSTR': [java_library_message],
        'JAVACCOMSTR': [java_compile_source_message],
    }