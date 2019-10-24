#include <iostream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  delete root;
}

void printMovieInventoryHelper(TreeNode *root) {
  if (root != NULL) {
    printMovieInventoryHelper(root->leftChild);
    cout << "Movies starting with letter: " << root->titleChar << endl;
    LLMovieNode *list = root->head;
    while (list != NULL) {
      if (list != NULL) {
        cout << " >> " << list->title << " " << list->rating << endl;
        list = list->next;
      }
    }
    printMovieInventoryHelper(root->rightChild);
  }
}

void MovieTree::printMovieInventory() {
  printMovieInventoryHelper(root);
}

TreeNode* addMovieHelper(TreeNode* root, LLMovieNode* movie) {
  TreeNode *temp = new TreeNode;
  char titleChar = movie->title.at(0);
  temp->titleChar = titleChar;
  temp->head = movie;
  if (root == NULL) {
    root = temp;
    return root;
  }
  // Current movie's titles are higher up in the alphabet
  if (root->titleChar > titleChar) {
    if (root->leftChild == NULL) {
      root->leftChild = temp;
      return root;
    }
    else{
      root->leftChild = addMovieHelper(root->leftChild, movie);
    }
  }
  // Current movie's title are lower in the alphabet
  else if (root->titleChar < titleChar) {
    if (root->rightChild == NULL) {
      root->rightChild = temp;
      return root;
    }
    else {
        root->rightChild = addMovieHelper(root->rightChild, movie);
    }
  }
  // Movie title belongs in the current group of movies
  else {
    LLMovieNode *currentMovie = root->head;
    LLMovieNode *previousMovie = NULL;
    // Now traversing linked list to sort movie
    while (currentMovie != NULL) {
      // Current movie is higher up in the alphabet
      if (currentMovie->title.compare(movie->title) > 0) {
        // Current movie is the head
        if (previousMovie == NULL) {
          movie->next = currentMovie;
          root->head = movie;
        }
        else {
          previousMovie->next = movie;
          movie->next = currentMovie;
        }
        break;
      }
      // Current movie is lower in the alphabet
      else if (currentMovie->title.compare(movie->title) < 0) {
        // Current movie is the tail
        if (currentMovie->next == NULL) {
          currentMovie->next = movie;
          break;
        }
        else {
          previousMovie = currentMovie;
          currentMovie = currentMovie->next;
        }
      }
      else {
        break;
      }
    }
    return root;
  }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating) {
  LLMovieNode *movie = new LLMovieNode(ranking, title, year, rating);
  movie->next = NULL;
  root = addMovieHelper(root, movie);
  delete movie;
}


void MovieTree::deleteMovie(string title) {
  TreeNode *curr = new TreeNode;
  curr = root;
  char titleChar = title.at(0);
  while (true) {
    // Group of titles does not exist in the tree
    if (curr == NULL) {
      cout << "Movie: " << title << " not found, cannot delete." << endl;
      return;
    }
    // Current movie's titles are higher up in the alphabet
    if (curr->titleChar > titleChar) {
      curr = curr->leftChild;
    }
    // Current movie's titles are lower in the alphabet
    else if (curr->titleChar < titleChar) {
      curr = curr->rightChild;
    }
    // Movie title shares a starting letter with the current group of movies
    else {
      break;
    }
  }
  LLMovieNode *currentMovie = new LLMovieNode;
  currentMovie = curr->head;
  LLMovieNode *previousMovie = new LLMovieNode;
  previousMovie = NULL;
  while (true) {
    // If the movie to be deleted was not found
    if (currentMovie == NULL) {
      cout << "Movie: " << title << " not found, cannot delete." << endl;
      return;
    }
    // Found movie to be deleted
    if (currentMovie->title == title) {
      // Check to see if movie being deleted is the head
      if (previousMovie == NULL) {
        curr->head = currentMovie->next;
      }
      else {
        previousMovie->next = currentMovie->next;
      }
      break;
    }
    else {
      previousMovie = currentMovie;
      currentMovie = currentMovie->next;
    }
  }
  // If the group of movies where movie was deleted is now empty
  if (curr->head == NULL) {
    // Current has no children
    if (curr->leftChild == NULL && curr->rightChild == NULL) {
      curr = NULL;
    }
    // Current has only left child
    else if (curr->rightChild == NULL) {
      // If current is the root
      if (curr->parent == NULL) {
        root = curr->leftChild;
        curr->leftChild->parent = NULL;
      }
      else {
        // Current is the left child of parent
        if (curr->parent->titleChar > curr->titleChar) {
          curr->parent->leftChild = curr->leftChild;
          curr->leftChild->parent = curr->parent;
        }
        // Current is the right child of parent
        else if (curr->parent->titleChar < curr->titleChar) {
          curr->parent->rightChild = curr->leftChild;
          curr->leftChild->parent = curr->parent;
        }
      }
    }
    // Current has only right child
    else if (curr->leftChild == NULL) {
      // If current is the root
      if (curr->parent == NULL) {
        root = curr->rightChild;
        curr->rightChild->parent = NULL;
      }
      else {
        // Current is the left child of parent
        if (curr->parent->titleChar > curr->titleChar) {
          curr->parent->leftChild = curr->rightChild;
          curr->rightChild->parent = curr->parent;
        }
        // Current is the right child of parent
        else if (curr->parent->titleChar < curr->titleChar) {
          curr->parent->rightChild = curr->rightChild;
          curr->rightChild->parent = curr->parent;
        }
      }
    }
    // If the current group has a left child and right child
    else {
      TreeNode *temp = new TreeNode;
      TreeNode *tempPrev = new TreeNode;
      temp = curr->rightChild;
      tempPrev = NULL;
      while (true) {
        if (temp->leftChild != NULL) {
          tempPrev = temp;
          temp = temp->leftChild;
        }
        else {
          if (temp->rightChild == NULL) {
            tempPrev->leftChild = NULL;
          }
          else {
            tempPrev->leftChild = temp->rightChild;
            temp->rightChild->parent = tempPrev;
          }
          break;
        }
      }
      temp->leftChild = curr->leftChild;
      temp->rightChild = curr->rightChild;
      // If group of movies deleted was the root
      if (curr->parent == NULL) {
        temp->parent = NULL;
        root = temp;
      }
      else {
        // Current is the right child of their parent
        if (curr->titleChar > curr->parent->titleChar) {
          curr->parent->rightChild = temp;
        }
        // Current is the left child of their parent
        else if (curr->titleChar < curr->parent->titleChar) {
          curr->parent->leftChild = temp;
        }
      }
    }
  }
}
