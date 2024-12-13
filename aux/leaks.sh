#!/bin/bash

valgrind --suppressions=.readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes -s -q ./minishell