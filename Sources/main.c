/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:19:25 by artvan-d          #+#    #+#             */
/*   Updated: 2023/04/12 21:34:46 by artvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *input;
    size_t input_size = 0;
    ssize_t input_length;
    
    while (1) {
        // Display prompt
        printf("$ ");
        
        // Read user input
        input_length = getline(&input, &input_size, stdin);
        
        if (input_length == -1) {
            // End of input reached (e.g. ctrl-D was pressed)
            break;
        }
        
        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';
        
        // TODO: Parse and execute command
    }
    
    // Free memory
    free(input);
    
    return 0;
}
