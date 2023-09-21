#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <map>
using namespace std;

#define MAX_CHARS 26 //26 letters plus one for empty char

struct trie_node{
    int                 data;
    bool                isEnd;
    struct  trie_node  *children[MAX_CHARS];
};

struct trie_node* create_node(){
    struct trie_node *q= (struct trie_node*)malloc(sizeof(struct trie_node));
    q->data =-1;
    q->isEnd=false;
    for(int i=0;i<MAX_CHARS;i++)
        q->children[i]=NULL;
    return q;
}

void insert_node(struct trie_node *head, string input){
    int n = input.size();
    struct trie_node *curr = head;
    for(int i=0;i<n;i++){
        int idx = input[i]-'a';
        if(curr->children[idx] == NULL){
            auto new_node = create_node();
            new_node->data=idx;
            new_node->isEnd = i==n-1;
            curr->children[idx] = new_node;
        }
        //curr->isEnd = curr->isEnd || i==n-1;
        curr=curr->children[idx];
    }
}


void create_trie(struct trie_node* head,vector<string> &words){
    for(auto word:words){
        insert_node(head,word);
    }
}

//TO DO implement

vector<string> trie_to_list(struct trie_node* head){
    if(head ==NULL)return {};
    vector<string> retVal;
    
    stack<trie_node *> s;
    map<trie_node*,bool> isVisited;
    //for(auto node: head->children)if(node != NULL)s.push(node);
    s.push(head);
    string curr = "";
    while(s.empty() == false){
        struct trie_node* top = s.top();
        if(top->data != -1 && !isVisited[top])curr+=(char )(97 + top->data) ;
        if(top->isEnd && !isVisited[top])retVal.push_back(curr);
        isVisited[top] = true;

        for(int i=MAX_CHARS-1;i>=0;i--){
            if(top->children[i]!=NULL && !isVisited[top->children[i]]){
                s.push(top->children[i]);
            };
        }

        if(top == s.top()){
            s.pop();
            curr.pop_back();
            continue;
        }
    }
    return retVal;

}

struct trie_node * search_trie(trie_node * head,string inp){
    trie_node * curr = head;
    
    for(char ch : inp){
        int idx=ch-'a';
        if(curr->children[idx]==NULL)return NULL;
        curr=curr->children[idx];
    }
    
    return curr;
}

int main(){
    vector<string> list;
    int size;
    cout<<"Enter arr size"<<endl;
    cin>>size;
    for(int i=0;i<size;i++){
        string suff = (i+1)%10==1 ? "st" : (i+1)%10==2 ? "nd" : (i+1)%10 == 3 ? "rd" : "th";
        cout<<"Enter "<<i+1<<suff<<" word"<<endl;
        string s;
        cin>>s;
        list.push_back(s);
    }
    string test;
    cout<<"Enter word to search\n";
    cin>>test;
    struct trie_node *trie = create_node();
    create_trie(trie,list);
    struct trie_node *curr_head = search_trie(trie,test);
    vector<string> lst = trie_to_list(curr_head);
    {
        test.pop_back();
        for(int i=0;i<lst.size();i++){
            string temp = lst[i];
            lst[i] = test+temp;
        }
    }
    cout<<"List of matching words are\n";
    for(auto x: lst)cout<<x<<endl;
    exit(0);

}
