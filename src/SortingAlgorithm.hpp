#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace SortLibrary 
{

    template<typename T>
    concept Sortable = requires(T& t) 
    {
        {t < t} -> std::convertible_to<bool>;
    };
    
    /// BUBBLESORT
    template<Sortable T>
    void BubbleSort(std::vector<T>& v)
    {
        const unsigned int n = v.size();
    
        for(unsigned int i = 0; i < n - 1; i++)
        {
            for(unsigned int j = i + 1; j < n; j++)
            {
                if(v[j] < v[i])
                {
                    T tmp = v[j];
                    v[j] = v[i];
                    v[i] = tmp;
                }
            }
    
        }
    }
    
    
    /// HEAPSORT
    int heap_size = 0;

    template<Sortable T>
    void enqueue(std::vector<T>& heap, T value) 
    {
        heap.push_back(value);
        heap_size++;
    }

    template<Sortable T>
    T dequeue(std::vector<T>& heap) 
    {
        T root = heap[0];
        heap[0] = heap[heap_size - 1];
        heap.pop_back();
        heap_size--;
        return root;
    }

    template<Sortable T>
    void HeapSort(std::vector<T>& v)
    {
        const unsigned int n = v.size();
        vector<T> heap;
        heap_size = 0;

        // Aggiungo gli elementi di v dentro heap
        for (unsigned int i = 0; i < n; i++) 
        {
            enqueue(heap, v[i]);
        }

        // Riordino per ottenre un max heap
        for (int i = (heap_size / 2) - 1; i >= 0; i--) 
        {
            int current = i;
            while (true) 
            {
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                int largest = current;

                if (left < heap_size && heap[left] > heap[largest])
                    largest = left;
                if (right < heap_size && heap[right] > heap[largest])
                    largest = right;

                if (largest != current) 
                {
                    swap(heap[current], heap[largest]);
                    current = largest;
                } 
                else 
                {
                    break;
                }
            }
        }

        //Estraggo gli elementi per ordinarli
        int index = n - 1;
        while (heap_size > 0)
        {
            v[index] = dequeue(heap);

            int current = 0;
            while (true) 
            {
                int left = 2 * current + 1;
                int right = 2 * current + 2;
                int largest = current;

                if (left < heap_size && heap[left] > heap[largest])
                    largest = left;
                if (right < heap_size && heap[right] > heap[largest])
                    largest = right;

                if (largest != current) 
                {
                    swap(heap[current], heap[largest]);
                    current = largest;
                } 
                else 
                {
                    break;
                }
            }

            index--;
        }
    }

}
