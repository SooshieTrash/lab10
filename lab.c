#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trie {
    int isWord; // 0/1
    struct trie* next[26];
};

struct trie* createnode() {
    struct trie* newnode = malloc(sizeof(struct trie));

    for (int i = 0; i < 26; i++) {
        newnode->next[i] = NULL;
    }
    newnode->isWord = 0;
    return newnode;
}

void insert(struct trie** root, char* word) {
    if (*root == NULL) {
        *root = createnode();
    }
    unsigned char* text = (unsigned char*) word;
    struct trie* tmp = *root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (tmp->next[text[i] - 'a'] == NULL) {
            tmp->next[text[i] - 'a'] = createnode();
        }
        tmp = tmp->next[text[i] - 'a'];
    }
    tmp->isWord = 1;
}

int numberOfOccurrences(struct trie* pTrie, char* word) {
    unsigned char* text = (unsigned char*) word;
    struct trie* tmp = pTrie;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (tmp->next[text[i] - 'a'] == NULL) {
            return 0;
        }
        tmp = tmp->next[text[i] - 'a'];
    }
    return tmp->isWord;
}

struct trie* deallocateTrie(struct trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    struct trie* trie = NULL;

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
