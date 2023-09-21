#ifndef Trie_hpp
#define Trie_hpp

#define MAX_CHARS 26 // For 26 characters right now
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <map>

namespace SKU
{

    struct trieNode
    {
        int character;
        bool isEnd;
        struct trieNode *children[MAX_CHARS];
    };

    class Trie
    {
    private:
        struct trieNode *head;
        // Create an empty struct with default values
        struct trieNode *createNode();
        // Insert a node into head
        void insertWord(std::string input);
        // Converts a sub trie to its corresponding list
        std::vector<std::string> trieToList(struct trieNode *node);
        // Searches trie to get the appropriate node
        struct trieNode *searchTrie(std::string inp);

    public:
        Trie(std::vector<std::string> words);
        std::vector<std::string> search(std::string inp);
    };

    struct trieNode *Trie::createNode()
    {
        struct trieNode *newNode = (struct trieNode *)malloc(sizeof(struct trieNode));
        newNode->character = -1;
        newNode->isEnd = false;
        for (int i = 0; i < MAX_CHARS; i++)
            newNode->children[i] = NULL;

        return newNode;
    }

    void Trie::insertWord(std::string input)
    {
        int n = input.size();
        struct trieNode *curr = head;
        for (int i = 0; i < n; i++)
        {
            int idx = input[i] - 'a'; // To do abstract away index logic to a separate function

            if (curr->children[idx] == NULL)
            {
                struct trieNode *newNode = createNode();
                newNode->character = idx;
                newNode->isEnd = i == n - 1;
                curr->children[idx] = newNode;
            }
            curr = curr->children[idx];
        }
    }

    std::vector<std::string> Trie::trieToList(struct trieNode *node)
    {
        if (head == NULL)
            return {};

        std::vector<std::string> list;
        std::map<trieNode *, bool> visited;
        std::stack<trieNode *> stck;

        std::string path = ""; // path from parent node till now
        stck.push(node);
        // dfs traversal iterative
        while (!stck.empty())
        {
            struct trieNode *top = stck.top();
            // Add the non empty string char when going top to bottom dfs
            if (top->character != -1 && !visited[top])
            {
                path += (char)(97 + top->character); // abstract away to a function
            }
            // Add char to path if non leaf node found to be terminating too
            if (top->isEnd && !visited[top])
            {
                list.push_back(path);
            }
            // set current node as visited
            visited[top] = true;
            // starting from end just for inorder traversal
            for (int i = MAX_CHARS - 1; i >= 0; i--)
            {
                trieNode *child = top->children[i];
                if (child != NULL && !visited[child])
                {
                    stck.push(child);
                }
            }

            // If no children pushed that means leaf node reached, thus pop the top, and reduce path by one
            if (top == stck.top())
            {
                stck.pop();
                path.pop_back();
            }
        }

        return list;
    }

    struct trieNode *Trie::searchTrie(std::string inp)
    {
        trieNode *curr = head;
        for (auto ch : inp)
        {
            int idx = ch - 'a'; // To do abstract away index mapping
            if (curr->children[idx] == NULL)
                return NULL;
            curr = curr->children[idx];
        }

        return curr;
    }

    Trie::Trie(std::vector<std::string> words)
    {
        head = createNode();
        for (auto word : words)
        {
            insertWord(word);
        }
    }

    std::vector<std::string> Trie::search(std::string inp)
    {
        struct trieNode *searchHead = searchTrie(inp);
        std::vector<std::string> list = trieToList(searchHead);
        // remove last char since it is the parent node of the subtrie thus counted twice
        inp.pop_back();
        for (int i = 0; i < list.size(); i++)
        {
            std::string temp = list[i];
            list[i] = inp + temp;
        }
        return list;
    }
}

#endif