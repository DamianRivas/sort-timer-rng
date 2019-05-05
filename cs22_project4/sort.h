#pragma once

#include <iostream>
#include <functional>

namespace sort
{
    template <class T>
    void insertion_sort(T list[], int first, int last)
    {
        for (int firstOutOfOrder = first + 1; firstOutOfOrder <= last; ++firstOutOfOrder)
            if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
            {
                T temp = list[firstOutOfOrder];
                int location = firstOutOfOrder;

                do
                {
                    list[location] = list[location - 1];
                    --location;
                } while (location > 0 && list[location - 1] > temp);

                list[location] = temp;
            }
    }

    template <class T>
    void swap(T list[], int first, int second)
    {
        T temp;

        temp = list[first];
        list[first] = list[second];
        list[second] = temp;
    }

    template <class T>
    int partition(T list[], int first, int last, std::function<int(T[], int, int)> pivot_function)
    {
        T pivot;
        int small_index;
        swap(list, first, pivot_function(list, first, last));
        pivot = list[first];
        small_index = first;

        for (int index = first + 1; index <= last; ++index)
            if (list[index] < pivot)
            {
                ++small_index;
                swap(list, small_index, index);
            }

        swap(list, first, small_index);

        return small_index;
    }

    template <class T>
    void rec_quick_sort(T list[], int first, int last, int insertion_ceiling, std::function<int(T[], int, int)> pivot_function)
    {
        int pivot_location;

        if (first < last)
            if (insertion_ceiling > 0 && last - first <= insertion_ceiling)
                insertion_sort(list, first, last);
            else
            {
                pivot_location = partition(list, first, last, pivot_function);
                rec_quick_sort(list, first, pivot_location - 1, insertion_ceiling, pivot_function);
                rec_quick_sort(list, pivot_location + 1, last, insertion_ceiling, pivot_function);
            }
    }

    template <class T>
    void quick_sort(T list[], int length, int insertion_ceiling, std::function<int(T[], int, int)> pivot_function)
    {
        rec_quick_sort(list, 0, length - 1, insertion_ceiling, pivot_function);
    }

    template<class T>
    int middle_pivot(T list[], int first, int last)
    {
        return (first + last) / 2;
    }

    template <class T>
    int median_pivot(T list[], int first, int last)
    {
        int middle = (first + last) / 2;
        T begin = list[first], end = list[last], mid = list[middle];

        if ((begin < mid && mid < end) || (end < mid && mid < begin))
            return middle;
        else if ((mid < begin && begin < end) || (end < begin && begin < mid))
            return first;
        else
            return last;
    }
}
