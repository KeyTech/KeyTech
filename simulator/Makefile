include variables.mk

all: .prepare $(BUILD_DIR)/$(RELEASE_EXECUTABLE)

.test: .prepare $(BUILD_DIR)/$(TEST_EXECUTABLE)

.debug: .prepare $(BUILD_DIR)/$(DEBUG_EXECUTABLE)

.ci: .test .test-execution .documentation .coverage-report .checkstyle

.test-execution:
	$(BUILD_DIR)/$(TEST_EXECUTABLE) --gtest_output=xml:$(BUILD_DIR)/test-results.xml

.documentation:
	doxygen $(WORKING_DIR)/doxygen.config

.coverage-report:
	$(GCOVR) -f '$(WORKING_DIR)/$(SRC_DIR)' -x -o $(BUILD_DIR)/coverage.xml -r $(WORKING_DIR)/$(SRC_DIR)

.checkstyle:
	cppcheck --xml --includes-file=include -v --enable=all src/ 2> $(BUILD_DIR)/checkstyle.xml

.clean:
	-rm -R $(BUILD_DIR)

.prepare:
	-mkdir $(BUILD_DIR)
	-mkdir -p $(OBJ_DIR)
	-mkdir -p $(TEST_OBJ_DIR)
	-mkdir -p $(DEBUG_OBJ_DIR)

$(BUILD_DIR)/$(RELEASE_EXECUTABLE): $(OBJ_FILES)
	g++ $(OPTIONS) -o $(BUILD_DIR)/$(RELEASE_EXECUTABLE) $^

$(BUILD_DIR)/$(TEST_EXECUTABLE): $(filter-out $(MAIN_DEBUG_OBJ),$(DEBUG_OBJ_FILES)) $(TEST_OBJ_FILES) $(BUILD_DIR)/gtest.o
	g++ $(TEST_OPTIONS) $(DEBUG_OPTIONS) -o $(BUILD_DIR)/$(TEST_EXECUTABLE) $^

$(BUILD_DIR)/$(DEBUG_EXECUTABLE): $(DEBUG_OBJ_FILES)
	g++ $(DEBUG_OPTIONS) -o $(BUILD_DIR)/$(DEBUG_EXECUTABLE) $^
	
$(BUILD_DIR)/gmock.o: $(GMOCK_CPP_FILES)
	g++ $(TEST_OPTIONS) $(TEST_INCLUDES) -c -o $@ $^

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	g++ $(DEBUG_OPTIONS) $(INCLUDES) -c -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	g++ $(OPTIONS) $(INCLUDES) -c -o $@ $^

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	g++ $(TEST_OPTIONS) $(TEST_INCLUDES) -c -o $@ $^
	
$(BUILD_DIR)/gtest.o: $(GTEST_CPP_FILES)
	g++ $(TEST_OPTIONS) $(TEST_INCLUDES) -c -o $@ $^
