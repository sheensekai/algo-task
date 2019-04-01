#ifndef ALGOLAB_2_3_AVLTREE_H
#define ALGOLAB_2_3_AVLTREE_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <climits>
#define DELETE 0
#define ADD 1

struct vertex;
struct edge {
    int vert = 0;
    int weight = 0;
};

struct vertex {
    int pos = 0;
    bool inQ = true;
    vertex * par = nullptr;
};

typedef struct item {
    int val = INT_MAX;
    vertex * vert;
    int bal = 0;
    int hei = 1;

    item *par = nullptr;
    item *left = nullptr;
    item *right = nullptr;
} item;
typedef struct avl_tree {
    item *root = nullptr;
    int size = 0;
} avl_tree;
using namespace std;

void item_add(avl_tree *tree, int val, vertex * vptr);

void item_del(avl_tree *tree, int val);

void item_balance(avl_tree *tree, item *par, int mode);

void item_hb_recalc(item *par);

item *item_search(avl_tree *tree, int val);

item *item_ll_rotate(avl_tree *tree, item *par);

item *item_rl_rotate(avl_tree *tree, item *par);

item *item_lb_rotate(avl_tree *tree, item *par);

item *item_rb_rotate(avl_tree *tree, item *par);

void tree_delete(avl_tree *tree);

void tree_item_delete(item *node);

int main() {
    ifstream in("avlset.in");
    ofstream out("avlset.out");
    // read the number of actions we'll do
    int actions = 0;
    in >> actions;
    // make new tree object
    avl_tree *tree = new avl_tree;

    int val = 0;
    char command = 0;
    item *node = nullptr;
    for (int i = 0; i < actions; i++) {
        in >> command;
        in >> val;

        if (command == 'A') { // A is for add
            item_add(tree, val);
            out << tree->root->bal << endl;
        } else if (command == 'D') { // d is for delete
            item_del(tree, val);
            if (tree->root == nullptr)
                out << 0 << endl;
            else out << tree->root->bal << endl;
        } else if (command == 'C') { // c is for check
            node = item_search(tree, val);

            if (node == nullptr || val != node->val)
                out << 'N' << endl;
            else out << 'Y' << endl;

        }

    }
    // close files and delete tree finally
    in.close();
    out.close();
    tree_delete(tree);

    return 0;
}

void item_add(avl_tree *tree, int val, vertex * vptr) {
    // find the parent
    item *par = item_search(tree, val);
    // empty tree case
    if (par == nullptr) {
        tree->size = 1;
        tree->root = new item;
        tree->root->val = val;
        tree->root->vert = vptr;
    } // root only case
    else if (val == par->val)
        return;

    else {// add new
        item *node = new item;
        node->val = val;
        node->par = par;
        node->vert = vptr;
        // set parent
        if (val < par->val)
            par->left = node;
        else par->right = node;

        tree->size++; // F800 size
        item_balance(tree, par, ADD); // balance parent
    }

}

void item_del(avl_tree *tree, int val) {
    // find the item
    item *node = item_search(tree, val);
    // empty tree / root only != val cases
    if (node == nullptr || val != node->val)
        return;
    // leaf node case
    item *par = node->par;
    if (node->left == nullptr && node->right == nullptr) {
        // root case
        if (node->par == nullptr) {
            delete node;
            tree->root = nullptr;
            tree->size = 0;
        }
            // not root case
        else {
            if (node->val < par->val)
                par->left = nullptr;
            else par->right = nullptr;
            delete node;
            tree->size--;
            item_balance(tree, par, DELETE);
        }

    }
        // node->left AND right case
    else if (node->left != nullptr && node->right != nullptr) {
        // r_node is prev for node
        item *r_node = node->left;
        // node = r_node, delete r_node
        while (r_node->right != nullptr)
            r_node = r_node->right;

        int tmp_val = r_node->val;
        item *check = nullptr;
        // r_node->left case
        if (r_node->left != nullptr) {
            r_node->val = r_node->left->val;
            delete r_node->left;
            r_node->left = nullptr;
            check = r_node;
        }
            // leaf case
        else {
            item *r_par = r_node->par;
            if (r_node->val < r_par->val)
                r_par->left = nullptr;
            else r_par->right = nullptr;
            delete r_node;
            check = r_par;
        }

        tree->size--; // F900 tree size
        node->val = tmp_val; // change the node val
        item_balance(tree, check, DELETE); // balance item
    } else { // node->left or right only case
        // left==NULL case
        if (node->left != nullptr) {
            node->val = node->left->val;
            delete node->left;
            node->left = nullptr;
        }
            // left!=NULL case
        else {
            node->val = node->right->val;
            delete node->right;
            node->right = nullptr;
        }

        tree->size--;
        item_balance(tree, node, DELETE);
    }
}

item *item_search(avl_tree *tree, int val) {
    // let node = root
    item *node = tree->root;
    // if root==NULL -> return NULL
    // find the item or it's parent if there's no such
    while (node != nullptr) {
        if (val < node->val && node->left != nullptr)
            node = node->left;
        else if (val > node->val && node->right != nullptr)
            node = node->right;
        else break;
    }

    return node;
}

void item_hb_recalc(item *par) {
    //recalculate height and balance
    // leaf case
    if (par->left == nullptr && par->right == nullptr) {
        par->bal = 0;
        par->hei = 1;
    }
        // par->right only case
    else if (par->left == nullptr) {
        par->bal = par->right->hei;
        par->hei = par->right->hei + 1;
    }
        // par->left only case
    else if (par->right == nullptr) {
        par->bal = -1 * par->left->hei;
        par->hei = par->left->hei + 1;
    }
        // par->left AND right case
    else {
        par->bal = par->right->hei - par->left->hei;
        par->hei = (par->right->hei > par->left->hei ?
                    par->right->hei : par->left->hei) + 1;
    }
}

void item_balance(avl_tree *tree, item *par, int mode) {
    //balance par / the tree
    while (true) {
        // stop when get to the root's par
        if (par == nullptr)
            return;
        // recalc par's h and b
        item_hb_recalc(par);
        // if there was a deletion
        // you can stop at bal == 0 parent
        if (mode == ADD && par->bal == 0)
            return;
        // if there was an addition
        // you can stop at ball == 1\-1 parent
        if (mode == DELETE)
            if (par->bal == -1 || par->bal == 1)
                return;

        // left rot and check next parent
        if (par->bal == 2) {
            if (par->right->bal == -1)
                par = item_lb_rotate(tree, par);
            else par = item_ll_rotate(tree, par);
        }
            // right rot and check next parent
        else if (par->bal == -2) {
            if (par->left->bal == 1)
                par = item_rb_rotate(tree, par);
            else par = item_rl_rotate(tree, par);
        }
            // check next parent
        else par = par->par;
    }
}

item *item_ll_rotate(avl_tree *tree, item *par) {
    item *p_l = par->left;
    item *p_r = par->right;
    item *p_r_left = p_r->left;
    item *p_r_right = p_r->right;
    // change root if need
    if (tree->root == par)
        tree->root = p_r;

    par->right = p_r_left;
    if (p_r_left != nullptr)
        p_r_left->par = par;
    // a's par is p_r's par
    p_r->par = par->par;
    if (p_r->par != nullptr) {
        if (p_r->val < p_r->par->val)
            p_r->par->left = p_r;
        else p_r->par->right = p_r;
    }
    p_r->left = par;
    par->par = p_r;
    // calculate h and p_r for a
    par->hei = (p_r_left != nullptr ? p_r_left->hei : 0) + 1;
    par->bal = par->hei - 1;
    if (p_l != nullptr) {
        if (p_l->hei >= par->hei)
            par->hei = p_l->hei + 1;
        par->bal -= p_l->hei;
    }
// calculate h and p_r for p_r
    p_r->hei = (p_r_right != nullptr ? p_r_right->hei : 0) + 1;
    p_r->bal = p_r->hei - 1;
    if (par->hei >= p_r->hei)
        p_r->hei = par->hei + 1;
    p_r->bal -= par->hei;

    return p_r->par;
}

item *item_rl_rotate(avl_tree *tree, item *par) {
    item *p_l = par->left;
    item *p_r = par->right;
    item *p_l_left = p_l->left;
    item *p_l_right = p_l->right;
    // change root if need
    if (tree->root == par)
        tree->root = p_l;

    par->left = p_l_right;
    if (p_l_right != nullptr)
        p_l_right->par = par;
    // a's parent is p_l's parent
    p_l->par = par->par;
    if (p_l->par != nullptr) {
        if (p_l->val < p_l->par->val)
            p_l->par->left = p_l;
        else p_l->par->right = p_l;
    }
    p_l->right = par;
    par->par = p_l;
    // calculate h and p_l for a
    par->hei = (p_r != nullptr ? p_r->hei : 0) + 1;
    par->bal = par->hei - 1;
    if (p_l_right != nullptr) {
        if (p_l_right->hei >= par->hei)
            par->hei = p_l_right->hei + 1;
        par->bal -= p_l_right->hei;
    }
    // calculate h and p_l for p_l
    p_l->hei = par->hei + 1;
    p_l->bal = p_l->hei - 1;
    if (p_l_left != nullptr) {
        if (p_l_left->hei >= p_l->hei)
            p_l->hei = p_l_left->hei + 1;
        p_l->bal -= p_l_left->hei;
    }

    return p_l->par;
}

item *item_lb_rotate(avl_tree *tree, item *par) {
    item *p_l = par->left;
    item *p_r = par->right;
    item *p_r_left = p_r->left;
    item *p_r_right = p_r->right;
    item *p_r_left_l = p_r_left->left;
    item *p_r_left_r = p_r_left->right;
    // change root if need
    if (tree->root == par)
        tree->root = p_r_left;

    par->right = p_r_left_l;
    if (p_r_left_l != nullptr)
        p_r_left_l->par = par;
    p_r->left = p_r_left_r;
    if (p_r_left_r != nullptr)
        p_r_left_r->par = p_r;
    // a's parent is p_r_left's parent
    p_r_left->par = par->par;
    if (p_r_left->par != nullptr){
        if (p_r_left->val < p_r_left->par->val)
            p_r_left->par->left = p_r_left;
        else p_r_left->par->right = p_r_left;
    }
    p_r_left->left = par;
    par->par = p_r_left;
    p_r_left->right = p_r;
    p_r->par = p_r_left;
    // calculate h and p_r for a
    par->hei = (p_r_left_l != nullptr ? p_r_left_l->hei : 0) + 1;
    par->bal = par->hei - 1;
    if (p_l != nullptr) {
        if (p_l->hei >= par->hei)
            par->hei = p_l->hei + 1;
        par->bal -= p_l->hei;
    }
    // calculate h and p_r for p_r
    p_r->hei = (p_r_right != nullptr ? p_r_right->hei : 0) + 1;
    p_r->bal = p_r->hei - 1;
    if (p_r_left_r != nullptr) {
        if (p_r_left_r->hei >= p_r->hei)
            p_r->hei = p_r_left_r->hei + 1;
        p_r->bal -= p_r_left_r->hei;
    }
    // calculate h and p_r for p_r_left
    p_r_left->hei = (par->hei > p_r->hei ? par->hei : p_r->hei) + 1;
    p_r_left->bal = p_r->hei - par->hei;

    return p_r_left->par;
}

item *item_rb_rotate(avl_tree *tree, item *par) {
    item *p_l = par->left;
    item *p_r = par->right;
    item *p_l_left = p_l->left;
    item *p_l_right = p_l->right;
    item *p_l_right_l = p_l_right->left;
    item *p_l_right_r = p_l_right->right;
    // change root if need
    if (tree->root == par)
        tree->root = p_l_right;

    p_l->right = p_l_right_l;
    if (p_l_right_l != nullptr)
        p_l_right_l->par = p_l;
    par->left = p_l_right_r;
    if (p_l_right_r != nullptr)
        p_l_right_r->par = par;
    // a's parent is p_l_right's parent
    p_l_right->par = par->par;
    if (p_l_right->par != nullptr) {
        if (p_l_right->val < p_l_right->par->val)
            p_l_right->par->left = p_l_right;
        else p_l_right->par->right = p_l_right;
    }

    p_l_right->left = p_l;
    p_l->par = p_l_right;
    p_l_right->right = par;
    par->par = p_l_right;
    // calculate h and p_l for p_l
    p_l->hei = (p_l_right_l != nullptr ? p_l_right_l->hei : 0) + 1;
    p_l->bal = p_l->hei - 1;
    if (p_l_left != nullptr) {
        if (p_l_left->hei >= p_l->hei)
            p_l->hei = p_l_left->hei + 1;
        p_l->bal -= p_l_left->hei;
    }
    // calculate h and p_l for a
    par->hei = (p_r != nullptr ? p_r->hei : 0) + 1;
    par->bal = par->hei - 1;
    if (p_l_right_r != nullptr) {
        if (p_l_right_r->hei >= par->hei)
            par->hei = p_l_right_r->hei + 1;
        par->bal -= p_l_right_r->hei;
    }
    // calculate h and p_l for p_l_right
    p_l_right->hei = (par->hei > p_l->hei ? par->hei : p_l->hei) + 1;
    p_l_right->bal = par->hei - p_l->hei;

    return p_l_right->par;
}

void tree_delete(avl_tree *tree) {
    // delete the tree
    // dele the root if it exists
    if (tree->root != nullptr)
        tree_item_delete(tree->root);

    delete tree;
}

void tree_item_delete(item *node) {
    // delete left, right if they exist
    if (node->left != nullptr)
        tree_item_delete(node->left);
    if (node->right != nullptr)
        tree_item_delete(node->right);

    delete node;
}

#endif //ALGOLAB_2_3_AVLTREE_H
