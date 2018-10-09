# cpp-string-switch

cpp-string-switch project generates perfect hash function (via gperf) to be
used as string switch with given case values. The project is based in
GNU GPERF, which is used for hash function generation.

## Usage

Default usage reads list of case values (case sensitive) from stdin, one per
each line, and outputs produced code to be used in switch statements.

    cat cases.txt | cpp-switch-gen --func-name foo --namespace bar::baz > generated_code.hpp

See `examples/weekday.cpp` for examle usage.

## License

cpp-string-switch is licensed under GNU General Public License Version 3,
or any later version. See COPYING file.
