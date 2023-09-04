include_directories(${nandu_SOURCE_DIR}/sat/public
                    ${nandu_SOURCE_DIR}/sat/private
                    ${CMAKE_CURRENT_BINARY_DIR})


add_custom_command(
    OUTPUT cnf_reader_yacc.cc cnf_reader_def.h
    COMMAND bison -o cnf_reader_yacc.cc --defines=cnf_reader_def.h
                     ${nandu_SOURCE_DIR}/sat/private/cnf_reader.y
    DEPENDS ${nandu_SOURCE_DIR}/sat/private/cnf_reader.y
    COMMENT "Generating cnf_reader_yacc.cc"
)

add_custom_command(
    OUTPUT cnf_reader_lex.cc
    COMMAND flex -o cnf_reader_lex.cc ${nandu_SOURCE_DIR}/sat/private/cnf_reader.l
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/cnf_reader_def.h
    DEPENDS ${nandu_SOURCE_DIR}/sat/private/cnf_reader.l
    COMMENT "Generating cnf_reader_lex.cc"
)

file(GLOB sat_files "${nandu_SOURCE_DIR}/sat/private/*.cc")
add_library(sat_lib ${sat_files}
                    ${CMAKE_CURRENT_BINARY_DIR}/cnf_reader_lex.cc
                    ${CMAKE_CURRENT_BINARY_DIR}/cnf_reader_yacc.cc)
