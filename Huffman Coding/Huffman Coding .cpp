#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 정의: Huffman Tree 노드
typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// 구조체 정의: 힙
typedef struct Heap {
    Node** nodes;
    int size;
} Heap;

// 함수 선언
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

// 문자별 빈도수 계산 및 stats.txt에 저장
void countFrequencies(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    int frequencies[256] = { 0 };
    char character;

    // 파일 읽기
    while ((character = fgetc(file)) != EOF) {
        frequencies[(int)character]++;
    }

    fclose(file);

    // 결과 저장
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

// Huffman 트리 구성 알고리즘
void buildHuffmanTree() {
    // 힙 초기화
    Heap heap;
    heap.size = 0;
    heap.nodes = malloc(256 * sizeof(Node*));
    if (heap.nodes == NULL) {
        printf("Error allocating memory for heap.\n");
        exit(1);
    }

    // stats.txt 파일 읽기
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

    // Huffman Tree 구성
    while (heap.size > 1) {
        Node* newNode = malloc(sizeof(Node));
        newNode->left = heap.nodes[heap.size - 2];
        newNode->right = heap.nodes[heap.size - 1];
        newNode->frequency = newNode->left->frequency + newNode->right->frequency;
        newNode->character = '\0';

        heap.size--;
        heap.nodes[heap.size - 1] = newNode;

        // 힙 재정렬
        int i = heap.size - 1;
        while (i > 0 && heap.nodes[i]->frequency < heap.nodes[i - 1]->frequency) {
            Node* temp = heap.nodes[i];
            heap.nodes[i] = heap.nodes[i - 1];
            heap.nodes[i - 1] = temp;
            i--;
        }
    }

    // Huffman Tree 루트 노드
    Node* root = heap.nodes[0];
}

// Huffman 압축 함수
void encodeAndCompress(const char* inputFilename, const char* outputFilename) {
    // Huffman 트리 구성

    // input.txt 파일 읽기

    // 문자열을 Huffman 코드로 변환

    // 변환된 Huffman 코드를 비트 단위로 압축하여 파일에 저장
}

// 압축 해제 함수
void decompressAndDecode(const char* inputFilename, const char* outputFilename) {
    // stats.txt 파일 읽기

    // Huffman 트리 재구성

    // input.huf 파일 읽기

    // 비트 단위로 압축 해제하여 Huffman 코드로 변환

    // Huffman 코드를 원래 문자열로 디코딩하여 파일에 저장
}
