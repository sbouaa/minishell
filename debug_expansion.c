#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple test for the expand function
// You can compile this separately to test your expand function

// Mock environment structure for testing
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Mock functions (you'll need to implement these or use your actual functions)
char *ft_strdup(const char *s);
char *ft_substr(const char *s, unsigned int start, size_t len);
char *ft_strjoin(const char *s1, const char *s2);
int ft_isalnum(int c);
int ft_isdigit(int c);

// Mock getenv function
char *ft_getenv(char *name, t_env *env) {
    while (env) {
        if (strcmp(env->key, name) == 0) {
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}

// Your expand function (copy from your actual implementation)
char *expand(char *prompt, t_env *env);

// Test function
void test_expansion() {
    // Create test environment
    t_env *env = malloc(sizeof(t_env));
    env->key = ft_strdup("HOME");
    env->value = ft_strdup("/home/user");
    env->next = malloc(sizeof(t_env));
    env->next->key = ft_strdup("USER");
    env->next->value = ft_strdup("testuser");
    env->next->next = NULL;
    
    // Test cases
    char *test_cases[] = {
        "echo $HOME",
        "echo $USER",
        "export a='a b c'",
        "export d='c v b'",
        "export $a=$d",
        "echo $UNDEFINED_VAR",
        NULL
    };
    
    printf("=== EXPANSION DEBUG TESTS ===\n\n");
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test %d: '%s'\n", i + 1, test_cases[i]);
        
        char *expanded = expand(test_cases[i], env);
        if (expanded) {
            printf("Expanded: '%s'\n", expanded);
            free(expanded);
        } else {
            printf("Expanded: NULL\n");
        }
        printf("---\n");
    }
    
    // Cleanup
    while (env) {
        t_env *next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}

int main() {
    test_expansion();
    return 0;
} 