g++ -std=gnu++11 -o main       ../main.cpp       ../includes/table/table.cpp ../includes/binary_files/file_record.cpp ../includes/binary_files/utilities.cpp ../includes/rpn/rpn.cpp ../includes/token/token.cpp ../includes/token/child_tokens.cpp ../includes/shunting_yard/shunting_yard.cpp ../includes/parser/parser.cpp ../includes/tokenizer/stokenize.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/sql/sql.cpp  ../includes/tokenizer/ftokenize.cpp                -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest
g++ -std=gnu++11 -o basic_test ../_tests/_test_files/basic_test.cpp ../includes/table/table.cpp ../includes/binary_files/file_record.cpp ../includes/binary_files/utilities.cpp ../includes/rpn/rpn.cpp ../includes/token/token.cpp ../includes/token/child_tokens.cpp ../includes/shunting_yard/shunting_yard.cpp ../includes/parser/parser.cpp ../includes/tokenizer/stokenize.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/sql/sql.cpp ../includes/tokenizer/ftokenize.cpp -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest
@REM g++ -std=gnu++11 -o testB      ../_tests/_test_files/testB.cpp   ../includes/table/table.cpp ../includes/binary_files/file_record.cpp ../includes/binary_files/utilities.cpp  ../includes/rpn/rpn.cpp ../includes/token/token.cpp ../includes/token/child_tokens.cpp ../includes/shunting_yard/shunting_yard.cpp ../includes/parser/parser.cpp ../includes/tokenizer/stokenize.cpp ../includes/tokenizer/state_machine_functions.cpp ../includes/sql/sql.cpp ../includes/tokenizer/ftokenize.cpp -Igoogletest/googletest/include -pthread -Lgoogletest/build/lib -lgtest



