###########################################

NAME        := pipex

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRCS        source files
#
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS        := ft
LIBS_TARGET := libft/libft.a 

INCS        := include    \
    libft/include

SRCS        := pipex.c validation.c parser.c

OBJS        := $(SRCS:%.c=%.o)
#DEPS        := $(OBJS:.o=.d)

CC          := gcc -g3 -fsanitize=address
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS))
#-MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))


#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags

RM          := rm -f
MAKEFLAGS   += --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
    
-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS) pipex.h.gch

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
#.SILENT:
