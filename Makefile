################################################################################
# Makefile
################################################################################

CC 			= clang
LD 			= $(CC)
CFLAGS	= -Wall -pedantic -ansi -std=c99
LDFLAGS	=

project_NAME		= 3d_object_viewer
source_DIR			= src
main_DIR				= $(source_DIR)/main
test_DIR				= $(source_DIR)/tests
core_DIR				= $(main_DIR)/core
model_DIR				= $(main_DIR)/model
util_DIR				= $(main_DIR)/util
view_DIR				= $(main_DIR)/view
build_DIR				= build

## configuration ###############################################################

ifeq ($(shell uname), Darwin)
LDFLAGS += -framework openGL -framework glut
else
LDFLAGS += -lGL -lglut -lGLU
endif

################################################################################

default: init $(build_DIR)/$(project_NAME)

all: init util model view core test

init:
	@mkdir -p $(build_DIR)

$(build_DIR)/$(project_NAME): core util model view cleantest
	$(LD) -o $@ $(build_DIR)/*.o $(LDFLAGS)

core: $(build_DIR)/command_line_tool.o

view:

model: util $(build_DIR)/coordinate.o $(build_DIR)/texture.o \
			 $(build_DIR)/face.o $(build_DIR)/graphical_object.o \
			 $(build_DIR)/obj_file.o

util: $(build_DIR)/vector.o $(build_DIR)/string_iterator.o
	
test: model util \
			test_vector test_string_iterator test_coordinate test_texture	test_face \
			test_obj_file

## core ########################################################################

$(build_DIR)/command_line_tool.o: $(core_DIR)/command_line_tool.c \
										 							$(core_DIR)/command_line_tool.h
	$(CC) -o $@ -c $< $(CFLAGS)

## model #######################################################################

$(build_DIR)/coordinate.o: $(model_DIR)/coordinate.c $(model_DIR)/coordinate.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(build_DIR)/texture.o: $(model_DIR)/texture.c $(model_DIR)/texture.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(build_DIR)/face.o: $(model_DIR)/face.c $(model_DIR)/face.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(build_DIR)/graphical_object.o: $(model_DIR)/graphical_object.c \
																 $(model_DIR)/graphical_object.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(build_DIR)/obj_file.o: $(model_DIR)/obj_file.c $(model_DIR)/obj_file.h
	$(CC) -o $@ -c $< $(CFLAGS)

## util ########################################################################

$(build_DIR)/vector.o: $(util_DIR)/vector.c $(util_DIR)/vector.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(build_DIR)/string_iterator.o: $(util_DIR)/string_iterator.c \
																$(util_DIR)/string_iterator.h
	$(CC) -o $@ -c $< $(CFLAGS)

## test ########################################################################

test_vector: test_vector.o vector.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_vector.o: $(test_DIR)/test_vector.c
	$(CC) -o $@ -c $< $(CFLAGS)

test_string_iterator: $(build_DIR)/test_string_iterator.o \
											$(build_DIR)/string_iterator.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_string_iterator.o: $(test_DIR)/test_string_iterator.c
	$(CC) -o $@ -c $< $(CFLAGS)

test_coordinate: $(build_DIR)/test_coordinate.o \
								 $(build_DIR)/coordinate.o string_iterator.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_coordinate.o: $(test_DIR)/test_coordinate.c
	$(CC) -o $@ -c $< $(CFLAGS)

test_texture: $(build_DIR)/test_texture.o $(build_DIR)/texture.o \
							$(build_DIR)/string_iterator.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_texture.o: $(test_DIR)/test_texture.c
	$(CC) -o $@ -c $< $(CFLAGS)

test_face: $(build_DIR)/test_face.o $(build_DIR)/face.o $(build_DIR)/vector.o \
					 $(build_DIR)/string_iterator.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_face.o: $(test_DIR)/test_face.c
	$(CC) -o $@ -c $< $(CFLAGS)

test_obj_file: $(build_DIR)/test_obj_file.o $(build_DIR)/obj_file.o \
							 $(build_DIR)/graphical_object.o $(build_DIR)/face.o \
							 $(build_DIR)/coordinate.o $(build_DIR)/texture.o \
							 $(build_DIR)/vector.o $(build_DIR)/string_iterator.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(build_DIR)/test_obj_file.o: $(test_DIR)/test_obj_file.c
	$(CC) -o $@ -c $< $(CFLAGS)

################################################################################

.PHONY: clean mrproper

clean:
	rm -rf $(build_DIR)/*.o

cleantest:
	rm -rf $(build_DIR)/test_*

mrproper:
	rm -rf $(build_DIR)

