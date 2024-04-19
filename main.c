#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    struct Trie *children[26];
    int count;
};

void insertWord(struct Trie **root, char *word) {
    if (*root == NULL) {
        *root = malloc(sizeof(struct Trie));
        memset((*root)->children, 0, sizeof((*root)->children));
        (*root)->count = 0;
    }
    struct Trie *current = *root;
    while (*word) {
        int index = *word - 'a';
        if (!current->children[index]) {
            current->children[index] = malloc(sizeof(struct Trie));
            memset(current->children[index]->children, 0, sizeof(current->children[index]->children));
            current->children[index]->count = 0;
        }
        current = current->children[index];
        word++;
    }
    current->count++;
}

int findWordCount(struct Trie *root, char *word) {
    while (*word) {
        int index = *word - 'a';
        if (!root->children[index]) {
            return 0;
        }
        root = root->children[index];
        word++;
    }
    return root->count;
}

struct Trie *freeTrie(struct Trie *root) {
    if (root) {
        for (int i = 0; i < 26; i++) {
            if (root->children[i]) {
                freeTrie(root->children[i]);
            }
        }
        free(root);
    }
    return NULL;
}

int main(void) {
    int wordCount;
    printf("Enter the number of words: ");
    scanf("%d", &wordCount);

    struct Trie *trie = NULL;
    char word[101];
    for (int i = 0; i < wordCount; i++) {
        scanf("%s", word);
        insertWord(&trie, word);
    }

    char *testWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", testWords[i], findWordCount(trie, testWords[i]));
    }

    trie = freeTrie(trie);
    if (trie) {
        printf("Memory deallocation failed.\n");
    }

    return 0;
}
