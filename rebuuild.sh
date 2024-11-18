rm -rf build
mkdir build
cmake -B ./build
cmake --build ./build

# cd build
# ctest
# ./utest


# cd ..
# ./coverage.sh
# COVERAGE_FILE=coverage.info
# REPORT_FOLDER=coverage_report
# lcov --c lcov_branch_coverage=1 -c -d build -o ${COVERAGE_FILE}_tmp
# lcov --c lcov_branch_coverage=1  -e ${COVERAGE_FILE}_tmp "*src*" -o ${COVERAGE_FILE}
# genhtml --rc genhtml_branch_coverage=1 ${COVERAGE_FILE} -o ${REPORT_FOLDER}
# # rm -rf ${COVERAGE_FILE}_tmp
# # rm -rf ${COVERAGE_FILE}

# if [[ "$OSTYPE" == "darwin"* ]]; then
#     open ./${REPORT_FOLDER}/index.html
# fi