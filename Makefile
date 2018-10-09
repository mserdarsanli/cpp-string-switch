# (C) Copyright 2018 Mustafa Serdar Sanli <mserdarsanli@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = g++ -Wall -Wextra -Wpedantic -std=c++17 -I src/third_party -O3

out/switch_gen: $(wildcard src/*)
	@mkdir -p out
	$(CC) -o $@ src/main.cpp src/search.cpp

out/test: $(wildcard src/* tests/search_test.cpp)
	@mkdir -p out
	$(CC) -o $@ -I src tests/search_test.cpp src/search.cpp

.PHONY: test
test: out/test out/switch_gen out/examples/weekday out/tests/escaping
	@echo "Running catch2 tests in parallel"
	out/test --list-test-names-only | xargs -n 1  -P 10 out/test -r compact
	@echo "Testing weekday example"
	echo "Monday"   | out/examples/weekday | grep -q "Work"
	echo "Saturday" | out/examples/weekday | grep -q "Home"
	echo "qeqwe"    | out/examples/weekday | grep -q "Unknown"

out/examples/weekday.switch.hpp: examples/weekday.strings.txt out/switch_gen
	@mkdir -p out/examples
	out/switch_gen --func-name weekday < $< > $@

out/examples/weekday: examples/weekday.cpp out/examples/weekday.switch.hpp
	$(CC) -o $@ -I out/examples $<

out/tests/escaping.switch.hpp: tests/escaping.strings.txt out/switch_gen
	@mkdir -p out/tests
	out/switch_gen --func-name hash < $< > $@

out/tests/escaping: tests/escaping.cpp out/tests/escaping.switch.hpp
	$(CC) -o $@ -I out/tests $<

.PHONY: benchmark
benchmark: out/switch_gen examples/http_headers.strings.txt examples/http.cpp
	out/switch_gen --namespace match::http_header --func-name weekday < examples/http_headers.strings.txt > out/http_header_switch.hpp
	$(CC) -o out/http -I out -std=c++17 examples/http.cpp
	out/http

.PHONY: clean
clean:
	rm -rf out
