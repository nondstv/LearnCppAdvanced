cmake_minimum_required(VERSION 3.1)

project(02.cpp)

add_executable(homeTask Home_task.cpp)


if (MSVC)
    target_compile_options(auto PRIVATE
        /W4
    )
    target_compile_options(decltype PRIVATE
        /W4
    )
    target_compile_options(lambda PRIVATE
        /W4
    )
    target_compile_options(tuple PRIVATE
        /W4
    )
else ()
    target_compile_options(auto PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(decltype PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lambda PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(tuple PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()