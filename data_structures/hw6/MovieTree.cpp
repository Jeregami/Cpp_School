#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <stack>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  if (root != NULL) {
    root->right = NULL;
    root->left = NULL;
    root = NULL;
  }
}

void MovieTree::printMovieInventory() {
  if (root == NULL) {
    cout << "Tree is Empty. Cannot print" << endl;
    return;
  }
  stack<MovieNode*> stack;
  MovieNode *curr = root;
  while (curr != NULL || stack.empty() == false) {
    while (curr != NULL) {
      stack.push(curr);
      curr = curr->left;
    }
    curr = stack.top();
    stack.pop();
    cout << "Movie: " << curr->title << " " << curr->rating << endl;
    curr = curr->right;
  }
  delete curr;
}

// Assuming movie added does not match the title of an existing movie in the tree
void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  MovieNode *temp = new MovieNode(ranking, title, year, rating);
  MovieNode *curr = root;
  if (root == NULL) {
    root = temp;
    return;
  }
  while (true) {
    // Current movie's title is higher up in the alphabet
    if (curr->title.compare(title) > 0) {
      if (curr->left == NULL) {
        curr->left = temp;
        return;
      }
      else {
        curr = curr->left;
      }
    }
    // Current movie's title is lower down in the alphabet
    else if (curr->title.compare(title) < 0) {
      if (curr->right == NULL) {
        curr->right = temp;
        return;
      }
      else {
        curr = curr->right;
      }
    }
  }
}

void MovieTree::findMovie(string title) {
  MovieNode *curr;
  curr = root;
  while (true) {
    // Movie Found
    if (curr->title.compare(title) == 0) {
      cout << "Movie Info:" << endl;
      cout << "==================" << endl;
      cout << "Ranking:" << curr->ranking << endl;
      cout << "Title :" << curr->title << endl;
      cout << "Year :" << curr->year << endl;
      cout << "rating :" << curr->rating << endl;
      return;
    }
    // Movie is lower in alphabet than current movie
    else if (curr->title.compare(title) > 0) {
      // No more movies lower in alphabet than current movie
      if (curr->left == NULL) {
        cout << "Movie not found." << endl;
        return;
      }
      else {
        curr = curr->left;
      }
    }
    // Movie is higher up in alphabet than current movie
    else if (curr->title.compare(title) < 0) {
      // No more movies higher in alphabet than current movie
      if (curr->right == NULL) {
        cout << "Movie not found." << endl;
        return;
      }
      else {
        curr = curr->right;
      }
    }
  }
}

void MovieTree::queryMovies(float rating, int year) {
  if (root == NULL) {
    cout << "Tree is empty. Cannot query Movies" << endl;
    return;
  }
  stack<MovieNode*> stack;
  MovieNode *curr = root;
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  while (curr != NULL || stack.empty() == false) {
    while (curr != NULL) {
      if (curr->rating >= rating && curr->year > year) {
        cout << curr->title << "(" << curr->year << ") " << curr->rating << endl;
      }
      stack.push(curr);
      curr = curr->left;
    }
    curr = stack.top();
    stack.pop();
    curr = curr->right;
  }
  delete curr;
}

void MovieTree::averageRating() {
  if (root == NULL) {
    cout << "Average rating:0.0" << endl;
    return;
  }
  float average;
  float totalRating = 0;
  float count = 0;
  stack<MovieNode*> stack;
  MovieNode *curr = root;
  while (curr != NULL || stack.empty() == false) {
    while (curr != NULL) {
      stack.push(curr);
      curr = curr->left;
    }
    curr = stack.top();
    stack.pop();
    totalRating += curr->rating;
    count++;
    curr = curr->right;
  }
  average = totalRating / count;
  cout << "Average rating:" << average << endl;
}
