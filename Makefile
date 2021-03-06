LIGHT_FLAGS = -g -std=gnu++14 -I Include
HEAVY_FLAGS = -g -std=gnu++14 -I Include -O2 -Wall -Werror -pedantic-errors -Wextra -fsanitize=undefined
OBJECTS = Source/cards.cpp Source/main.cpp 
COVERAGE = -g -std=gnu++14 -I Include --coverage

debug :
	g++ $(LIGHT_FLAGS) $(OBJECTS) -o a.out
full :
	g++ $(HEAVY_FLAGS) $(OBJECTS) -o b.out
run : debug
	./a.out
coverage :
	g++ $(LIGHT_FLAGS) --coverage $(OBJECTS) -o a.out
gcover : test
	gcov main.cpp -b
	mkdir -p Coverage
	mv *.gcda *.gcno *.gcov Coverage
lcoverage : gcover
	lcov/bin/lcov --capture --directory Coverage --rc lcov_branch_coverage=1 --output-file Coverage/coverage.info
	lcov/bin/genhtml Coverage/coverage.info --branch-coverage
	mv *.html Coverage
	mv *.png Coverage
	mv *.css Coverage
	cp -r Source Coverage
	rm -f Source/*.html
	rm -f Source/*.png
	rm -f Source/*.css
	rm -f Source/*.info
	cp -r Include Coverage
	rm -f Include/*.html
	rm -f Include/*.png
	rm -f Include/*.css
	rm -f Include/*.info
	cp -r 5 Coverage
	cp -r home Coverage
	rm -rf 5
	rm -rf home
download : 
	git clone https://github.com/linux-test-project/lcov.git
delete : 
	rm -rf lcov
test: coverage
	./Include/run
clean :
	rm -rf *.out
	rm -rf Coverage	
	rm -rf Results
	rm -rf usr
	rm -rf 1.gcda
	rm -rf 1.gcno
only_process_cov: 
	gcov main.cpp -b
	mkdir -p Coverage
	mv *.gcda *.gcno *.gcov Coverage
	lcov/bin/lcov --capture --directory Coverage --rc lcov_branch_coverage=1 --output-file Coverage/coverage.info
	lcov/bin/genhtml Coverage/coverage.info --branch-coverage
	mv *.html Coverage
	mv *.png Coverage
	mv *.css Coverage
	cp -r Source Coverage
	rm -f Source/*.html
	rm -f Source/*.png
	rm -f Source/*.css
	rm -f Source/*.info
	cp -r Include Coverage
	rm -f Include/*.html
	rm -f Include/*.png
	rm -f Include/*.css
	rm -f Include/*.info
	cp -r 5 Coverage
	cp -r home Coverage
	rm -rf 5
	rm -rf home