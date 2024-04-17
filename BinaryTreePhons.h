#pragma once
#include <iostream>
#include <vector>
#include "smartphones.h"

using namespace std;

class BinaryTreePhons {
private:
    // узел двоичного дерева
    struct Node {
        Smartphone data;
        Node* left;
        Node* right;

        Node(const Smartphone& s) : data(s), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // вспомогательный метод insertRecursive для рекурсивных операций сравнения объектов структуры для корректного добавления, удаления и т.п. 
    Node* insertRecursive(Node* root, const Smartphone& smartphone) {
        if (root == nullptr) {
            return new Node(smartphone);
        }

        // сравниваем по комбинации полей "размер диагонали экрана + цена"
        double combined_key = smartphone.screen_size + smartphone.price;
        double root_key = root->data.screen_size + root->data.price;

        if (combined_key < root_key) {
            root->left = insertRecursive(root->left, smartphone);
        }
        else if (combined_key > root_key) {
            root->right = insertRecursive(root->right, smartphone);
        }
        else {
            // уже существует элемент с таким же ключом
            throw invalid_argument("Аналогичный смартфон уже имеется в списке!");
        }

        return root;
    }

    // метод для поиска узла по сочетанию значений полей
    Node* findNode(Node* root, double screen_size, double price) {
        if (root == nullptr || (root->data.screen_size == screen_size && root->data.price == price)) {
            return root;
        }

        double combined_key = screen_size + price;
        double root_key = root->data.screen_size + root->data.price;

        if (combined_key < root_key) {
            return findNode(root->left, screen_size, price);
        }
        else {
            return findNode(root->right, screen_size, price);
        }
    }

    // метод для удаления объекта по сочетанию значений полей
    Node* deleteNode(Node* root, double screen_size, double price) {
        if (root == nullptr) {
            return root;
        }

        double combined_key = screen_size + price;
        double root_key = root->data.screen_size + root->data.price;

        if (combined_key < root_key) {
            root->left = deleteNode(root->left, screen_size, price);
        }
        else if (combined_key > root_key) {
            root->right = deleteNode(root->right, screen_size, price);
        }
        else {
            // объект совпадает с другим , удаляем его
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Узел имеет два дочерних узла
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.screen_size, temp->data.price);
        }
        return root;
    }

    // вспомогательный метод для поиска объекта с минимальным значением индекса (ключа)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // вспомогательный метод для заполнения массива данными о смартфонах
    void inorderTraversal(Node* root, std::vector<Smartphone>& result) {
        if (root != nullptr) {
            inorderTraversal(root->left, result);
            result.push_back(root->data);
            inorderTraversal(root->right, result);
        }
    }

public:
    // конструктор класса
    BinaryTreePhons() : root(nullptr) {}

    // деструктор класса (освобождение памяти)
    ~BinaryTreePhons() {
        clear();
    }

    // метод для добавления элемента
    void addSmartphone(const Smartphone& smartphone) {
        root = insertRecursive(root, smartphone);
    }

    // метод для удаления элемента по сочетанию значений полей
    void removeSmartphone(double screen_size, double price) {
        root = deleteNode(root, screen_size, price);
    }

    // метод для проверки наличия элемента с заданным сочетанием значений полей
    bool containsSmartphone(double screen_size, double price) {
        return findNode(root, screen_size, price) != nullptr;
    }

    // метод для получения описаний всех структур в виде массива
    std::vector<Smartphone> getAllSmartphones() {
        std::vector<Smartphone> result;
        inorderTraversal(root, result);
        return result;
    }

    // метод для очистки дерева (освобождение памяти)
    void clear() {
        clearRecursive(root);
        root = nullptr;
    }

    // метод для рекурсивной очистки дерева
    void clearRecursive(Node* root) {
        if (root != nullptr) {
            clearRecursive(root->left);
            clearRecursive(root->right);
            delete root;
        }
    }
};


