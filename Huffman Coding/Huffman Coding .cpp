#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ü ����: Huffman Tree ���
typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// ����ü ����: ��
typedef struct Heap {
    Node** nodes;
    int size;
} Heap;

// �Լ� ����
void countFrequencies(const char* filename);
void buildHuffmanTree();
void encodeAndCompress(const char* inputFilename, const char* outputFilename);
void decompressAndDecode(const char* inputFilename, const char* outputFilename);

int main() {
    const char* inputFilename = "input.txt";
    const char* statsFilename = "stats.txt";
    const char* huffmanCompressedFilename = "output.huf";
    const char* huffmanDecompressedFilename = "output.txt";

    countFrequencies(inputFilename);
    buildHuffmanTree();
    encodeAndCompress(inputFilename, huffmanCompressedFilename);
    decompressAndDecode(statsFilename, huffmanCompressedFilename, huffmanDecompressedFilename);

    return 0;
}

// ���ں� �󵵼� ��� �� stats.txt�� ����
void countFrequencies(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    int frequencies[256] = { 0 };
    char character;

    // ���� �б�
    while ((character = fgetc(file)) != EOF) {
        frequencies[(int)character]++;
    }

    fclose(file);

    // ��� ����
    FILE* statsFile = fopen("stats.txt", "w");
    if (statsFile == NULL) {
        printf("Error opening file: stats.txt\n");
        exit(1);
    }

    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            fprintf(statsFile, "%c\t%d\n", (char)i, frequencies[i]);
        }
    }

    fclose(statsFile);
}

// Huffman Ʈ�� ���� �˰���
void buildHuffmanTree() {
    // �� �ʱ�ȭ
    Heap heap;
    heap.size = 0;
    heap.nodes = malloc(256 * sizeof(Node*));
    if (heap.nodes == NULL) {
        printf("Error allocating memory for heap.\n");
        exit(1);
    }

    // stats.txt ���� �б�
    FILE* statsFile = fopen("stats.txt", "r");
    if (statsFile == NULL) {
        printf("Error opening file: stats.txt\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), statsFile)) {
        char character;
        int frequency;
        sscanf(line, "%c\t%d", &character, &frequency);

        Node* newNode = malloc(sizeof(Node));
        newNode->character = character;
        newNode->frequency = frequency;
        newNode->left = NULL;
        newNode->right = NULL;

        heap.nodes[heap.size] = newNode;
        heap.size++;
    }

    fclose(statsFile);

    // Huffman Tree ����
    while (heap.size > 1) {
        Node* newNode = malloc(sizeof(Node));
        newNode->left = heap.nodes[heap.size - 2];
        newNode->right = heap.nodes[heap.size - 1];
        newNode->frequency = newNode->left->frequency + newNode->right->frequency;
        newNode->character = '\0';

        heap.size--;
        heap.nodes[heap.size - 1] = newNode;

        // �� ������
        int i = heap.size - 1;
        while (i > 0 && heap.nodes[i]->frequency < heap.nodes[i - 1]->frequency) {
            Node* temp = heap.nodes[i];
            heap.nodes[i] = heap.nodes[i - 1];
            heap.nodes[i - 1] = temp;
            i--;
        }
    }

    // Huffman Tree ��Ʈ ���
    Node* root = heap.nodes[0];
}

// Huffman ���� �Լ�
void encodeAndCompress(const char* inputFilename, const char* outputFilename) {
    // Huffman Ʈ�� ����

    // input.txt ���� �б�

    // ���ڿ��� Huffman �ڵ�� ��ȯ

    // ��ȯ�� Huffman �ڵ带 ��Ʈ ������ �����Ͽ� ���Ͽ� ����
}

// ���� ���� �Լ�
void decompressAndDecode(const char* inputFilename, const char* outputFilename) {
    // stats.txt ���� �б�

    // Huffman Ʈ�� �籸��

    // input.huf ���� �б�

    // ��Ʈ ������ ���� �����Ͽ� Huffman �ڵ�� ��ȯ

    // Huffman �ڵ带 ���� ���ڿ��� ���ڵ��Ͽ� ���Ͽ� ����
}
