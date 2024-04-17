#pragma once
#include <iostream>
#include <vector>
#include "smartphones.h"

using namespace std;

class BinaryTreePhons {
private:
    // ���� ��������� ������
    struct Node {
        Smartphone data;
        Node* left;
        Node* right;

        Node(const Smartphone& s) : data(s), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // ��������������� ����� insertRecursive ��� ����������� �������� ��������� �������� ��������� ��� ����������� ����������, �������� � �.�. 
    Node* insertRecursive(Node* root, const Smartphone& smartphone) {
        if (root == nullptr) {
            return new Node(smartphone);
        }

        // ���������� �� ���������� ����� "������ ��������� ������ + ����"
        double combined_key = smartphone.screen_size + smartphone.price;
        double root_key = root->data.screen_size + root->data.price;

        if (combined_key < root_key) {
            root->left = insertRecursive(root->left, smartphone);
        }
        else if (combined_key > root_key) {
            root->right = insertRecursive(root->right, smartphone);
        }
        else {
            // ��� ���������� ������� � ����� �� ������
            throw invalid_argument("����������� �������� ��� ������� � ������!");
        }

        return root;
    }

    // ����� ��� ������ ���� �� ��������� �������� �����
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

    // ����� ��� �������� ������� �� ��������� �������� �����
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
            // ������ ��������� � ������ , ������� ���
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

            // ���� ����� ��� �������� ����
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.screen_size, temp->data.price);
        }
        return root;
    }

    // ��������������� ����� ��� ������ ������� � ����������� ��������� ������� (�����)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // ��������������� ����� ��� ���������� ������� ������� � ����������
    void inorderTraversal(Node* root, std::vector<Smartphone>& result) {
        if (root != nullptr) {
            inorderTraversal(root->left, result);
            result.push_back(root->data);
            inorderTraversal(root->right, result);
        }
    }

public:
    // ����������� ������
    BinaryTreePhons() : root(nullptr) {}

    // ���������� ������ (������������ ������)
    ~BinaryTreePhons() {
        clear();
    }

    // ����� ��� ���������� ��������
    void addSmartphone(const Smartphone& smartphone) {
        root = insertRecursive(root, smartphone);
    }

    // ����� ��� �������� �������� �� ��������� �������� �����
    void removeSmartphone(double screen_size, double price) {
        root = deleteNode(root, screen_size, price);
    }

    // ����� ��� �������� ������� �������� � �������� ���������� �������� �����
    bool containsSmartphone(double screen_size, double price) {
        return findNode(root, screen_size, price) != nullptr;
    }

    // ����� ��� ��������� �������� ���� �������� � ���� �������
    std::vector<Smartphone> getAllSmartphones() {
        std::vector<Smartphone> result;
        inorderTraversal(root, result);
        return result;
    }

    // ����� ��� ������� ������ (������������ ������)
    void clear() {
        clearRecursive(root);
        root = nullptr;
    }

    // ����� ��� ����������� ������� ������
    void clearRecursive(Node* root) {
        if (root != nullptr) {
            clearRecursive(root->left);
            clearRecursive(root->right);
            delete root;
        }
    }
};


