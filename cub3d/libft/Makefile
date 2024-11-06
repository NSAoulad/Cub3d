# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: skoene <skoene@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/10 18:34:04 by skoene        #+#    #+#                  #
#    Updated: 2024/11/06 17:45:08 by aaoulad-      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
HEADER  = libft.h
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_atoll.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstadd_front.c

OBJDIR  = obj/
OBJECTS = $(addprefix $(OBJDIR), $(SOURCES:.c=.o))
TOTAL_SRC := $(words $(SOURCES))

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -fPIC

# Clear default suffixes
.SUFFIXES:

# Set VPATH to include all source directories
VPATH = $(sort $(dir $(SOURCES)))

# Color Codes
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
MAGENTA = \033[1;35m
NC      = \033[0m

# Default target
all: $(NAME)

# Rule to build the library
$(NAME): $(OBJECTS)
	@echo
	@echo "$(YELLOW)Linking library...$(NC)"
	@ar -rcs $@ $(OBJECTS)
	@echo "$(GREEN)Library $(NAME) compiled successfully!$(NC)"

# Pattern rule to compile object files
$(OBJDIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $< -o $@
	@CURRENT_COUNT=`find $(OBJDIR) -type f -name '*.o' 2>/dev/null | wc -l`; \
	printf "\r$(MAGENTA)[%d/$(TOTAL_SRC)] Compiling: %s$(NC)" "$$CURRENT_COUNT" "$(notdir $<)"

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning libft object files...$(NC)"
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)libft object files cleaned.$(NC)"

# Full clean: remove library and object files
fclean: clean
	@echo "$(YELLOW)Removing library $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Library $(NAME) removed.$(NC)"

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
